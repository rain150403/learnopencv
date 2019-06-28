//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//void GammaCorrection(Mat &src, Mat &dst, float fGamma);
//
//int main(){
//	Mat src = imread("D:\\newSample\\0513\\b\\20.JPG");
//	Mat dst;
//	
//	GammaCorrection(src, dst, 1/2.4);
//
//	imshow("JIEGUO", dst);
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
////Gamma灰度矫正
//void GammaCorrection(Mat &src, Mat &dst, float fGamma)
//{
//	CV_Assert(src.data);
//
//	CV_Assert(src.depth() != sizeof(uchar));
//
//	unsigned char lut[256];
//
//	for (int i = 0; i < 256; i++)
//	{
//		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
//	}
//
//	dst = src.clone();
//	const int channels = dst.channels();
//	switch (channels)
//	{
//	case 1:
//	{
//		MatIterator_<uchar> it, end;
//		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
//		{
//			*it = lut[(*it)];
//		}
//		break;
//	}
//	case 3:
//	{
//		MatIterator_<Vec3b> it, end;
//		for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
//		{
//			(*it)[0] = lut[((*it)[0])];   ///LUT查找表
//			(*it)[1] = lut[((*it)[1])];
//			(*it)[2] = lut[((*it)[2])];
//		}
//		break;
//	}
//	}
//
//}
//
//
//
//
//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//#define NUM_COL 11  //二维数组的列， 每一个点缺陷信息的详细信息
//#define MINAREA 0   //面积小于该阈值的轮廓都要被删掉
//#define MAXAREA 2000   //面积大于该阈值的轮廓都要被删除
//
//RNG g_rng(12345);  //随机数生成器
//
//void morphOpen(Mat mor_input);
//
//int AreaLimit = 20;
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int blockSize = 5;
//
//void unevenLightCompensate(Mat &image, int blockSize);
//
//void GammaCorrection(Mat &src, Mat &dst, float fGamma);
//
//int main(){
//	Mat lightImg, thrImg;
//	Mat src = imread("D:\\newSample\\0513\\b\\20.JPG");
//
//	/*lightImg = src.clone();
//
//	unevenLightCompensate(lightImg, blockSize);
//	imshow("wuguang", lightImg);
//
//	threshold(lightImg, thrImg, 120, 255, CV_THRESH_BINARY_INV);
//	imshow("erzhihua", thrImg);*/
//
//	GammaCorrection(src, src, 1 / 2.4);
//
//	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
//
//	int g_nThresh = 20;
//	Mat canny_out;
//
//	vector<vector<Point> > g_vContours;
//	vector<Vec4i> g_vHierarchy;
//	int contour_num = 0;
//
//	vector<Rect> boundRect(g_vContours.size());
//
//	//调用canny算子检测边缘 
//	Canny(src, canny_out, g_nThresh, g_nThresh * 2, 3);
//	imshow("bianyuantu", canny_out);
//	imwrite("D:\\roiImgForTest\\huahen\\canny.jpg", canny_out);
//	waitKey(0);
//
//	ROIComDenoise(canny_out, canny_out, AreaLimit);
//	imshow("noNoise", canny_out);
//
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//	vector<vector<Point> >::iterator itc = g_vContours.begin();
//	while (itc != g_vContours.end()) {
//		if (itc->size() > MAXAREA) {
//			itc = g_vContours.erase(itc);
//		}
//		else if (itc->size()<MINAREA){
//			itc = g_vContours.erase(itc);
//		}
//		else {
//			++itc;
//		}
//	}
//
//	for (int i = 0; i < g_vContours.size(); i++) {
//
//		Scalar color = Scalar(0, 255, 0);
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//		imshow("drawing", drawing);
//		imwrite("D:\\roiImgForTest\\huahen\\drawing.jpg", drawing);
//
//		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
//		Point2f vertices[4];    //定义矩形的四个顶点
//		rect.points(vertices);   //计算矩形的四个顶点
//		for (int i = 0; i < 4; i++){
//			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//			imshow("juxing", src);
//			imwrite("D:\\roiImgForTest\\huahen\\juxing.jpg", src);
//		}	
//	}
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//// 去除孤立噪声点   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
//{
//	int RemoveCount = 0;
//	//新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
//	//初始化的图像全部为0，未检查  
//	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
//	//去除小连通区域的白色点  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (Src.at<uchar>(i, j) < 10)
//			{
//				PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
//			}
//		}
//	}
//
//	vector<Point2i>NeihborPos;//将邻域压进容器  
//	NeihborPos.push_back(Point2i(-1, 0));
//	NeihborPos.push_back(Point2i(1, 0));
//	NeihborPos.push_back(Point2i(0, -1));
//	NeihborPos.push_back(Point2i(0, 1));
//	//cout << "Neighbor mode: 8邻域." << endl;
//	NeihborPos.push_back(Point2i(-1, -1));
//	NeihborPos.push_back(Point2i(-1, 1));
//	NeihborPos.push_back(Point2i(1, -1));
//	NeihborPos.push_back(Point2i(1, 1));
//
//	int NeihborCount = 8;
//	int CurrX = 0, CurrY = 0;
//	//开始检测  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
//			{   //开始检查  
//				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
//				GrowBuffer.push_back(Point2i(j, i));
//				PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
//				int CheckResult = 0;
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					for (int q = 0; q < NeihborCount; q++)
//					{
//						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
//						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
//						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
//						{
//							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
//							{
//								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
//								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
//							}
//						}
//					}
//				}
//				if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
//					CheckResult = 2;
//				else
//				{
//					CheckResult = 1;
//					RemoveCount++;//记录有多少区域被去除  
//				}
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					CurrX = GrowBuffer.at(z).x;
//					CurrY = GrowBuffer.at(z).y;
//					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
//				}
//				//********结束该点处的检查**********    
//			}
//		}
//	}
//	//开始反转面积过小的区域    
//	for (int i = 0; i < Src.rows; ++i)
//	{
//		for (int j = 0; j < Src.cols; ++j)
//		{
//			if (PointLabel.at<uchar>(i, j) == 2)
//			{
//				Dst.at<uchar>(i, j) = 0;
//			}
//			else if (PointLabel.at<uchar>(i, j) == 3)
//			{
//				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
//
//			}
//		}
//	}
//}
//
//// 不均匀光照补偿
//void unevenLightCompensate(Mat &image, int blockSize)
//{
//	if (image.channels() == 3) cvtColor(image, image, 7);
//	double average = mean(image)[0];
//	int rows_new = ceil(double(image.rows) / double(blockSize));
//	int cols_new = ceil(double(image.cols) / double(blockSize));
//	Mat blockImage;
//	blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
//	for (int i = 0; i < rows_new; i++)
//	{
//		for (int j = 0; j < cols_new; j++)
//		{
//			int rowmin = i*blockSize;
//			int rowmax = (i + 1)*blockSize;
//			if (rowmax > image.rows) rowmax = image.rows;
//			int colmin = j*blockSize;
//			int colmax = (j + 1)*blockSize;
//			if (colmax > image.cols) colmax = image.cols;
//			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
//			double temaver = mean(imageROI)[0];
//			blockImage.at<float>(i, j) = temaver;
//		}
//	}
//	blockImage = blockImage - average;
//	Mat blockImage2;
//	resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
//	Mat image2;
//	image.convertTo(image2, CV_32FC1);
//	Mat dst = image2 - blockImage2;
//	dst.convertTo(image, CV_8UC1);
//}
//
//
////Gamma灰度矫正
//void GammaCorrection(Mat &src, Mat &dst, float fGamma)
//{
//	CV_Assert(src.data);
//
//	CV_Assert(src.depth() != sizeof(uchar));
//
//	unsigned char lut[256];
//
//	for (int i = 0; i < 256; i++)
//	{
//		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
//	}
//
//	dst = src.clone();
//	const int channels = dst.channels();
//	switch (channels)
//	{
//	case 1:
//	{
//		MatIterator_<uchar> it, end;
//		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
//		{
//			*it = lut[(*it)];
//		}
//		break;
//	}
//	case 3:
//	{
//		MatIterator_<Vec3b> it, end;
//		for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
//		{
//			(*it)[0] = lut[((*it)[0])];
//			(*it)[1] = lut[((*it)[1])];
//			(*it)[2] = lut[((*it)[2])];
//		}
//		break;
//	}
//	}
//
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <iostream>
////
////using namespace cv;
////using namespace std;
////
////#define SCALE 0.3
////#define NUM_COL 11  //二维数组的列， 每一个点缺陷信息的详细信息
////#define MINAREA 0   //面积小于该阈值的轮廓都要被删掉
////#define MAXAREA 2000   //面积大于该阈值的轮廓都要被删除
////
////Mat morph_out;
////
////RNG g_rng(12345);  //随机数生成器
////  // 成功  //并且已经加入代码里面
////void hough_line(Mat src_hough);
////void fanse(Mat dst);
////void morph(Mat mor_input);
////
////int AreaLimit = 20;
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
////
////int blockSize = 20;
////
////void unevenLightCompensate(Mat &image, int blockSize);
////
////int main(){
////	Mat lightImg, thrImg;
////	Mat src = imread("D:\\newSample\\0513\\b\\20.JPG");   
////	//D:\\waitDelete\\VS_project\\GetPlateArea\\GetPlateArea\\huahen.JPG
////	//D:\\roiImgForTest\\ngSave\\ng01.JPG
////	//D:\\roiImgForTest\\huahen\\8.jpg
////
////	//morph(src);
////
////	lightImg = src.clone();
////
////	unevenLightCompensate(lightImg, blockSize);
////	imshow("wuguang", lightImg);
////	//waitKey(0);
////
////	threshold(lightImg, thrImg, 100, 255, CV_THRESH_BINARY_INV);
////	imshow("erzhihua", thrImg);
////	//waitKey(0);
////
////	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
////
////	int g_nThresh = 20;
////	Mat canny_out;
////
////	vector<vector<Point> > g_vContours;
////	vector<Vec4i> g_vHierarchy;
////	int contour_num = 0;
////
////	Mat SrcImage_or;
////	CvSize src_sz;
////
////	//////////////////////////基本操作///////////////////////////////
////	////resize
////	//src_sz.width = src.rows * picture.scale;
////	//src_sz.height = SrcImage_origin.cols * picture.scale;
////	//SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
////	//resize(SrcImage_origin, SrcImage_or, src_sz, CV_INTER_CUBIC);
////
////	//imshow("原图", SrcImage_origin);
////
////	////单通道灰度化处理
////	//g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////	//cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
////
////	////创建二值化原图
////	//g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////	//threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
////
////	////显示二值化后的图片
////	//imshow("二值化", g_BinaryImage);
////
////	///////////////////////////////////////////////////////////////////////////////////////////////////////////
////	//double length = arcLength(g_vContours[i], true);  //计算封闭轮廓的周长或曲线的长度，默认closed
////	//double area = contourArea(g_vContours[i]);   //用于计算整个轮廓或部分轮廓的面积， 带符号的面积值表示方向
////
////	vector<Rect> boundRect(g_vContours.size());
////
////	Mat SrcImage;
////	Size sz;
////
////	//sz.width = dst.cols * SCALE;
////	//sz.height = dst.rows * SCALE;
////
////	//调用canny算子检测边缘 
////	Canny(thrImg, canny_out, g_nThresh, g_nThresh * 2, 3);
////	imshow("bianyuantu", canny_out);
////	imwrite("D:\\roiImgForTest\\huahen\\canny.jpg", canny_out);
////	waitKey(0);
////
////	ROIComDenoise(canny_out, canny_out, AreaLimit);
////	imshow("noNoise", canny_out);
////
////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
////
////	vector<vector<Point> >::iterator itc = g_vContours.begin();
////	while (itc != g_vContours.end()) {
////		if (itc->size() > MAXAREA) {   //itc->size()<MINAREA ||
////			itc = g_vContours.erase(itc);
////		}
////		else if (itc->size()<MINAREA){
////			itc = g_vContours.erase(itc);
////		}
////		else {
////			++itc;
////		}
////	}
////
////	for (int i = 0; i < g_vContours.size(); i++) {
////
////		//double tmparea = fabs(contourArea(g_vContours[i]));
////		//if (tmparea <= MINAREA)
////		//{
////		//	cvSeqRemove(contour, 0); //删除面积小于设定值的轮廓   
////		//	continue;
////		//}
////		//else
////		//{
////		//	liantong_all_area = liantong_all_area + tmparea;
////		//}
////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
////		Point2f vertices[4];    //定义矩形的四个顶点
////		rect.points(vertices);   //计算矩形的四个顶点
////		for (int i = 0; i < 4; i++){
////			cout << "顶点" << i << "坐标：" << vertices[i] << endl;
////			//////////////////////////////////////////////////////////////////////
////
////			///////////////////////////////////////////////////////////////////////
////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
////			imshow("juxing", src);
////			imwrite("D:\\roiImgForTest\\huahen\\juxing.jpg", src);
////		}
////
////		//因为cvPolyLine要求点集的输入类型是CvPoint**
////		//所以要把 CvPoint2D32f 型的 rect_pts0 转换为 CvPoint 型的 rect_pts
////		//并赋予一个对应的指针 *pt
////		//int npts = 4;  //一共有几个顶点，用于一次性画多边形
////		//CvPoint rect_pts[4], *pt = rect_pts; //四个顶点
////
////		int temp = 0;
////		int sum_rect_x = 0, sum_rect_y = 0;
////		int rect_height = 0, rect_width = 0;
////		int rect_area = 0;
////		int rect_all_area = 0;
////
////		cout << "编号：" << contour_num << "连通区域最小外接矩形顶点坐标分别为：" << endl;
////
////		//feature是一个二维数组，即缺陷的个数及每个缺陷的一些信息
////		int** feature = 0;
////		feature = new int*[130];
////		feature[contour_num] = new int[NUM_COL];
////
////		for (int i = 0; i < 4; i++){
////			feature[contour_num][i] = vertices[i].x;  //特征值数组第0-3个数
////			feature[contour_num][i + 4] = vertices[i].y;  //特征值数组第4-7个数
////
////			cout << "第" << i << "个顶点的坐标：" << vertices[i].x << ", " << vertices[i].y << endl;
////			sum_rect_x += vertices[i].x;
////			sum_rect_y += vertices[i].y;
////			rect_height = (int)sqrt((pow((vertices[0].x - vertices[1].x), 2) + pow((vertices[0].y - vertices[1].y), 2)));
////			rect_width = (int)sqrt((pow((vertices[0].x - vertices[3].x), 2) + pow((vertices[0].y - vertices[3].y), 2)));
////			if (rect_height < rect_width)
////			{
////				temp = rect_height;
////				rect_height = rect_width;
////				rect_width = temp;
////			}
////		}
////
////		rect_area = rect_height * rect_width;
////
////		cout << "最小外接矩形的长为：" << rect_height << "，宽为：" << rect_width << "。面积：" << rect_area << endl;
////		feature[contour_num][8] = rect_height;   //特征值数组第8个数
////		feature[contour_num][9] = rect_width;   //特征值数组第8个数
////		feature[contour_num][10] = rect_area;   //特征值数组第8个数
////
////		rect_all_area += rect_area; //最小外接矩形总的面积
////
////		int font_face = FONT_HERSHEY_COMPLEX;
////		Point origin;
////		origin.x = sum_rect_x / 4;
////		origin.y = sum_rect_y / 4;
////
////		char number_buf[10];  //用于显示的数字编号存入数组，puttext
////
////		double font_scale = 0.6;
////		int font_thickness = 0.8;
////
////		//数字标记
////		sprintf(number_buf, "%3d", contour_num);
////		string number_buf_string = number_buf;
////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
////
////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //计算并返回指定点集最外面的矩形边界
////
////		Scalar color = Scalar(g_rng.uniform(0, 255));
////		//画出Box
////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
////		contour_num++;       //连通区域个数，用于数字标记
////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////		imshow("drawing", drawing);
////		imwrite("D:\\roiImgForTest\\huahen\\drawing.jpg", drawing);
////	}
////
////	//而且我也不知道为什么要加直线检测这一步
////
////	//不知道为什么轮廓图上面就可以检测到直线，而矩形框图上面就不能画直线？？？
////	//hough_line(src);
////	hough_line(drawing);
////
////	fanse(drawing);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
//////////？？？
//////霍夫变换检测直线
////void hough_line(Mat src_hough){
////	Mat canny_out;
////	Mat color_dst;
////
////	Canny(src_hough, canny_out, 50, 200, 3);
////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
////
////	vector<Vec2f> lines;  //定义一个矢量结构lines用于存放得到的线段矢量集合
////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
////
////	//依次在图中绘制出每条线段
////	for (size_t i = 0; i < MIN(lines.size(), 100); i++){
////		float rho = lines[i][0], theta = lines[i][1];
////		Point pt1, pt2;
////		double a = cos(theta), b = sin(theta);
////		double x0 = a*rho, y0 = b*rho;
////		pt1.x = cvRound(x0 + 1000 * (-b));
////		pt1.y = cvRound(y0 + 1000 * (a));
////		pt2.x = cvRound(x0 - 1000 * (-b));
////		pt2.y = cvRound(y0 - 1000 * (a));
////
////		line(color_dst, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
////		//这里有两种画直线的方法， 在color_dst上只画直线, 在dst_min_rec上既有直线又有矩形
////	}
////
////	imshow("huazhixiantu", color_dst);
////	imwrite("D:\\roiImgForTest\\huahen\\line.jpg", color_dst);
////}
////
////
////void fanse(Mat dst){
////	Mat m2;
////	m2.create(dst.size(), dst.type());
////
////	//获取图片的一些属性
////	int height2 = dst.rows;
////	int width2 = dst.cols;
////	int np = dst.channels();
////
////	cout << "tongdaoshu :" << np << endl;
////
////	//反色操作
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
////	imshow("duotongdao fanse", m2);
////	imwrite("D:\\roiImgForTest\\huahen\\fanse.jpg", m2);
////}
////
////void morph(Mat mor_input){
////	
////
////	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //以后慢慢考虑，现在看来open好一些
////	imshow("fushi", morph_out);
////	//imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
////}
////
////// 去除孤立噪声点   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
////{
////	int RemoveCount = 0;
////	//新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
////	//初始化的图像全部为0，未检查  
////	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
////	//去除小连通区域的白色点  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (Src.at<uchar>(i, j) < 10)
////			{
////				PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
////			}
////		}
////	}
////
////	vector<Point2i>NeihborPos;//将邻域压进容器  
////	NeihborPos.push_back(Point2i(-1, 0));
////	NeihborPos.push_back(Point2i(1, 0));
////	NeihborPos.push_back(Point2i(0, -1));
////	NeihborPos.push_back(Point2i(0, 1));
////	//cout << "Neighbor mode: 8邻域." << endl;
////	NeihborPos.push_back(Point2i(-1, -1));
////	NeihborPos.push_back(Point2i(-1, 1));
////	NeihborPos.push_back(Point2i(1, -1));
////	NeihborPos.push_back(Point2i(1, 1));
////
////	int NeihborCount = 8;
////	int CurrX = 0, CurrY = 0;
////	//开始检测  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
////			{   //开始检查  
////				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
////				GrowBuffer.push_back(Point2i(j, i));
////				PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
////				int CheckResult = 0;
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					for (int q = 0; q < NeihborCount; q++)
////					{
////						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
////						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
////						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
////						{
////							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
////							{
////								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
////								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
////							}
////						}
////					}
////				}
////				if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
////					CheckResult = 2;
////				else
////				{
////					CheckResult = 1;
////					RemoveCount++;//记录有多少区域被去除  
////				}
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					CurrX = GrowBuffer.at(z).x;
////					CurrY = GrowBuffer.at(z).y;
////					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
////				}
////				//********结束该点处的检查**********    
////			}
////		}
////	}
////	//开始反转面积过小的区域    
////	for (int i = 0; i < Src.rows; ++i)
////	{
////		for (int j = 0; j < Src.cols; ++j)
////		{
////			if (PointLabel.at<uchar>(i, j) == 2)
////			{
////				Dst.at<uchar>(i, j) = 0;
////			}
////			else if (PointLabel.at<uchar>(i, j) == 3)
////			{
////				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
////
////			}
////		}
////	}
////}
////
////void unevenLightCompensate(Mat &image, int blockSize)
////{
////	if (image.channels() == 3) cvtColor(image, image, 7);
////	double average = mean(image)[0];
////	int rows_new = ceil(double(image.rows) / double(blockSize));
////	int cols_new = ceil(double(image.cols) / double(blockSize));
////	Mat blockImage;
////	blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
////	for (int i = 0; i < rows_new; i++)
////	{
////		for (int j = 0; j < cols_new; j++)
////		{
////			int rowmin = i*blockSize;
////			int rowmax = (i + 1)*blockSize;
////			if (rowmax > image.rows) rowmax = image.rows;
////			int colmin = j*blockSize;
////			int colmax = (j + 1)*blockSize;
////			if (colmax > image.cols) colmax = image.cols;
////			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
////			double temaver = mean(imageROI)[0];
////			blockImage.at<float>(i, j) = temaver;
////		}
////	}
////	blockImage = blockImage - average;
////	Mat blockImage2;
////	resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
////	Mat image2;
////	image.convertTo(image2, CV_32FC1);
////	Mat dst = image2 - blockImage2;
////	dst.convertTo(image, CV_8UC1);
////}
////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
//////
//////
////////#include <opencv2/opencv.hpp>
////////#include <opencv2/imgproc/imgproc.hpp>
////////#include <opencv2/highgui/highgui.hpp>
////////#include <iostream>
////////
////////using namespace cv;
////////using namespace std;
////////
////////#define SCALE 0.3
////////#define NUM_COL 11  //二维数组的列， 每一个点缺陷信息的详细信息
////////#define MINAREA 80   //面积小于该阈值的轮廓都要被删掉
////////#define MAXAREA 2000   //面积大于该阈值的轮廓都要被删除
////////
////////RNG g_rng(12345);  //随机数生成器
////////
////////void hough_line(Mat src_hough);
////////void fanse(Mat dst);
////////
////////int main(){
////////	Mat src = imread("D:\\waitDelete\\VS_project\\GetPlateArea\\GetPlateArea\\huahen.JPG");
////////	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
////////
////////	int g_nThresh = 20;
////////	Mat canny_out;
////////
////////	vector<vector<Point> > g_vContours;
////////	vector<Vec4i> g_vHierarchy;
////////	int contour_num = 0;
////////
////////	Mat SrcImage_or;
////////	CvSize src_sz;
////////	
////////	//////////////////////////基本操作///////////////////////////////
////////	//resize
////////	src_sz.width = src.rows * picture.scale;
////////	src_sz.height = SrcImage_origin.cols * picture.scale;
////////	SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
////////	resize(SrcImage_origin, SrcImage_or, src_sz,  CV_INTER_CUBIC);
////////	
////////	imshow("原图",  SrcImage_origin);
////////	
////////	//单通道灰度化处理
////////	g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////////	cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
////////	
////////	//创建二值化原图
////////	g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////////	threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
////////	
////////	//显示二值化后的图片
////////	imshow("二值化", g_BinaryImage);
////////	
////////	///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////	//double length = arcLength(g_vContours[i], true);  //计算封闭轮廓的周长或曲线的长度，默认closed
////////	//double area = contourArea(g_vContours[i]);   //用于计算整个轮廓或部分轮廓的面积， 带符号的面积值表示方向
////////		
////////	vector<Rect> boundRect(g_vContours.size());
////////	
////////	Mat SrcImage;
////////	Size sz;
////////
////////	//sz.width = dst.cols * SCALE;
////////	//sz.height = dst.rows * SCALE;
////////
////////	//调用canny算子检测边缘 
////////	Canny(src, canny_out, g_nThresh, g_nThresh * 2, 3);
////////	imshow("bianyuantu", canny_out);
////////	waitKey(0);
////////
////////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
////////
////////	vector<vector<Point> >::iterator itc = g_vContours.begin(); 
////////	while (itc != g_vContours.end()) { 
////////		if ( itc->size() > MAXAREA) {   //itc->size()<MINAREA ||
////////			itc = g_vContours.erase(itc); 
////////		} 
////////		else if (itc->size()<MINAREA){
////////			itc = g_vContours.erase(itc);
////////		}
////////		else { 
////////			++itc; 
////////		} 
////////	}
////////
////////	for (int i = 0; i < g_vContours.size(); i++) {
////////
////////		//double tmparea = fabs(contourArea(g_vContours[i]));
////////		//if (tmparea <= MINAREA)
////////		//{
////////		//	cvSeqRemove(contour, 0); //删除面积小于设定值的轮廓   
////////		//	continue;
////////		//}
////////		//else
////////		//{
////////		//	liantong_all_area = liantong_all_area + tmparea;
////////		//}
////////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
////////		Point2f vertices[4];    //定义矩形的四个顶点
////////		rect.points(vertices);   //计算矩形的四个顶点
////////		for (int i = 0; i < 4; i++){
////////			cout << "顶点" << i << "坐标：" << vertices[i] << endl;
////////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
////////			imshow("juxing", src);
////////		}
////////
////////		//因为cvPolyLine要求点集的输入类型是CvPoint**
////////		//所以要把 CvPoint2D32f 型的 rect_pts0 转换为 CvPoint 型的 rect_pts
////////		//并赋予一个对应的指针 *pt
////////		//int npts = 4;  //一共有几个顶点，用于一次性画多边形
////////		//CvPoint rect_pts[4], *pt = rect_pts; //四个顶点
////////
////////		int temp = 0;
////////		int sum_rect_x = 0, sum_rect_y = 0;
////////		int rect_height = 0, rect_width = 0;
////////		int rect_area = 0;
////////		int rect_all_area = 0;
////////		
////////		cout << "编号：" << contour_num << "连通区域最小外接矩形顶点坐标分别为：" << endl;
////////
////////		//feature是一个二维数组，即缺陷的个数及每个缺陷的一些信息
////////		int** feature = 0;
////////		feature = new int*[130];
////////		feature[contour_num] = new int[NUM_COL];
////////
////////		for (int i = 0; i < 4; i++){
////////			feature[contour_num][i] = vertices[i].x;  //特征值数组第0-3个数
////////			feature[contour_num][i + 4] = vertices[i].y;  //特征值数组第4-7个数
////////
////////			cout << "第" << i << "个顶点的坐标：" << vertices[i].x << ", " << vertices[i].y << endl;
////////			sum_rect_x += vertices[i].x;
////////			sum_rect_y += vertices[i].y;
////////			rect_height = (int)sqrt((pow((vertices[0].x - vertices[1].x), 2) + pow((vertices[0].y - vertices[1].y), 2)));
////////			rect_width = (int)sqrt((pow((vertices[0].x - vertices[3].x), 2) + pow((vertices[0].y - vertices[3].y), 2)));
////////			if (rect_height < rect_width)
////////			{
////////				temp = rect_height;
////////				rect_height = rect_width;
////////				rect_width = temp;
////////			}
////////		}
////////
////////		rect_area = rect_height * rect_width;
////////
////////		cout << "最小外接矩形的长为：" << rect_height << "，宽为：" << rect_width << "。面积：" << rect_area << endl;
////////		feature[contour_num][8] = rect_height;   //特征值数组第8个数
////////		feature[contour_num][9] = rect_width;   //特征值数组第8个数
////////		feature[contour_num][10] = rect_area;   //特征值数组第8个数
////////
////////		rect_all_area += rect_area; //最小外接矩形总的面积
////////
////////		int font_face = FONT_HERSHEY_COMPLEX;
////////		Point origin;
////////		origin.x = sum_rect_x / 4;
////////		origin.y = sum_rect_y / 4;
////////
////////		char number_buf[10];  //用于显示的数字编号存入数组，puttext
////////
////////		double font_scale = 0.6;
////////		int font_thickness = 0.8;
////////
////////		//数字标记
////////		sprintf(number_buf, "%3d", contour_num);
////////		string number_buf_string = number_buf;
////////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
////////
////////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //计算并返回指定点集最外面的矩形边界
////////
////////		Scalar color = Scalar(g_rng.uniform(0, 255));
////////		//画出Box
////////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
////////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
////////		contour_num++;       //连通区域个数，用于数字标记
////////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////////		imshow("drawing", drawing);
////////	}
////////
////////	//而且我也不知道为什么要加直线检测这一步
////////
////////	//不知道为什么轮廓图上面就可以检测到直线，而矩形框图上面就不能画直线？？？
////////	hough_line(src);
////////	hough_line(drawing);
////////	
////////	fanse(drawing);
////////
////////	waitKey(0);
////////	system("pause");
////////	return 0;
////////}
////////
////////////？？？
//////////霍夫变换检测直线
////////void hough_line(Mat src_hough){
////////	Mat canny_out;
////////	Mat color_dst;
////////
////////	Canny(src_hough, canny_out, 50, 200, 3);
////////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
////////
////////	vector<Vec2f> lines;  //定义一个矢量结构lines用于存放得到的线段矢量集合
////////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
////////
////////	//依次在图中绘制出每条线段
////////	for (size_t i = 0; i < MIN(lines.size(), 100); i++){
////////		float rho = lines[i][0], theta = lines[i][1];
////////		Point pt1, pt2;
////////		double a = cos(theta), b = sin(theta);
////////		double x0 = a*rho, y0 = b*rho;
////////		pt1.x = cvRound(x0 + 1000 * (-b));
////////		pt1.y = cvRound(y0 + 1000 * (a));
////////		pt2.x = cvRound(x0 - 1000 * (-b));
////////		pt2.y = cvRound(y0 - 1000 * (a));
////////
////////		line(color_dst, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
////////		//这里有两种画直线的方法， 在color_dst上只画直线, 在dst_min_rec上既有直线又有矩形
////////	}
////////
////////	imshow("huazhixiantu", color_dst);
////////}
////////
////////
////////void fanse(Mat dst){
////////	Mat m2;
////////	m2.create(dst.size(), dst.type());
////////
////////	//获取图片的一些属性
////////	int height2 = dst.rows;
////////	int width2 = dst.cols;
////////	int np = dst.channels();
////////
////////	cout << "tongdaoshu :" << np << endl;
////////
////////	//反色操作
////////	for (int row = 0; row < height2; row++){
////////		for (int col = 0; col < width2; col++){
////////			if (np == 1){
////////				m2.at<uchar>(row, col) = 255 - dst.at<uchar>(row, col);
////////			}
////////			else if (np == 3){
////////				m2.at<Vec3b>(row, col)[0] = 255 - dst.at<Vec3b>(row, col)[0];
////////				m2.at<Vec3b>(row, col)[1] = 255 - dst.at<Vec3b>(row, col)[1];
////////				m2.at<Vec3b>(row, col)[2] = 255 - dst.at<Vec3b>(row, col)[2];
////////			}
////////		}
////////	}
////////	imshow("duotongdao fanse", m2);
////////}
////////////////////////////////////////////////
////////
//////////前期图像预处理（载入原图，resize， 灰度化，二值化）
//////////图像腐蚀膨胀 （把断裂的部分连接在一起）
//////////检测连通区域   （检测连通域，删除宽高比例小于设定值的轮廓）
//////////求最小外接矩形  （倾斜的最小外接矩形）
//////////Hough直线检测    （不知道为什么还要有直线检测？）
//////////图像反色    （突出缺陷划痕）
////////
/////////////////////////////////////////////////
////////
////////
//////////#include <opencv2/opencv.hpp>
//////////#include <opencv2/imgproc/imgproc.hpp>
//////////#include <opencv2/highgui/highgui.hpp>
//////////#include <iostream>
//////////
//////////using namespace cv;
//////////using namespace std;
//////////
//////////#define SCALE 0.3
//////////#define NUM_COL 11  //二维数组的列， 每一个点缺陷信息的详细信息
//////////#define MINAREA 80   //面积小于该阈值的轮廓都要被删掉
//////////#define MAXAREA 2000   //面积大于该阈值的轮廓都要被删除
//////////
//////////RNG g_rng(12345);  //随机数生成器
//////////
//////////void hough_line(Mat src_hough);
//////////
//////////int main(){
//////////	Mat src = imread("D:\\waitDelete\\VS_project\\GetPlateArea\\GetPlateArea\\huahen.JPG");
//////////	//Mat src = imread("D:\\roiImage_2\\sample6\\9.JPG");    ///threshold 60
//////////	//Mat dst = imread("D:\\roiImage_2\\sample1\\2.JPG");
//////////	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
//////////
//////////	int g_nThresh = 20;
//////////	Mat canny_out;
//////////
//////////	vector<vector<Point> > g_vContours;
//////////	vector<Vec4i> g_vHierarchy;
//////////	int contour_num = 0;
//////////
//////////	//double length = arcLength(g_vContours[i], true);  //计算封闭轮廓的周长或曲线的长度，默认closed
//////////	//double area = contourArea(g_vContours[i]);   //用于计算整个轮廓或部分轮廓的面积， 带符号的面积值表示方向
//////////		
//////////	vector<Rect> boundRect(g_vContours.size());
//////////	
//////////	Mat SrcImage;
//////////	Size sz;
//////////
//////////	//sz.width = dst.cols * SCALE;
//////////	//sz.height = dst.rows * SCALE;
//////////
//////////	//调用canny算子检测边缘 
//////////	Canny(src, canny_out, g_nThresh, g_nThresh * 2, 3);
//////////	imshow("bianyuantu", canny_out);
//////////	waitKey(0);
//////////
//////////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//////////
//////////	vector<vector<Point> >::iterator itc = g_vContours.begin(); 
//////////	while (itc != g_vContours.end()) { 
//////////		if ( itc->size() > MAXAREA) {   //itc->size()<MINAREA ||
//////////			itc = g_vContours.erase(itc); 
//////////		} 
//////////		else if (itc->size()<MINAREA){
//////////			itc = g_vContours.erase(itc);
//////////		}
//////////		else { 
//////////			++itc; 
//////////		} 
//////////	}
//////////
//////////	for (int i = 0; i < g_vContours.size(); i++) {
//////////
//////////		//double tmparea = fabs(contourArea(g_vContours[i]));
//////////		//if (tmparea <= MINAREA)
//////////		//{
//////////		//	cvSeqRemove(contour, 0); //删除面积小于设定值的轮廓   
//////////		//	continue;
//////////		//}
//////////		//else
//////////		//{
//////////		//	liantong_all_area = liantong_all_area + tmparea;
//////////		//}
//////////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
//////////		Point2f vertices[4];    //定义矩形的四个顶点
//////////		rect.points(vertices);   //计算矩形的四个顶点
//////////		for (int i = 0; i < 4; i++){
//////////			cout << "顶点" << i << "坐标：" << vertices[i] << endl;
//////////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//////////			imshow("juxing", src);
//////////		}
//////////
//////////		//因为cvPolyLine要求点集的输入类型是CvPoint**
//////////		//所以要把 CvPoint2D32f 型的 rect_pts0 转换为 CvPoint 型的 rect_pts
//////////		//并赋予一个对应的指针 *pt
//////////		//int npts = 4;  //一共有几个顶点，用于一次性画多边形
//////////		//CvPoint rect_pts[4], *pt = rect_pts; //四个顶点
//////////
//////////		int temp = 0;
//////////		int sum_rect_x = 0, sum_rect_y = 0;
//////////		int rect_height = 0, rect_width = 0;
//////////		int rect_area = 0;
//////////		int rect_all_area = 0;
//////////		
//////////		cout << "编号：" << contour_num << "连通区域最小外接矩形顶点坐标分别为：" << endl;
//////////
//////////		//feature是一个二维数组，即缺陷的个数及每个缺陷的一些信息
//////////		int** feature = 0;
//////////		feature = new int*[130];
//////////		feature[contour_num] = new int[NUM_COL];
//////////
//////////		for (int i = 0; i < 4; i++){
//////////			feature[contour_num][i] = vertices[i].x;  //特征值数组第0-3个数
//////////			feature[contour_num][i + 4] = vertices[i].y;  //特征值数组第4-7个数
//////////
//////////			cout << "第" << i << "个顶点的坐标：" << vertices[i].x << ", " << vertices[i].y << endl;
//////////			sum_rect_x += vertices[i].x;
//////////			sum_rect_y += vertices[i].y;
//////////			rect_height = (int)sqrt((pow((vertices[0].x - vertices[1].x), 2) + pow((vertices[0].y - vertices[1].y), 2)));
//////////			rect_width = (int)sqrt((pow((vertices[0].x - vertices[3].x), 2) + pow((vertices[0].y - vertices[3].y), 2)));
//////////			if (rect_height < rect_width)
//////////			{
//////////				temp = rect_height;
//////////				rect_height = rect_width;
//////////				rect_width = temp;
//////////			}
//////////		}
//////////
//////////		rect_area = rect_height * rect_width;
//////////
//////////		cout << "最小外接矩形的长为：" << rect_height << "，宽为：" << rect_width << "。面积：" << rect_area << endl;
//////////		feature[contour_num][8] = rect_height;   //特征值数组第8个数
//////////		feature[contour_num][9] = rect_width;   //特征值数组第8个数
//////////		feature[contour_num][10] = rect_area;   //特征值数组第8个数
//////////
//////////		rect_all_area += rect_area; //最小外接矩形总的面积
//////////
//////////		int font_face = FONT_HERSHEY_COMPLEX;
//////////		Point origin;
//////////		origin.x = sum_rect_x / 4;
//////////		origin.y = sum_rect_y / 4;
//////////
//////////		char number_buf[10];  //用于显示的数字编号存入数组，puttext
//////////
//////////		double font_scale = 0.6;
//////////		int font_thickness = 0.8;
//////////
//////////		//数字标记
//////////		sprintf(number_buf, "%3d", contour_num);
//////////		string number_buf_string = number_buf;
//////////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
//////////
//////////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //计算并返回指定点集最外面的矩形边界
//////////
//////////		Scalar color = Scalar(g_rng.uniform(0, 255));
//////////		//画出Box
//////////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
//////////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
//////////		contour_num++;       //连通区域个数，用于数字标记
//////////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//////////		imshow("drawing", drawing);
//////////
//////////		waitKey(0);
//////////	}
//////////
//////////	//而且我也不知道为什么要加直线检测这一步
//////////
//////////	//不知道为什么轮廓图上面就可以检测到直线，而矩形框图上面就不能画直线？？？
//////////	hough_line(src);
//////////	hough_line(drawing);
//////////	
//////////	system("pause");
//////////	return 0;
//////////}
//////////
//////////
////////////霍夫变换检测直线
//////////void hough_line(Mat src_hough){
//////////	Mat canny_out;
//////////	Mat color_dst;
//////////
//////////	Canny(src_hough, canny_out, 50, 200, 3);
//////////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
//////////
//////////	vector<Vec2f> lines;  //定义一个矢量结构lines用于存放得到的线段矢量集合
//////////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
//////////
//////////	//依次在图中绘制出每条线段
//////////	for (size_t i = 0; i < MIN(lines.size(), 100); i++){
//////////		float rho = lines[i][0], theta = lines[i][1];
//////////		Point pt1, pt2;
//////////		double a = cos(theta), b = sin(theta);
//////////		double x0 = a*rho, y0 = b*rho;
//////////		pt1.x = cvRound(x0 + 1000 * (-b));
//////////		pt1.y = cvRound(y0 + 1000 * (a));
//////////		pt2.x = cvRound(x0 - 1000 * (-b));
//////////		pt2.y = cvRound(y0 - 1000 * (a));
//////////
//////////		line(color_dst, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
//////////		//这里有两种画直线的方法， 在color_dst上只画直线, 在dst_min_rec上既有直线又有矩形
//////////	}
//////////
//////////	imshow("huazhixiantu", color_dst);
//////////	waitKey(0);
//////////}
////////
////////	
////////	
////////	
////////
////////
////////////划痕检测
//////////
//////////#include <opencv2\opencv.hpp>
//////////#include <iostream>
//////////
//////////using namespace cv;
//////////using namespace std;
//////////
//////////#define			WINDOW_NAME_BINARY "【二值化图片】"  //定义二值化窗口标题
//////////#define			WINDOW_NAME_SRC "【灰度图像】"   //创建原图像窗口标题变量
//////////#define			WINDOW_NAME_SLIDER "【二值化阈值】"  //创建滑块标题变量
//////////
//////////#define			num_col 11   //二维数组的列，每一个点缺陷信息的详细信息
//////////
////////////定义图片变量
//////////Mat				g_GrayImage;
//////////Mat				g_BinaryImage;
//////////Mat				g_pGrayImage_liantong;
//////////Mat				g_pBinaryImage_liantong;
//////////
////////////其他变量
//////////int						contour_num = 0;  //轮廓数字编号
//////////char					number_buf[10];  //数字编号存入数组，puttext
//////////long int				liantong_all_area = 0;  //连通区域总面积
//////////long int				Rect_all_area = 0; //保存最小外接矩形总的面积
//////////
////////////定义图片路径
//////////string				srcPath = "1.jpg";
//////////
////////////////////////相关结构体 ////////////////////////
//////////struct my_struct1{
//////////	double				scale;    //定义显示图像的比例
//////////	const int			threshold_value_binaryzation;   //定义第一次二值化阈值
//////////	const int			threshold_value_second_binaryzation;  //定义第二次二值化阈值
//////////};
//////////my_struct1 picture = { 0.3, 50, 100 };
//////////
//////////struct my_struct2{
//////////	int				Model1_k1;   //图像腐蚀膨胀
//////////	int				Model1_k2;   //图像腐蚀膨胀
//////////	int				Model2_k1;   //图像腐蚀膨胀
//////////	int				Model2_k2;   //图像腐蚀膨胀
//////////};
//////////my_struct2 value = { 5, 2, 3, 2 };
//////////
//////////struct my_struct3{
//////////	double				maxarea;   //最大缺陷面积
//////////	double				minarea;   //最小显示保留的缺陷面积
//////////
//////////	double				font_scale;   //字体大小
//////////	int						font_thickness;   //字体粗细
//////////
//////////	const int			Feature_value2_number;   //定义一个二维数组的列，即缺陷的个数
//////////};
//////////my_struct3 value2 = { 0, 4, 0.6, 0.8, 100 };
//////////
//////////struct my_struct4{
//////////	const int			hough_Canny_thresh1;
//////////	const int			hough_Canny_thresh2;
//////////	const int			hough_Canny_kernel;
//////////
//////////	const int			cvHoughLines2_thresh;    //像素值大于多少才显示，值越大，显示的线段越少
//////////	const int			cvHoughLines2_param1;     //显示线段的最小长度
//////////	const int			cvHoughLines2_param2;     //线段之间的最小间隔
//////////};
//////////my_struct4 Hough = { 50, 100, 3, 50, 20, 10 };
///////////////////////////////////////////////////////////////////
//////////
//////////int** on_trackbar(){
//////////
//////////	vector<vector<Point>>  contours;
//////////	vector<vector<Point>>  _contours;
//////////	vector<Vec4i> hierarchy;
//////////
//////////	//定义存放数组的二维数组，返回指针数组
//////////	int** Feature_value2 = 0;
//////////	Feature_value2 = new int*[value2.Feature_value2_number];
//////////
//////////	Mat SrcImage_or;
//////////	CvSize src_sz;
//////////
//////////	//////////////////////////基本操作///////////////////////////////
//////////	Mat SrcImage_origin = imread(srcPath);   //载入原图
//////////
//////////	//resize
//////////	src_sz.width = SrcImage_origin.rows * picture.scale;
//////////	src_sz.height = SrcImage_origin.cols * picture.scale;
//////////	SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
//////////	resize(SrcImage_origin, SrcImage_or, src_sz,  CV_INTER_CUBIC);
//////////
//////////	imshow("原图",  SrcImage_origin);
//////////
//////////	//单通道灰度化处理
//////////	g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
//////////
//////////	//创建二值化原图
//////////	g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
//////////
//////////	//显示二值化后的图片
//////////	imshow("二值化", g_BinaryImage);
//////////
//////////	///////////////////////////// 图像腐蚀膨胀 ////////////////////////////
//////////	// 先膨胀后腐蚀，这个为闭合操作，图片中断裂处会缝合。
//////////	// 利用这个操作可以填充细小空洞，连接临近物体，平滑物体边缘，同时不明显改变物体面积
//////////
//////////	Mat temp_cvDilate = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	//Mat temp_cvErode = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	Mat temp_cvErode_cvErode = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	
//////////	Mat element1 = getStructuringElement(MORPH_ELLIPSE,  Size(value.Model1_k1, value.Model1_k1), Point(value.Model1_k2, value.Model1_k2));
//////////	Mat element2 = getStructuringElement(MORPH_RECT, Size(value.Model2_k1, value.Model2_k1), Point(value.Model2_k2, value.Model2_k2));
//////////
//////////	//先膨胀后腐蚀
//////////	dilate(g_BinaryImage, temp_cvDilate, element1);
//////////	erode(temp_cvDilate, temp_cvErode_cvErode, element2);
//////////
//////////	imshow("腐蚀膨胀", temp_cvErode_cvErode);
//////////	////////////////////////////////////////////////////////////////////////////////////
//////////
//////////	////////////////////////////检测连通区域 //////////////////////////////////
//////////	g_BinaryImage = temp_cvErode_cvErode.clone();   //本来想拷贝的，但是会出现问题
//////////
//////////	Mat liantong_dst = Mat::zeros(src_sz, CV_8UC1);
//////////
//////////	//提取轮廓
//////////	findContours(g_BinaryImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
//////////
//////////	int n = -1, m = 0;   //n为面积最大轮廓索引， m为迭代索引。
//////////
//////////	///------------------------------------------ 对连通区域做处理 
//////////	//获取轮廓，计算面积，判断面积大小，
//////////	//（1）删除面积小于设定值的轮廓，（2）删除宽高比小于设定值的轮廓， 
//////////	//并记录轮廓面积最大的那个轮廓的索引
//////////
//////////
//////////	//////////////////////////求最小外接矩形 //////////////////////////////
//////////
//////////	double length = arcLength(contours[i], true);  //计算封闭轮廓的周长或曲线的长度，默认closed
//////////	double area = contourArea(contours[i]);   //用于计算整个轮廓或部分轮廓的面积， 带符号的面积值表示方向
//////////	
//////////	vector<Rect> boundRect(contours.size());
//////////
//////////	for (unsigned int i = 0; i < contours.size(); i++){
//////////		boundRect[i] = boundingRect(Mat(contours[i]));
//////////	}
//////////
//////////	RotatedRect box = minAreaRect(Mat(contours[i]));
//////////	Mat SrcImage;
//////////	Size sz;
//////////
//////////	Mat 
//////////
//////////
//////////	///////////////////////////////////打印缺陷面积占比////////////////
//////////	float temp_percent = 0.0;
//////////
//////////	cout << "连通区域面积：" << liantong_all_area << endl;   //打印连通区域面积， 放在前面被掩盖， 所以放在后面
//////////	cout << "图像矩形面积：" << Rect_all_area << endl;
//////////	cout << "整幅图像面积：" << sizeof_pic << endl;
//////////
//////////	temp_percent = (float)liantong_all_area / sizeof_pic * 100;
//////////	cout << "缺陷面积占比：" << temp_percent << endl;
//////////
//////////
//////////
//////////	////Hough变换检测直线
//////////
//////////
//////////	////////////////
//////////	//////图像反色 ///////////////
//////////
//////////	return Feature_value2; //原来可以返回数组
//////////}
//////////
//////////int main11(){
//////////
//////////	int **Tan_return;
//////////
//////////	Tan_return = on_trackbar();
//////////
//////////	for (int i = 0; i < contour_num; i++){
//////////		cout << "Number " << i << ": ";
//////////		for (int j = 0; j < num_col; j++){
//////////			cout << Tan_return[i][j] << " , ";
//////////		}
//////////		cout << endl;
//////////	}
//////////
//////////	for (int i = 0; i < contour_num; i++){   //释放内存
//////////		delete[] Tan_return[i];
//////////	}
//////////	delete[] Tan_return; 
//////////	waitKey(0);
//////////
//////////	////销毁窗口， 释放图片（实际运行退出时一定要销毁窗口）
//////////	//destroyWindow();
//////////	//destroyWindow();
//////////	//cvReleaseImage();
//////////	//cvReleaseImage();
//////////	//cvReleaseImage();
//////////
//////////	system("pause");
//////////	return 0; 
//////////}