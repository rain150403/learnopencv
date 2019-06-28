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
//	//����canny���Ӽ���Ե 
//	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//Ѱ������ 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("ȱ������ͼ", drawing);
//}
//
//int main23(int argc, char** argv)
//{
//	Mat srcImage = imread("D:\\roiImage_2\\sample12\\fushi.jpg");
//	//Mat midImage, dstImage;
//	imshow("��ԭʼͼ��", srcImage);
//
//	//cvtColor(srcImage, midImage, CV_BGR2GRAY);//ת����Ե�����ͼΪ�Ҷ�ͼ
//	//GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);
//	//vector<Vec3f> circles;
//	//HoughCircles(midImage, circles, CV_HOUGH_GRADIENT, 1, midImage.rows / 20, 100, 100, 0, 0);
//	////������ͼ�л��Ƴ�Բ
//	//for (size_t i = 0; i < circles.size(); i++)
//	//{
//	//	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//	//	int radius = cvRound(circles[i][2]);
//	//	//����Բ��
//	//	circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
//	//	//����Բ����
//	//	circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
//	//}
//
//	draw_contour(srcImage);
//
//	imshow("��Ч��ͼ��", srcImage);
//	waitKey(0);
//	return 0;
//}