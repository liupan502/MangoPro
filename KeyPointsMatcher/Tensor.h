#ifndef TENSOR
#define TENSOR
#include <vector>
#include <cv.h>
using namespace std;
using namespace cv;
bool ComputeTensor(vector<vector<Point2f>>& pointSets,vector<Mat>& tensor,bool bClearPoint);
#endif