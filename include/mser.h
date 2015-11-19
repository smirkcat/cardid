#ifndef _MSER_H_
#define _MSER_H_


#include "headline.h"


class Mser{
public:
	//截取图块
	Mat detectNumber(Mat &src);
	//返回一幅图中安全的安全矩形
	void secureRect(Rect &r, const Mat &src);
	void showWindowImg(string name, Mat &img);
	Mat AutoBinary(Mat &src);
	Mat Filter(Mat &src);
	
	//byte[] char* to Mat
	Mat charrArrayToMat(char *buff, int size);
	//char* matToCharArray(Mat &src);
};

#endif