//#include <opencv2/opencv.hpp>        
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp> 
//
//#include <iostream> 
//#include<cmath>
//
//using namespace cv;
//using namespace std;
//
//double e, sigma, eta = 8;     //eta增加，sigma增加  图像都是白的    ///对于小船，只有0.2有点效果的         //对于黑条0.8可以分开缺陷
////eta增加，sigma也会增加，但其实标准图也会受影响，这样对结果的判断也有影响，所以说，不只是前两者的关系，其他也多多少少会受影响
////eta增加，标准图会变成白色，也就是后面无论怎么变化都是白色了，，而且虽然留下的黑点增多了，但是sigma增大，也就是可容忍的范围也增多了。
//int mn, mx, ntrain = 40, w = 100, h = 100;///////w = 5, h = 5  eta=0.162;    //ntest = 20;
//Mat_<double> img(h, w), imge(h, w);
//Mat_<uchar> img1, imgs;
//
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
//			resultImage.at<uchar>(i, j) =
//				srcImage.at<uchar>(x, y);
//		}
//	}
//	return resultImage;
//}
///*Vec3b areaAverage(const Mat &srcImage,
//Point_<int> leftPoint, Point_<int> rightPoint)
//{
//int temp1 = 0, temp2 = 0, temp3 = 0;
//// 计算区域子块像素点个数
//int nPix = (rightPoint.x - leftPoint.x + 1)*
//(rightPoint.y - leftPoint.y + 1);
//// 区域子块各个通道对像素值求和
//for (int i = leftPoint.x; i <= rightPoint.x; i++){
//for (int j = leftPoint.y; j <= rightPoint.y; j++){
//temp1 += srcImage.at<Vec3b>(i, j)[0];
//temp2 += srcImage.at<Vec3b>(i, j)[1];
//temp3 += srcImage.at<Vec3b>(i, j)[2];
//}
//}
//// 对每个通道求均值
//Vec3b vecTemp;
//vecTemp[0] = temp1 / nPix;
//vecTemp[1] = temp2 / nPix;
//vecTemp[2] = temp3 / nPix;
//return vecTemp;
//}*/
//
//void train()
//{
//	int i, j, k, s, num = 0;
//	double s1 = 0;
//	char filename[50];
//	Mat srcImage, srcGray, m = Mat::zeros(h, w, CV_8UC1), m1 = Mat::zeros(h, w, CV_64FC1);
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		m += srcGray;
//	}
//	imshow("一张灰度图srcGray", srcGray);   /////////here
//
//	img1 = m;
//	imshow("总和图像img1", img1);          ///////////here
//	
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//			imge(j, k) = (double)img1(j, k) / ntrain;
//	}
//
//	imshow("均值图像imge", imge);     //////////////////here
//
//	/*cout << "****************************" << endl;
//	cout << imge << endl;
//	cout << "****************************" << endl;*/
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//				img(j, k) = (imgs(j, k) - imge(j, k))*(imgs(j, k) - imge(j, k)) / (ntrain - 1);
//		}
//		m1 += img;
//	}
//	img = m1;
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//			img(j, k) = eta*sqrt(img(j, k));
//	}
//
//	imshow("标准图像img", img);      ////////// here
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//					s++;
//			}
//		}
//		num += s;
//	}
//
//	cout << "训练图片一共的符合条件的点数" << num << endl;    ///// here
//
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//					s++;
//			}
//		}
//		cout << i << ".jpg" << "->" << s << endl;
//		s1 += (s - (double)num / ntrain)*(s - (double)num / ntrain);
//		if (i == 1)
//			mn = mx = s;
//		else
//		{
//			if (s < mn)
//				mn = s;
//			if (s > mx)
//				mx = s;
//		}
//	}
//	e = (double)num / ntrain;
//	sigma = sqrt(s1 / (ntrain - 1));
//	cout << "min:" << mn << endl;
//	cout << "max:" << mx << endl;
//	cout << "e:" << e << ' ' << "sigma:" << sigma << endl;
//
//	//waitKey(0);
//}
//
//int fasttest(Mat srcImage)
//{
//	int j, k, result, s = 0;
//	Mat srcGray;
//	if (!srcImage.data)
//		return 1;
//	srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//	imgs = srcGray;
//
//	//Mat diff_dst;
//	//absdiff(double(imgs), imge, diff_dst);
//
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//		{
//			if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//			{
//				s++;
//				imgs(j, k) = 255;
//			}
//			else
//				imgs(j, k) = 0;
//		}
//	}
//
//	imshow("结果图", imgs);
//	//waitKey(0);
//
//	cout <<"测试值：" << s << endl;
//	if (s > e)
//		result = 0;
//	else
//		result = 1;
//	return result;
//}
//
//int main()
//{
//	int i, result;
//	char filename[50];
//	Mat srcImage;
//	cout << "Now, beginning to preprocess..." << endl;
//	train();
//	cout << "The preparation work is over, now beginning to test..." << endl;
//	for (i = 41; i <= 60; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\test\\%05d.jpg", i);
//		srcImage = imread(filename);
//		result = fasttest(srcImage);
//		cout << i << ".jpg" << "->" << result << endl;
//		if (result == 0)
//		{
//			sprintf_s(filename, "D:\\roiImage_1\\ng\\%05d.jpg", i);
//			//imwrite(filename, srcImage);
//			imwrite(filename, imgs);
//		}
//		else
//		{
//			sprintf_s(filename, "D:\\roiImage_1\\ok\\%d.jpg", i);
//			imwrite(filename, imgs);
//		}
//	}
//	waitKey(0);
//	system("pause");
//	return 0;
//}
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
//
//
//
////#include <opencv2/opencv.hpp>        
////#include <opencv2/highgui/highgui.hpp> 
////#include <opencv2/imgproc/imgproc.hpp> 
////
////#include <iostream> 
////#include<cmath>
////
////using namespace cv;
////using namespace std;
////
////double e, sigma, eta = 0.6;     //eta增加，sigma增加  图像都是白的    ///对于小船，只有0.2有点效果的         //对于黑条0.8可以分开缺陷
//////eta增加，sigma也会增加，但其实标准图也会受影响，这样对结果的判断也有影响，所以说，不只是前两者的关系，其他也多多少少会受影响
//////eta增加，标准图会变成白色，也就是后面无论怎么变化都是白色了，，而且虽然留下的黑点增多了，但是sigma增大，也就是可容忍的范围也增多了。
////int mn, mx, ntrain = 40, w = 1116, h = 239;///////w = 50, h = 50;    //ntest = 20;
////Mat_<double> img(h, w), imge(h, w);
////Mat_<uchar> img1, imgs;
////
////
////// 基于等间隔提取图像缩放
////Mat imageReduction(Mat &srcImage, double kx, double ky)
////{
////	// 获取输出图像分辨率
////	int nRows = cvRound(srcImage.rows * kx);
////	int nCols = cvRound(srcImage.cols * ky);
////	Mat resultImage(nRows, nCols, srcImage.type());
////	for (int i = 0; i < nRows; ++i)
////	{
////		for (int j = 0; j < nCols; ++j)
////		{
////			// 根据水平因子计算坐标
////			int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
////			// 根据垂直因子计算坐标
////			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
////			resultImage.at<uchar>(i, j) =
////				srcImage.at<uchar>(x, y);
////		}
////	}
////	return resultImage;
////}
/////*Vec3b areaAverage(const Mat &srcImage,
////Point_<int> leftPoint, Point_<int> rightPoint)
////{
////int temp1 = 0, temp2 = 0, temp3 = 0;
////// 计算区域子块像素点个数
////int nPix = (rightPoint.x - leftPoint.x + 1)*
////(rightPoint.y - leftPoint.y + 1);
////// 区域子块各个通道对像素值求和
////for (int i = leftPoint.x; i <= rightPoint.x; i++){
////for (int j = leftPoint.y; j <= rightPoint.y; j++){
////temp1 += srcImage.at<Vec3b>(i, j)[0];
////temp2 += srcImage.at<Vec3b>(i, j)[1];
////temp3 += srcImage.at<Vec3b>(i, j)[2];
////}
////}
////// 对每个通道求均值
////Vec3b vecTemp;
////vecTemp[0] = temp1 / nPix;
////vecTemp[1] = temp2 / nPix;
////vecTemp[2] = temp3 / nPix;
////return vecTemp;
////}*/
////
////void train()
////{
////	int i, j, k, s, num = 0;
////	double s1 = 0;
////	char filename[50];
////	Mat srcImage, srcGray, m = Mat::zeros(h, w, CV_8UC1), m1 = Mat::zeros(h, w, CV_64FC1);
////	for (i = 1; i <= ntrain; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		m += srcGray;
////	}
////	imshow("一张灰度图srcGray", srcGray);   /////////here
////
////	img1 = m;
////	imshow("总和图像img1", img1);          ///////////here
////	
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////			imge(j, k) = (double)img1(j, k) / ntrain;
////	}
////
////	imshow("均值图像imge", imge);     //////////////////here
////
////	/*cout << "****************************" << endl;
////	cout << imge << endl;
////	cout << "****************************" << endl;*/
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		// srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////				img(j, k) = (imgs(j, k) - imge(j, k))*(imgs(j, k) - imge(j, k)) / (ntrain - 1);
////		}
////		m1 += img;
////	}
////	img = m1;
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////			img(j, k) = eta*sqrt(img(j, k));
////	}
////
////	imshow("标准图像img", img);      ////////// here
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		s = 0;
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////			{
////				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////					s++;
////			}
////		}
////		num += s;
////	}
////
////	cout << "训练图片一共的符合条件的点数" << num << endl;    ///// here
////
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		s = 0;
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////			{
////				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////					s++;
////			}
////		}
////		cout << i << ".jpg" << "->" << s << endl;
////		s1 += (s - (double)num / ntrain)*(s - (double)num / ntrain);
////		if (i == 1)
////			mn = mx = s;
////		else
////		{
////			if (s < mn)
////				mn = s;
////			if (s > mx)
////				mx = s;
////		}
////	}
////	e = (double)num / ntrain;
////	sigma = sqrt(s1 / (ntrain - 1));
////	cout << "min:" << mn << endl;
////	cout << "max:" << mx << endl;
////	cout << "e:" << e << ' ' << "sigma:" << sigma << endl;
////
////	//waitKey(0);
////}
////
////int fasttest(Mat srcImage)
////{
////	int j, k, result, s = 0;
////	Mat srcGray;
////	if (!srcImage.data)
////		return 1;
////	//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////	imgs = srcGray;
////
////	//Mat diff_dst;
////	//absdiff(double(imgs), imge, diff_dst);
////
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////		{
////			if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////			{
////				s++;
////				imgs(j, k) = 255;
////			}
////			else
////				imgs(j, k) = 0;
////		}
////	}
////
////	imshow("结果图", imgs);
////	//waitKey(0);
////
////	cout <<"测试值：" << s << endl;
////	if (s > e + sigma || s < e - sigma)
////		result = 0;
////	else
////		result = 1;
////	return result;
////}
////
////int main()
////{
////	int i, result;
////	char filename[50];
////	Mat srcImage;
////	cout << "Now, beginning to preprocess..." << endl;
////	train();
////	cout << "The preparation work is over, now beginning to test..." << endl;
////	for (i = 41; i <= 60; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\test\\%05d.jpg", i);
////		srcImage = imread(filename);
////		result = fasttest(srcImage);
////		cout << i << ".jpg" << "->" << result << endl;
////		if (result == 0)
////		{
////			sprintf_s(filename, "D:\\roiImage_1\\ng\\%05d.jpg", i);
////			//imwrite(filename, srcImage);
////			imwrite(filename, imgs);
////		}
////		else
////		{
////			sprintf_s(filename, "D:\\roiImage_1\\ok\\%d.jpg", i);
////			imwrite(filename, imgs);
////		}
////	}
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////
////
////
////
