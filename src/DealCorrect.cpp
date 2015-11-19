#include "DealCorrect.h"

#define GRAY_THRESH 130
#define HOUGH_VOTE 150

Mat DealCorrect::standardizeW(double target_w, Mat &src)
{
	double w = src.size().width;
	double h = src.size().height;
	resize(src, src, Size(target_w, target_w*h/w), 0, 0, INTER_LINEAR );
	return src;
}

Mat DealCorrect::standardizeH(double ratio_h, Mat &src)
{
	double w = src.size().width;
	double h = src.size().height;
	resize(src, src, Size(w*ratio_h/h, ratio_h), 0, 0, INTER_LINEAR );
//	cout<<"w = "<<src.size().width<<" h= "<<src.size().height<<endl;
	return src;
}

Mat DealCorrect::deskew(Mat &src, RotatedRect &re)
{
	cv::Point center = Point(src.cols / 2, src.rows / 2);
	float angle = re.angle;
	Size size = re.size;

	//通过实验估计大概是这个公式，角度过大，则无法判断
	if (angle<-45)
		angle = angle+90;

	//保持原图大小Rotate the image to recover
	Mat rotMat = getRotationMatrix2D(center,angle,1.0);
	Mat dstImg;// = Mat::ones(src.size(), src.type());
	warpAffine(src,dstImg,rotMat,src.size(),1,0,Scalar(255,255,255));
	//保持原图内容

	return dstImg;
}
