#include "mser.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char * argv[]){
	//Mat img = imread(argv[1], 1); //linux测试调用
	Mat img = imread("..//3.jpg");
	if (!img.data){
		cout << "File not found" << endl;
		return -1;
	}
	Mser fun;
	Mat binaryNumber = fun.detectNumber(img);
	//showWindowImg("binary number",binaryNumber);
	if (!binaryNumber.data)
		cout << "执行失败" << endl;
	else
		cout << "执行成功" << endl;
	waitKey(0);
	return 0;
}