//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <windows.h>
//
//using namespace std;
//using namespace cv;
//
//int AreaLimit = 20;
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int main(){
//
//	////------------------>时间统计<-------------------------------------
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	double dtime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);
//	////////////////////////////////////////////////////////////////////////////////////////////
//	
//	Mat src = imread("D:\\newSample\\0508\\a\\7.JPG");
//	Mat detectImg = imread("D:\\newSample\\0508\\a\\6.JPG");
//
//	bool  m_resultDetectCom = 0;
//	int safePix = 3;
//
//	//高斯滤波,归一化 获取原图边缘
//	GaussianBlur(detectImg, detectImg, Size(5, 5), 3, 3);
//	imshow("gauss", detectImg);
//	Mat edgeImgOk;
//	//Canny(detectImg, edgeImgOk, 20, 20 * 3, 3);
//	Canny(src, edgeImgOk, 80, 80 * 3, 3);  //很奇怪，明明是获取原图边缘，怎么给的是检测图像
//	imshow("edgeImgOk",edgeImgOk);
//	normalize(detectImg, detectImg, 0, 255, cv::NORM_MINMAX);
//	imshow("guiyihua", detectImg);
//	waitKey(0);
//
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//	
//	//高斯滤波,归一化
//	GaussianBlur(src, src, Size(5, 5), 3, 3);
//	imshow("gauss2", src);
//	normalize(src, src, 0, 255, NORM_MINMAX);
//	imshow("guiyihua2", src);
//	waitKey(0);
//
//	int  rowOK = src.rows;
//	int  colOK = src.cols;
//
//	Mat diff_dst, morph_out;
//
//	////----------------->两图之差<-----------------------------------------------------
//	absdiff(src, detectImg, diff_dst);
//	imshow("diff", diff_dst);
//
//	for (int i = 0; i < rowOK; i++)
//	{
//		for (int j = 0; j < colOK; j++)
//		{
//			if (diff_dst.at<uchar>(i, j)>40)
//			{
//				diff_dst.at<uchar>(i, j) = 255;
//			}
//			else
//			{
//				diff_dst.at<uchar>(i, j) = 0;
//			}
//		}
//	}
//	imshow("threshold", diff_dst);
//	waitKey(0);
//
//	//边缘图像设置安全像素
//	Mat elementSafe = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(safePix, safePix));
//
//	cv::Mat edgeImgSafe;
//	cv::dilate(edgeImgOk, edgeImgSafe, elementSafe);
//	imshow("safe", edgeImgSafe);
//
//	//反色且归一化
//	//edgeImgSafe = (255 - edgeImgSafe) / 255;
//	edgeImgSafe = (255 - edgeImgSafe);
//	imshow("fanse", edgeImgSafe);
//
//	Mat resultImg = Mat::zeros(rowOK, colOK, CV_8UC1);
//	for (int i = 0; i < rowOK; i++)
//	{
//		for (int j = 0; j < colOK; j++)
//		{
//			resultImg.at<uchar>(i, j) =
//				diff_dst.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//		}
//	}
//	imshow("result", resultImg);
//	//连通区域去噪
//	ROIComDenoise(resultImg, resultImg, AreaLimit);
//	imshow("noNoise", resultImg);
//
//	//结果判断
//	int resultNum = 0;
//	for (int i = 0; i<rowOK; i++)
//	{
//		for (int j = 0; j < colOK; j++)
//		{
//			if (resultImg.at<uchar>(i, j) > 0)
//			{
//				resultNum++;
//			}
//		}
//	}
//
//	if (resultNum < 200){
//		cout << "this is OK !" << endl;    //ok
//	}
//	else{
//		cout << "this is NG !" << endl;     //ng
//	}
//
//	////----------------->时间统计<--------------------------------------------------------------
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	//cout << "代码的运行时间为" << dtime << "毫秒!" << endl;
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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