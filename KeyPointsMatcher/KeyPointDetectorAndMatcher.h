#ifndef KEYPOINT_DETECTOR_AND_MATCHER
#define KEYPOINT_DETECTOR_AND_MATCHER
#include "cv.h"
#include "highgui.h"
using namespace std;
using namespace cv;

#define MAX_MATCH_SIZE 100;
#define MIN_MATCH_SIZE 30;
struct MatchInfo{
	int leftImageIndex;
	int rightImageIndex;
	vector<DMatch> matchs
};

typedef vector<KeyPoint> KeyPoints;

void KeyPointDetector(Mat image,KeyPoints& keyPoints);

void Match(vector<KeyPoints> keyPointsSet,vector<MatchInfo>& matchInfos);

#endif