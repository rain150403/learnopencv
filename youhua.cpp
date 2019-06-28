//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <windows.h>
//
//using namespace cv;
//using namespace std;
//
//
//int detectThr = 500;
//int grayThr = 10;
//
//
//bool ROIBubbleDetectMethod(Mat &srcImg, Mat &detectImage, int detectThr, int grayThr);
//
////Gamma灰度矫正
//void GammaCorrection(cv::Mat &src, cv::Mat &dst, float fGamma);
//
//int main(){
//
//	DWORD dwLast;
//	DWORD dwCurrent;
//	DWORD dwInterval;
//	
//	Mat srcImg = imread("D:\\newSample\\0508\\a\\4.jpg", 0);
//	Mat detectImage = imread("D:\\newSample\\0508\\a\\5.jpg", 0);
//
//	bool flag = 0;
//	dwLast = GetTickCount();
//	flag = ROIBubbleDetectMethod(srcImg, detectImage, detectThr, grayThr);
//	dwCurrent = GetTickCount();
//
//	dwInterval = dwCurrent - dwLast;
//
//	cout << "用时ms：" << dwInterval << endl;
//
//	if (flag == 1){
//		cout << "ok" << endl;
//	}
//	else{
//		cout << "ng" << endl;
//	}
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
//
//bool ROIBubbleDetectMethod(Mat &srcImg, Mat &detectImage, int detectThr, int grayThr)
//{
//	bool m_resultDetectCom = false;
//	int safePix = 10;
//
//	//GammaCorrection(detectImage, detectImage, 1 / 2.0);
//
//	medianBlur(detectImage, detectImage, 7);
//	GaussianBlur(detectImage, detectImage, Size(3, 3), 3, 3);
//	//normalize(detectImg, detectImg, 0, 255, cv::NORM_MINMAX);
//	int row = detectImage.rows;
//	int col = detectImage.cols;
//
//	//灰度矫正
//	//GammaCorrection(srcImg, srcImg, 0.5);
//	
//	//高斯滤波,归一化
//	medianBlur(srcImg, srcImg, 7);
//	GaussianBlur(srcImg, srcImg, Size(3, 3), 3, 3);
//	cv::Mat edgeImgOk;
//	Canny(srcImg, edgeImgOk, 15, 15 * 3, 3);
//	//normalize(imgOK, imgOK, 0, 255, NORM_MINMAX);
//	int  rowOK = srcImg.rows;
//	int  colOK = srcImg.cols;
//
//	cv::Mat diff_dst;
//
//	////----------------->两图之差<-----------------------------------------------------
//	absdiff(srcImg, detectImage, diff_dst);
//	//imshow("cha", diff_dst);
//	//imwrite("D:\\roiImgForTest\\TEST\\7diff.jpg", diff_dst);
//	//归一化
//	//normalize(diff_dst, diff_dst, 0, 255, NORM_MINMAX);
//	for (int i = 0; i != row; ++i)
//	{
//		auto p = diff_dst.ptr<uchar>(i);
//		for (int j = 0; j != col; ++j)
//		{
//			p[j] = p[j] > grayThr ? 255 : 0;
//			/*
//			if (diff_dst.at<uchar>(i, j)>grayThr)
//			{
//			p[j] = 255;
//			}
//			else
//			{
//			p[j] = 0;
//			}
//			*/
//		}
//	}
//	//边缘图像设置安全像素
//	cv::Mat elementSafe = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(safePix, safePix));
//
//	cv::Mat edgeImgSafe;
//	cv::dilate(edgeImgOk, edgeImgSafe, elementSafe);
//	//反色
//	edgeImgSafe = (255.0 - edgeImgSafe) / 255.0;
//
//	Mat resultImg = Mat::zeros(row, col, CV_8UC1);
//	for (int i = 0; i != row; ++i)
//	{
//		auto p = resultImg.ptr<uchar>(i);
//		auto q = diff_dst.ptr<uchar>(i);
//		auto r = edgeImgSafe.ptr<uchar>(i);
//		for (int j = 0; j != col; ++j)
//		{
//			p[j] = q[j] * r[j];
//			//resultImg.at<uchar>(i, j) = diff_dst.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//		}
//	}
//	
//	//结果判断
//	int resultNum = 0;
//	
//	for (int i = 0; i != row; ++i)
//	{
//		auto p = resultImg.ptr<uchar>(i);
//		for (int j = 0; j != col; ++j)
//		{
//			if (p[j] > 0)
//			{
//				resultNum++;
//			}
//		}
//	}
//	cout << resultNum << endl;
//
//	if (resultNum < detectThr || (resultNum >row*col*0.7))
//	//if (resultNum < detectThr)
//	{
//		m_resultDetectCom = true;      //ok
//	}
//	else
//	{
//		m_resultDetectCom = false;     //ng
//	}
//	return m_resultDetectCom;
//}
//
//
////Gamma灰度矫正
//void GammaCorrection(cv::Mat &src, cv::Mat &dst, float fGamma)
//{
//	/*DWORD dwLast1;
//	DWORD dwCurrent1;
//	DWORD dwInterval1;
//
//	dwLast1 = GetTickCount();*/
//	
//	CV_Assert(src.data);
//
//	CV_Assert(src.depth() != sizeof(uchar));
//
//	unsigned char lut[256];
//
//	for (int i = 0; i != 256; i++)
//	{
//		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
//	}
//
//	dst = src.clone();
//	const int channels = dst.channels();
//	switch (channels)
//	{
//	case 1:
//	{
//		MatIterator_<uchar> it, end;
//		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
//		{
//			*it = lut[(*it)];
//		}
//		break;
//	}
//	case 3:
//	{
//		MatIterator_<Vec3b> it, end;
//		for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
//		{
//			(*it)[0] = lut[((*it)[0])];
//			(*it)[1] = lut[((*it)[1])];
//			(*it)[2] = lut[((*it)[2])];
//		}
//		break;
//	}
//	}
//
//	/*dwCurrent1 = GetTickCount();
//
//	dwInterval1 = dwCurrent1 - dwLast1;
//
//	cout << "用时2ms：" << dwInterval1 << endl;*/
//}
//
//
//
///*
////连通区域去噪
//if (1 == stCamera[camIndex].nFlagDenoise)
//{
////ROIComDenoise(resultImg, resultImg, stCamera[camIndex].nDenoiseThr);
//Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
//morphologyEx(resultImg, resultImg, MORPH_OPEN, element);
//}
//*/