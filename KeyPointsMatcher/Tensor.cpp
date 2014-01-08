#include "Tensor.h"
#include <set>
#include <iostream>
#include <vector>
#include <iterator>
#include <math.h>
#include <stdlib.h>

bool FirstLess(float f1,float f2)
{
	return f1<f2;
}

void GetIndex(int maxValue,int result[7])
{
	for(int i=0;i<7;i++)
		result[i] = -1;
	 srand((unsigned) time(NULL)); 
	 for(int i=0;i<7;i++)
	 {
		 while(true)
		 {
			 int index = rand()%maxValue;
			 bool bFind = false;
			 for(int j=0;j<i;j++)
			 {
				 if(result[j] == index)
				 {
					 bFind = true;
					 break;
				 }
			 }
			 if(!bFind)
			 {
				 result[i] = index;
				 break;
			 }
		 }
	 }
}

void NormalizePoints(vector<vector<Point2f>>& pointSets,vector<Mat>& mats)
{
	for(int i=0;i<pointSets.size();i++)
	{
		Mat mat(3,3,CV_32FC1,Scalar(0.0));
		Point2f pointCenter(0.0,0.0);
		for(int j=0;j<pointSets[i].size();j++)
		{
			pointCenter += pointSets[i][j];
		}
		pointCenter.x = pointCenter.x/pointSets[i].size();
		pointCenter.y = pointCenter.y/pointSets[i].size();
		float distance = 0;
		for(int j=0;j<pointSets[i].size();j++)
		{
			 pointSets[i][j] = pointSets[i][j] - pointCenter;
			 distance+= sqrt(pow((double)pointSets[i][j].x,2.0)+pow((double)pointSets[i][j].y,2.0));
			//distance += pointSets[i][j].dot(pointSets[i][j]);
		}
		distance = distance/pointSets[i].size();
		float scale = sqrt(2.0)/distance;
		for(int j=0;j<pointSets[i].size();j++)
		{
			pointSets[i][j] *= scale; 
		}
		mat.at<float>(0,0) = scale;
		mat.at<float>(0,2) = -pointCenter.x*scale;
		mat.at<float>(1,1) = scale;
		mat.at<float>(1,2) = -pointCenter.y*scale;
		mat.at<float>(2,2) = 1.0;	
		mats.push_back(mat.inv());
		
	}
}

void UnNormalizePoint(Point2f& pt,Mat& mat)
{
	pt.x = mat.at<float>(0,0) *pt.x+ mat.at<float>(0,2);
	pt.y = mat.at<float>(1,1) *pt.y+ mat.at<float>(1,2);
}

void UnNormalizePoints(vector<vector<Point2f>>& pointSets,vector<Mat>& mats)
{
	for(int i=0;i<pointSets.size();i++)
	{
		for(int j=0;j<pointSets[i].size();j++)
		{
			UnNormalizePoint(pointSets[i][j],mats[i]);
		}
	}
}

void CreateIndex(vector<set<int>> indexSets,int currentIndex,vector<vector<int>>& result)
{
	if(currentIndex >= indexSets.size())
		return;
	set<int> indexSet = indexSets[currentIndex];
	if(indexSet.size() == 0)
		return;
	int setSize = indexSet.size();
	vector<vector<int>> tmp;
	vector<vector<int>> tmpVecSet;	
	for(set<int>::iterator itset = indexSet.begin();itset != indexSet.end();itset++)
	{
		vector<int> tmp1;
		for(vector<vector<int>>::iterator itvec = result.begin();itvec != result.end(); itvec++ )
		{
			//tmp1.clear();
			tmp.clear();
			tmp1 = *itvec;
			tmp1.push_back(*itset);
			tmp.push_back(tmp1);
			//set<int> tmpSet(indexSet.begin(),indexSet.end()) ;			
			//set<int>::iterator pos = find(tmpSet.begin(),tmpSet.end(),*itset);
			//tmpSet.erase(pos);
			CreateIndex(indexSets,currentIndex+1,tmp);
			copy(tmp.begin(), tmp.end(), back_inserter(tmpVecSet));					
		}
	}
	result.clear();
	copy(tmpVecSet.begin(), tmpVecSet.end(), back_inserter(result));		
}

void CreateIndex(int indexSize,vector<vector<int>>&result)
{
	vector<set<int>> indexSets;
	for(int j=0;j<indexSize;j++)
	{
		set<int> indexSet;
		for(int i=0;i<indexSize;i++)
			indexSet.insert(2-i);
		indexSets.push_back(indexSet);
	}
	
	result.resize(1);
	CreateIndex(indexSets,0,result);
}

float GetPointValue(int index,Point2f pt)
{
	if(index == 0)
		return pt.x;
	else if(index == 1)
		return pt.y;
	else 
		return 1.0;
}

int ComputeFlag(int first,int last)
{
	if(first == last)
		return 0;
	int i1 = first,i3 = last,i2;
	for(int index = 0;index < 3;index++)
	{
		if(i1 != index&&i3!= index)
		{
				i2 = index;
				break;
		}
	}
	if(i1 == i2||i2 == i3||i1==i3)
		return 0;
	int count = 0;
	if(i1>i2)
		count++;
	if(i1>i3)
		count++;
	if(i2 > i3)
		count++;
	return count%2 == 0?1:-1;
}

void ComputeParams(int s,int t,Point2f p1,Point2f p2,Point2f p3,vector<vector<int>>& indiceSet,float params[27])
{
	for(int i=0;i<indiceSet.size();i++)
	{
		vector<int> indexSet = indiceSet[i];
		assert(indexSet.size() ==3);
		int flag = ComputeFlag(indexSet[1],s);
	    flag *=  ComputeFlag(indexSet[2],t);
		if(flag == 0)
		{
			params[i] = 0;
			continue;
		}
		float v1 = GetPointValue(indexSet[0],p1);
		float v2 = GetPointValue(indexSet[1],p2);
		float v3 = GetPointValue(indexSet[2],p3);
		params[i] = v1*v2*v3*flag;
	}
}

float ComputResidual(float tensor[27],vector<vector<int>>& indiceSet,Point2f p1,Point2f p2,Point2f p3)
{
	float params[27],	result = 0.0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			float sum = 0;
			ComputeParams(0,0,p1,p2,p3,indiceSet,params);
			for(int k=0;k<27;k++)
			{
				sum+=params[k]*tensor[k];
			}
			result += sum*sum;
		}
		return result;
}

void ComputeTensorRansac(int iteratorNum ,vector<vector<int>>& indiceSet,float tensor[27],vector<vector<Point2f>>& pointSets,vector<Mat>& mats)
{	
	vector<int> outliersSet;
	outliersSet.resize(pointSets[0].size(),0);
	for(int i=0;i<iteratorNum;i++)
	{
		int index[7];
		GetIndex(pointSets[0].size(),index);
		int resultNum = 26;
		//int pointSize = 7;
		Mat leftMat(7*4,resultNum,CV_32FC1),rightMat(7*4,1,CV_32FC1,Scalar(0.0)),result(resultNum,1,CV_32FC1,Scalar(2.0)),result1(resultNum,1,CV_32FC1,Scalar(3.0));
		float params[27];
		for(int j=0;j<7;j++)
		{
			Point2f p1 = pointSets[0][index[j]];
			Point2f p2 = pointSets[1][index[j]];  
			Point2f p3 = pointSets[2][index[j]];
			ComputeParams(0,0,p1,p2,p3,indiceSet,params);
			memcpy((float*)(leftMat.data)+j*4,params,resultNum*sizeof(float));
			rightMat.at<float>(j*4,0) = -params[26];
			ComputeParams(0,1,p1,p2,p3,indiceSet,params);
			memcpy((float*)(leftMat.data)+j*4+1,params,resultNum*sizeof(float));
			rightMat.at<float>(j*4+1,0) = -params[26];
			ComputeParams(1,0,p1,p2,p3,indiceSet,params);
			memcpy((float*)(leftMat.data)+j*4+2,params,resultNum*sizeof(float));
			rightMat.at<float>(j*4+2,0) = -params[26];
			ComputeParams(1,1,p1,p2,p3,indiceSet,params);
			memcpy((float*)(leftMat.data)+j*4+3,params,resultNum*sizeof(float));
			rightMat.at<float>(j*4+3,0) = -params[26];
		}		
		solve(leftMat,rightMat,result1,DECOMP_QR);
		
		vector<float> residualSet;
		float tensor[27];
		for(int i=0;i<26;i++)
		{
			tensor[i] = result1.at<float>(i,0);
		}
		tensor[26] = 1;
		int pointSize = pointSets[0].size();
		for(int i=0;i<pointSize;i++)
		{
			Point2f p1 = pointSets[0][i];
			Point2f p2 = pointSets[1][i];
			Point2f p3 = pointSets[2][i];
			residualSet.push_back(ComputResidual(tensor,indiceSet,p1,p2,p3));
		}
		//sort(residualSet.begin(),residualSet.end(),FirstLess);
		for(int i=0;i<residualSet.size();i++)
		{
			Point2f p1 = pointSets[0][i];
			Point2f p2 = pointSets[1][i];
			Point2f p3 = pointSets[2][i];
			p1.x = mats[0].at<float>(0,0) *p1.x+ mats[0].at<float>(0,2);
			p1.y = mats[0].at<float>(1,1) *p1.y+ mats[0].at<float>(1,2);
			p2.x = mats[1].at<float>(0,0) *p2.x+ mats[1].at<float>(0,2);
			p2.y = mats[1].at<float>(1,1) *p2.y+ mats[1].at<float>(1,2);
			p3.x = mats[2].at<float>(0,0) *p3.x+ mats[2].at<float>(0,2);
			p3.y = mats[2].at<float>(1,1) *p3.y+ mats[2].at<float>(1,2);
			if(residualSet[i] > 100)
			{
				//cout << residualSet[i] << "    " <<p1 <<"  "<< p2 << "  "<< p3<<endl;
				outliersSet[i]++;
			}
		}	
}
	int maxIndex = -1,max = -1;;
	for(int i=0;i<outliersSet.size();i++)
	{
		if(max < outliersSet[i])
		{
			max = outliersSet[i];
		}
		Point2f p1 = pointSets[0][i];
		Point2f p2 = pointSets[1][i];
		Point2f p3 = pointSets[2][i];
		p1.x = mats[0].at<float>(0,0) *p1.x+ mats[0].at<float>(0,2);
		p1.y = mats[0].at<float>(1,1) *p1.y+ mats[0].at<float>(1,2);
		p2.x = mats[1].at<float>(0,0) *p2.x+ mats[1].at<float>(0,2);
		p2.y = mats[1].at<float>(1,1) *p2.y+ mats[1].at<float>(1,2);
		p3.x = mats[2].at<float>(0,0) *p3.x+ mats[2].at<float>(0,2);
		p3.y = mats[2].at<float>(1,1) *p3.y+ mats[2].at<float>(1,2);
		cout <<outliersSet[i] << "    " <<p1 <<"  "<< p2 << "  "<< p3<<endl;
	}

	if(max > iteratorNum/5)
	{
		for(int i=0;i<pointSets.size();i++)
		{
			vector<Point2f> tmpVec;
			for(int j=0;j<pointSets[i].size();j++)
			{
				if(outliersSet[j] != max)
					tmpVec.push_back(pointSets[i][j]);
			}
			pointSets[i] = tmpVec;
		}
	}	
}

bool ComputeTensor(vector<vector<Point2f>>& pointSets,vector<Mat>& tensor,bool bClearPoint)
{
	vector<vector<int>> indiceSet;
	CreateIndex(3,indiceSet);
	// check data
	for(int index = 0;index < pointSets.size() - 1;index++)
	{
		if(pointSets[index].size() != pointSets[index + 1].size())
			return false;		
	}
	
	int pointSetSize = pointSets.size();
	if(pointSetSize < 3)
		return false;
	int pointSize = pointSets[0].size();
	if(pointSize < 7)
		return false;
	vector<Mat> HMatSet;
	NormalizePoints(pointSets,HMatSet);
	float tensorArray[27];
	ComputeTensorRansac(100,indiceSet,tensorArray,pointSets,HMatSet);
	ComputeTensorRansac(50,indiceSet,tensorArray,pointSets,HMatSet);
	ComputeTensorRansac(25,indiceSet,tensorArray,pointSets,HMatSet);
	UnNormalizePoints(pointSets,HMatSet);
	/*int resultNum = 26;
	Mat leftMat(pointSize*4,resultNum,CV_32FC1),rightMat(pointSize*4,1,CV_32FC1,Scalar(0.0)),result(resultNum,1,CV_32FC1,Scalar(2.0)),result1(resultNum,1,CV_32FC1,Scalar(3.0));
	float params[27];
	for(int i=0;i<pointSize;i++)
	{
		Point2f p1 = pointSets[0][i];
		Point2f p2 = pointSets[1][i];
		Point2f p3 = pointSets[2][i];
		ComputeParams(0,0,p1,p2,p3,indiceSet,params);
		memcpy((float*)(leftMat.data)+i*4,params,resultNum*sizeof(float));
		rightMat.at<float>(i*4,0) = -params[26];
		ComputeParams(0,1,p1,p2,p3,indiceSet,params);
		memcpy((float*)(leftMat.data)+i*4+1,params,resultNum*sizeof(float));
		rightMat.at<float>(i*4+1,0) = -params[26];
		ComputeParams(1,0,p1,p2,p3,indiceSet,params);
		memcpy((float*)(leftMat.data)+i*4+2,params,resultNum*sizeof(float));
		rightMat.at<float>(i*4+2,0) = -params[26];
		ComputeParams(1,1,p1,p2,p3,indiceSet,params);
		memcpy((float*)(leftMat.data)+i*4+3,params,resultNum*sizeof(float));
		rightMat.at<float>(i*4+3,0) = -params[26];
	}
	cout << rightMat<< endl;
	bool bright1;
	bright1 = solve(leftMat,rightMat,result,DECOMP_SVD);
	cout << result << endl;
	bright1 = solve(leftMat,rightMat,result1,DECOMP_QR);
	cout << result1 << endl;
	vector<float> residualSet;
	float tensor[27];
	for(int i=0;i<26;i++)
	{
		tensor[i] = result1.at<float>(i,0);
	}
	tensor[26] = 1;
	for(int i=0;i<pointSize;i++)
	{
		Point2f p1 = pointSets[0][i];
		Point2f p2 = pointSets[1][i];
		Point2f p3 = pointSets[2][i];
		residualSet.push_back(ComputResidual(tensor,indiceSet,p1,p2,p3));
	}
	sort(residualSet.begin(),residualSet.end(),FirstLess);
	for(int i=0;i<residualSet.size();i++)
	{
		cout << residualSet[i] << endl;
	}*/
}