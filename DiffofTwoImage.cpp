//将两张图片相减，看差异图

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void main1(){

	//1
	Mat img1 = imread("D:\\roiImage\\0 detectImgNew.JPG");
	Mat img2 = imread("D:\\roiImage\\0 ImgOK.JPG");
	Mat dst;  

	imshow("img1", img1);
	imshow("img2", img2);
	cout << "img1 " << int(img1.at<Vec3b>(10, 10)[0]) << endl;
	cout << "img2 " << int(img2.at<Vec3b>(10, 10)[0]) << endl;

	absdiff(img1, img2, dst);
	cout << "dst " << int(dst.at<Vec3b>(10, 10)[0]) << endl;
	imshow("dst", dst);

	waitKey(0);
	system("pause");
}