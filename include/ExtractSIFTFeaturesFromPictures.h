
#include <iostream>
#include <vector>
#include <cv.h>
#include "nonfree/features2d.hpp"





#ifdef ExtractSiftFeaturesDLL_EXPORTS  
#define ExtractSiftFeaturesDLL_API __declspec(dllimport)   
#else  
#define ExtractSiftFeaturesDLL_API __declspec(dllexport)   
#endif 

//接口函数：   提取图像组中SIFT特征点，并匹配特征点，最后输出匹配特征点对
//输入参数：   int camidx: 相机索引
//             vector<Mat >& VImage: 一组图像数据
//             float RatioTh：比值法剔除误匹配点对的阈值
//             bool flage: 图像中车子区域是否需要剔除掉

//输出参数：   vector<vector<KeyPoint>> &KeyPointSet： 存储所有图像中每个图像的SIFT特征点
//             vector<vector<DMatch>> &MatchesSet: 存储所有图像中两图像间SIFT特征点匹配关系，其中存储顺序为：
//             example: 图像（0，1，2）
//             存储顺序为：01，02，12
bool ExtractSiftFeaturesDLL_API ExtractSIFTFeaturesFromPictures(int camidx,std::vector<cv::Mat> &VImage,std::vector<std::vector<cv::KeyPoint>> &KeyPointSet,
	                                                            std::vector<std::vector<cv::DMatch>> &MatchesSet,float RatioTh,bool flag = true);