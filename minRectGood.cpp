////����С��Ӿ��κ���

///���Լ����������س���
#include "opencv2/opencv.hpp"  
using namespace cv;
#include <iostream>  
using namespace std;
int main12()
{
	//1.��������  
	//1.1��������ǰ��Ԥ�����Ҷ�ͼ����ֵ����  
	Mat srcImg = imread("D:\\roiImage_2\\sample1\\00018.JPG", CV_LOAD_IMAGE_COLOR);
	imshow("srcImg", srcImg);
	Mat copyImg = srcImg.clone();
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 100, 255, CV_THRESH_BINARY_INV); //Ҫ��֤�����Ұ�
	imshow("threshold", srcImg);
	vector <vector<Point>> contours;
	vector<Vec4i> hierarcy;//û�õ�  
	//1.2��������  
	findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//���������  
	//1.3������������  
	drawContours(copyImg, contours, -1, Scalar(0, 255, 0), 1, 8);
	//2.������ȷ������Ӿ��μ���С��Ӿ��� 
	//2.1 ����Rect���͵�vector����boundRect�������Ӿ��Σ���ʼ����СΪcontours.size()����������  
	vector<Rect> boundRect(contours.size());
	//2.2 ����Rect���͵�vector����roRect�����С��Ӿ��Σ���ʼ����СΪcontours.size()����������  
	vector<RotatedRect> roRect(contours.size());
	//2.3 ����ÿ������  
	for (int i = 0; i < contours.size(); i++)
	{
		//2.4 ���������㼯��ȷ��������Ӿ��β�����
		boundRect[i] = boundingRect(Mat(contours[i]));
		//2.4.1�������Ӿ��ε����Ͻ����꼰���  
		int width = boundRect[i].width;
		int height = boundRect[i].height;
		int x = boundRect[i].x;
		int y = boundRect[i].y;
		//2.4.2�û����η�����������Ӿ���  
		rectangle(copyImg, Rect(x, y, width, height), Scalar(255, 0, 0), 2, 8);
		//2.5 ���������㼯��ȷ������С��Ӿ��β�����
		//��ת������Ҫ��Ա��center��size�� angle��points()
		roRect[i] = minAreaRect(Mat(contours[i]));
		//2.5.1 ��ת������RotatedRect����Point()����������Point2f* pts������ת���ε��ĸ��˵�洢��pts.
		Point2f pts[4] = { 0 };
		roRect[i].points(pts);
		//2.5.2 ��line������������ת���ε��ĸ��ǵ㻭������
		line(copyImg, pts[0], pts[1], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[0], pts[3], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[2], pts[1], Scalar(0, 0, 255), 2, 8);
		line(copyImg, pts[2], pts[3], Scalar(0, 0, 255), 2, 8);
		//*2.5.3 ����ת���ε�center��Ա�ó����ĵ�
		Point center = roRect[i].center;
		//*2.5.4 ��circle�����������ĵ�center
		circle(copyImg, center, 5, Scalar(0, 255, 0), -1, 8);
		//*2.5.5 ����ת���ε�size��Ա�ó���͸�
		double widthRotated = roRect[i].size.width;
		double heightRotated = roRect[i].size.height;
		char widthStr[20] = { 0 };
		char heightStr[20] = { 0 };
		sprintf(widthStr, "width:%.2f", widthRotated);
		sprintf(heightStr, "height:%.2f", heightRotated);
		//*2.5.6 ��putText��������С��Ӿ��εĿ����ʾ��ͼ����
		//putText(copyImg, widthStr, Point(center.x, center.y + 50), CV_FONT_HERSHEY_PLAIN, 1, Scalar(64, 64, 255), 1, 8);
		//putText(copyImg, heightStr, Point(center.x, center.y + 80), CV_FONT_HERSHEY_PLAIN, 1, Scalar(64, 64, 255), 1, 8);
	}
	imshow("���Լ����������س���", copyImg);
	waitKey(0);
	return 0;
}