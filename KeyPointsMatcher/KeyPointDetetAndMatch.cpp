#include "KeyPointDetectAndMatch.h"
#include "Tensor.h"
#include <set>
//const char* imgPath1 = "E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\0\\Cam1.jpg"; 
//const char* imgPath2 = "E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\1\\Cam1.jpg"; 
//const char* imgPath3 = "E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\2\\Cam1.jpg"; 

template <typename T> void Swap(T&item1,T& item2)
{
	T tmp = item1;
	item1 = item2;
	item2 = tmp;
}

bool FirstTrainIndexLess(const vector<DMatch>& it1, const vector<DMatch>&it2)
{
	if(it1.empty())
		return false;
	if(it2.empty())
		return true;
	return it1[0].trainIdx < it2[0].trainIdx;
}

bool FirstRatioLess(const vector<DMatch>&it1,const vector<DMatch>&it2)
{
	if(it1.size() < 2)
		return false;
	if(it2.size() <2)
		return true;
	float ratio1 = it1[0].distance/it1[1].distance;
	ratio1 = ratio1 <1?ratio1:1.0/ratio1;
	float ratio2 = it2[0].distance/it2[1].distance;
	ratio2 = ratio2 <1?ratio2:1.0/ratio2;
	return ratio1 < ratio2;
}

float ComputeRatio(const vector<DMatch>& matches)
{
	if(matches.size() < 2)
		return -1;
	float ratio = matches[0].distance/matches[1].distance;
	return ratio < 1? ratio:1.0/ratio;
}

bool FirstSizeMore( const vector<pair<int,int>>& it1, const vector<pair<int,int>>&it2)
{
	return it1.size() > it2.size();
}

void KeyPointDetect(Mat& image, Mat& mask,KeyPoints& keyPoints,Mat& descriptors)
{
	/*SURF surf(400);	
	surf(image,mask,keyPoints,descriptors);*/
	SIFT sift;
	sift(image,mask,keyPoints,descriptors);
}

void KeyPointMatch(vector<Mat>& descriptorsSet,vector<KeyPoints>& keyPointsSet,
	vector<MatchInfo>& matchInfos,vector<Mat>& images)
{
	vector<MatchInfo> tmpMatchInfos;
	int size = descriptorsSet.size();

	BFMatcher matcher(NORM_L2,false);
	for(int i=0;i<size;i++)
	{		
		for(int j = i+1;j<size;j++)
		{
			MatchInfo tmpMatchInfo;
			tmpMatchInfo.trainImageIndex = i;
			tmpMatchInfo.queryImageIndex = j;
			vector<vector<DMatch>> matches,matches12,matches21;
			vector<vector<DMatch>> tmpMatches;
			matcher.knnMatch(descriptorsSet[j],descriptorsSet[i],matches12,2);
			matcher.knnMatch(descriptorsSet[i],descriptorsSet[j],matches21,2);
			
			int count = 0;
			for( size_t m = 0; m < matches12.size(); m++ )
			{
				bool bMatch = false;
				for(size_t n = 0; n < matches12[m].size(); n++)
				{
					if(bMatch)
						break;
					DMatch match12 = matches12[m][n];
					
					for(size_t l = 0; l < matches21[match12.trainIdx].size();l++)
					{
						int trainIndex12 = match12.trainIdx;
						DMatch match21 = matches21[match12.trainIdx][l];
						if(match21.trainIdx == match12.queryIdx)
						{
							bMatch = true;
							//tmpMatches.push_back(match12);
							if(n != 0 || l != 0)
								int a = 0;
							Swap(matches21[match12.trainIdx][l],matches21[match12.trainIdx][0]);
							Swap(matches12[m][n],matches12[m][0]);
							if(matches12[m].size() > 1&&matches21[trainIndex12].size() > 1)
							{								
								float ratio12 = matches12[m][0].distance/matches12[m][1].distance;
								ratio12 = ratio12 <1?ratio12:1.0/ratio12;
								float ratio21 = matches21[trainIndex12][0].distance/matches21[trainIndex12][1].distance;
								ratio21 = ratio21 <1?ratio21:1.0/ratio21;
								if(ratio12 < 0.6||ratio21 < 0.6)
								{
									if(ratio12 < ratio21)
										tmpMatches.push_back(matches12[m]);
									else
									{
										vector<DMatch> tmpMatchSet;
										for(size_t index = 0;index < matches21[trainIndex12].size();index++)
										{
											DMatch tmpMatch = matches21[trainIndex12][index];
											int tmpInt = tmpMatch.trainIdx;
											tmpMatch.trainIdx = tmpMatch.queryIdx;
											tmpMatch.queryIdx = tmpInt;
											tmpMatchSet.push_back(tmpMatch);
										}
										tmpMatches.push_back(tmpMatchSet);
									}										
								}	
								else
									count++;
							}
						}
					}
					
				}
				
			}
			//cout << count << endl;
			//sort(tmpMatches.begin(),tmpMatches.end(),FirstRatioLess);		
			matches = tmpMatches;
			sort(matches.begin(),matches.end(),FirstTrainIndexLess);
			for(int i=0;i<matches.size() - 1;i++)
			{
				if(matches[i].size() == 0||matches[i+1].size() == 0)
					continue;
				if(matches[i][0].trainIdx == matches[i+1][0].trainIdx)
					matches[i].clear();
			}
			tmpMatchInfo.matches = matches;
			tmpMatchInfos.push_back(tmpMatchInfo);
		}
	}
		vector<vector<pair<int,int>>> relation;
	for(vector<MatchInfo>::iterator it = tmpMatchInfos.begin();
		it != tmpMatchInfos.end();
		it++)
	{
		for(vector<vector<DMatch>>::iterator subIt = it->matches.begin();
			subIt != it->matches.end();
			subIt++)
		{
			if(subIt->size() == 0)
				continue;
			pair<int,int> query(it->queryImageIndex,subIt->at(0).queryIdx);
			pair<int,int> train(it->trainImageIndex,subIt->at(0).trainIdx);
			vector<vector<pair<int,int>>>::iterator result = find_if(relation.begin(),relation.end(),KeyPointFind(train)) ;
			if(result == relation.end())
			{
				result =  find_if(relation.begin(),relation.end(),KeyPointFind(query));
				if(result == relation.end())
				{
					vector<pair<int,int>> tmp;
					tmp.push_back(query);
					tmp.push_back(train);
					relation.push_back(tmp);
				}
				else
				{
					//if(result != find_if(result,result+1,KeyPointFind(train)))
						result->push_back(train);
					//if(result != find_if(result,result+1,KeyPointFind(query)))
						result->push_back(query);
				}
			}			
			else
			{
				//if(result != find_if(result,result+1,KeyPointFind(train)))
					result->push_back(train);
				//if(result != find_if(result,result+1,KeyPointFind(query)))
					result->push_back(query);
			}
			
		}
	}
	sort(relation.begin(),relation.end(),FirstSizeMore);
	vector<vector<pair<int,int>>> strictRelation;
	for(size_t index = 0;index < relation.size();index++)
	{
		vector<pair<int,int>> tmpRelation = relation[index];
		if(tmpRelation.size() < 6)
			break;
		if(tmpRelation.size() != 6)
			continue;
		set<pair<int,int>> valueSet;
		int numTmp = 0;
		for(int i = 0;i<tmpRelation.size();i++)
		{
			if(valueSet.find(tmpRelation[i]) == valueSet.end())
				valueSet.insert(tmpRelation[i]);
			else
				numTmp++;
		}
		if(valueSet.size() == 3&&numTmp == 3)
			strictRelation.push_back(tmpRelation);
	}
	//namedWindow("image1");
	//namedWindow("image2");
	//namedWindow("image3");
	const char* windowName[3] = {
		"image1",
		"image2",
		"image3"
	};

	/*int num =14;*/
	relation = strictRelation;
	vector<Point2f> pointSet1,pointSet2,pointSet3;
	vector<vector<Point2f>> pointSets;
	for(size_t index = 0;index < strictRelation.size();index++)
	{
		pointSet1.push_back(keyPointsSet[strictRelation[index][1].first][strictRelation[index][1].second].pt);
		pointSet2.push_back(keyPointsSet[strictRelation[index][0].first][strictRelation[index][0].second].pt);
		pointSet3.push_back(keyPointsSet[strictRelation[index][3].first][strictRelation[index][3].second].pt);
	}
	pointSets.push_back(pointSet1);
	pointSets.push_back(pointSet2);
	pointSets.push_back(pointSet3);
	Mat f12,f13,f23;
	Mat r12,r13,r23;
	f12 = findFundamentalMat(pointSet1,pointSet2,CV_FM_RANSAC,1.5,0.99,r12);
	cout << r12 << endl;
	f13 =  findFundamentalMat(pointSet1,pointSet3,CV_FM_RANSAC,1.5,0.99,r13);
	cout << r13 << endl;
	f23 =  findFundamentalMat(pointSet2,pointSet3,CV_FM_RANSAC,1.5,0.99,r23);
	cout << r23 << endl;
	vector<Mat> tensors;
	ComputeTensor(pointSets,tensors,false);
	pointSet1 = pointSets[0];
	pointSet2 = pointSets[1];
	pointSet3 = pointSets[2];
	//matchInfos[0];
	for(size_t index= 0;index < r13.rows;index++)
	{
		if(!r12.at<unsigned char>(index,0)||!r13.at<unsigned char>(index,0)||!r23.at<unsigned char>(index,0))
		{
			strictRelation[index].clear();
		}
	}

	

	for(int i=0;i<relation.size();i++)
	{
		/*if(i != 0)
			continue;*/
		/*if(relation[i].size() < 3)
			break;
		if(relation[i].size() != 3)
			continue;
		if(--num)
			continue;*/
		int pointIndex ,imageIndex;
		/*for(int j=0;j<relation[i].size();j++)
		{
			imageIndex =  relation[i][j].first;
			pointIndex = relation[i][j].second;	
			Point2f pt = keyPointsSet[imageIndex][pointIndex].pt;
			circle(images[imageIndex],pt,3,Scalar(255.0,255.0,0));
		}*/
		for(int i=0;i<pointSet1.size();i++)
		{
			circle(images[0],pointSet1[i],3,Scalar(255.0,255.0,0));
			circle(images[1],pointSet2[i],3,Scalar(255.0,255.0,0));
			circle(images[2],pointSet3[i],3,Scalar(255.0,255.0,0));
		}
		//break;
	}

	imshow(windowName[0],images[0]);
	imshow(windowName[1],images[1]);
	imshow(windowName[2],images[2]);
	cv::waitKey(0);
}

bool CreateMask0(int width,int height,Mat &Mask)     //对0镜头创建模板
{
	float s=1.311688;                           //对于图像大小为616*808而言 s=616/808
	float ratio=(float)width/(float)height;
	if (abs(s-ratio)>0.0001)
	{
		return false;
	}
	float scale=(float)width/808.0;           //获取当前图像与标准图像的尺寸比例

	const BuildMask::Coor LeftTop(525*scale,230*scale);
	const BuildMask::Coor RightTop(width,0);
	const BuildMask::Coor RightBottom(width,height);
	const BuildMask::Coor LeftBottom(515*scale,380*scale);

	BuildMask mat(width,height);

	Mask = mat.Building(LeftTop,RightTop,RightBottom,LeftBottom);
	return true;

}

bool CreateMask2(int width,int height,Mat &Mask)     //对2镜头创建模板
{
	float s=1.311688;                           //对于图像大小为616*808而言 s=616/808
	float ratio=(float)width/(float)height;
	if (abs(s-ratio)>0.0001)
	{
		return false;
	}
	float scale=(float)width/808.0;           //获取当前图像与标准图像的尺寸比例

	const BuildMask::Coor LeftTop(615*scale,0);
	const BuildMask::Coor RightTop(width,0);
	const BuildMask::Coor RightBottom(width,height);
	const BuildMask::Coor LeftBottom(520*scale,285*scale);

	BuildMask mat(width,height);

	Mask = mat.Building(LeftTop,RightTop,RightBottom,LeftBottom);
	return true;
}

bool CreateMask1(int width,int height,Mat &Mask)     //对1镜头创建模板
{
	float s=1.311688;
	float ratio=(float)width/(float)height;
	if (abs(s-ratio)>0.0001)
	{
		return false;
	}
	float scale=(float)width/808.0;

	const BuildMask::Coor LeftTop(680*scale,300*scale);
	const BuildMask::Coor RightTop(width,300*scale);
	const BuildMask::Coor RightBottom(width,height);
	const BuildMask::Coor LeftBottom(545*scale,height);

	BuildMask mat(width,height);

	Mask = mat.Building(LeftTop,RightTop,RightBottom,LeftBottom);
	return true;
}

bool CreateMask4(int width,int height,Mat &Mask)     //对4镜头创建模板
{
	float s=1.311688;                           //对于图像大小为616*808而言 s=616/808
	float ratio=(float)width/(float)height;
	if (abs(s-ratio)>0.0001)
	{
		return false;
	}
	float scale=(float)width/808.0;


	const BuildMask::Coor LeftTop(535*scale,0);
	const BuildMask::Coor RightTop(width,0);
	const BuildMask::Coor RightBottom(width,340*scale);
	const BuildMask::Coor LeftBottom(675*scale,340*scale);

	BuildMask mat(width,height);

	Mask = mat.Building(LeftTop,RightTop,RightBottom,LeftBottom);

	imwrite("E:\\masklllllll.bmp",Mask);
	return true;
}

bool CreateMask3(int width,int height,Mat &Mask)     //对3镜头创建模板
{
	float s=1.311688;                            //对于标准图像大小为616*808而言 s=808/616
	float ratio=(float)width/(float)height;
	if (abs(s-ratio)>0.0001)
	{
		return false;
	}
	float scale=(float)width/808.0;          //获取当前图像与标准图像的尺寸比例

	const BuildMask::Coor LeftTop(520*scale,365*scale);
	const BuildMask::Coor RightTop(width,0);
	const BuildMask::Coor RightBottom(width,height);
	const BuildMask::Coor LeftBottom(615*scale,height);

	BuildMask mat(width,height);

	Mask = mat.Building(LeftTop,RightTop,RightBottom,LeftBottom);
	return true;
}

bool GetCarMask(int camidx,int width,int height,bool flag,Mat& mask)
{
	bool result=false;
	if (flag)
	{
		switch(camidx)
		{
		case 0:
			result=CreateMask0(width,height,mask);
			break;
		case 1:
			result=CreateMask1(width,height,mask);
			break;
		case 2:
			result=CreateMask2(width,height,mask);
			break;
		case 3:
			result=CreateMask3(width,height,mask);
			break;
		case 4:
			result=CreateMask4(width,height,mask);
			break;
		} 
	}
	return result;
}
