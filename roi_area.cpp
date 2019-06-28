///////˵��������״������ʵ�����Զ���Ķ����
//
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//#define WIDTH 256
//#define HEIGHT 256
//
////draw in gray image
//void draw_external_contour_gray(CvSeq *seq, IplImage* grayImage)
//{
//
//	if (seq->total < 2)
//	{
//		return;
//	}
//	CvPoint* prePoint = (CvPoint*)cvGetSeqElem(seq, 0);
//	CvPoint* lastPoint = (CvPoint*)cvGetSeqElem(seq, seq->total - 1);
//	cvLine(grayImage, *prePoint, *lastPoint, cvScalar(255), 1, 8, 0);
//	for (int i = 1; i<seq->total; i++) {
//		CvPoint *p;
//		p = (CvPoint*)cvGetSeqElem(seq, i);
//
//		cvLine(grayImage, *prePoint, *p, cvScalar(255), 1, 8, 0);
//		//cvSet2D(img, p->y, p->x, color);
//		*prePoint = *p;
//	}
//
//}
////����4����������߽�Ϊ������ʹ����ģͼ���л�������ʹ����ˮ����㷨������ͼ���ڲ���ֵ����Ϊ255
//int main20()
//{
//	Mat image = imread("D:\\��ƷͼƬ\\sample1\\ng\\5.JPG");
//
//	Mat mask = Mat::zeros(image.size(), CV_8UC1);
//	CvMemStorage* storage = cvCreateMemStorage(0);
//	//  CvSeq* contour = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), storage);
//
//	CvSeqWriter writer;
//	cvStartWriteSeq(CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), storage, &writer);
//
//	CvPoint p1 = { 25, 60 };  CvPoint p2 = { 50, 110 };  CvPoint p4 = { 100, 60 }; CvPoint p3 = { 100, 110 }; CvPoint p5 = { 50, 10 };
//	CV_WRITE_SEQ_ELEM(p1, writer);
//	CV_WRITE_SEQ_ELEM(p2, writer);
//	CV_WRITE_SEQ_ELEM(p3, writer);
//	CV_WRITE_SEQ_ELEM(p4, writer);
//	CV_WRITE_SEQ_ELEM(p5, writer);
//
//	cvFlushSeqWriter(&writer);
//	CvSeq* contour = cvEndWriteSeq(&writer);
//	printf("contour.size=%d", contour->total);
//	IplImage* imask = &IplImage(mask);
//	IplImage* iimage = &IplImage(image);
//
//	draw_external_contour_gray(contour, imask);
//
//	Point seed;
//	seed.x = 35;
//	seed.y = 60;
//	//��ˮ���
//	//pi��ֵ��ʾΪ v(pi),if  v(seed)-loDiff<v(pi)<v(seed)+upDiff,��pi��ֵ����ΪnewVal
//	floodFill(mask, seed, 255, NULL, cvScalarAll(0), cvScalarAll(0), CV_FLOODFILL_FIXED_RANGE);
//
//	Mat maskImage;
//	image.copyTo(maskImage, mask);
//	imshow("mask", maskImage);
//	cvShowImage("imask", imask);
//	waitKey();
//	return 0;
//}


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream> 
//#include <cvInclude.h> 

using namespace std; 
using namespace cv;

int main20(void) { 
	//����Դͼ�� 20
	Mat inImg = imread("D:\\��ƷͼƬ\\sample1\\ng\\14.JPG", 0); 
	imshow("input image", inImg); 
	Mat inImgTemp = inImg.clone();//��Ҫֱ����Դͼ���Ͻ��в��� 
	
	//Ѱ������(������Ҫ�ҵ����������) 
	std::vector<std::vector<Point>> contours; //������ ÿ��Ԫ�ر����� һ����������Point�㹹�ɵĵ㼯��������ÿһ��Point�㼯����һ�������� 
	std::vector<Vec4i> hierarchy;//ͼ�����˽ṹ ��i�������ĺ�һ��������ǰһ������������������Ƕ������������š� 
	findContours(inImgTemp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point()); //Pointƫ���������е�������Ϣ�����ԭʼͼ���Ӧ���ƫ���� 
	
	//��ȡ����1������Ӿ��ε�4���������� 
	RotatedRect rectPoint = minAreaRect(contours[3]); 
	Point2f fourPoint[4];//����һ���洢����4���������ı��� 
	rectPoint.points(fourPoint);//��rectPoint�����д洢������ֵ �ŵ�fourPoint�������� 
	int minX = fourPoint[0].x; 
	int minY = fourPoint[0].y; 
	int maxX = fourPoint[0].x; 
	int maxY = fourPoint[0].y; 
	
	//���ROI�����ĸ��������Ͳ��ҵ�X,Y��������/��Сֵ����ȷ���˾���ROI���� 
	for (int i = 0; i < contours.size(); i++)//����ÿһ������ 
	{ 
		//��ȡ����i+1������Ӿ��ε�4���������� 
		RotatedRect rectPoint = minAreaRect(contours[i]); 
		Point2f fourPoint[4];//����һ���洢����4���������ı��� 
		rectPoint.points(fourPoint);//��rectPoint�����д洢������ֵ �ŵ�fourPoint�������� 
		
		for (int j = 0; j < 4; j++) { 
			if (fourPoint[j].x < minX) { 
				minX = fourPoint[j].x; 
			} 
			if (fourPoint[j].x > maxX) { 
				maxX = fourPoint[j].x; 
			} 
			if (fourPoint[j].y < minY) { 
				minY = fourPoint[j].y; 
			} 
			if (fourPoint[j].y > maxY) { 
				maxY = fourPoint[j].y; 
			} 
		} 
	} 
	
	int width = maxX - minX; 
	int height = maxY - minY; 
	std::cout << "ROI������Դͼ������Ͻ�����Ϊ�� " << "minX = " << minX << " , " << "minY = " << minY << std::endl; 
	std::cout << "ROI����Ŀ�Ⱥ͸߶�Ϊ�� " << "width = " << width << " , " << "height =" << height << std::endl; 
	
	//��Դͼ��ROI������вü� 
	Mat roiImg = inImg(Rect(minX, minY, width, height)); //��ȡ�Ĺؼ�����Rect(minX, minY, width, height)������minX, minY��ʾ����Ȥ��������Ͻ�λ�ã������width, height��ʾ����Ȥ���ֵĿ�Ⱥ͸߶� 
	imshow("�ü����ROIͼƬ", roiImg); 

	waitKey(0); 
	return 0; 
}