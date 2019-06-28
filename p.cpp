//
//
//bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
//{
//	bool  m_resultDetectCom = 0;
//	//// 比较法识别缺陷代码  
//
//	// 计算源图像及待检测图像的边缘图像
//	int  safePix = 9;      // 安全像素个数    
//	int  numModel = 5;     // 扫描模板大小  
//	int dataSafe = int(float(numModel*numModel) / 2);
//	//int grayTh = int(255 / 3);  // 计算图像边缘阈值  
//	int grayTh_1 = 50;
//	int grayTh_2 = 30;
//	int  numDetectTh = detectThr;   // 允许不同像素个数  
//
//	//// 截图待检测图像  
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//
//	//平移之后图像大小不同，但是这里处理的是变换后的图像，需要修改？？？
//
//
//	///////////////////////////////////////////////
//	int offset = 1;  // 求边界偏移量
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//
//	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//
//	ROIComEdge(detectImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//	//imshow("ok边缘图", edgeImgSrc);
//
//	////////////////////////////////////////////////
//	// 计算图像边缘  
//	ROIComEdge(srcImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
//	//imshow("ng边缘图", edgeImgDetect);
//	////////////////////////////////////////////////
//	// ---------- 方法一 两图的边缘图像相减 ----------
//	// --- 在边缘位置设置安全范围，留下不同的像素点  
//	// --- 用5*5模板去扫描， 
//	// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//	// --- 像素个数小于10，去除，计数加0     
//	// --- 计数值>0，则NG； 计数值=0, 则OK     
//	////////////////////////////////////////////////
//	// 1 沿源图像边缘区域设置安全范围
//	// 把边缘图像变成二值化图像   
//	Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
//	for (int i = 1; i < rowe; i++)
//	{
//		for (int j = 1; j < cole; j++)
//		{
//			if (edgeImgSrc.at <uchar>(i, j) > 0)
//			{
//				edgeImgSrcTh.at <uchar>(i, j) = 255;
//			}
//			if (edgeImgDetect.at <uchar>(i, j) > 0)
//			{
//				edgeImgDetectTh.at <uchar>(i, j) = 255;
//			}
//		}
//	}
//	////////////////////////////////////////////////
//	// 用膨胀法，扩展边缘亮区域
//	//获取自定义核
//	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//膨胀操作
//	Mat edgeImgSafe;
//	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//	// 反色，且归一化到[0, 1]; 
//	edgeImgSafe = (255 - edgeImgSafe) / 255;
//
//	////////////////////////////////////////////////
//	// 2 两幅边缘图像相减
//	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	imshow("相减结果", edgeImgSub);
//	//waitKey(0);
//
//	////////////////////////////////////////////////
//	// 用5*5模板去扫描， 
//	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//	int resultNum = 0;
//	int dataTem = 0;
//	int dataZong = 0;
//	int dataNum = 0;
//
//	//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
//	for (int i = numModel; i < rowe - numModel; i++)
//	{
//		for (int j = numModel; j < cole - numModel; j++)
//		{
//			dataTem = 0;
//			dataZong = 0;
//			dataNum = 0;
//			for (int m = 0; m < numModel; m++)
//			{
//				for (int n = 0; n < numModel; n++)
//				{
//					dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//					if (dataTem > 0)
//					{
//						dataZong = dataZong + 1;
//					}
//				}
//			}
//			if (dataZong > dataSafe)
//			{
//				//只要有不同，都会标出来的，而且不只是它们不同的地方，最主要是边界，边界没重合，有红点，那就表示坏片。
//				//resultImg.at<uchar>(i, j) = 255;
//				resultImg.at<Vec3b>(i, j)[0] = 0;
//				resultImg.at<Vec3b>(i, j)[1] = 0;
//				resultImg.at<Vec3b>(i, j)[2] = 255;
//
//				//showImg.at<Vec3b>(m, n)[2] = 255;
//				resultNum++;
//			}
//		}
//	}
//	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
//	imshow("滤波结果", resultImg);   ///滤波结果其实保留的是原图， 然后与detect图重合的部分不显示
//	//waitKey(0);


//bool  DistRectDetectOne(Mat &srcImg, int detectThreshold, int detectDirection)
//{
//	Point2f point4Ver[4];      //定义4个点的数组
//
//	Point  rectLTPoint;
//	rectLTPoint.x = int(point4Ver[1].x);
//	rectLTPoint.y = int(point4Ver[1].y); 
//	
//	// 测距为真，检测直线或圆并测距 
//
//	float atLine = 0.0, btLine = 0.0, ctLine = 0.0;
//
//	bool mLineTest = 1;
//
//	int rectRotAngle = 0;
//	float  rectAngle = rectRotAngle * 2 * 3.141592654 / 360;
//	
//	// 检测直线
//	mLineTest = LineDetectMethod(srcImg, detectThreshold, detectDirection, atLine, btLine, ctLine);
//
//	if (mLineTest == 0)
//	{
//		// 未检测到直线，画方框
//		return false;
//	}
//	else
//	{
//		// 绘制直线
//		Point2f  onePoint2f, twoPoint2f;
//		Point   onePoint, twoPoint;
//		float   edgePoint = 5.0;
//		switch (detectDirection)
//		{
//		case 0:  //从左到右
//			// Point One  
//			onePoint2f.x = point4Ver[1].x + ctLine*cos(rectAngle);
//			onePoint2f.y = point4Ver[1].y + ctLine*sin(rectAngle);
//			// Point Two
//			twoPoint2f.x = point4Ver[0].x + ctLine*cos(rectAngle);
//			twoPoint2f.y = point4Ver[0].y + ctLine*sin(rectAngle);
//			if (onePoint2f.x > point4Ver[2].x - edgePoint || twoPoint2f.x > point4Ver[3].x - edgePoint){
//				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
//				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
//				return false;
//			}
//			else
//			{
//				// 中心点
//				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
//				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
//				onePoint.x = int(onePoint2f.x);
//				onePoint.y = int(onePoint2f.y);
//				twoPoint.x = int(twoPoint2f.x);
//				twoPoint.y = int(twoPoint2f.y);
//				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
//				break;
//			}
//		case 1:  //从右到左
//			onePoint2f.x = point4Ver[1].x + ctLine*cos(rectAngle);
//			onePoint2f.y = point4Ver[1].y + ctLine*sin(rectAngle);
//			// Point Two
//			twoPoint2f.x = point4Ver[0].x + ctLine*cos(rectAngle);
//			twoPoint2f.y = point4Ver[0].y + ctLine*sin(rectAngle);
//			if (onePoint2f.x > point4Ver[2].x - edgePoint || twoPoint2f.x > point4Ver[3].x - edgePoint)
//			{
//				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
//				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
//				return false;
//			}
//			else{
//				// 中心点
//				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
//				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
//				onePoint.x = int(onePoint2f.x);
//				onePoint.y = int(onePoint2f.y);
//				twoPoint.x = int(twoPoint2f.x);
//				twoPoint.y = int(twoPoint2f.y);
//				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
//				break;
//			}
//		case 2:  
//			//从上到下
//			onePoint2f.x = point4Ver[1].x - ctLine*sin(rectAngle);
//			onePoint2f.y = point4Ver[1].y + ctLine*cos(rectAngle);
//			
//			// Point Two
//			twoPoint2f.x = point4Ver[2].x - ctLine*sin(rectAngle);
//			twoPoint2f.y = point4Ver[2].y + ctLine*cos(rectAngle);
//			if (onePoint2f.y > point4Ver[0].y - edgePoint || onePoint2f.y > point4Ver[3].y - edgePoint)
//			{
//				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
//				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
//				return false;
//			}
//			else
//			{
//				// 中心点
//				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
//				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
//				onePoint.x = int(onePoint2f.x);
//				onePoint.y = int(onePoint2f.y);
//				twoPoint.x = int(twoPoint2f.x);
//				twoPoint.y = int(twoPoint2f.y);
//				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
//				break;
//			}
//		case 3:  
//			//从下到上
//			onePoint2f.x = point4Ver[1].x - ctLine*sin(rectAngle);
//			onePoint2f.y = point4Ver[1].y + ctLine*cos(rectAngle);
//			// Point Two
//			twoPoint2f.x = point4Ver[2].x - ctLine*sin(rectAngle);
//			twoPoint2f.y = point4Ver[2].y + ctLine*cos(rectAngle);
//			if (onePoint2f.y > point4Ver[0].y - edgePoint || onePoint2f.y > point4Ver[3].y - edgePoint)
//			{
//				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
//				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
//				return false;
//			}
//			else
//			{
//				// 中心点
//				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
//				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
//				onePoint.x = int(onePoint2f.x);
//				onePoint.y = int(onePoint2f.y);
//				twoPoint.x = int(twoPoint2f.x);
//				twoPoint.y = int(twoPoint2f.y);
//				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
//				break;
//			}
//		default:
//			break;
//		}
//		return  true;
//	}
//}
//
////检测直线只能返回true， 或者false， 并且有方向
//bool  LineDetectMethod(Mat &srcImg, int detectThreshold, int detectDirection, float &aLine, float &bLine, float &cLine)
//{
//	const int grayValThr = 8;   //////////////////
//	const int pixelSet = detectThreshold;
//	int row = srcImg.rows;
//	int col = srcImg.cols;
//	Mat srcGray = srcImg;
//	int i = 0, j = 0;
//	//cvtColor(srcImg, srcGray, CV_BGR2GRAY);  
//	//srcGray = srcImg;  
//
//	// 左右
//	if (detectDirection == 0 || detectDirection == 1)
//	{
//		// 找每列像素值总的变化值  
//		vector<int>  grayVerdiff(col);
//		for (j = 0; j < col; j++)
//		{
//			grayVerdiff[j] = 0;   // 初始化为0
//		}
//		for (i = 0; i < row; i++)
//		{
//			for (j = 1 + detectThreshold; j < col; j++)
//			{
//				grayVerdiff[j] += abs(srcGray.at<uchar>(i, j) - srcGray.at<uchar>(i, j - 1 - detectThreshold));
//			}
//		}
//		for (j = 0; j < col; j++)
//		{
//			//grayVerdiff[j] = int(float(grayVerdiff[j]) / float(row));
//			grayVerdiff[j] = int(float(grayVerdiff[j]) / float(row) + 0.5);
//		}
//		int xypix = 1;
//		int xypixFirst = 1;
//		int xypixSecond = 1;
//		int gerrMax = 0;
//		int gerrMaxFirst = 0;
//		int gerrMaxSecond = 0;
//		int js = 1;
//		int jsFirst = 1;
//		int jsSecond = 1;
//		for (js = 1; js < col; js++)
//		{
//			if (gerrMax < grayVerdiff[js])
//			{
//				gerrMax = grayVerdiff[js];
//				xypix = js;
//			}
//		}
//		if (gerrMax < grayValThr)
//		{
//			return false;
//		}
//
//		for (jsFirst = 1; jsFirst < xypix - pixelSet; jsFirst++)
//		{
//			if (gerrMaxFirst <= grayVerdiff[jsFirst] && grayVerdiff[jsFirst] < gerrMax)
//			{
//				gerrMaxFirst = grayVerdiff[jsFirst];
//				xypixFirst = jsFirst;
//			}
//		}
//		for (jsSecond = col - 1; jsSecond > xypix + pixelSet; jsSecond--)
//		{
//			if (gerrMaxSecond < grayVerdiff[jsSecond] && grayVerdiff[jsSecond] < gerrMax)
//			{
//				gerrMaxSecond = grayVerdiff[jsSecond];
//				xypixSecond = jsSecond;
//			}
//		}
//		if (detectDirection == 0)  		// 从左到右  
//		{
//			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixFirst;
//			}
//			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixSecond;
//			}
//		}
//		else if (detectDirection == 1)  // 从右到左 
//		{
//			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixFirst;
//			}
//			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixSecond;
//			}
//		}
//		aLine = 0;
//		bLine = -1;
//		cLine = xypix;
//		//// 找中心点  
//		//xCenterPoint = int(float(row) / 2);
//		//yCenterPoint = xypix;
//		return true;
//	}
//
//	// 上下边缘  
//	else if (detectDirection == 2 || detectDirection == 3)
//	{
//		// 找每列像素值总的变化值  
//		vector<int>  grayVerdiff(row);
//		for (i = 0; i < row; i++)
//		{
//			grayVerdiff[i] = 0;   // 初始化为0
//		}
//		for (i = 1 + detectThreshold; i < row; i++)
//		{
//			for (j = 0; j < col; j++)
//			{
//				grayVerdiff[i] += abs(srcGray.at<uchar>(i, j) - srcGray.at<uchar>(i - 1 - detectThreshold, j));
//			}
//		}
//		for (i = 0; i < row; i++)
//		{
//			//grayVerdiff[i] = int(float(grayVerdiff[i]) / float(col));
//			grayVerdiff[i] = int(float(grayVerdiff[i]) / float(col) + 0.5);
//		}
//
//		int xypix = 1;
//		int xypixFirst = 1;
//		int xypixSecond = 1;
//		int gerrMax = 0;
//		int gerrMaxFirst = 0;
//		int gerrMaxSecond = 0;
//		int js = 1;
//		int jsFirst = 1;
//		int jsSecond = 1;
//		for (js = 1; js < row; js++)
//		{
//			if (gerrMax < grayVerdiff[js])
//			{
//				gerrMax = grayVerdiff[js];
//				xypix = js;
//			}
//		}
//		if (gerrMax < grayValThr)
//		{
//			return false;
//		}
//
//		for (jsFirst = 1; jsFirst < xypix - pixelSet; jsFirst++)
//		{
//			if (gerrMaxFirst <= grayVerdiff[jsFirst] && grayVerdiff[jsFirst] < gerrMax)
//			{
//				gerrMaxFirst = grayVerdiff[jsFirst];
//				xypixFirst = jsFirst;
//			}
//		}
//		for (jsSecond = row - 1; jsSecond > xypix + pixelSet; jsSecond--)
//		{
//			if (gerrMaxSecond <= grayVerdiff[jsSecond] && grayVerdiff[jsSecond] < gerrMax)
//			{
//				gerrMaxSecond = grayVerdiff[jsSecond];
//				xypixSecond = jsSecond;
//			}
//		}
//		if (detectDirection == 2)  //从上到下  
//		{
//			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixFirst;
//			}
//			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixSecond;
//			}
//		}
//		else if (detectDirection == 3)  // 从下到上  
//		{
//			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixFirst;
//			}
//			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
//			{
//				xypix = xypixSecond;
//			}
//		}
//		aLine = -1;
//		bLine = 0;
//		cLine = xypix;
//		//// 找中心点  
//		//yCenterPoint = int(float(col) / 2);
//		//xCenterPoint = xypix;
//		return true;
//	}
//}
//
//


////#include<iostream>
////#include <opencv2/core/core.hpp>
////#include <opencv2/highgui/highgui.hpp>
////using namespace cv;
////Mat& ScanImageAndReduceC(Mat& I) { // accept only char type matrices 
////	CV_Assert(I.depth() == CV_8U);
////	int channels = I.channels();
////	int nRows = I.rows;
////	int nCols = I.cols * channels;
////	if (I.isContinuous()) {
////		nCols *= nRows;
////		nRows = 1;
////	}
////	int i, j;
////	uchar* p;
////	for (i = 0; i < nRows; ++i) {
////		p = I.ptr<uchar>(i);
////		for (j = 0; j < nCols; ++j) {
////			if (p[j] <= 50){
////				p[j] = 255;
////			}
////		}
////	}
////	return I;
////}
//////p[j] = p[j] / 4;       //循环遍历，对每一个像素都做同样的操作，这里是变暗
////int main() {
////
////	// 读入一张图片（游戏原画）  
////	Mat img = imread("D:\\roiImgForTest\\5dstImage.jpg");
////	ScanImageAndReduceC(img);
////	// 创建一个名为 "游戏原画"窗口  
////	namedWindow("游戏原画");
////	// 在窗口中显示游戏原画  
////	imshow("游戏原画", img);
////
////	// 等待6000 ms后窗口自动关闭 
////	waitKey(60000);
////	//system("pause");
////	//return 0;
////}
//
//////鼠标放上就可以看到位置坐标
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
//#include <stdio.h>
//#include <cstdlib>
//
//using namespace std;
//using namespace cv;
//
//void my_mouse_callback(int event, int x, int y, int flags, void *param);
//
//CvPoint st_point;
//int blue = 0;
//int green = 0;
//int red = 0;
//CvFont font;
//
//int main(int argc, const char * argv[]) {
//	const char filename[] = "D:\\roiImgForTest\\5dstImage.jpg";
//
//	IplImage * image = cvLoadImage(filename);
//
//	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1, 1, 0, 2, 8);
//
//	cvNamedWindow("Lena");
//
//	cvSetMouseCallback("Lena", my_mouse_callback, (void *)image);
//
//	cvShowImage("Lena", image);
//
//	cvWaitKey(0);
//
//	cvReleaseImage(&image);
//
//	cvDestroyWindow("Lena");
//}
//
//void my_mouse_callback(int event, int x, int y, int flags, void *param)
//{
//	IplImage * image = (IplImage *)param;
//
//	switch (event) {
//		/*鼠标离开*/
//	case CV_EVENT_LBUTTONDOWN:
//	{
//		/*鼠标左键点击事件，记录点击的（x，y）*/
//		st_point.x = x;
//		st_point.y = y;
//		cout << "按下左键 ： " << " x = " << x << " y " << y << endl;
//		break;
//	}
//	case CV_EVENT_LBUTTONUP:
//	{
//		/*鼠标左键放开事件，读取当前点的像素值BGR*/
//		unsigned char * ptr = (uchar *)(image->imageData + st_point.x * image->widthStep);
//		blue = (int)(*(ptr + st_point.y));
//		green = (int)(*(ptr + st_point.y + 1));
//		red = (int)(*(ptr + st_point.y + 2));
//		cout << "抬起左键 ： " << " blue= " << blue << " green = " << green << " red =  " << red << endl;
//		char text[20] = "0";
//		sprintf(text, "(%d,%d,%d)", blue, green, red);
//		cout << "Text = " << text << endl;
//		cvPutText(image, text, st_point, &font, CV_RGB(0, 0, 0));
//		cvShowImage("Lena", image);
//		break;
//	}
//	default:
//		break;
//	}
//}