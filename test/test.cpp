#include "mser.h"
#include "headline.h"

int main(int argc, char * argv[]){
	//Mat img = imread(argv[1], 1); //通过参数传入测试调用
	Mat img = imread("D:\\Users\\Administrator\\Desktop\\测试图片\\09.jpg");
	//Mat img = imread("..//a1.jpg");
	if (!img.data){
		cout << "File not found" << endl;
		return -1;
	}
	Mser fun;
	Mat binaryNumber = fun.detectNumber(img);
	//showWindowImg("binary number",binaryNumber);
	if (!!binaryNumber.data){
		cout << binaryNumber.cols << endl;
		cout << binaryNumber.rows << endl;
	
		cout << "执行成功" << endl;
	}
	else
		cout << "执行失败" << endl;
	waitKey(0);
	return 0;
}