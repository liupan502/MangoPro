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
	double R[9];  // ��ת����
	double T[3];  // ƽ������
} Extrinsic;

/************************************************************************/
/* ��������������    
*  keyPoints------ ����ͼƬ����������Ϣ
*  matchs--------- ����ͼƬ���������ƥ���ϵ
*  result----------- �����������
*  params[0] ----- �������f
*  params[1],params[2] --���������ͼƬ��λ�÷�Χ��0,1��
*  params[3],params[4] --ͼ��Ŀ��w�͸߶�h
*/
/************************************************************************/
COMPUTEEXTRINSICAPI bool ComputeExtrinsic(std::vector<std::vector<cv::KeyPoint>> keyPoints,std::vector<std::vector<cv::DMatch>>matchs,double R[][9],double T[][3],double params[5]);
#endif