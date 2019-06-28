//
//#include <opencv2/core/core.hpp>        
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream> 
//#include<cmath>
//using namespace cv;
//using namespace std;
//
//double e, sigma, eta = 2;
//int w = 200, h = 200;
//Mat_<double> img(h, w);
//
//// 基于等间隔提取图像缩放
//Mat imageReduction(Mat &srcImage, double kx, double ky)
//{
//	// 获取输出图像分辨率
//	int nRows = cvRound(srcImage.rows * kx);
//	int nCols = cvRound(srcImage.cols * ky);
//	Mat resultImage(nRows, nCols, srcImage.type());
//	for (int i = 0; i < nRows; ++i)
//	{
//		for (int j = 0; j < nCols; ++j)
//		{
//			// 根据水平因子计算坐标
//			int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
//			// 根据垂直因子计算坐标
//			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
//			resultImage.at<Vec3b>(i, j) =
//				srcImage.at<Vec3b>(x, y);
//		}
//	}
//	return resultImage;
//}
////Vec3b areaAverage(const Mat &srcImage,
////	Point_<int> leftPoint, Point_<int> rightPoint)
////{
////	int temp1 = 0, temp2 = 0, temp3 = 0;
////	// 计算区域子块像素点个数
////	int nPix = (rightPoint.x - leftPoint.x + 1)*
////		(rightPoint.y - leftPoint.y + 1);
////	// 区域子块各个通道对像素值求和
////	for (int i = leftPoint.x; i <= rightPoint.x; i++){
////		for (int j = leftPoint.y; j <= rightPoint.y; j++){
////			temp1 += srcImage.at<Vec3b>(i, j)[0];
////			temp2 += srcImage.at<Vec3b>(i, j)[1];
////			temp3 += srcImage.at<Vec3b>(i, j)[2];
////		}
////	}
////	// 对每个通道求均值
////	Vec3b vecTemp;
////	vecTemp[0] = temp1 / nPix;
////	vecTemp[1] = temp2 / nPix;
////	vecTemp[2] = temp3 / nPix;
////	return vecTemp;
////}
//
//int train()
//{
//	int i, j, k, s, num = 0, ntrain = 56;
//	double s1 = 0;
//	char filename[50];
//	Mat srcImage, srcGray, m = Mat::zeros(h, w, CV_8UC1), m1 = Mat::zeros(h, w, CV_64FC1);
//	Mat_<uchar> img1, img2;
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "..\\ok\\%d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return 1;
//		srcImage =
//			imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		m += srcGray;
//	}
//	img1 = m;
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "..\\ok\\%d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return 1;
//		srcImage =
//			imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		img2 = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//				img(j, k) = (img2(j, k) - (double)img1(j, k) / ntrain)*(img2(j, k) - (double)img1(j, k) / ntrain) / (ntrain - 1);
//		}
//		m1 += img;
//	}
//	img = m1;
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "..\\ok\\%d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return 1;
//		srcImage =
//			imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		img1 = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (img1(j, k)>eta*sqrt(img(j, k)))
//					s++;
//			}
//		}
//		num += s;
//	}
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "..\\ok\\%d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return 1;
//		srcImage =
//			imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		img1 = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (img1(j, k)>eta*sqrt(img(j, k)))
//					s++;
//			}
//		}
//		s1 += (s - (double)num / ntrain)*(s - (double)num / ntrain);
//	}
//	e = (double)num / ntrain;
//	sigma = sqrt(s1 / (ntrain - 1));
//}
//
//int fasttest(Mat srcImage)
//{
//	int j, k, result, s = 0;
//	Mat srcGray;
//	Mat_<uchar> img1;
//	if (!srcImage.data)
//		return 1;
//	srcImage =
//		imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//	img1 = srcGray;
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//		{
//			if (img1(j, k)>eta*sqrt(img(j, k)))
//				s++;
//		}
//	}
//	if (s > e + sigma || s < e - sigma)
//		result = 0;
//	else
//		result = 1;
//	return result;
//}
//
//int main()
//{
//	int result;
//	Mat srcImage;
//	cout << "Now, beginning to preprocess..." << endl;
//	train();
//	cout << "The preparation work is over, now beginning to test..." << endl;
//	srcImage = imread("..\\figs\\00015.jpg");
//	result = fasttest(srcImage);
//	cout << result << endl;
//	system("pause");
//	return 0;
//}
//
//
