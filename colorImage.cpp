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
//	//OpenCV��ͨ����BGR ���� RGB,˳��Ҫע��
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
//	imshow("�ϲ���", fin_img);
//
//
//	waitKey(0);
//
//	system("pause");
//	return 0;
//}
///*
//Ϊʲô��ʾ�ĵ�ͨ��ͼ���ǻҶ�ͼ��
//�ú����õ�ֻ��һ��ͨ����B��G��R�����ǻҶȵģ�Ҫ�õ�ֻ��һ����ɫ�ĵ�ͨ��ͼ��ֻ��ͨ������ÿһ�����أ�����������ͨ������Ϊ0.
//
//��ͨ������ֻ��һ��ɫ��ͨ�������������Ǻ���̵Ļ������ģ�����ȡֵ��Χ���ǴӰ�������
//����ν�ĻҶȣ����ϸ���˵��ͨ��ͼ����ǻҶ�ͼ��
//
//��ɫͼ��һ������ͨ��ͼ��24λ����һ��������Ҫ3��ֵ����ʾ�ֱ���0-255�����磨255,178,233����
//�㵥ͨ����8λ��ֻ�ܱ�ʾһ��ֵ����Χ0-255�����Զ��ǻҶ�ͼ��
//*/
//
//
//
////int main()
////{
////	//�����ɫͼ��
////	Mat img = imread("D:\\newSample\\0619\\32.jpg");
////	Mat dst = imread("D:\\newSample\\0619\\37-2.jpg");
////	imshow("ԭͼ", img);
////	int rows = img.rows;
////	int cols = img.cols;
////	//���ɺ�imgͬ����С�Ŀհ׻Ҷ�ͼ��
////	Mat grayImg = Mat(rows, cols, CV_8UC3);
////	//for (int i = 0; i < rows; i++)
////	//{
////	//	for (int j = 0; j < cols; j++)
////	//	{
////	//		////��ɫͼ���ȡ����������
////	//		//Vec3b pix = img.at<Vec3b>(i, j);
////	//		////��ȡ��RGB������ֵ��
////	//		//uchar B = pix[0];
////	//		//uchar G = pix[1];
////	//		//uchar R = pix[2];
////	//		////����ʹ������ķ���
////	//		////uchar B = img.at<Vec3b>(i, j)[0];
////	//		////uchar G = img.at<Vec3b>(i, j)[1];
////	//		////uchar G = img.at<Vec3b>(i, j)[2];
////	//		////����Ҷ�ֵ��Ȼ��ֵ���Ҷ�ͼ�е�����
////	//		////grayImg.at<uchar>(i, j) = R * 0.299 + G * 0.587 + B * 0.114;//�Ҷ���������ѧ��ʽ
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
////	//imshow("��ͨ��", grayImg);
////
////	//imshow("R", img.at<Vec3b>[0]);
////
////	//imshow("�Ҷ�ͼ", grayImg);
////	waitKey(0);
////
////	system("pause");
////	return 0;
////}