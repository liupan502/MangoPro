#ifndef KEYPOINT_DETECTOR_AND_MATCHER
#define KEYPOINT_DETECTOR_AND_MATCHER
#include "cv.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "BuildMask.h"
#include "highgui.h"
#include <iostream>
using namespace std;
using namespace cv;

#define MAX_MATCH_SIZE 100;
#define MIN_MATCH_SIZE 30;
struct MatchInfo{
	int queryImageIndex;
	int trainImageIndex;
	vector<vector<DMatch>> matches;
};

typedef vector<KeyPoint> KeyPoints;
typedef vector<Mat> Descriptors;

void KeyPointDetect(Mat& image, Mat& mask,KeyPoints& keyPoints,Mat& descriptors);
void KeyPointMatch(vector<Mat>& descriptorsSet,vector<KeyPoints>& keyPointsSet,vector<MatchInfo>& matchInfos,vector<Mat>& images);
void Match(vector<KeyPoints> keyPointsSet,vector<MatchInfo>& matchInfos);
bool CreateMask0(int width,int height,Mat &Mask);
bool CreateMask1(int width,int height,Mat &Mask);
bool CreateMask2(int width,int height,Mat &Mask);
bool CreateMask3(int width,int height,Mat &Mask);
bool CreateMask4(int width,int height,Mat &Mask);
bool GetCarMask(int camidx,int width,int height,bool flag,Mat& mask);

class KeyPointFind
	{
	private :
		pair<int,int> keyPoint;
	public:
		KeyPointFind(pair<int,int>& target) :keyPoint(target){};
		bool operator()(vector<pair<int,int>>& valueSet)
		{
			for(vector<pair<int,int>>::iterator it = valueSet.begin();
				it != valueSet.end();
				it++)
			{
				if(it->first == keyPoint.first&&it->second == keyPoint.second )
					return true;
			}
			return false;
		}
};

#endif