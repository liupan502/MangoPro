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
	// ���ݳ�ʼ��
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
	// ���ͼƬ������
	int rowNum;
	// ���ͼƬ������
	int colNum;
public:
	// �������ͼƬ�ĳߴ�
	void SetSaveImageSize(int rowNum,int colNum);
	// ��ȡ���ͼƬ�ĳߴ�
	void GetSaveImageSize(int& rowNum, int& colNum);
private:
	// ��ǰ�Դ��д�ŵ����������
	int currentBufferIndex;
};
#endif