//#include<opencv2\opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Point ptStart;
//
//
///***************************************************
//功能：以ptStart为起点对图像进行填充
//参数：src-边界图像
//ptStart-种子点的坐标
//****************************************************/
//void BoundarySeedFill(Mat &src, Point ptStart)
//{
//	Mat dst = Mat::zeros(src.size(), src.type());
//	int se[3][3] = { { -1, 1, -1 }, { 1, 1, 1 }, { -1, 1, -1 } };//十字形结构元素
//	Mat tempImg = Mat::ones(src.size(), src.type()) * 255;
//	Mat revImg = tempImg - src;//原图像的补集
//	dst.at<uchar>(ptStart.y, ptStart.x) = 255;//绘制种子点
//	while (true)//循环膨胀图像直到图像不在产生变化
//	{
//		Mat temp;
//		dst.copyTo(temp);
//		dilate(dst, dst, se); //用十字结构元素膨胀
//		dst = dst&revImg; //限制膨胀不会超过原始边界
//		if (equalImg(dst, temp)) //不在变化时停止
//		{
//			break;
//		}
//	}
//	src = dst;
//
//}
//void on_MouseHandle(int event, int x, int y, int flag, void* param)
//{
//	Mat& image = *(cv::Mat*)param;
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN:
//		ptStart.x = x;
//		ptStart.y = y;
//		break;
//	case EVENT_LBUTTONUP:
//		BoundarySeedFill(image, ptStart);
//		imshow("边界图像", image);
//		break;
//	}
//}
//
//int main()
//{
//	//读取二值图像（此步可以忽略）
//	Mat src = imread("test1.jpg", 0);
//	imshow("原始图像", src);
//
//	//创建模板
//	int se[3][3] = { { -1, 1, -1 }, { 1, 1, 1 }, { 1, 1, 1 } };
//
//	//区域填充
//	setMouseCallback("边界图像", on_MouseHandle, (void*)&src);
//	waitKey(0);
//	return 0;
//}
//
////https ://blog.csdn.net/wxplol/article/details/73137397 
