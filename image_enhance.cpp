/////*
////https://www.cnblogs.com/jukan/p/7815722.html
////https://blog.csdn.net/guanzhen3657/article/details/81138868
////八种常见的图像增强算法
////1.直方图均衡化
////2.对数图像增强算法
////3.指数图像增强算法
////4.加masaic算法（马赛克）
////5.曝光过度问题处理
////6.高反差保留
////7.Laplace算子图像增强
////8.gamma校正
////*/
////
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>      
////#include <opencv2/imgproc/imgproc.hpp>  
////
////using namespace cv;
////
////int main22(int argc, char *argv[])
////{  //22
////	Mat image = imread("D:\\样品图片\\sample1\\ng\\7.JPG");
////	Mat imageGamma(image.size(), CV_32FC3);
////	for (int i = 0; i < image.rows; i++)
////	{
////		for (int j = 0; j < image.cols; j++)
////		{
////			imageGamma.at<Vec3f>(i, j)[0] = (image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0]);
////			imageGamma.at<Vec3f>(i, j)[1] = (image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1]);
////			imageGamma.at<Vec3f>(i, j)[2] = (image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2]);
////		}
////	}
////	//归一化到0~255    
////	normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
////	//转换成8bit图像显示    
////	convertScaleAbs(imageGamma, imageGamma);
////	imshow("原图", image);
////	imshow("伽马变换图像增强效果", imageGamma);
////	waitKey();
////	return 0;
////}
//
//
////
////#include <opencv2/highgui/highgui.hpp>      
////#include <opencv2/imgproc/imgproc.hpp>  
////
////using namespace cv;
////
////int main(int argc, char *argv[])
////{
////	Mat image = imread("D:\\roiImgForTest\\diff_dst.JPG");
////	Mat imageLog(image.size(), CV_32FC3);
////	for (int i = 0; i < image.rows; i++)
////	{
////		for (int j = 0; j < image.cols; j++)
////		{
////			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
////			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
////			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
////		}
////	}
////	//归一化到0~255    
////	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
////	//转换成8bit图像显示    
////	convertScaleAbs(imageLog, imageLog);
////	imshow("Soure", image);
////	imshow("after", imageLog);
////	waitKey();
////	return 0;
////}
//////
//
//
//#include <opencv2/highgui/highgui.hpp>      
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
//using namespace cv;
//////一片白，效果不好
//int main22(int argc, char *argv[])
//{
//	Mat image = imread("D:\\样品图片\\sample1\\ng\\7.JPG", 1);
//	if (image.empty())
//	{
//		std::cout << "打开图片失败,请检查" << std::endl;
//		return -1;
//	}
//	imshow("原图像", image);
//	Mat imageEnhance;
//	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
//	filter2D(image, imageEnhance, CV_8UC3, kernel);
//	imshow("拉普拉斯算子图像增强效果", imageEnhance);
//	waitKey();
//	return 0;
//}
//
//
//
//#include <opencv2/highgui/highgui.hpp>      
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
//using namespace cv;
//
//int main22(int argc, char *argv[])
//{
//	Mat image = imread("D:\\样品图片\\sample1\\ng\\7.JPG", 1);
//	if (image.empty())
//	{
//		std::cout << "打开图片失败,请检查" << std::endl;
//		return -1;
//	}
//	imshow("原图像", image);
//	Mat imageRGB[3];
//	split(image, imageRGB);
//	for (int i = 0; i < 3; i++)
//	{
//		equalizeHist(imageRGB[i], imageRGB[i]);
//	}
//	merge(imageRGB, 3, image);
//	imshow("直方图均衡化图像增强效果", image);
//	waitKey();
//	return 0;
//}
//////////////////////////////////////////////////////////////////////

/////////增加图像对比度////////////
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//double alpha; /**< 控制对比度 */
//int beta;  /**< 控制亮度 */
//
//////α = 1.2， β = 30
//int main22(int argc, char** argv)
//{
//	/// 读入用户提供的图像
//	Mat image = imread("D:\\样品图片\\sample1\\ng\\7.JPG");
//	Mat new_image = Mat::zeros(image.size(), image.type());
//
//	/// 初始化
//	cout << " Basic Linear Transforms " << endl;
//	cout << "-------------------------" << endl;
//	cout << "* Enter the alpha value [1.0-3.0]: ";
//	cin >> alpha;
//	cout << "* Enter the beta value [0-100]: ";
//	cin >> beta;
//
//	/// 执行运算 new_image(i,j) = alpha*image(i,j) + beta
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//			}
//		}
//	}
//
//	/// 创建窗口
//	namedWindow("Original Image", 1);
//	namedWindow("New Image", 1);
//
//	/// 显示图像
//	imshow("Original Image", image);
//	imshow("New Image", new_image);
//
//	/// 等待用户按键
//	waitKey();
//	return 0;
//}


//// 提高图片亮度和对比度.cpp: 定义控制台应用程序的入口点。 // 
//
//#include "opencv2/opencv.hpp" 
//#include "opencv2/highgui/highgui.hpp" 
//
//using namespace std; 
//using namespace cv; 
//
//int main22() { 
//	Mat src,dest; src = imread("D:\\样品图片\\sample1\\ng\\7.JPG"); 
//	namedWindow("src", CV_WINDOW_AUTOSIZE); 
//	imshow("src", src); 
//	dest = Mat::zeros(src.size(), src.type()); 
//	int width = src.cols; 
//	int height = src.rows; 
//	int channels = src.channels(); 
//	int alphe = 1.8; //(alphe > 1) 
//	int beta = -30;// 负数对比度越高 
//	Mat m1; 
//	src.convertTo(m1, CV_32F); //将原始图片数据（CV_8U类型）转换成CV_32类型，以提高操作的精度 
//	for (int row = 0; row < height;row++) { 
//		for (int col = 0; col < width; col++) { 
//			if (channels == 3) { //对于3通道 
//				float b = m1.at<Vec3f>(row,col)[0]; 
//				float g = m1.at<Vec3f>(row, col)[1]; 
//				float r = m1.at<Vec3f>(row, col)[2]; 
//				
//				dest.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alphe * b + beta); 
//				dest.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alphe * g + beta); 
//				dest.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alphe * r + beta); 
//			} 
//			else if (channels == 1){ //对于单通道 
//				int pix = src.at<uchar>(row, col); 
//				dest.at<uchar>(row,col) = saturate_cast<uchar>(alphe * pix + beta); 
//			} 
//		} 
//	} 
//	
//	namedWindow("change"); 
//	imshow("change",dest); 
//	waitKey(0); 
//	return 0; 
//}


//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//
//using namespace cv;
//
////全局变量声明
//Mat srcImage;
//Mat dstImage;
//int contrastValue;
//int brightValue;
////const string WINDOW_NAME = "contrast&brightValue";
///*******改变图像对比度和亮度值的回调函数*******/
//void on_change(int, void*)
//{
//	namedWindow("contrast&brightValue", 1);
//	for (int i = 0; i < srcImage.rows; i++)
//	{
//		for (int j = 0; j < srcImage.cols; j++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				dstImage.at<Vec3b>(i, j)[c] =
//					saturate_cast<uchar>((contrastValue * 0.01) * (srcImage.at<Vec3b>(i, j)[c]) + brightValue);
//			}
//		}
//	}
//	imshow("contrast&brightValue", dstImage);
//}
//
////感觉对比度变化和亮度变化是一样的，根本不能增强区分度
//
//int main22()
//{
//	srcImage = imread("D:\\样品图片\\sample1\\ng\\7.JPG");
//	dstImage = Mat::zeros(srcImage.size(), srcImage.type());
//	contrastValue = 80;//设定对比度初值
//	brightValue = 80;//设定对亮度的初值
//
//	namedWindow("contrast&brightValue", 1);
//
//	//创建轨迹条
//	createTrackbar("对比度: ", "contrast&brightValue", &contrastValue, 300, on_change);//第二个参数不能为中文，该参数为中文时，我的运行不成功
//	createTrackbar("亮度: ", "contrast&brightValue", &brightValue, 200, on_change);
//
//	//进行回调函数初始化
//	on_change(contrastValue, 0);
//	on_change(brightValue, 0);
//
//	waitKey(0);
//	return 0;
//}