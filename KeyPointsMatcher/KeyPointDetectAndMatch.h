#ifndef KEYPOINT_DETECTOR_AND_MATCHER
#define KEYPOINT_DETECTOR_AND_MATCHER
#include "cv.h"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include "highgui.h"
using namespace std;
using namespace cv;

#define MAX_MATCH_SIZE 100;
#define MIN_MATCH_SIZE 30;
struct MatchInfo{
	int leftImageIndex;
	int rightImageIndex;
	vector<DMatch> matchs;
};

typedef vector<KeyPoint> KeyPoints;

void KeyPointDetect(Mat image,KeyPoints& keyPoints);

void Match(vector<KeyPoints> keyPointsSet,vector<MatchInfo>& matchInfos);

#endif