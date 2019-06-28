//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <windows.h>
//
//using namespace cv;
//using namespace std;
//
////Mat grayImg, thrImg, morph_out, drawing;
////int ng_num = 0;
////int num_contours = 0;
////bool m_resultDetectCom = 0;
////bool binaryThreshold(Mat srcImg, int i);
////void morph(Mat mor_input);
////void draw_contour(Mat canny_input);
//
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//int AreaLimit = 50;
//
//bool binaryThreshold(Mat srcImg, int i){
//	Mat grayImg, thrImg, morph_out, drawing;
//	int ng_num = 0;
//	int num_contours = 0;
//	bool m_resultDetectCom = 0;
//
//	//二值化
//	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
//	threshold(grayImg, thrImg, 200, 255, 3);    //170 不错, 对于a\\3.jpg,,去噪面积设为10 也可以
//
//	imshow("erzhihua", thrImg);
//	imwrite("D:\\roiImage_2\\sample3\\save\\二值化.jpg", thrImg);
//
//	ROIComDenoise(thrImg, thrImg, AreaLimit);
//
//	//腐蚀
//	/*Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
//	morphologyEx(thrImg, morph_out, MORPH_OPEN, element);
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);*/
//
//	int g_nThresh = 80;
//	RNG g_rng(12345);
//	Mat canny_out;
//	vector<vector<Point> > g_vContours;
//	vector<Vec4i> g_vHierarchy;
//
//	//调用canny算子检测边缘 
//	Canny(thrImg, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//寻找轮廓 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("lunkuo", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	num_contours = g_vContours.size();
//
//	string strImg;
//
//	if (num_contours == 0){
//		m_resultDetectCom = 1;
//		strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//		imwrite(strImg, thrImg);
//		cout << "此样片为ok片！" << endl;
//	}
//	else{
//		m_resultDetectCom = 0;
//		cout << "此样片为ng片！" << endl;
//		strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//		imwrite(strImg, thrImg);
//		ng_num++;
//	}
//
//	return m_resultDetectCom;
//}
//
//int main(){
//	Mat srcImg = imread("D:\\newSample\\xianchang\\1234.JPG");
//	bool flag = binaryThreshold(srcImg, 0);
//
//	cout << flag << endl;
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
//
////
//////int main(int argc, char* argv[])
//////{
//////	//21
//////	string dir_path = "D:\\newSample\\0506\\ng\\";
//////	Directory dir;
//////	vector<string> fileNames = dir.GetListFiles(dir_path, "*.jpg", false);
//////	bool flag = 0;
//////
//////	LARGE_INTEGER nFreq;
//////	LARGE_INTEGER nBeginTime;
//////	LARGE_INTEGER nEndTime;
//////	double dtime;
//////	QueryPerformanceFrequency(&nFreq);
//////	QueryPerformanceCounter(&nBeginTime);
//////
//////	for (int i = 0; i < fileNames.size(); i++){
//////		//get image name
//////		string fileName = fileNames[i];
//////		string fileFullName = dir_path + fileName;
//////		cout << "Full path:" << fileFullName << endl;
//////
//////		//load image
//////		Mat srcImg = imread(fileFullName.c_str());
//////		flag = binaryThreshold(srcImg, i);
//////
//////		string strImg;
//////
//////		if (flag == 1){
//////			strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//////			//imwrite(strImg, thrImg);
//////			cout << "此样片为ok片！" << endl;
//////		}
//////		else{
//////			cout << "此样片为ng片！" << endl;
//////			strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//////			//imwrite(strImg, thrImg);
//////			//ng_num++;
//////		}
//////	}
//////
//////	//cout << "总图片数：" << fileNames.size() << ", ng图片数:" << ng_num << endl;
//////
//////	QueryPerformanceCounter(&nEndTime);
//////	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//////	cout << "代码的运行时间为" << dtime << "秒!" << endl;
//////
//////	waitKey(0);
//////	system("pause");
//////	return 0;
//////}
//////
////////bool binaryThreshold(Mat srcImg, int i){
////////	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
////////	threshold(grayImg, thrImg, 200, 255, 3);    //170 不错
////////	imshow("二值化", thrImg);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\二值化.jpg", thrImg);
////////	//waitKey(0);
////////
////////	morph(thrImg);
////////	
////////	//////----------------->画轮廓，圈出缺陷，首先转换成彩色图像就能画颜色框了
////////	draw_contour(morph_out);
////////	waitKey(0);
////////
////////	if (num_contours == 0){
////////		m_resultDetectCom = 1;
////////	}
////////	else{
////////		m_resultDetectCom = 0;
////////	}
////////	
////////	return m_resultDetectCom;
////////}
////////
////////void morph(Mat mor_input){
////////	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////////	Mat element = getStructuringElement(MORPH_RECT, Size(3,3)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
////////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //以后慢慢考虑，现在看来open好一些
////////	imshow("fushi", morph_out);
//////////	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
////////}
////////
////////void draw_contour(Mat canny_input){
////////	int g_nThresh = 80;
////////	RNG g_rng(12345);
////////	Mat canny_out;
////////	vector<vector<Point> > g_vContours;
////////	vector<Vec4i> g_vHierarchy;
////////
////////	//调用canny算子检测边缘 
////////	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
////////	imshow("边缘图", canny_out);
////////	//寻找轮廓 
////////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
////////	drawing = Mat::zeros(canny_out.size(), CV_8UC3);
////////	for (int i = 0; i < g_vContours.size(); i++) {
////////		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////////	}
////////	imshow("缺陷轮廓图", drawing);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
////////
////////	num_contours = g_vContours.size();
////////}