//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace cv;
//
//void draw_contour(Mat canny_input){
//	int g_nThresh = 80;
//	RNG g_rng(12345);
//	Mat canny_out;
//	vector<vector<Point> > g_vContours;
//	vector<Vec4i> g_vHierarchy;
//
//	//调用canny算子检测边缘 
//	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//寻找轮廓 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("缺陷轮廓图", drawing);
//}
//
//int main23(int argc, char** argv)
//{
//	Mat srcImage = imread("D:\\roiImage_2\\sample12\\fushi.jpg");
//	//Mat midImage, dstImage;
//	imshow("【原始图】", srcImage);
//
//	//cvtColor(srcImage, midImage, CV_BGR2GRAY);//转化边缘检测后的图为灰度图
//	//GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
//	//vector<Vec3f> circles;
//	//HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1, midImage.rows / 20, 100, 100, 0, 0);
//	////依次在图中绘制出圆
//	//for (size_t i = 0; i < circles.size(); i++)
//	//{
//	//	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//	//	int radius = cvRound(circles[i][2]);
//	//	//绘制圆心
//	//	circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
//	//	//绘制圆轮廓
//	//	circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
//	//}
//
//	draw_contour(srcImage);
//
//	imshow("【效果图】", srcImage);
//	waitKey(0);
//	return 0;
//}