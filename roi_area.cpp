///////说是任意形状，但其实还是自定义的多边形
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
////方法4，假如区域边界为轮廓，使用掩模图像中画轮廓，使用漫水填充算法将几何图形内部的值设置为255
//int main20()
//{
//	Mat image = imread("D:\\样品图片\\sample1\\ng\\5.JPG");
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
//	//漫水填充
//	//pi的值表示为 v(pi),if  v(seed)-loDiff<v(pi)<v(seed)+upDiff,将pi的值设置为newVal
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
	//读入源图像 20
	Mat inImg = imread("D:\\样品图片\\sample1\\ng\\14.JPG", 0); 
	imshow("input image", inImg); 
	Mat inImgTemp = inImg.clone();//不要直接在源图像上进行操作 
	
	//寻找轮廓(我们需要找到最外层轮廓) 
	std::vector<std::vector<Point>> contours; //向量内 每个元素保存了 一组由连续的Point点构成的点集的向量，每一组Point点集就是一个轮廓。 
	std::vector<Vec4i> hierarchy;//图的拓扑结构 第i个轮廓的后一个轮廓、前一个轮廓、父轮廓、内嵌轮廓的索引编号。 
	findContours(inImgTemp, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point()); //Point偏移量，所有的轮廓信息相对于原始图像对应点的偏移量 
	
	//获取（第1个）外接矩形的4个顶点坐标 
	RotatedRect rectPoint = minAreaRect(contours[3]); 
	Point2f fourPoint[4];//定义一个存储以上4个点的坐标的变量 
	rectPoint.points(fourPoint);//将rectPoint变量中存储的坐标值 放到fourPoint的数组中 
	int minX = fourPoint[0].x; 
	int minY = fourPoint[0].y; 
	int maxX = fourPoint[0].x; 
	int maxY = fourPoint[0].y; 
	
	//输出ROI矩形四个点的坐标和并找到X,Y坐标的最大/最小值，即确定了矩形ROI区域 
	for (int i = 0; i < contours.size(); i++)//遍历每一个轮廓 
	{ 
		//获取（第i+1个）外接矩形的4个顶点坐标 
		RotatedRect rectPoint = minAreaRect(contours[i]); 
		Point2f fourPoint[4];//定义一个存储以上4个点的坐标的变量 
		rectPoint.points(fourPoint);//将rectPoint变量中存储的坐标值 放到fourPoint的数组中 
		
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
	std::cout << "ROI区域在源图像的左上角坐标为： " << "minX = " << minX << " , " << "minY = " << minY << std::endl; 
	std::cout << "ROI区域的宽度和高度为： " << "width = " << width << " , " << "height =" << height << std::endl; 
	
	//对源图像ROI区域进行裁剪 
	Mat roiImg = inImg(Rect(minX, minY, width, height)); //提取的关键就是Rect(minX, minY, width, height)，其中minX, minY表示感兴趣区域的左上角位置，后面的width, height表示感兴趣部分的宽度和高度 
	imshow("裁剪后的ROI图片", roiImg); 

	waitKey(0); 
	return 0; 
}