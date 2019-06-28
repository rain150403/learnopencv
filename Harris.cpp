//#include<opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int thresh = 0;  //当前阈值
//int AreaLimit = 1000;
//
//int safePix = 5;
//
//// 去除孤立噪声点   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int main(){
//	Mat srcImage = imread("D:\\roiImage_2\\sample3\\save\\thr_img.jpg");   ///D:\\newSample\\0513\\b\\11.jpg
//	imshow("原图", srcImage);
//	Mat dstImage = Mat::zeros(srcImage.size(), CV_32FC1);
//	Mat g_srcImage1 = srcImage.clone();
//	Mat g_grayImage;
//	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
//
//	int row, col;
//	row = srcImage.rows;
//	col = srcImage.cols;
//
//	Mat cannyOut;
//	Canny(g_srcImage1, cannyOut, 50, 100, 3);
//	imshow("边缘", cannyOut);
//
//
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//膨胀操作
//	Mat edgeImgSafe;
//	dilate(cannyOut, edgeImgSafe, elementSafe);
//	// 反色，且归一化到[0, 1]; 
//	//edgeImgSafe = (255 - edgeImgSafe) / 255;
//
//	imshow("安全边界", edgeImgSafe);
//	
//	// 2 两幅边缘图像相减
//	//Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	
//	cornerHarris(g_grayImage, dstImage, 2, 3, 0.001, BORDER_DEFAULT);
//
//	Mat harrisCorner;
//	threshold(dstImage, harrisCorner, 0.000001, 255, THRESH_BINARY);
//	//harrisCorner = 255 - harrisCorner;
//	imshow("二值化", harrisCorner);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img.jpg", harrisCorner);
//
//	// 计算结果图像      
//	Mat resultImg = Mat::zeros(row, col, CV_8UC1);
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			resultImg.at<uchar>(i, j) =
//				harrisCorner.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//		}
//	}
//
//	imshow("结果", resultImg);
//
//	//将检测到的， 且符合阈值条件的角点绘制出来
//	for (int j = 0; j < harrisCorner.rows; j++){     //normImage
//		for (int i = 0; i < harrisCorner.cols; i++){   //normImage
//			if ((int)harrisCorner.at<float>(j, i) > thresh + 30){
//				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
//			}
//		}
//	}
//	imshow("画图3", g_srcImage1);
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
//// 去除孤立噪声点   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
//{
//	int RemoveCount = 0;
//	//新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
//	//初始化的图像全部为0，未检查  
//	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
//	//去除小连通区域的白色点  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (Src.at<uchar>(i, j) < 10)
//			{
//				PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
//			}
//		}
//	}
//
//	vector<Point2i>NeihborPos;//将邻域压进容器  
//	NeihborPos.push_back(Point2i(-1, 0));
//	NeihborPos.push_back(Point2i(1, 0));
//	NeihborPos.push_back(Point2i(0, -1));
//	NeihborPos.push_back(Point2i(0, 1));
//	//cout << "Neighbor mode: 8邻域." << endl;
//	NeihborPos.push_back(Point2i(-1, -1));
//	NeihborPos.push_back(Point2i(-1, 1));
//	NeihborPos.push_back(Point2i(1, -1));
//	NeihborPos.push_back(Point2i(1, 1));
//
//	int NeihborCount = 8;
//	int CurrX = 0, CurrY = 0;
//	//开始检测  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
//			{   //开始检查  
//				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
//				GrowBuffer.push_back(Point2i(j, i));
//				PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
//				int CheckResult = 0;
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					for (int q = 0; q < NeihborCount; q++)
//					{
//						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
//						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
//						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
//						{
//							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
//							{
//								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
//								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
//							}
//						}
//					}
//				}
//				if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
//					CheckResult = 2;
//				else
//				{
//					CheckResult = 1;
//					RemoveCount++;//记录有多少区域被去除  
//				}
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					CurrX = GrowBuffer.at(z).x;
//					CurrY = GrowBuffer.at(z).y;
//					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
//				}
//				//********结束该点处的检查**********    
//			}
//		}
//	}
//	//开始反转面积过小的区域    
//	for (int i = 0; i < Src.rows; ++i)
//	{
//		for (int j = 0; j < Src.cols; ++j)
//		{
//			if (PointLabel.at<uchar>(i, j) == 2)
//			{
//				Dst.at<uchar>(i, j) = 0;
//			}
//			else if (PointLabel.at<uchar>(i, j) == 3)
//			{
//				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
//
//			}
//		}
//	}
//}
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////#include<opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int thresh = 0;  //当前阈值
////int AreaLimit = 1000;
////
////// 去除孤立噪声点   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
////
//////harris角点检测，对于灰度对比度要求有点高，比如一个图像下面有一行字，那它就只能检测一行字。剩下的角点都检不出来
//////删除这一行字，剩下的对比度较高的地方可以区分出来，但有的也找不到，这就是为什么它检测的点很少
////
//////或者也可以先角点检测，再二值化，然后对二值化的图画圈，但是这样检出来的就有点像边缘了
////
////int main(){
////	Mat srcImage = imread("D:\\newSample\\0513\\b\\23.jpg");   ///D:\\newSample\\0513\\b\\11.jpg
////	imshow("原图", srcImage);
////	Mat dstImage = Mat::zeros(srcImage.size(), CV_32FC1);
////	Mat g_srcImage1 = srcImage.clone();
////	Mat g_grayImage;
////	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
////
////	//拿过一张灰度图直接二值化很容易产生很多噪声点，尤其光照不均的样片
////
////	//Mat cornerStrength;
////	cornerHarris(g_grayImage, dstImage, 2, 3, 0.001, BORDER_DEFAULT);
////	//imshow("harris", cornerStrength);
////
////	Mat normImage, scaledImage;
////	//归一化与转换
////	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
////	imshow("归一化", normImage);
////	convertScaleAbs(normImage, scaledImage);    //将归一化后的图线性变换成8位无符号整型
////
////	//cout << scaledImage << endl;
////
////	//将检测到的， 且符合阈值条件的角点绘制出来
////	for (int j = 0; j < normImage.rows; j++){     //normImage
////		for (int i = 0; i < normImage.cols; i++){   //normImage
////			if ((int)normImage.at<float>(j, i) > thresh + 1){
////				circle(srcImage, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
////				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);   //(0, 10, 255)
////			}
////		}
////	}
////	imshow("画图1", srcImage);
////	imshow("画图2", scaledImage);
////
////
////	Mat harrisCorner;
////	threshold(dstImage, harrisCorner, 0.000001, 255, THRESH_BINARY);
////	//harrisCorner = 255 - harrisCorner;
////	imshow("二值化", harrisCorner);
////
////	/*ROIComDenoise(harrisCorner, harrisCorner, AreaLimit);
////	imshow("去噪", harrisCorner);*/
////
////	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////	Mat element = getStructuringElement(MORPH_RECT, Size(3,3)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(harrisCorner, harrisCorner, MORPH_OPEN, element);
////	//morphologyEx(mor_input, morph_out, MORPH_DILATE, element);   //以后慢慢考虑，现在看来open好一些
////	//morphologyEx(morph_out, morph_out, MORPH_DILATE, element);
////	imshow("腐蚀", harrisCorner);
////
////	//将检测到的， 且符合阈值条件的角点绘制出来
////	for (int j = 0; j < harrisCorner.rows; j++){     //normImage
////		for (int i = 0; i < harrisCorner.cols; i++){   //normImage
////			if ((int)harrisCorner.at<float>(j, i) > thresh + 30){
////				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
////				//circle(scaledImage, Point(j, i), 5, Scalar(0, 10, 255), 2, 8, 0);   //(0, 10, 255)
////			}
////		}
////	}
////	imshow("画图3", g_srcImage1);
////	//imshow("画图2", scaledImage);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////
////// 去除孤立噪声点   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
////{
////	int RemoveCount = 0;
////	//新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
////	//初始化的图像全部为0，未检查  
////	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
////	//去除小连通区域的白色点  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (Src.at<uchar>(i, j) < 10)
////			{
////				PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
////			}
////		}
////	}
////
////	vector<Point2i>NeihborPos;//将邻域压进容器  
////	NeihborPos.push_back(Point2i(-1, 0));
////	NeihborPos.push_back(Point2i(1, 0));
////	NeihborPos.push_back(Point2i(0, -1));
////	NeihborPos.push_back(Point2i(0, 1));
////	//cout << "Neighbor mode: 8邻域." << endl;
////	NeihborPos.push_back(Point2i(-1, -1));
////	NeihborPos.push_back(Point2i(-1, 1));
////	NeihborPos.push_back(Point2i(1, -1));
////	NeihborPos.push_back(Point2i(1, 1));
////
////	int NeihborCount = 8;
////	int CurrX = 0, CurrY = 0;
////	//开始检测  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
////			{   //开始检查  
////				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
////				GrowBuffer.push_back(Point2i(j, i));
////				PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
////				int CheckResult = 0;
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					for (int q = 0; q < NeihborCount; q++)
////					{
////						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
////						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
////						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
////						{
////							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
////							{
////								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
////								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
////							}
////						}
////					}
////				}
////				if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
////					CheckResult = 2;
////				else
////				{
////					CheckResult = 1;
////					RemoveCount++;//记录有多少区域被去除  
////				}
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					CurrX = GrowBuffer.at(z).x;
////					CurrY = GrowBuffer.at(z).y;
////					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
////				}
////				//********结束该点处的检查**********    
////			}
////		}
////	}
////	//开始反转面积过小的区域    
////	for (int i = 0; i < Src.rows; ++i)
////	{
////		for (int j = 0; j < Src.cols; ++j)
////		{
////			if (PointLabel.at<uchar>(i, j) == 2)
////			{
////				Dst.at<uchar>(i, j) = 0;
////			}
////			else if (PointLabel.at<uchar>(i, j) == 3)
////			{
////				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
////
////			}
////		}
////	}
////}