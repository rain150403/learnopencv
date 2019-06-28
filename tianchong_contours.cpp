#include <opencv2/opencv.hpp>
#include "iostream"

using namespace std;
using namespace cv;

int main21(){
	Mat src = imread("D:\\样品图片\\sample1\\ng\\14.JPG");
	imshow("Source Image", src);
	//waitKey(0);

	int k = 0, m = 0;

	/// 得到轮廓
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	Mat drawImg;
	drawImg = src.clone();

	//灰度化
	cvtColor(drawImg, drawImg, COLOR_RGB2GRAY);
	imshow("灰度图", drawImg);
	//二值化
	threshold(drawImg, drawImg, 180, 200, CV_THRESH_BINARY);
	imshow("二值化", drawImg);

	Canny(drawImg, drawImg, 10, 100, 3);    ///sample1   (10, 100)
	imshow("canny", drawImg);

	//contours为函数findContours计算得到的轮廓点分布值
	cv::findContours(drawImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++){
		drawContours(drawImg, contours, -1, Scalar(255), 3);
	}
	cout << "边缘个数 ： " << contours.size() << endl;
	imshow("contours", drawImg);

	// 计算到轮廓的距离
	cv::Mat raw_dist(src.size(), CV_32FC1);

	for (int j = 0; j < src.rows; j++){
		for (int i = 0; i < src.cols; i++){
			raw_dist.at<float>(j, i) = cv::pointPolygonTest(contours[100], Point2f(i, j), false);
			//cout << raw_dist.at<float>(100, 900) << endl;
			if (raw_dist.at<float>(j, i) >= 0){
				k++;
			}
			else{
				m++;
			}
		}
	}

	cout << "k: " << k << "m: " << m << endl;
	imshow("julitu", raw_dist);

	waitKey(0);

	system("pause");
	return 0;
}

//#include <opencv2/opencv.hpp>
//#include "iostream"
//
//using namespace std;
//using namespace cv;
//
//int main21(int argc, char** argv)
//{
//	Mat img = imread("D:\\样品图片\\sample1\\ng\\14.JPG");
//	threshold(img, img, 180, 255, CV_THRESH_BINARY);
//	cvtColor(img, img, CV_BGR2GRAY);
//
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierachy;
//	findContours(img, contours, hierachy, RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//	drawContours(img, contours, 1, Scalar::all(255), 2, 8, hierachy);
//
//	//这里说明下，轮廓1是圈出的枫叶
//	Mat dist = Mat::zeros(img.size(), CV_32FC1);
//	for (int i = 0; i<img.rows; i++)	{
//		for (int j = 0; j<img.cols; j++)	{
//			double distance = pointPolygonTest(contours[1], Point2f(j, i), true);
//			dist.at<float>(i, j) = static_cast<float>(distance);
//		}
//	}
//
//
//
//	double minVal, maxVal;
//	minMaxLoc(dist, &minVal, &maxVal, 0, 0, Mat());
//	Mat drawImg1 = Mat::zeros(img.size(), CV_8UC3);
//	int thredVal1 = 1;
//	for (int i = 0; i<img.rows; i++)	{
//		for (int j = 0; j<img.cols; j++)	{
//			double distance = dist.at<float>(i, j);
//			if (distance > thredVal1){
//				drawImg1.at<Vec3b>(i, j)[0] = (uchar)(abs(distance / maxVal) * 255);
//			}
//			else if (distance < (thredVal1 *(-1))){
//				drawImg1.at<Vec3b>(i, j)[2] = (uchar)(abs(distance / minVal) * 255);
//			}
//			else {
//				drawImg1.at<Vec3b>(i, j)[0] = (uchar)(abs(255 - distance));
//				drawImg1.at<Vec3b>(i, j)[1] = (uchar)(abs(255 - distance));
//				drawImg1.at<Vec3b>(i, j)[2] = (uchar)(abs(255 - distance));
//			}
//		}
//	}
//	//imshow("drawImg1", drawImg1);
//	//imwrite("drawImg1.jpg", drawImg1);
//
//
//
//	normalize(dist, dist, -255, 255, NORM_MINMAX);
//	Mat drawImg2 = Mat::zeros(img.size(), CV_8UC3);
//	int thredVal2 = 3;
//	for (int i = 0; i<img.rows; i++)	{
//		for (int j = 0; j<img.cols; j++)	{
//			double distance = dist.at<float>(i, j);
//			if (distance > thredVal2){
//				drawImg2.at<Vec3b>(i, j)[0] = (uchar)(distance);
//			}
//			else if (distance < (thredVal2 *(-1))){
//				drawImg2.at<Vec3b>(i, j)[2] = (uchar)(distance*(-1));
//			}
//			else {
//				drawImg2.at<Vec3b>(i, j)[0] = (uchar)(255);
//				drawImg2.at<Vec3b>(i, j)[1] = (uchar)(255);
//				drawImg2.at<Vec3b>(i, j)[2] = (uchar)(255);
//			}
//		}
//	}
//	//imshow("drawImg2", drawImg2);
//	//imwrite("drawImg2.jpg", drawImg2);
//
//	imshow("img", img);
//
//	waitKey();
//	return 0;
//}