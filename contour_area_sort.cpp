/////////////�������������////////////////////////////////////////////////////////////////////////////////

//�����������ɾ�����С����ֵ������
#include <iostream>  
#include<vector>
#include<algorithm>
#include <opencv2\opencv.hpp>  
#include <opencv2\highgui\highgui.hpp> 

using namespace std;
using namespace cv;

//10

//�������������С��������
bool ascendSort(vector<Point> a, vector<Point> b) {
	return a.size() < b.size();
}

//�������������С��������
bool descendSort(vector<Point> a, vector<Point> b) {
	return a.size() > b.size();
}
int main10() {
	Mat srcImage = imread("D:\\��ƷͼƬ\\sample1\\ng\\14.JPG");
	Mat thresholdImage;
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	threshold(grayImage, thresholdImage, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	imshow("��ֵͼ", thresholdImage);
	//Mat resultImage;
	//thresholdImage.copyTo(resultImage);
	vector< vector< Point> > contours;  //���ڱ�������������Ϣ
	vector< vector< Point> > contours2; //���ڱ����������100������
	vector<Point> tempV;				//�ݴ������

	findContours(thresholdImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	//cv::Mat labels;
	//int N = connectedComponents(resultImage, labels, 8, CV_16U);
	//findContours(labels, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//�������������С������������
	sort(contours.begin(), contours.end(), ascendSort);//��������
	vector<vector<Point> >::iterator itc = contours.begin();
	int i = 0;
	while (itc != contours.end())
	{
		//��������ľ��α߽�
		Rect rect = boundingRect(*itc);
		int x = rect.x;
		int y = rect.y;
		int w = rect.width;
		int h = rect.height;
		//���������ľ��α߽�
		cv::rectangle(srcImage, rect, { 0, 0, 255 }, 1);
		//����ͼƬ
		char str[10];
		sprintf(str, "%d.jpg", i++);
		cv::imshow("srcImage", srcImage);
		imwrite(str, srcImage);
		waitKey(1000);

		if (itc->size() < 100)
		{
			//�������������100�����򣬷ŵ�����contours2�У�
			tempV.push_back(Point(x, y));
			tempV.push_back(Point(x, y + h));
			tempV.push_back(Point(x + w, y + h));
			tempV.push_back(Point(x + w, y));
			contours2.push_back(tempV);
			/*Ҳ����ֱ���ã�contours2.push_back(*itc);���������5�����*/
			//contours2.push_back(*itc);

			//ɾ�������������100�����򣬼��ú�ɫ��������������100������
			cv::drawContours(srcImage, contours2, -1, Scalar(0, 0, 0), CV_FILLED);
		}
		//����ͼƬ
		sprintf(str, "%d.jpg", i++);
		cv::imshow("srcImage", srcImage);
		imwrite(str, srcImage);
		cv::waitKey(100);
		tempV.clear();
		++itc;
	}

	system("pause");
	return 0;
}
