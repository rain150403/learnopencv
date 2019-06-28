//直线检测函数

//并且画了两次， 一次是矩形加直线（最小矩形图）， 一次是只有直线（彩色图）
//在待修改代码里面，无非就是在计算点的时候，画线需要的点， 有一点点不同
//无非就是灰度变化，边缘检测，直线检测， 画线，有多少条，画多少条
//用hough变换也好，canny算子也好，阈值都是可调整的，所以一定要加上滑动条去调节阈值。
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main8()
{
	Mat Image = imread("D:\\roiImage_2\\sample1\\00018.JPG", 0);
	Mat CannyImg;
	Canny(Image, CannyImg, 50, 200, 3);   ///140, 250
	imshow("CannyImg", CannyImg);

	Mat DstImg;
	cvtColor(Image, DstImg, CV_GRAY2BGR);

	vector<Vec4i> Lines;
	HoughLinesP(CannyImg, Lines, 1, CV_PI / 360, 170, 30, 15);
	for (size_t i = 0; i < Lines.size(); i++)
	{
		line(DstImg, Point(Lines[i][0], Lines[i][1]), Point(Lines[i][2], Lines[i][3]), Scalar(0, 0, 255), 2, 8);
	}
	imshow("HoughLines_Detect", DstImg);
	//imwrite(".//res//HoughLines_Detect.jpg", DstImg);
	waitKey(0);
	return 0;
}