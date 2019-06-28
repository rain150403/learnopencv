//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int detectThr = 1000;         //���İ׵������ֵ
//int EdgeGrayThr = 20;       //��ֵ������ֵ     
//int DenoiseThr = 50;           //ȥ�����ֵ
//
//bool ROIBubbleDetectMethod(Mat &srcImg, Mat &detectImage, int detectThr);
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int main(){
//	Mat src = imread("D:\\newSample\\BlueBlackHole��\\OK\\00002.JPG");
//	Mat dst = imread("D:\\newSample\\BlueBlackHole��\\NG\\00001.JPG");
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
//	//��˹�˲��� ��ȡԭͼ��Ե
//	GaussianBlur(detectImg, detectImg, Size(5, 5), 3, 3);
//
//	//normalize(detectImg, detectImg, 0, 255, cv::NORM_MINMAX);
//
//	imwrite("D:\\roiImgForTest\\TEST\\2detectImg.jpg", detectImg);
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//	
//	//��˹�˲�,��һ��
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
//	////----------------->��ͼ֮��<-----------------------------------------------------
//	absdiff(imgOK, detectImg, diff_dst);
//	imwrite("D:\\roiImgForTest\\TEST\\7diff_dst.jpg", diff_dst);
//	//��һ��
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
//	//��Եͼ�����ð�ȫ����
//	cv::Mat elementSafe = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(safePix, safePix));
//
//	cv::Mat edgeImgSafe;
//	cv::dilate(edgeImgOk, edgeImgSafe, elementSafe);
//	imwrite("D:\\roiImgForTest\\TEST\\7edgeImgSafe.jpg", edgeImgSafe);
//	imshow("��ȫ�߽�1", edgeImgSafe);
//	//��ɫ
//	edgeImgSafe = (255 - edgeImgSafe) / 255;
//	imshow("��ȫ�߽�", edgeImgSafe);
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
//	//��ͨ����ȥ��
//
//	imshow("2", diff_dst);
//	imshow("���ͼ��", resultImg);
//
//	//ROIComDenoise(resultImg, resultImg, DenoiseThr);
//
//
//	//����ж�
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
//		cout << "����ng" << endl;
//	}
//
//	return m_resultDetectCom;
//}
//
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