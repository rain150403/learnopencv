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
//	////------------------>ʱ��ͳ��<-------------------------------------
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
//	//��˹�˲�,��һ�� ��ȡԭͼ��Ե
//	GaussianBlur(detectImg, detectImg, Size(5, 5), 3, 3);
//	imshow("gauss", detectImg);
//	Mat edgeImgOk;
//	//Canny(detectImg, edgeImgOk, 20, 20 * 3, 3);
//	Canny(src, edgeImgOk, 80, 80 * 3, 3);  //����֣������ǻ�ȡԭͼ��Ե����ô�����Ǽ��ͼ��
//	imshow("edgeImgOk",edgeImgOk);
//	normalize(detectImg, detectImg, 0, 255, cv::NORM_MINMAX);
//	imshow("guiyihua", detectImg);
//	waitKey(0);
//
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//	
//	//��˹�˲�,��һ��
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
//	////----------------->��ͼ֮��<-----------------------------------------------------
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
//	//��Եͼ�����ð�ȫ����
//	Mat elementSafe = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(safePix, safePix));
//
//	cv::Mat edgeImgSafe;
//	cv::dilate(edgeImgOk, edgeImgSafe, elementSafe);
//	imshow("safe", edgeImgSafe);
//
//	//��ɫ�ҹ�һ��
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
//	//��ͨ����ȥ��
//	ROIComDenoise(resultImg, resultImg, AreaLimit);
//	imshow("noNoise", resultImg);
//
//	//����ж�
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
//	////----------------->ʱ��ͳ��<--------------------------------------------------------------
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	//cout << "���������ʱ��Ϊ" << dtime << "����!" << endl;
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//// ȥ������������   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
//{
//	int RemoveCount = 0;
//	//�½�һ����ǩͼ���ʼ��Ϊ0���ص㣬Ϊ�˼�¼ÿ�����ص����״̬�ı�ǩ��0����δ��飬1�������ڼ��,2�����鲻�ϸ���Ҫ��ת��ɫ����3������ϸ������   
//	//��ʼ����ͼ��ȫ��Ϊ0��δ���  
//	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
//	//ȥ��С��ͨ����İ�ɫ��  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (Src.at<uchar>(i, j) < 10)
//			{
//				PointLabel.at<uchar>(i, j) = 3;//��������ɫ����Ϊ�ϸ�����Ϊ3  
//			}
//		}
//	}
//
//	vector<Point2i>NeihborPos;//������ѹ������  
//	NeihborPos.push_back(Point2i(-1, 0));
//	NeihborPos.push_back(Point2i(1, 0));
//	NeihborPos.push_back(Point2i(0, -1));
//	NeihborPos.push_back(Point2i(0, 1));
//	//cout << "Neighbor mode: 8����." << endl;
//	NeihborPos.push_back(Point2i(-1, -1));
//	NeihborPos.push_back(Point2i(-1, 1));
//	NeihborPos.push_back(Point2i(1, -1));
//	NeihborPos.push_back(Point2i(1, 1));
//
//	int NeihborCount = 8;
//	int CurrX = 0, CurrY = 0;
//	//��ʼ���  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (PointLabel.at<uchar>(i, j) == 0)//��ǩͼ�����ص�Ϊ0����ʾ��δ���Ĳ��ϸ��  
//			{   //��ʼ���  
//				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
//				GrowBuffer.push_back(Point2i(j, i));
//				PointLabel.at<uchar>(i, j) = 1;//���Ϊ���ڼ��  
//				int CheckResult = 0;
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					for (int q = 0; q < NeihborCount; q++)
//					{
//						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
//						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
//						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //��ֹԽ��    
//						{
//							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
//							{
//								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //��������buffer    
//								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //���������ļ���ǩ�������ظ����    
//							}
//						}
//					}
//				}
//				if (GrowBuffer.size()>AreaLimit) //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����    
//					CheckResult = 2;
//				else
//				{
//					CheckResult = 1;
//					RemoveCount++;//��¼�ж�������ȥ��  
//				}
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					CurrX = GrowBuffer.at(z).x;
//					CurrY = GrowBuffer.at(z).y;
//					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//��ǲ��ϸ�����ص㣬����ֵΪ2  
//				}
//				//********�����õ㴦�ļ��**********    
//			}
//		}
//	}
//	//��ʼ��ת�����С������    
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