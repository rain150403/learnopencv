/////*
////https://www.cnblogs.com/jukan/p/7815722.html
////https://blog.csdn.net/guanzhen3657/article/details/81138868
////���ֳ�����ͼ����ǿ�㷨
////1.ֱ��ͼ���⻯
////2.����ͼ����ǿ�㷨
////3.ָ��ͼ����ǿ�㷨
////4.��masaic�㷨�������ˣ�
////5.�ع�������⴦��
////6.�߷����
////7.Laplace����ͼ����ǿ
////8.gammaУ��
////*/
////
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>      
////#include <opencv2/imgproc/imgproc.hpp>  
////
////using namespace cv;
////
////int main22(int argc, char *argv[])
////{  //22
////	Mat image = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG");
////	Mat imageGamma(image.size(), CV_32FC3);
////	for (int i = 0; i < image.rows; i++)
////	{
////		for (int j = 0; j < image.cols; j++)
////		{
////			imageGamma.at<Vec3f>(i, j)[0] = (image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0])*(image.at<Vec3b>(i, j)[0]);
////			imageGamma.at<Vec3f>(i, j)[1] = (image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1])*(image.at<Vec3b>(i, j)[1]);
////			imageGamma.at<Vec3f>(i, j)[2] = (image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2])*(image.at<Vec3b>(i, j)[2]);
////		}
////	}
////	//��һ����0~255    
////	normalize(imageGamma, imageGamma, 0, 255, CV_MINMAX);
////	//ת����8bitͼ����ʾ    
////	convertScaleAbs(imageGamma, imageGamma);
////	imshow("ԭͼ", image);
////	imshow("٤��任ͼ����ǿЧ��", imageGamma);
////	waitKey();
////	return 0;
////}
//
//
////
////#include <opencv2/highgui/highgui.hpp>      
////#include <opencv2/imgproc/imgproc.hpp>  
////
////using namespace cv;
////
////int main(int argc, char *argv[])
////{
////	Mat image = imread("D:\\roiImgForTest\\diff_dst.JPG");
////	Mat imageLog(image.size(), CV_32FC3);
////	for (int i = 0; i < image.rows; i++)
////	{
////		for (int j = 0; j < image.cols; j++)
////		{
////			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
////			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
////			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
////		}
////	}
////	//��һ����0~255    
////	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
////	//ת����8bitͼ����ʾ    
////	convertScaleAbs(imageLog, imageLog);
////	imshow("Soure", image);
////	imshow("after", imageLog);
////	waitKey();
////	return 0;
////}
//////
//
//
//#include <opencv2/highgui/highgui.hpp>      
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
//using namespace cv;
//////һƬ�ף�Ч������
//int main22(int argc, char *argv[])
//{
//	Mat image = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG", 1);
//	if (image.empty())
//	{
//		std::cout << "��ͼƬʧ��,����" << std::endl;
//		return -1;
//	}
//	imshow("ԭͼ��", image);
//	Mat imageEnhance;
//	Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
//	filter2D(image, imageEnhance, CV_8UC3, kernel);
//	imshow("������˹����ͼ����ǿЧ��", imageEnhance);
//	waitKey();
//	return 0;
//}
//
//
//
//#include <opencv2/highgui/highgui.hpp>      
//#include <opencv2/imgproc/imgproc.hpp>  
//#include <iostream>  
//
//using namespace cv;
//
//int main22(int argc, char *argv[])
//{
//	Mat image = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG", 1);
//	if (image.empty())
//	{
//		std::cout << "��ͼƬʧ��,����" << std::endl;
//		return -1;
//	}
//	imshow("ԭͼ��", image);
//	Mat imageRGB[3];
//	split(image, imageRGB);
//	for (int i = 0; i < 3; i++)
//	{
//		equalizeHist(imageRGB[i], imageRGB[i]);
//	}
//	merge(imageRGB, 3, image);
//	imshow("ֱ��ͼ���⻯ͼ����ǿЧ��", image);
//	waitKey();
//	return 0;
//}
//////////////////////////////////////////////////////////////////////

/////////����ͼ��Աȶ�////////////
//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//double alpha; /**< ���ƶԱȶ� */
//int beta;  /**< �������� */
//
//////�� = 1.2�� �� = 30
//int main22(int argc, char** argv)
//{
//	/// �����û��ṩ��ͼ��
//	Mat image = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG");
//	Mat new_image = Mat::zeros(image.size(), image.type());
//
//	/// ��ʼ��
//	cout << " Basic Linear Transforms " << endl;
//	cout << "-------------------------" << endl;
//	cout << "* Enter the alpha value [1.0-3.0]: ";
//	cin >> alpha;
//	cout << "* Enter the beta value [0-100]: ";
//	cin >> beta;
//
//	/// ִ������ new_image(i,j) = alpha*image(i,j) + beta
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//			}
//		}
//	}
//
//	/// ��������
//	namedWindow("Original Image", 1);
//	namedWindow("New Image", 1);
//
//	/// ��ʾͼ��
//	imshow("Original Image", image);
//	imshow("New Image", new_image);
//
//	/// �ȴ��û�����
//	waitKey();
//	return 0;
//}


//// ���ͼƬ���ȺͶԱȶ�.cpp: �������̨Ӧ�ó������ڵ㡣 // 
//
//#include "opencv2/opencv.hpp" 
//#include "opencv2/highgui/highgui.hpp" 
//
//using namespace std; 
//using namespace cv; 
//
//int main22() { 
//	Mat src,dest; src = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG"); 
//	namedWindow("src", CV_WINDOW_AUTOSIZE); 
//	imshow("src", src); 
//	dest = Mat::zeros(src.size(), src.type()); 
//	int width = src.cols; 
//	int height = src.rows; 
//	int channels = src.channels(); 
//	int alphe = 1.8; //(alphe > 1) 
//	int beta = -30;// �����Աȶ�Խ�� 
//	Mat m1; 
//	src.convertTo(m1, CV_32F); //��ԭʼͼƬ���ݣ�CV_8U���ͣ�ת����CV_32���ͣ�����߲����ľ��� 
//	for (int row = 0; row < height;row++) { 
//		for (int col = 0; col < width; col++) { 
//			if (channels == 3) { //����3ͨ�� 
//				float b = m1.at<Vec3f>(row,col)[0]; 
//				float g = m1.at<Vec3f>(row, col)[1]; 
//				float r = m1.at<Vec3f>(row, col)[2]; 
//				
//				dest.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(alphe * b + beta); 
//				dest.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alphe * g + beta); 
//				dest.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alphe * r + beta); 
//			} 
//			else if (channels == 1){ //���ڵ�ͨ�� 
//				int pix = src.at<uchar>(row, col); 
//				dest.at<uchar>(row,col) = saturate_cast<uchar>(alphe * pix + beta); 
//			} 
//		} 
//	} 
//	
//	namedWindow("change"); 
//	imshow("change",dest); 
//	waitKey(0); 
//	return 0; 
//}


//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//
//using namespace cv;
//
////ȫ�ֱ�������
//Mat srcImage;
//Mat dstImage;
//int contrastValue;
//int brightValue;
////const string WINDOW_NAME = "contrast&brightValue";
///*******�ı�ͼ��ԱȶȺ�����ֵ�Ļص�����*******/
//void on_change(int, void*)
//{
//	namedWindow("contrast&brightValue", 1);
//	for (int i = 0; i < srcImage.rows; i++)
//	{
//		for (int j = 0; j < srcImage.cols; j++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				dstImage.at<Vec3b>(i, j)[c] =
//					saturate_cast<uchar>((contrastValue * 0.01) * (srcImage.at<Vec3b>(i, j)[c]) + brightValue);
//			}
//		}
//	}
//	imshow("contrast&brightValue", dstImage);
//}
//
////�о��Աȶȱ仯�����ȱ仯��һ���ģ�����������ǿ���ֶ�
//
//int main22()
//{
//	srcImage = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG");
//	dstImage = Mat::zeros(srcImage.size(), srcImage.type());
//	contrastValue = 80;//�趨�Աȶȳ�ֵ
//	brightValue = 80;//�趨�����ȵĳ�ֵ
//
//	namedWindow("contrast&brightValue", 1);
//
//	//�����켣��
//	createTrackbar("�Աȶ�: ", "contrast&brightValue", &contrastValue, 300, on_change);//�ڶ�����������Ϊ���ģ��ò���Ϊ����ʱ���ҵ����в��ɹ�
//	createTrackbar("����: ", "contrast&brightValue", &brightValue, 200, on_change);
//
//	//���лص�������ʼ��
//	on_change(contrastValue, 0);
//	on_change(brightValue, 0);
//
//	waitKey(0);
//	return 0;
//}