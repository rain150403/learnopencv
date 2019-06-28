#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int num = 10;  //左右搜索范围
int pix = 100;  //直方图的峰高

int main(){
	Mat srcImage = imread("D:\\newSample\\0619\\50.jpg",0);
	imshow("src", srcImage);
	if (!srcImage.data){
		cout << "fail to load image" << endl;
		return 0;
	}

	MatND dstHist;   //在CV中用CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };    //这里需要为const类型

	int size = 256;
	int channels = 0;

	//计算图像的直方图
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;

	//cout << "dstHist : " << dstHist << endl;

	int row = dstHist.rows;
	int col = dstHist.cols;

	float *h = (float*)dstHist.data;
	double hh[256];
	if (h) {
		for (int i = 0; i < 256; ++i) {
			hh[i] = h[i];
		}
	}

	for (int i = 0; i < 256; i++){
		cout << hh[i] << ",";
	}
	cout << endl;
	
	vector<int> peakA, peakB;
	int k = 0;

	for (int i = 1; i < 255; i++){
		if ((hh[i] > hh[i - 1]) && (hh[i] > hh[i + 1])){
			peakA.push_back(i);
		}
	}
	cout << "size:" << peakA.size() << endl;

	for (int i = 0; i<peakA.size(); i++)
		cout << "位置： " << peakA.at(i) << ", 像素值：" << hh[peakA.at(i)] << endl;

	//方案三
	for (auto it = peakA.begin(); it != peakA.end(); ++it){
		int flag = 0;
		for (int j = 1; j <= num; j++){
			if ((hh[*it - j] > hh[*it]) || (hh[*it + j] > hh[*it])){    //(hh[*it - j] > hh[*it]) || (hh[*it + j] > hh[*it]),(hh[*it - j] < hh[*it]) && (hh[*it + j] < hh[*it]) && (hh[*it] > pix)
				break;
			}
			else{
				//cout << hh[*it - j] << "," << h[*it] << "," << h[*it + j] << endl;
				//cout << "****************" << endl;
				flag++;
			}
		}

		if ((flag >= num - 3) && (hh[*it] > pix)){
			peakB.push_back(*it);
		}
	}
	
	cout << "peakB.size: " << peakB.size() << endl;

	cout << "******************************" << endl;

	for (int i = 0; i<peakB.size(); i++)
		cout << peakB.at(i) << endl;

	cout << "最终峰的个数 :" << peakB.size() << endl;

	Mat dstImage(size *scale, size, CV_8U, Scalar(0));

	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//绘制出直方图
	int hpt = saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++){
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImage);



	waitKey(0);
	system("pause");
	return 0;
}
//
//vector<int> peakA, peakB;
//for (int a = 0; a < peakA.size())



//
//
//
//
//
//
//
//
//
//
//

/*
遍历256个值，比较该值是否比左右都大，如果都大，也就是有可能是峰值，存下来

再遍历这些存下来的近似峰值，如果它左右两侧十个值的范围内它都是最大的，那么，他就是真正的峰值，存下来

比较两张图像的直方图的峰值的个数
*/

//
//
//
//
//
//
//
//
//
//
//////////////////////////////////////////////////////////
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int main(){
////	Mat srcImage = imread("1.jpg", 0);
////	imshow("src", srcImage);
////	if (!srcImage.data)
////
////		waitKey(0);
////	system("pause");
////	return 0;
////}

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(){
//	Mat srcImage = imread("D:\\newSample\\0619\\50.jpg", 0);
//	imshow("src", srcImage);
//	if (!srcImage.data){
//		cout << "fail to load image" << endl;
//		return 0;
//	}
//
//	MatND dstHist;   //在CV中用CvHistogram *hist = cvCreateHist
//	int dims = 1;
//	float hranges[] = { 0, 255 };
//	const float *ranges[] = { hranges };    //这里需要为const类型
//	int size = 256;
//	int channels = 0;
//
//	//计算图像的直方图
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
//	int scale = 1;
//
//	//cout << "dstHist : " << dstHist << endl;
//
//	int row = dstHist.rows;
//	int col = dstHist.cols;
//
//	float *h = (float*)dstHist.data;
//	double hh[256];
//	if (h) {
//		for (int i = 0; i < 256; ++i) {
//			hh[i] = h[i];
//		}
//	}
//
//	for (int i = 0; i < 256; i++){
//		cout << hh[i] << ",";
//	}
//	cout << endl;
//
//	vector<int> peakA;
//	int k = 0;
//
//	for (int i = 1; i < 255; i++){
//		if (hh[i] > hh[i - 1] && hh[i] < hh[i + 1]){
//			peakA.push_back(hh[i]);
//		}
//	}
//
//	/*for (int i = 0; i<peakA.size(); i++)
//	cout << peakA.at(i) << endl;*/
//
//	vector<int>::iterator ite, itj;
//	for (ite = peakA.begin(); ite != peakA.end(); ++ite){
//		for (itj = ite; itj < ite + 10; itj++)
//			if (*ite < *itj)
//				ite = peakA.erase(ite);
//	}
//
//
//
//	cout << "peakA.size: " << peakA.size() << endl;
//
//	cout << "******************************" << endl;
//
//	for (int i = 0; i<peakA.size(); i++)
//		cout << peakA.at(i) << endl;
//
//	cout << "jkj :" << peakA.size() << endl;
//	/*for (int i = 0; i < peakA.size(); i++){
//	for (int j = i; j < i + 10; j++){
//	if (peakA.at(j) > peakA.at(i)){
//
//	}
//	}
//	}*/
//
//	Mat dstImage(size *scale, size, CV_8U, Scalar(0));
//
//	//获取最大值和最小值
//	double minValue = 0;
//	double maxValue = 0;
//	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
//
//	//绘制出直方图
//	int hpt = saturate_cast<int>(0.9*size);
//	for (int i = 0; i < 256; i++){
//		float binValue = dstHist.at<float>(i);
//		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
//		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
//	}
//	imshow("一维直方图", dstImage);
//
//
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}