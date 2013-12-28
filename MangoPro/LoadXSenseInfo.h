#ifndef LOAD_XSENSE_INFO_H	
#define LOAD_XSENSE_INFO_H
#include "EstimateDistance.h"
#include <iostream>
#include <vector>
using namespace std;

bool LoadXSenseInfo(const char* fileName,std::vector<XsenseInfo>& xsenseInfos);

XsenseInfo CreateXSenseInfo(char buf[]);

class SenseInfoSet{
public:
	vector<XsenseInfo> senseInfos;		
public:
	bool IsAvailable();
	bool Init(const char* fileName);
	XsenseInfo operator[](int index);
	bool GetValidImage(int imageIndex,vector<int>& imageIndices);
	SenseInfoSet();
    friend bool LoadXSenseInfo(const char* fileName,std::vector<XsenseInfo>& xsenseInfos);
};

#endif
