#include <iostream>
#include "PGRReader.h"


using namespace std;
using namespace cv;

#define _CHECK_ERROR \
	if(error != LADYBUG_OK) \
{ \
	isAvailable = false; \
	return false; \
} \

// 数据初始化

bool PGRReader::Init(const char* pgrFileName)
{
	LadybugError error;
	error = ladybugCreateContext(&context);
	_CHECK_ERROR
    error = ladybugCreateGPSContext(&gpsContext);
	_CHECK_ERROR
	error = ladybugCreateStreamContext(&streamContext);
	_CHECK_ERROR
    error = ladybugInitializeStreamForReading(streamContext,pgrFileName);
	_CHECK_ERROR
  /*  error = ladybugLoadConfig(context,configFileName);
	_CHECK_ERROR*/
    error = ladybugGetStreamHeader(streamContext,&streamHeadInfo);
	_CHECK_ERROR

    // Get configration from stream
	char* pszTempFileName   = NULL;
	if( 
		( ( pszTempFileName = ::_tempnam( "\\", NULL ) ) == NULL ) &&
		( ( pszTempFileName = ::_tempnam( "C:\\temp", NULL ) ) == NULL ) &&
		( ( pszTempFileName = ::_tempnam( "C:\\", NULL ) ) == NULL ) )
	{
		return false;
	}
	else{
		error = ladybugGetStreamConfigFile(streamContext,pszTempFileName);
		_CHECK_ERROR
	    error = ladybugLoadConfig(context,pszTempFileName);
		DeleteFile(pszTempFileName);
		_CHECK_ERROR
        free(pszTempFileName);		
	}

	error = ladybugSetColorTileFormat(context,streamHeadInfo.stippledFormat);
	_CHECK_ERROR

		LadybugColorProcessingMethod colorProcessingMethod = LADYBUG_DOWNSAMPLE4;
	error = ladybugSetColorProcessingMethod(context,colorProcessingMethod);
	_CHECK_ERROR

	error =  ladybugConfigureOutputImages(context,LADYBUG_ALL_RECTIFIED_IMAGES);
	_CHECK_ERROR
		
	return true;
}


bool PGRReader::IsAvailable(void)
{
	return this->isAvailable;
}

bool PGRReader::GetImage(int index,Mat& image,LadybugOutputImage type /* = LADYBUG_ALL_RECTIFIED_IMAGES */)
{
	LadybugError error;
	if(currentBufferIndex != index)
	{
	 error =ladybugGoToImage(streamContext,index);
	if(error != LADYBUG_OK)
		return false;
	LadybugImage ladybugImage;
	error = ladybugReadImageFromStream(streamContext,&ladybugImage);
	if(error != LADYBUG_OK)
		return false;
	
	LadybugPixelFormat pixelFormat = LADYBUG_BGRU;	
	error = ladybugConvertImage(context,&ladybugImage,NULL,pixelFormat);		
	if(error != LADYBUG_OK)
		return false;
	error = ladybugUpdateTextures(context,LADYBUG_NUM_CAMERAS,
		NULL,LADYBUG_BGRU);
	currentBufferIndex = index;
	}
	error = ladybugSetOffScreenImageSize(context,LADYBUG_ALL_RECTIFIED_IMAGES,
		colNum,rowNum);
	error = ladybugSetOffScreenImageSize(context,LADYBUG_PANORAMIC,
		colNum,rowNum);
	LadybugProcessedImage procImage;
	error = ladybugRenderOffScreenImage( context, type, LADYBUG_BGR, &procImage);

	//Mat mat(procImage.uiRows,procImage.uiCols,CV_8UC3);
	image.create(procImage.uiRows,procImage.uiCols,CV_8UC3);
	for(int i=0;i<image.rows;i++)
	{
		int num = sizeof(unsigned char)*3;
		unsigned char* ptr = image.data + i*image.step;
		memcpy(ptr,procImage.pData+i*procImage.uiCols*num,procImage.uiCols*num);
	}	
}


// 设置输出图片的尺寸
void PGRReader::SetSaveImageSize(int rowNum,int colNum)
{
	this->rowNum = rowNum;
	this->colNum = colNum;
}


// 获取输出图片的尺寸
void PGRReader::GetSaveImageSize(int& rowNum, int& colNum)
{
	rowNum = this->rowNum;
	colNum = this->colNum;
}

PGRReader::PGRReader():currentBufferIndex(-1)
{

}
