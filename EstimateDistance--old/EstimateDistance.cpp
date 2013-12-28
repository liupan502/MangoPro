//#include "stdafx.h"
//#include "stdafx.h"
#include "EstimateDistance.h"
#include <math.h>
#define STEPNUM 1//1000
#define SQURESTEPNUM 1//1000000
#define GRAVITY 9.8

void EstimateAngleParams(const XsenseInfo* startInfo,const XsenseInfo* endInfo,double* params);

void EstimateAngularVelocityParams(int frequency,double startAngle,double startAngularVelocity,double endAngle,double endAngularVelocity,double params[3]);

void EstimateAccelerationParams(double frequency,double startVelocity,double startAcceleration,double endVelocity,double endAcceleration,double params[3]);

int GetFrequency(int recordFrequency)
{
	if(STEPNUM%recordFrequency == 0)
		return STEPNUM/recordFrequency;
	else
		return STEPNUM/recordFrequency+1;
}



double EstimateDistance(const XsenseInfo* startInfo,const XsenseInfo* endInfo,int recordFrequency)
{
	if(!startInfo || !endInfo )
	{
		return -1.0;
	}
	double frequency = GetFrequency(recordFrequency);
	/*double angularVelocityParams[3][3];
	EstimateAngularVelocityParams(frequency,startInfo->anglex,startInfo->wx,endInfo->anglex,endInfo->wx,angularVelocityParams[0]);
	EstimateAngularVelocityParams(frequency,startInfo->angley,startInfo->wy,endInfo->angley,endInfo->wy,angularVelocityParams[1]);
	EstimateAngularVelocityParams(frequency,startInfo->anglez,startInfo->wz,endInfo->anglez,endInfo->wz,angularVelocityParams[2]);*/
	double accelerationParams[3][3];
	frequency = 0.2;
	EstimateAccelerationParams(frequency,startInfo->vx,startInfo->ax,endInfo->vx,endInfo->ax,accelerationParams[0]);
	EstimateAccelerationParams(frequency,startInfo->vy,startInfo->ay,endInfo->vy,endInfo->ay,accelerationParams[1]);
	EstimateAccelerationParams(frequency,startInfo->vz,startInfo->az - GRAVITY,endInfo->vz,endInfo->az - GRAVITY,accelerationParams[2]);
	
	double dx = accelerationParams[0][0] * pow(frequency,4.0)/12.0+
				accelerationParams[0][1] * pow(frequency,3.0)/6.0+
				accelerationParams[0][2] * pow(frequency,2.0)/2.0+
				frequency*startInfo->vx/STEPNUM;

	double vx = accelerationParams[0][0] * pow(frequency,3.0)/3.0+
				accelerationParams[0][1] * pow(frequency,2.0)/2.0
				;//+
			/*	accelerationParams[0][2] * pow(frequency,1.0)/1.0+
				startInfo->vx/STEPNUM;*/
	double dy = accelerationParams[1][0] * pow(frequency,4.0)/12.0+
				accelerationParams[1][1] * pow(frequency,3.0)/6.0+
				accelerationParams[1][2] * pow(frequency,2.0)/2.0+
				frequency*startInfo->vy/STEPNUM;
	double dz = accelerationParams[2][0] * pow(frequency,4.0)/12.0+
				accelerationParams[2][1] * pow(frequency,3.0)/6.0+
				accelerationParams[2][2] * pow(frequency,2.0)/2.0+
				frequency*startInfo->vz/STEPNUM;
	return sqrt(pow(dx,2.0)+pow(dy,2.0)+pow(dz,2.0));

}


void EstimateAngularVelocityParams(int frequency,double startAngle,double startAngularVelocity,double endAngle,double endAngularVelocity,double params[3])
{
	params[2] = startAngularVelocity/STEPNUM;

	double deltaAngle = endAngle - startAngle;
	double deltaAngularVelocity = (endAngularVelocity - startAngularVelocity)/STEPNUM;
	double m_12 = deltaAngle - frequency*startAngularVelocity; 
	double m_02 = deltaAngularVelocity;
	double m_00 = pow(frequency,2.0);
	double m_01 = frequency ;
	double m_10 = pow(frequency,3.0)/3.0;
	double m_11 = pow(frequency,2.0)/2.0;
	params[0] = (m_02*m_10 - m_12*m_00)/(m_01*m_10 - m_11*m_00);
	params[1] = (m_11*m_02 - m_01*m_12)/(m_01*m_10 - m_11*m_00);
}


void EstimateAccelerationParams(double frequency,double startVelocity,double startAcceleration, double endVelocity,double endAcceleration,double params[3])
{
	params[2] = startAcceleration/SQURESTEPNUM;
	double m_00 = pow(frequency,2.0);
	double m_01 = frequency;
	double m_02 = (endAcceleration - startAcceleration)/SQURESTEPNUM;
	double m_10 = pow(frequency,3.0)/3.0;
	double m_11 = pow(frequency,2.0)/2.0;
	double m_12 = (startVelocity - endVelocity)/STEPNUM - startAcceleration/SQURESTEPNUM*frequency;
	params[1] = (m_02*m_10 - m_12*m_00)/(m_01*m_10 - m_11*m_00);
	params[0] = -(m_11*m_02 - m_01*m_12)/(m_01*m_10 - m_11*m_00);

	double tmp = params[0]*m_10+params[1]*m_11;
}