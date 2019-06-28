////铜片边缘检测
//
//
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//int thresholds = 40;
//Mat src1;
//
//int blockSize = 5;
//
////void canny_track(int, void *);
//void canny_track(Mat src1);
//
//void unevenLightCompensate(Mat &image, int blockSize);
//
//void GammaCorrection(Mat &src, Mat &dst, float fGamma);
//
//int main(){
//	src1 = imread("D:\\newSample\\daguang\\1\\11.JPG");
//
//	//GammaCorrection(src1, src1, 2.4);   ///1/2.4
//	//unevenLightCompensate(src1, blockSize);
//
//	//namedWindow("边缘检测", WINDOW_NORMAL);
//	//createTrackbar("阈值：", "边缘检测", &thresholds, 255, canny_track);//滑动条创建
//	//canny_track(0, 0);//回调函数*****这里不要忘记写，否则不能调用！！！！
//
//	canny_track(src1);
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
////void canny_track(int, void *)
//void canny_track(Mat src1){
//	Mat canny_out;
//	Mat color_dst;
//
//	Canny(src1, canny_out, thresholds, thresholds*3, 3);
//
//	imshow("canny", canny_out);
//	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
//
//	vector<Vec2f> lines;  //定义一个矢量结构lines用于存放得到的线段矢量集合
//	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
//
//	//依次在图中绘制出每条线段
//	for (size_t i = 0; i < MIN(lines.size(), 100); i++){
//		float rho = lines[i][0], theta = lines[i][1];
//		Point pt1, pt2;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//
//		line(color_dst, pt1, pt2, Scalar(0, 0, 0), 5, CV_AA);   ///Scalar(55, 100, 195)
//		//这里有两种画直线的方法， 在color_dst上只画直线, 在dst_min_rec上既有直线又有矩形
//	}
//
//	//unevenLightCompensate(color_dst, blockSize);
//	//imshow("guangzhao ", color_dst);
//
//	cvtColor(color_dst, color_dst, CV_BGR2GRAY);
//	Mat drawing = Mat::zeros(src1.size(), CV_8UC3);
//	
//	vector<vector<Point> > g_vContours;
//	vector<Vec4i> g_vHierarchy;
//
//	findContours(color_dst, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(0, 255, 0);
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//		imshow("drawing", drawing);
//	
//		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
//		Point2f vertices[4];    //定义矩形的四个顶点
//		rect.points(vertices);   //计算矩形的四个顶点
//		for (int i = 0; i < 4; i++){
//			line(src1, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//			imshow("juxing", src1);
//		}	
//	}
//
//	cout << "轮廓个数" << g_vContours.size() << endl;
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
//




//
//
//
//
//
//
//
//
//
////
//////////用轮廓判断白斑个数
////
////#include <iostream>
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////
////using namespace std;
////using namespace cv;
////
////int AreaLimit = 20;
////int num = 0;
////
////// 去除孤立噪声点   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
////
////int main(){
////	Mat src = imread("D:\\newSample\\daguang\\1\\5.JPG");
////	Mat dst;
////
////	cvtColor(src, src, CV_BGR2GRAY);
////	threshold(src, src, 20, 255, CV_THRESH_BINARY);
////	imshow("erzhihua ", src);
////
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(src, src, MORPH_ELLIPSE, element);
////
////	imshow("fushi ", src);
////
////	ROIComDenoise(src, dst, AreaLimit);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////// 白斑个数，去除孤立噪声点函数改进   
////void ROIWhiteCircle(Mat &Src, Mat &Dst, int AreaLimit)
////{
////	int num = 0;   //记录连通区域个数
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
////			{
////				//开始检查  
////				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
////
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
////
////				num++;  
////			}
////		}
////	}
////
////	cout << "白斑个数：" << num << endl;
////}
//
//
//
//
//
//
//
//
////
//////////用轮廓判断白斑个数
////
////#include <iostream>
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////
////using namespace std;
////using namespace cv;
////
////int AreaLimit = 20;
////int num = 0;
////
////// 去除孤立噪声点   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
////
////int main(){
////	Mat src = imread("D:\\newSample\\daguang\\1\\5.JPG");
////	Mat dst;
////
////	cvtColor(src, src, CV_BGR2GRAY);
////	threshold(src, src, 20, 255, CV_THRESH_BINARY);
////	imshow("erzhihua ", src);
////
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(src, src, MORPH_ELLIPSE, element);
////
////	imshow("fushi ", src);
////
////	ROIComDenoise(src, dst, AreaLimit);
////
////	waitKey(0);
////	system("pause");
////	return 0;
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
////			{   
////				//cout << "*******************************************************************" << endl;
////				//开始检查  
////				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
////				
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
////
////				num++;
////				//if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
////				//	CheckResult = 2;
////				//else
////				//{
////				//	CheckResult = 1;
////				//	RemoveCount++;//记录有多少区域被去除  
////				//}
////
////				//for (int z = 0; z < GrowBuffer.size(); z++)
////				//{
////				//	CurrX = GrowBuffer.at(z).x;
////				//	CurrY = GrowBuffer.at(z).y;
////				//	PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
////				//}
////				
////				//********结束该点处的检查**********    
////			}
////		}
////	}
////
////	cout << "白斑个数：" << num << endl;
////
////	//cout << "白斑个数：" << num << endl;
////
////	////开始反转面积过小的区域    
////	//for (int i = 0; i < Src.rows; ++i)
////	//{
////	//	for (int j = 0; j < Src.cols; ++j)
////	//	{
////	//		if (PointLabel.at<uchar>(i, j) == 2)
////	//		{
////	//			Dst.at<uchar>(i, j) = 0;
////	//		}
////	//		else if (PointLabel.at<uchar>(i, j) == 3)
////	//		{
////	//			Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
////
////	//		}
////	//	}
////	//}
////}
//
////void morph(Mat mor_input);
////Mat morph_out;
////
////int main(){
////	Mat thrImg;
////	Mat src = imread("D:\\newSample\\daguang\\1\\5.JPG");
////
////	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
////
////	int g_nThresh = 20;
////	Mat canny_out;
////	int num = 0;
////
////	threshold(src, src, 50, 255, CV_THRESH_BINARY_INV);
////
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(src, src, MORPH_ELLIPSE, element);
////
////	vector<vector<Point> > g_vContours;
////	vector<Vec4i> g_vHierarchy;
////	int contour_num = 0;
////
////	vector<Rect> boundRect(g_vContours.size());
////
////	//调用canny算子检测边缘 
////	Canny(src, canny_out, g_nThresh, g_nThresh * 2, 3);
////	imshow("bianyuantu", canny_out);
////	imwrite("D:\\roiImgForTest\\huahen\\canny.jpg", canny_out);
////	waitKey(0);
////
////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
////
////	vector<vector<Point> >::iterator itc = g_vContours.begin();
////	while (itc != g_vContours.end()) {
////		if (itc->size() > 2000) {
////			itc = g_vContours.erase(itc);
////		}
////		else if (itc->size()<20){
////			itc = g_vContours.erase(itc);
////		}
////		else {
////			++itc;
////		}
////	}
////
////	for (int i = 0; i < g_vContours.size(); i++) {
////
////		cout << "白斑个数：" << g_vContours.size() << endl;
////
////		Scalar color = Scalar(0, 255, 0);
////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////		imshow("drawing", drawing);
////		imwrite("D:\\roiImgForTest\\huahen\\drawing.jpg", drawing);
////
////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //用于对给定的2D点集，寻找可旋转的最小面积的包围矩形
////		Point2f vertices[4];    //定义矩形的四个顶点
////		rect.points(vertices);   //计算矩形的四个顶点
////		for (int i = 0; i < 4; i++){
////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
////			imshow("juxing", src);
////			imwrite("D:\\roiImgForTest\\huahen\\juxing.jpg", src);
////		}	
////	}
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////void morph(Mat mor_input){
////	
////	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //以后慢慢考虑，现在看来open好一些
////	imshow("fushi", morph_out);
////	//imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
////}