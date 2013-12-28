#include "LoadXSenseInfo.h"
#define MIN_VELOCITY 5.0
#define MAX_VELOCITY 15.0

double CalVelocity(XsenseInfo senseInfo)
{
	return sqrt(pow(senseInfo.vx,2)+pow(senseInfo.vy,2)+pow(senseInfo.vz,2));
}

bool LoadXSenseInfo(const char* fileName,std::vector<XsenseInfo>& senseInfos)
{
	FILE* fp = fopen(fileName,"r");
	if(!fp)
		return false;
	char buf[256];
	fgets(buf,256,fp);
	while(fgets(buf,256,fp))
	{
		XsenseInfo senseInfo = CreateXSenseInfo(buf);
		senseInfos.push_back(senseInfo);
	}
	fclose(fp);
	return true;
}

XsenseInfo CreateXSenseInfo(char buf[])
{
	XsenseInfo senseInfo;
	sscanf(buf,"%d %f %f %f %f %f %f %f %f %f %f %f %f %d",&senseInfo.frameIndex,
		&senseInfo.anglex,&senseInfo.angley,&senseInfo.anglez,
		&senseInfo.vx,&senseInfo.vy,&senseInfo.vz,
		&senseInfo.ax,&senseInfo.ay,&senseInfo.az,
		&senseInfo.wx,&senseInfo.wy,&senseInfo.wz,&senseInfo.gpsStatus);	
	return senseInfo;
}

bool SenseInfoSet::GetValidImage(int imageIndex,vector<int>& imageIndices)
{
	if(imageIndex <= 1)
		return false;
	if(imageIndex >= senseInfos.size() - 2)
		return false;
	imageIndices.clear();
	imageIndices.resize(3);
	imageIndices[1] = imageIndex;

	int step = 1;
	double v1 = 0.0,v2 = 0.0;
	v1 = CalVelocity(senseInfos[imageIndex-step]);
	v2 = CalVelocity(senseInfos[imageIndex+step]);
	if(MIN_VELOCITY<v1&&MAX_VELOCITY>v1)
		imageIndices[0] = imageIndex - step;
	else
		return false;
	if(MIN_VELOCITY<v2&&MAX_VELOCITY>v2)
		imageIndices[2] = imageIndex + step;
	else
		return false;
	return true;
}

XsenseInfo SenseInfoSet::operator[](int index)
{
	return senseInfos[index];
}

bool SenseInfoSet::IsAvailable()
{
	return senseInfos.size() == 0? false:true;
}

bool SenseInfoSet::Init(const char* fileName)
{
	return LoadXSenseInfo(fileName,this->senseInfos);
}

SenseInfoSet::SenseInfoSet()
{
	
}


