////这里是用一堆小矩形，
/////检测最小外接矩形函数，边缘检测比二值化效果更好，但问题是，检测不了内部的线条
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
#include <iostream> 

//7

using namespace std;
using namespace cv;

int main7(int argc, char *argv[])
{
	Mat imageSource = imread("D:\\样品图片\\sample1\\ng\\14.JPG", 0);
	imshow("Source Image", imageSource);

	Mat image;
	Canny(imageSource, image, 10, 100, 3);    ///sample1   (10, 100)
	imshow("canny", image);
	//blur(imageSource, image, Size(3, 3));
	//threshold(image, image, 10, 200, CV_THRESH_OTSU); ////0, 255  怎么感觉二值化不能用于轮廓提取呢
	//imshow("Threshold Image", image);

	//寻找最外层轮廓  
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	int area = 0;
	int max_area = 0; 

	Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //最小外接矩形画布  
	//Mat imageContours1 = Mat::zeros(image.size(), CV_8UC1); //最小外结圆画布  
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);

		if (area > max_area){
			max_area = area;
		}
		//cout << max_area << endl;

		//绘制轮廓  
		drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
		//drawContours(imageContours1, contours, i, Scalar(255), 1, 8, hierarchy);


		//绘制轮廓的最小外结矩形  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		for (int j = 0; j <= 3; j++)
		{
			line(imageContours, P[j], P[(j + 1) % 4], Scalar(155, 183, 205), 2);
		}

		////绘制轮廓的最小外结圆  
		//Point2f center; float radius;
		//minEnclosingCircle(contours[i], center, radius);
		//circle(imageContours1, center, radius, Scalar(255), 2);

	}

	cout << max_area << endl;

	//for (int i = 0; i < contours.size(); i++){

	//	if (contourArea(contours[i]) == max_area){
	//		//绘制轮廓  
	//		drawContours(imageContours, contours, i, Scalar(153, 187, 255), 1, 8, hierarchy);
	//		//drawContours(imageContours1, contours, i, Scalar(255), 1, 8, hierarchy);


	//		//绘制轮廓的最小外结矩形  
	//		RotatedRect rect = minAreaRect(contours[i]);
	//		Point2f P[4];
	//		rect.points(P);
	//		for (int j = 0; j <= 3; j++)
	//		{
	//			line(imageContours, P[j], P[(j + 1) % 4], Scalar(155, 183, 205), 2);
	//		}

	//		imshow("MinAreaRect", imageContours);

	//		////绘制轮廓的最小外结圆  
	//		//Point2f center; float radius;
	//		//minEnclosingCircle(contours[i], center, radius);
	//		//circle(imageContours1, center, radius, Scalar(255), 2);
	//	}
	//}

	imshow("MinAreaRect", imageContours);
	//imshow("MinAreaCircle", imageContours1);
	waitKey(0);
	return 0;
}