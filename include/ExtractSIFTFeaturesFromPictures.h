
#include <iostream>
#include <vector>
#include <cv.h>
#include "nonfree/features2d.hpp"





#ifdef ExtractSiftFeaturesDLL_EXPORTS  
#define ExtractSiftFeaturesDLL_API __declspec(dllimport)   
#else  
#define ExtractSiftFeaturesDLL_API __declspec(dllexport)   
#endif 

//�ӿں�����   ��ȡͼ������SIFT�����㣬��ƥ�������㣬������ƥ���������
//���������   int camidx: �������
//             vector<Mat >& VImage: һ��ͼ������
//             float RatioTh����ֵ���޳���ƥ���Ե���ֵ
//             bool flage: ͼ���г��������Ƿ���Ҫ�޳���

//���������   vector<vector<KeyPoint>> &KeyPointSet�� �洢����ͼ����ÿ��ͼ���SIFT������
//             vector<vector<DMatch>> &MatchesSet: �洢����ͼ������ͼ���SIFT������ƥ���ϵ�����д洢˳��Ϊ��
//             example: ͼ��0��1��2��
//             �洢˳��Ϊ��01��02��12
bool ExtractSiftFeaturesDLL_API ExtractSIFTFeaturesFromPictures(int camidx,std::vector<cv::Mat> &VImage,std::vector<std::vector<cv::KeyPoint>> &KeyPointSet,
	                                                            std::vector<std::vector<cv::DMatch>> &MatchesSet,float RatioTh,bool flag = true);