//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int detectThr = 1000;         //最后的白点个数阈值
//int EdgeGrayThr = 20;       //二值化的阈值     
//int DenoiseThr = 50;           //去噪的阈值
//
//bool ROIBubbleDetectMethod(Mat &srcImg, Mat &detectImage, int detectThr);
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int main(){
//	Mat src = imread("D:\\newSample\\BlueBlackHole√\\OK\\00002.JPG");
//	Mat dst = imread("D:\\newSample\\BlueBlackHole√\\NG\\00001.JPG");
//
//	ROIBubbleDetectMethod(src, dst, detectThr);
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//bool ROIBubbleDetectMethod(Mat &imgOK, Mat &detectImg, int detectThr)
//{
//	bool  m_resultDetectCom = 0;
//	int safePix = 5;
//
//	//高斯滤波， 获取原图边缘
//	GaussianBlur(detectImg, detectImg, Size(5, 5), 3, 3);
//
//	//normalize(detectImg, detectImg, 0, 255, cv::NORM_MINMAX);
//
//	imwrite("D:\\roiImgForTest\\TEST\\2detectImg.jpg", detectImg);
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//	
//	//高斯滤波,归一化
//	GaussianBlur(imgOK, imgOK, Size(5, 5), 3, 3);
//	cv::Mat edgeImgOk;
//	Canny(imgOK, edgeImgOk, 20, 20 * 3, 3);
//	//normalize(imgOK, imgOK, 0, 255, NORM_MINMAX);
//	imwrite("D:\\roiImgForTest\\TEST\\3imgOK.jpg", imgOK);
//	imwrite("D:\\roiImgForTest\\TEST\\3edgeimgOK.jpg", edgeImgOk);
//	int  rowOK = imgOK.rows;
//	int  colOK = imgOK.cols;
//
//	cv::Mat diff_dst;
//
//	////----------------->两图之差<-----------------------------------------------------
//	absdiff(imgOK, detectImg, diff_dst);
//	imwrite("D:\\roiImgForTest\\TEST\\7diff_dst.jpg", diff_dst);
//	//归一化
//	//normalize(diff_dst, diff_dst, 0, 255, NORM_MINMAX);
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			if (diff_dst.at<uchar>(i, j)>EdgeGrayThr)
//			{
//				diff_dst.at<uchar>(i, j) = 255;
//			}
//			else
//			{
//				diff_dst.at<uchar>(i, j) = 0;
//			}
//		}
//	}
//
//	imshow("1", diff_dst);
//	//边缘图像设置安全像素
//	cv::Mat elementSafe = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(safePix, safePix));
//
//	cv::Mat edgeImgSafe;
//	cv::dilate(edgeImgOk, edgeImgSafe, elementSafe);
//	imwrite("D:\\roiImgForTest\\TEST\\7edgeImgSafe.jpg", edgeImgSafe);
//	imshow("安全边界1", edgeImgSafe);
//	//反色
//	edgeImgSafe = (255 - edgeImgSafe) / 255;
//	imshow("安全边界", edgeImgSafe);
//
//	Mat resultImg = Mat::zeros(row, col, CV_8UC1);
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			resultImg.at<uchar>(i, j) =
//				diff_dst.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//		}
//	}
//	imwrite("D:\\roiImgForTest\\TEST\\7diff.jpg", diff_dst);
//	//连通区域去噪
//
//	imshow("2", diff_dst);
//	imshow("结果图像", resultImg);
//
//	//ROIComDenoise(resultImg, resultImg, DenoiseThr);
//
//
//	//结果判断
//	int resultNum = 0;
//	for (int i = 0; i<row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			if (resultImg.at<uchar>(i, j) > 0)
//			{
//				resultNum++;
//			}
//		}
//	}
//
//	if (resultNum < detectThr || resultNum >row*col*0.7)
//	{
//		m_resultDetectCom = 1;      //ok
//		cout << "ok" << endl;
//	}
//	else
//	{
//		m_resultDetectCom = 0;     //ng
//		cout << "这是ng" << endl;
//	}
//
//	return m_resultDetectCom;
//}
//
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