//
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//void show_1_dimension_hist(Mat srcImage);
//
//int main(){
//
//	//���������׼ͼ����������ŶԱ�ͼ��ľ���RGB��HSV��
//	Mat srcImage_base, hsvImage_base;
//	Mat srcImage_test1, hsvImage_test1;
//	Mat srcImage_test2, hsvImage_test2;
//	Mat srcImage_test3, hsvImage_test3;
//	Mat hsvImage_halfDown;
//
//
//	//�����׼ͼ��srcImage_base�������Ų���ͼ��srcImage_test1 ��srcImage_test2�� ����ʾ
//	srcImage_base = imread("D:\\newSample\\0619\\40.jpg", 1);
//	srcImage_test1 = imread("D:\\newSample\\0619\\42.jpg", 1);
//	srcImage_test2 = imread("D:\\newSample\\0619\\46.jpg", 1);
//	srcImage_test3 = imread("D:\\newSample\\0619\\48.jpg", 1);
//
//	//��ʾ���������ͼ��
//	imshow("��׼ͼ��", srcImage_base);
//	imshow("����ͼ��1", srcImage_test1);
//	imshow("����ͼ��2", srcImage_test2);
//	imshow("����ͼ��3", srcImage_test3);
//
//	//��ͼ����BGRɫ�ʿռ�ת����HSVɫ�ʿռ�
//	cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
//	cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
//	cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);
//	cvtColor(srcImage_test3, hsvImage_test3, COLOR_BGR2HSV);
//
//	//����������׼ͼ���°벿�İ���ͼ��HSV��ʽ��
//	//hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows / 2, hsvImage_base.rows - 1), Range(0, hsvImage_base.cols - 1));
//
//	hsvImage_halfDown = hsvImage_test3;
//
//	//��ʼ������ֱ��ͼ��Ҫ��ʵ��
//	//��hueͨ��ʹ��30��bin�� ��saturationͨ��ʹ��32��bin
//	int h_bins = 50; int s_bins = 60;
//	int histSize[] = { h_bins, s_bins };
//
//	//hue��ȡֵ��Χ��0��256�� saturationȡֵ��Χ��0��180
//	float h_ranges[] = { 0, 256 };
//	float s_ranges[] = { 0, 180 };
//	const float* ranges[] = {h_ranges, s_ranges};
//
//	//ʹ�õ�0�͵�1ͨ��
//	int channels[] = { 0, 1 };
//
//	//��������ֱ��ͼ��MatND���ʵ��
//	MatND baseHist;
//	MatND halfDownHist;
//	MatND testHist1;
//	MatND testHist2;
//
//	//�����׼ͼ�� ���Ų���ͼ�� �����׼ͼ���HSVֱ��ͼ
//	calcHist(&hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false);
//	normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());
//
//	show_1_dimension_hist(hsvImage_base);
//
//	calcHist(&hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false);
//	normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat());
//
//	show_1_dimension_hist(hsvImage_halfDown);
//
//	calcHist(&hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false);
//	normalize(testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat());
//
//	show_1_dimension_hist(hsvImage_test1);
//
//	calcHist(&hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false);
//	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());
//
//	show_1_dimension_hist(hsvImage_test2);
//
//	//��˳��ʹ��4�ֶԱȱ�׼����׼ͼ���ֱ��ͼ�������ֱ��ͼ���жԱ�
//	for (int i = 0; i < 4; i++){
//		//����ͼ��ֱ��ͼ�ĶԱ�
//		int compare_method = i;
//		double base_base = compareHist(baseHist, baseHist, compare_method);
//		double base_half = compareHist(baseHist, halfDownHist, compare_method);
//		double base_test1 = compareHist(baseHist, testHist1, compare_method);
//		double base_test2 = compareHist(baseHist, testHist2, compare_method);
//
//		cout << "i:" << i << ", base_base:" << base_base << ", base_half:" << base_half << ", base_test1:" << base_test1 << ", base_test2" << base_test2 << endl;
//	}
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
//void show_1_dimension_hist(Mat srcImage){
//	imshow("src", srcImage);
//	if (!srcImage.data){
//		cout << "fail to load image" << endl;
//		return ;
//	}
//	
//	MatND dstHist;   //��CV����CvHistogram *hist = cvCreateHist
//	int dims = 1;
//	float hranges[] = { 0, 255 };
//	const float *ranges[] = { hranges };    //������ҪΪconst����
//	int size = 256;
//	int channels = 0;
//	
//	//����ͼ���ֱ��ͼ
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
//	int scale = 1;
//	
//	Mat dstImage(size *scale, size, CV_8U, Scalar(0));
//	
//	//��ȡ���ֵ����Сֵ
//	double minValue = 0;
//	double maxValue = 0;
//	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
//	
//	//���Ƴ�ֱ��ͼ
//	int hpt = saturate_cast<int>(0.9*size);
//	for (int i = 0; i < 256; i++){
//		float binValue = dstHist.at<float>(i);
//		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
//		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
//	}
//	imshow("һάֱ��ͼ", dstImage);
//	
//	//waitKey(0);
//}
//
//
//
//
//
//
///////////////////////////////////////////////////////
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int main(){
////	Mat srcImage = imread("1.jpg", 0);
////	imshow("src", srcImage);
////	if (!srcImage.data)
////
////		waitKey(0);
////	system("pause");
////	return 0;
////}



