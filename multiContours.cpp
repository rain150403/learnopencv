//这种方法对于有的图还可以，尤其是复杂的图，对于简单的规则的图，根本没效果，一片黑
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

int main14()
{
	cv::Mat img = cv::imread("D:\\waitDelete\\VS_project\\GetPlateArea\\GetPlateArea\\1(1).JPG");
	cv::Mat imgHSV(img.size(), img.type());
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
	cv::Mat imgHSVMask(img.size(), CV_8UC1);
	// yellow color region
	cv::inRange(imgHSV, cv::Scalar(11, 43, 46), cv::Scalar(26, 255, 255), imgHSVMask);

	char *win1 = "original mask";   char *win2 = "after remove";
	cv::namedWindow(win1);  cv::moveWindow(win1, 10, 10);
	cv::namedWindow(win2);  cv::moveWindow(win2, 800, 10);

	cv::imshow(win1, imgHSVMask);   cv::waitKey(0);     cv::destroyWindow(win1);    cv::imwrite("data/original.png", imgHSVMask);

	// 提取连通区域，并剔除小面积联通区域
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(imgHSVMask, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	contours.erase(std::remove_if(contours.begin(), contours.end(),
		[](const std::vector<cv::Point>& c){return cv::contourArea(c) < 30; }), contours.end());

	// 显示图像并保存
	imgHSVMask.setTo(0);
	cv::drawContours(imgHSVMask, contours, -1, cv::Scalar(255), 3);
	cv::imshow(win2, imgHSVMask);   cv::waitKey(0); cv::destroyWindow(win2);    cv::imwrite("data/remove.png", imgHSVMask);
	return 0;
}
