//////图片反色函数
//#include<opencv2/opencv.hpp>
//#include<iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(){
//	Mat thr_img;
//
//	//Mat m2;
//	//m2.create(thr_img.size(), thr_img.type());
//
//	thr_img = imread("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg");
//	imshow("src", thr_img);
//	waitKey(0);
//
//	cvtColor(thr_img, thr_img, CV_BGR2GRAY);
//	imshow("gray", thr_img);
//	waitKey(0);
//
//	int height = thr_img.rows;
//	int width = thr_img.cols;
//
//	for (int row = 0; row < height; row++){
//		for (int col = 0; col < width; col++){
//			thr_img.at<uchar>(row, col) = 255 - thr_img.at<uchar>(row, col);
//		}
//	}
//	imshow("fanse", thr_img);
//	waitKey(0);
//	return 0;
//}
//
//
////int main9(){
////	//如果是多通道的图像
////
////	Mat src = imread("D:\\roiImage_2\\1.JPG");
////	if (src.empty()){
////		printf("Could not load image...");
////		return 0;
////	}
////
////	Mat dst;
////
////	cvtColor(src, dst, CV_BGR2GRAY);
////
////	Mat m2;
////	m2.create(dst.size(), dst.type());
////
////	int height2 = dst.rows;
////	int width2 = dst.cols;
////	int np = dst.channels();
////
////	cout << "tongdaoshu :" << np << endl;
////
////	for (int row = 0; row < height2; row++){
////		for (int col = 0; col < width2; col++){
////			if (np == 1){
////				m2.at<uchar>(row, col) = 255 - dst.at<uchar>(row, col);
////			}
////			else if (np == 3){
////				m2.at<Vec3b>(row, col)[0] = 255 - dst.at<Vec3b>(row, col)[0];
////				m2.at<Vec3b>(row, col)[1] = 255 - dst.at<Vec3b>(row, col)[1];
////				m2.at<Vec3b>(row, col)[2] = 255 - dst.at<Vec3b>(row, col)[2];
////			}
////		}
////	}
////
////	imshow("duotongdao fanse", m2);
////
////	waitKey(0);
////
////	system("pause");
////	return 0;
////}
