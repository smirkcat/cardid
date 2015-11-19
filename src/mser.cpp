#include "headline.h"
#include "GetCandidate.h"
#include "LinkCandidate.h"
#include "DealCorrect.h"
#include "Candidate.h"
#include "mser.h"
#include <vector>
#include <cmath>
#include <string>  
#include <sstream>


cv::Mat Mser::detectNumber(Mat &src){
	Mat image_roi;
	//step1: preprocessing - resize + correct
	DealCorrect dealCorrect;
	src = dealCorrect.standardizeW(1200.0, src);
   //showWindowImg("src", src);
	//step2: get candidate
	//time_t beg = time(0);
	//long time = clock();//获得开始时间，这种方式多线程不合适
	
	//return candidateStore
	vector<Candidate> candidateStore;
	GetCandidate getCandidate;
	candidateStore = getCandidate.run(src); 
	//time_t end = time(0);
	//time = clock()-time; 
	//cout << "GetCandidate候选区选择消耗时间:" << float(time) * 1000 / CLOCKS_PER_SEC <<"毫秒"<< endl;
	if( candidateStore.size() > 0 ) {

		////show the candidateStore
		//Mat test0 = src.clone();
		//for(int i = 0; i < candidateStore.size(); i++){
		//	Candidate c = candidateStore[i];
		//	Point tl = Point(c.min_j, c.min_i);
		//	Point br = Point(c.max_j, c.max_i);
		//	//rectangle(test0, tl, br, CV_RGB(0, 0, 255), 3, 8, 0);
		//}
		//showWindowImg("GetCandidate", test0);
		//step3: link candidates
		//time = clock();
		LinkCandidate linkCandidate(candidateStore);
		vector<RotatedRect> cgts;
		cgts = linkCandidate.run();
		//time = clock() - time;
		//cout << "linkCandidate候选区链接消耗时间:" << float(time) * 1000 / CLOCKS_PER_SEC << "毫秒" << endl;

		//step4: number cut  
		//ostringstream oss;
		//Mat test1 = src.clone();
		//Mat plot;
		//plot.create(src.size(), CV_8UC1);
		//plot = Scalar::all(255);

		//time = clock();
		int max_width = 40, idx = 0;
		int cgtssize = cgts.size();
		if (cgtssize>0){
			//RotatedRect re;
			Rect r;
			for (int i = 0; i <cgtssize; i++){
				r = cgts[i].boundingRect();
				if (r.width > max_width){
					max_width = r.width;
						idx = i;
					//secureRect(r, src);
					//rectangle( test1, r, CV_RGB(0, 255, 0), 5, 8, 0 );
				}
			}
			//showWindowImg("linkCandidate", test1);

			r = cgts[idx].boundingRect();
			//float iiii = cgts[idx].angle;
			//cout << iiii << endl;

			//取得截取的图块区域
			secureRect(r,src);
			image_roi = src(r);

			//imwrite("12341.jpg", image_roi);
			showWindowImg("number region", image_roi);
			
			//根据获得的角度旋转
			Mat dsrc = dealCorrect.deskew(image_roi, cgts[idx]);
			//imwrite("1231.jpg", dsrc);
			showWindowImg("deskew_image_roi", dsrc);

			image_roi = Filter(image_roi);//二值化图像
			showWindowImg("binary_image_roi", image_roi);

			Mat df = dealCorrect.deskew(image_roi, cgts[idx]);
			showWindowImg("deskew_binary_image_roi", df);
		}
	} 
	return image_roi;
}
//a secureRect in src Mat
void Mser::secureRect(Rect &r, const Mat &src){
	int minx = r.x;
	int miny = r.y;
	int maxx = minx + r.width ;
	int maxy = miny + r.height;
	minx = (minx >= 0 ? minx : 0);
	miny = (miny >= 0 ? miny : 0);
	maxx = (maxx <= src.cols ? maxx : src.cols);
	maxy = (maxy <= src.rows ? maxy : src.rows);
	r = Rect(minx, miny, maxx - minx, maxy - miny );

}

cv::Mat Mser::AutoBinary(cv::Mat &src)
{
	cv::Mat dst;
	cvtColor(src, src, COLOR_BGR2GRAY);
	threshold(src,dst,110,255,CV_THRESH_OTSU);//CV_THRESH_BINARY
	return dst;
}

cv::Mat Mser::Filter(cv::Mat &src)
{
	double w = src.cols;
	double h = src.rows;

	cvtColor(src, src, COLOR_BGR2GRAY);
	cv::Mat binarization;
	//Mat temp;

	int blockSize = src.rows;
	//取奇数，位运算
	blockSize = blockSize | 1;

	adaptiveThreshold(src, binarization, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, h*0.5);

//	threshold(src,binarization,100,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
	return binarization;
}

void Mser::showWindowImg(string name, cv::Mat &img)
{
	namedWindow(name, 0);
	imshow(name, img);
}

cv::Mat Mser::charrArrayToMat(char *buff, int size)
{
	cv::Mat binmat(1, size, CV_8U, buff);
	cv::Mat imgmat;
	imgmat = cv::imdecode(binmat, cv::IMREAD_COLOR);
	return imgmat;
}

//char* Mser::matToCharArray(cv::Mat)
//{
//	cv::Mat binmat(1, size, CV_8U, buff);
//	cv::Mat imgmat;
//	imgmat = cv::imdecode(binmat, cv::IMREAD_COLOR);
//	return imgmat;
//}