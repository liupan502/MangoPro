#ifndef _BUILD_MASK_H_
#define _BUILD_MASK_H_

#include <utility>

#pragma warning (disable:4996)
#pragma warning (push)
#include "opencv/cv.h"
#pragma warning (pop)

class BuildMask
{
public:
	typedef std::pair<int,int> Coor;

public:
	BuildMask(int width,int height)
		:mat(height,width,CV_8UC1)
	{
	}

public:
	const cv::Mat & Building(const Coor & lt,const Coor & rt,const Coor & rb, const Coor & lb)
	{
		ReSetMask();

		int row = mat.rows;
		int col = mat.cols;

		Coor lefttop(lt);
		Coor righttop(rt);
		Coor rightbottom(rb);
		Coor leftbottom(lb);

		lefttop.first = lefttop.first == righttop.first ? lefttop.first - 1 : lefttop.first;
		lefttop.second = lefttop.second == leftbottom.second ? lefttop.second - 1 : lefttop.second;
		rightbottom.first = rightbottom.first == leftbottom.first ? rightbottom.first + 1 : rightbottom.first;
		rightbottom.second = rightbottom.second == righttop.second ? rightbottom.second + 1 : rightbottom.second;

		for(int i = 0; i != row; ++i)
		{
			for(int j = 0; j != col; ++j)
			{
				Coor test(j,i);
				if(test.first > ((test.second - lefttop.second) * (leftbottom.first - lefttop.first) / 
					(leftbottom.second - lefttop.second) + lefttop.first)
					&& test.second > ((test.first - lefttop.first) * (righttop.second - lefttop.second) /
					(righttop.first - lefttop.first) + lefttop.second)
					&& test.first < ((test.second - rightbottom.second) * (rightbottom.first - righttop.first) / 
					(rightbottom.second - righttop.second) + rightbottom.first)
					&& test.second < ((test.first - rightbottom.first) * (rightbottom.second - leftbottom.second) /
					(rightbottom.first - leftbottom.first) + rightbottom.second))
					mat.ptr<unsigned char>(i)[j] = static_cast<unsigned char>(0);
			}
		}

		return mat;
	}

private:
	static const int LEFT = 110;
	static const int TOP = 110;
	static const int RIGHT = 700;
	static const int BOTTOM = 500;

private:
	cv::Mat mat;

private:
	void ReSetMask()
	{
		for(int i = 0,i_end = mat.rows; i != i_end; ++i)
			for(int j = 0,j_end = mat.cols; j != j_end; ++j)
				if (LEFT < j && j < RIGHT && TOP < i && i < BOTTOM)
					mat.ptr<unsigned char>(i)[j] = static_cast<unsigned char>(1);
				else
					mat.ptr<unsigned char>(i)[j] = static_cast<unsigned char>(0);
	}

};

#endif
