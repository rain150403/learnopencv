////求最小外接矩形函数

///粗略计算物体像素长宽
#include "opencv2/opencv.hpp"  
using namespace cv;
#include <iostream>  
using namespace std;
int main12()
{
	//1.查找轮廓  
	//1.1查找轮廓前的预处理（灰度图，阈值化）  
	Mat srcImg = imread("D:\\roiImage_2\\sample1\\00018.JPG", CV_LOAD_IMAGE_COLOR);
	imshow("srcImg", srcImg);
	Mat copyImg = srcImg.clone();
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY_INV); //要保证黑中找白
	imshow("threshold", srcImg);
	vector <vector<Point>> contours;
	vector<Vec4i> hierarcy;//没用到  
	//1.2查找轮廓  
	findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//最外层轮廓  
	//1.3绘制所有轮廓  
	drawContours(copyImg, contours, -1, Scalar(0, 255, 0), 1, 8);
	//2.由轮廓确定正外接矩形及最小外接矩形 
	//2.1 定义Rect类型的vector容器boundRect存放正外接矩形，初始化大小为contours.size()即轮廓个数  
	vector<Rect> boundRect(contours.size());
	//2.2 定义Rect类型的vector容器roRect存放最小外接矩形，初始化大小为contours.size()即轮廓个数  
	vector<RotatedRect> roRect(contours.size());
	//2.3 遍历每个轮廓  
	for (int i = 0; i < contours.size(); i++)
	{
		//2.4 由轮廓（点集）确定出正外接矩形并绘制
		boundRect[i] = boundingRect(Mat(contours[i]));
		//2.4.1获得正外接矩形的左上角坐标及宽高  
		int width = boundRect[i].width;
		int height = boundRect[i].height;
		int x = boundRect[i].x;
		int y = boundRect[i].y;
		//2.4.2用画矩形方法绘制正外接矩形  
		rectangle(copyImg, Rect(x, y, width, height), Scalar(255, 0, 0), 2, 8);
		//2.5 由轮廓（点集）确定出最小外接矩形并绘制
		//旋转矩形主要成员有center、size、 angle、points()
		roRect[i] = minAreaRect(Mat(contours[i]));
		//2.5.1 旋转矩形类RotatedRect中有Point()方法，参数Point2f* pts，将旋转矩形的四个端点存储进pts.
		Point2f pts[4] = { 0 };
		roRect[i].points(pts);
		//2.5.2 用line方法，根据旋转矩形的四个角点画出矩形
		line(copyImg, pts[0], pts[1], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[0], pts[3], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[2], pts[1], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[2], pts[3], Scalar(0, 0, 255), 2, 8);
		//*2.5.3 由旋转矩形的center成员得出中心点
		Point center = roRect[i].center;
		//*2.5.4 用circle方法画出中心点center
		circle(copyImg, center, 5, Scalar(0, 255, 0), -1, 8);
		//*2.5.5 由旋转矩形的size成员得出宽和高
		double widthRotated = roRect[i].size.width;
		double heightRotated = roRect[i].size.height;
		char widthStr[20] = { 0 };
		char heightStr[20] = { 0 };
		sprintf(widthStr, "width:%.2f", widthRotated);
		sprintf(heightStr, "height:%.2f", heightRotated);
		//*2.5.6 用putText方法将最小外接矩形的宽高显示在图像上
		//putText(copyImg, widthStr, Point(center.x, center.y + 50), CV_FONT_HERSHEY_PLAIN, 1, Scalar(64, 64, 255), 1, 8);
		//putText(copyImg, heightStr, Point(center.x, center.y + 80), CV_FONT_HERSHEY_PLAIN, 1, Scalar(64, 64, 255), 1, 8);
	}
	imshow("粗略计算物体像素长宽", copyImg);
	waitKey(0);
	return 0;
}