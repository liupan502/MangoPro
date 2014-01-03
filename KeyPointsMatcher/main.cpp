#include <iostream>
#include "KeyPointDetectAndMatch.h"
using namespace std;

const string imgPathSet[] = {
	"E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\0\\Cam1.jpg",
	"E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\1\\Cam1.jpg",
	"E:\\pgr\\gangjianglu10hz\\result\\0020\\00000200\\2\\Cam1.jpg"
};
const int imgNum = 3;
int main()
{
	vector<Mat> matSet;
	// load images
	for(int i=0;i<imgNum;i++)
	{
		Mat tmp = imread(imgPathSet[i].c_str());
		if(tmp.empty())
			return 0;
		matSet.push_back(tmp);
	}

	vector<KeyPoints> keyPointSet;
	vector<Mat> desriptorsSet;
	// keyPoint detect
	for(vector<Mat>::iterator it = matSet.begin();it != matSet.end(); it++)
	{
		Mat mask(it->rows,it->cols,CV_8UC1);
		if(!GetCarMask(1,it->cols,it->rows,true,mask))
		{			
			return -1;
		}
		KeyPoints tmpKeyPoints;
		Mat tmpDescriptors;
		KeyPointDetect(*it,mask,tmpKeyPoints,tmpDescriptors);
		keyPointSet.push_back(tmpKeyPoints);
		desriptorsSet.push_back(tmpDescriptors);
	}
	vector<MatchInfo> matchInfos;
	KeyPointMatch(desriptorsSet,keyPointSet,matchInfos,matSet);
	char a ;
	cin >> a;
	return 0;
}


