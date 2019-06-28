////��������һ��С���Σ�
/////�����С��Ӿ��κ�������Ե���ȶ�ֵ��Ч�����ã��������ǣ���ⲻ���ڲ�������
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>    
#include <iostream> 

//7

using namespace std;
using namespace cv;

int main7(int argc, char *argv[])
{
	Mat imageSource = imread("D:\\��ƷͼƬ\\sample1\\ng\\14.JPG", 0);
	imshow("Source Image", imageSource);

	Mat image;
	Canny(imageSource, image, 10, 100, 3);    ///sample1   (10, 100)
	imshow("canny", image);
	//blur(imageSource, image, Size(3, 3));
	//threshold(image, image, 10, 200, CV_THRESH_OTSU); ////0, 255  ��ô�о���ֵ����������������ȡ��
	//imshow("Threshold Image", image);

	//Ѱ�����������  
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

	int area = 0;
	int max_area = 0; 

	Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //��С��Ӿ��λ���  
	//Mat imageContours1 = Mat::zeros(image.size(), CV_8UC1); //��С���Բ����  
	for (int i = 0; i < contours.size(); i++)
	{
		area = contourArea(contours[i]);

		if (area > max_area){
			max_area = area;
		}
		//cout << max_area << endl;

		//��������  
		drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);
		//drawContours(imageContours1, contours, i, Scalar(255), 1, 8, hierarchy);


		//������������С������  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		for (int j = 0; j <= 3; j++)
		{
			line(imageContours, P[j], P[(j + 1) % 4], Scalar(155, 183, 205), 2);
		}

		////������������С���Բ  
		//Point2f center; float radius;
		//minEnclosingCircle(contours[i], center, radius);
		//circle(imageContours1, center, radius, Scalar(255), 2);

	}

	cout << max_area << endl;

	//for (int i = 0; i < contours.size(); i++){

	//	if (contourArea(contours[i]) == max_area){
	//		//��������  
	//		drawContours(imageContours, contours, i, Scalar(153, 187, 255), 1, 8, hierarchy);
	//		//drawContours(imageContours1, contours, i, Scalar(255), 1, 8, hierarchy);


	//		//������������С������  
	//		RotatedRect rect = minAreaRect(contours[i]);
	//		Point2f P[4];
	//		rect.points(P);
	//		for (int j = 0; j <= 3; j++)
	//		{
	//			line(imageContours, P[j], P[(j + 1) % 4], Scalar(155, 183, 205), 2);
	//		}

	//		imshow("MinAreaRect", imageContours);

	//		////������������С���Բ  
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