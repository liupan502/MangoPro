#ifndef PGR_READER
#define PGR_READER
#include "windows.h"
#include "ladybug.h"
#include "ladybuggeom.h"
#include "ladybugGPS.h"
#include "ladybugrenderer.h"
#include "ladybugstream.h"
#include "ladybugvideo.h"
#include "cv.h"
#include "highGUI.h"
using namespace cv;
using namespace std;
//#include "e:\vs 2010 workspace\mangopro\include\ladybugstream.h"

class PGRReader{

public:
	// 数据初始化
	bool Init(const char* pgrFileName);
	PGRReader();
private:
	LadybugGPSContext gpsContext;
	LadybugContext context;
	LadybugStreamContext streamContext;
	LadybugStreamHeadInfo streamHeadInfo;
	bool isAvailable;
public:
	bool IsAvailable(void);
	bool GetImage(int index,Mat& image,LadybugOutputImage type = LADYBUG_PANORAMIC);

private:
	// 输出图片的行数
	int rowNum;
	// 输出图片的列数
	int colNum;
public:
	// 设置输出图片的尺寸
	void SetSaveImageSize(int rowNum,int colNum);
	// 获取输出图片的尺寸
	void GetSaveImageSize(int& rowNum, int& colNum);
private:
	// 当前显存中存放的纹理的索引
	int currentBufferIndex;
};
#endif