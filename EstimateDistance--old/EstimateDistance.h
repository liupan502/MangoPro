#ifndef ESITIMATE_DISTANCE
#define ESITIMATE_DISTANCE
typedef struct{
	float vx; // velocity of X axis----m/s
	float vy; // velocity of Y axis----m/s
	float vz; // velocity of Z axis----m/s
	float ax; // acceleration of X axis----m/s2
	float ay; // acceleration of Y axis----m/s2
	float az; // acceleration of Z axis----m/s2
	float anglex; // angle of X axis
	float angley; // angle of Y axis
	float anglez; // angle of Z axis
	float wx; // angular velocity of X axis
	float wy; // angular velocity of Y axis
	float wz; // angular velocity of Z axis
	int frameIndex;
	int gpsStatus;
} XsenseInfo;
#ifndef ESTIMATEAPI
#define ESTIMATEAPI extern "C" __declspec(dllexport)
#else
#define ESTIMATEAPI extern "C" __declspec(dllimport)
#endif

ESTIMATEAPI double EstimateDistance(XsenseInfo* startInfo,XsenseInfo* endInfo,int frequency);

#endif