//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//using namespace cv;
//
//int main(){
//
//	vector<Mat> channels;
//	Mat imgBlueChannel;
//	Mat imgGreenChannel;
//	Mat imgRedChannel;
//
//	//OpenCV的通道是BGR 不是 RGB,顺序要注意
//	//Mat srcImg = imread("D:\\newSample\\0619\\32.jpg");
//	Mat srcImg = imread("1.jpg");
//
//	split(srcImg, channels);
//
//	imgBlueChannel = channels.at(0);
//	imgGreenChannel = channels.at(1);
//	imgRedChannel = channels.at(2);
//
//	imshow("Blue", imgBlueChannel);
//	imshow("Green", imgGreenChannel);
//	imshow("Red", imgRedChannel);
//
//	Mat fin_img;
//
//
//	merge(channels, fin_img);
//
//	imshow("合并后", fin_img);
//
//
//	waitKey(0);
//
//	system("pause");
//	return 0;
//}
///*
//为什么显示的单通道图像都是灰度图像？
//用函数得到只有一个通道（B或G或R）都是灰度的，要得到只有一个颜色的单通道图像只有通过遍历每一个像素，把另外两个通道都设为0.
//
//单通道就是只有一种色彩通道，你想让它是红的绿的还是蓝的，它的取值范围就是从暗到亮，
//即所谓的灰度，非严格来说单通道图像就是灰度图像。
//
//彩色图像一般是三通道图像（24位），一个像素需要3个值来表示分别是0-255，例如（255,178,233）。
//你单通道（8位）只能表示一个值，范围0-255，所以都是灰度图。
//*/
//
//
//
////int main()
////{
////	//读入彩色图像
////	Mat img = imread("D:\\newSample\\0619\\32.jpg");
////	Mat dst = imread("D:\\newSample\\0619\\37-2.jpg");
////	imshow("原图", img);
////	int rows = img.rows;
////	int cols = img.cols;
////	//生成和img同样大小的空白灰度图像
////	Mat grayImg = Mat(rows, cols, CV_8UC3);
////	//for (int i = 0; i < rows; i++)
////	//{
////	//	for (int j = 0; j < cols; j++)
////	//	{
////	//		////彩色图像获取到单个像素
////	//		//Vec3b pix = img.at<Vec3b>(i, j);
////	//		////获取到RGB分量的值。
////	//		//uchar B = pix[0];
////	//		//uchar G = pix[1];
////	//		//uchar R = pix[2];
////	//		////或者使用下面的方法
////	//		////uchar B = img.at<Vec3b>(i, j)[0];
////	//		////uchar G = img.at<Vec3b>(i, j)[1];
////	//		////uchar G = img.at<Vec3b>(i, j)[2];
////	//		////计算灰度值，然后赋值给灰度图中的像素
////	//		////grayImg.at<uchar>(i, j) = R * 0.299 + G * 0.587 + B * 0.114;//灰度著名心理学公式
////
////	//		/////cout << img.at<Vec3b>(i, j)[0] << ",";
////
////	//		//grayImg.at<Vec3b>(j, i) = img.at<Vec3b>(j, i)[0];
////
////	//		/*rotImg.at<Vec3b>(j, i)[0] = srcImg.at<Vec3b>(pix12[i].y, pix12[i].x)[0];
////	//		rotImg.at<Vec3b>(j, i)[1] = srcImg.at<Vec3b>(pix12[i].y, pix12[i].x)[1];
////	//		rotImg.at<Vec3b>(j, i)[2] = srcImg.at<Vec3b>(pix12[i].y, pix12[i].x)[2];*/
////
////	//	}
////	//}
////
////	vector<vector<uchar>> mv;
////
////	split(img, mv);
////
////	imshow("e", mv[0]);
////
////	//cout << img <<endl;
////
////	//Mat diff;
////	//absdiff(img, dst, diff);
////	//imshow("cha", diff);
////
////	//imshow("单通道", grayImg);
////
////	//imshow("R", img.at<Vec3b>[0]);
////
////	//imshow("灰度图", grayImg);
////	waitKey(0);
////
////	system("pause");
////	return 0;
////}