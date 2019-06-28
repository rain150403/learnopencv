//#include <opencv2\opencv.hpp>
//#include <iostream>
//#include <string>
//#include "kmeansMethon.h"
//
//using namespace std;
//
//cv::Scalar colorTab[] =     //10个颜色  
//{
//	cv::Scalar(255, 0, 0),
//	cv::Scalar(0, 255, 0),
//	cv::Scalar(0, 0, 255),
//	cv::Scalar(255, 100, 100),
//	cv::Scalar(255, 0, 255),
//	cv::Scalar(0, 255, 255),
//	cv::Scalar(255, 255, 0),
//	cv::Scalar(255, 0, 100),
//	cv::Scalar(100, 100, 100),
//	cv::Scalar(50, 125, 125)
//};
//
//
//void main()
//{
//	cv::Mat lenaImg = cv::imread("D:\\roiImage_2\\sample3\\save\\thr_img.jpg");
//
//	//boxFilter(dst, out2, -1, Size(5, 5));   //方框滤波
//	//blur(dst, out2, Size(11, 11));    //均值滤波
//	//GaussianBlur(dst, out2, Size(3, 3), 0, 0);    //高斯滤波
//	
//	medianBlur(lenaImg, lenaImg, 7);   //中值滤波
//	//bilateralFilter(dst, out2, 25, 25*2, 25/2);     //双边滤波
//
//	int imgHeight = lenaImg.rows;
//	int imgWidth = lenaImg.cols;
//	int channel = lenaImg.channels();
//	int imgSize = imgHeight*imgWidth;
//	//整理输入数据
//	cv::Mat input = cv::Mat::zeros(imgSize, 1, CV_32FC3);
//	cv::Mat labelImg = cv::Mat::zeros(imgSize, 1, CV_32SC1);
//	labelImg.setTo(-1);
//
//	uchar *pLena = (uchar*)lenaImg.data;
//	float *pInput = (float*)input.data;
//	for (int i = 0; i < imgHeight; i++)
//	{
//		for (int j = 0; j < imgWidth; j++)
//		{
//			int idx = (i*imgWidth + j)*channel;
//			pInput[idx] = (float)pLena[idx];
//			pInput[idx + 1] = (float)pLena[idx + 1];
//			pInput[idx + 2] = (float)pLena[idx + 2];
//		}
//	}
//
//	kmeansMethon kmeansCluster;
//	kmeansCluster.run(input, labelImg, 10, 1);
//
//	cv::Mat showColor = lenaImg.clone();
//	for (int i = 0; i < lenaImg.rows; i++)
//	{
//		for (int j = 0; j < lenaImg.cols; j++)
//		{
//			//标记像素点的类别，颜色区分  
//			cv::circle(showColor, cv::Point(j, i), 1, colorTab[labelImg.at<int>(i*lenaImg.cols + j)]);
//		}
//	}
//	cv::imshow("color", showColor);
//	cv::waitKey(0);
//}
