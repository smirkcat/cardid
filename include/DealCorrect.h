#ifndef _DEALCOTTRECT_
#define _DEALCOTTRECT_
#include "headline.h"

class DealCorrect{
public:
	Mat standardizeW(double, Mat &);
	Mat standardizeH(double, Mat &);
	Mat deskew(Mat &, RotatedRect &);
};
#endif