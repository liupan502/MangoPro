#ifndef COMPUTE_EXTRINSIC_H
#define COMPUTE_EXTRINSIC_H
#ifdef COMPUTEEXTRINSICAPI
#define COMPUTEEXTRINSICAPI  extern "C" __declspec(dllimport) 
#else
#define COMPUTEEXTRINSICAPI extern "C" __declspec(dllexport)
#endif
#include <iostream>
#include <vector>
#include "core/types_c.h"
#include "features2d/features2d.hpp"

typedef struct{
	double R[9];  // 旋转矩阵
	double T[3];  // 平移向量
} Extrinsic;

/************************************************************************/
/* 计算相机的外参数    
*  keyPoints------ 三幅图片的特征点信息
*  matchs--------- 三幅图片的特征点的匹配关系
*  result----------- 外参数计算结果
*  params[0] ----- 相机焦距f
*  params[1],params[2] --相机光心在图片中位置范围（0,1）
*  params[3],params[4] --图像的宽度w和高度h
*/
/************************************************************************/
COMPUTEEXTRINSICAPI bool ComputeExtrinsic(std::vector<std::vector<cv::KeyPoint>> keyPoints,std::vector<std::vector<cv::DMatch>>matchs,double R[][9],double T[][3],double params[5]);
#endif