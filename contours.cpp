#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <iostream> 

int main13() {
	cv::Mat image = cv::imread("D:\\roiImage_2\\00002.JPG", 0);
	cv::Mat binary;
	cv::threshold(image, binary, 120, 255, cv::THRESH_BINARY_INV);
	cv::namedWindow("binary");
	cv::imshow("binary", binary);
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result, contours, -1, cv::Scalar(0), 2);
	cv::namedWindow("contours");
	cv::imshow("contours", result);
	std::vector<std::vector<cv::Point>>::iterator it = contours.begin();
	while (it != contours.end()) {
		if (it->size() < 200) {
			it = contours.erase(it);
		}
		else {
			++it;
		}
	}
	cv::Mat result1(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result1, contours, -1, cv::Scalar(0), 2);
	cv::namedWindow("contours1");
	cv::imshow("contours1", result1);
	cv::waitKey(0);
	return 0;
}