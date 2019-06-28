//#include<opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int thresh = 0;  //��ǰ��ֵ
//int AreaLimit = 1000;
//
//int safePix = 5;
//
//// ȥ������������   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//int main(){
//	Mat srcImage = imread("D:\\roiImage_2\\sample3\\save\\thr_img.jpg");   ///D:\\newSample\\0513\\b\\11.jpg
//	imshow("ԭͼ", srcImage);
//	Mat dstImage = Mat::zeros(srcImage.size(), CV_32FC1);
//	Mat g_srcImage1 = srcImage.clone();
//	Mat g_grayImage;
//	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
//
//	int row, col;
//	row = srcImage.rows;
//	col = srcImage.cols;
//
//	Mat cannyOut;
//	Canny(g_srcImage1, cannyOut, 50, 100, 3);
//	imshow("��Ե", cannyOut);
//
//
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//���Ͳ���
//	Mat edgeImgSafe;
//	dilate(cannyOut, edgeImgSafe, elementSafe);
//	// ��ɫ���ҹ�һ����[0, 1]; 
//	//edgeImgSafe = (255 - edgeImgSafe) / 255;
//
//	imshow("��ȫ�߽�", edgeImgSafe);
//	
//	// 2 ������Եͼ�����
//	//Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	
//	cornerHarris(g_grayImage, dstImage, 2, 3, 0.001, BORDER_DEFAULT);
//
//	Mat harrisCorner;
//	threshold(dstImage, harrisCorner, 0.000001, 255, THRESH_BINARY);
//	//harrisCorner = 255 - harrisCorner;
//	imshow("��ֵ��", harrisCorner);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img.jpg", harrisCorner);
//
//	// ������ͼ��      
//	Mat resultImg = Mat::zeros(row, col, CV_8UC1);
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			resultImg.at<uchar>(i, j) =
//				harrisCorner.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//		}
//	}
//
//	imshow("���", resultImg);
//
//	//����⵽�ģ� �ҷ�����ֵ�����Ľǵ���Ƴ���
//	for (int j = 0; j < harrisCorner.rows; j++){     //normImage
//		for (int i = 0; i < harrisCorner.cols; i++){   //normImage
//			if ((int)harrisCorner.at<float>(j, i) > thresh + 30){
//				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
//			}
//		}
//	}
//	imshow("��ͼ3", g_srcImage1);
//
//	waitKey(0);
//	system("pause");
//	return 0;
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
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////#include<opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int thresh = 0;  //��ǰ��ֵ
////int AreaLimit = 1000;
////
////// ȥ������������   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
////
//////harris�ǵ��⣬���ڻҶȶԱȶ�Ҫ���е�ߣ�����һ��ͼ��������һ���֣�������ֻ�ܼ��һ���֡�ʣ�µĽǵ㶼�첻����
//////ɾ����һ���֣�ʣ�µĶԱȶȽϸߵĵط��������ֳ��������е�Ҳ�Ҳ����������Ϊʲô�����ĵ����
////
//////����Ҳ�����Ƚǵ��⣬�ٶ�ֵ����Ȼ��Զ�ֵ����ͼ��Ȧ����������������ľ��е����Ե��
////
////int main(){
////	Mat srcImage = imread("D:\\newSample\\0513\\b\\23.jpg");   ///D:\\newSample\\0513\\b\\11.jpg
////	imshow("ԭͼ", srcImage);
////	Mat dstImage = Mat::zeros(srcImage.size(), CV_32FC1);
////	Mat g_srcImage1 = srcImage.clone();
////	Mat g_grayImage;
////	cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
////
////	//�ù�һ�ŻҶ�ͼֱ�Ӷ�ֵ�������ײ����ܶ������㣬������ղ�������Ƭ
////
////	//Mat cornerStrength;
////	cornerHarris(g_grayImage, dstImage, 2, 3, 0.001, BORDER_DEFAULT);
////	//imshow("harris", cornerStrength);
////
////	Mat normImage, scaledImage;
////	//��һ����ת��
////	normalize(dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
////	imshow("��һ��", normImage);
////	convertScaleAbs(normImage, scaledImage);    //����һ�����ͼ���Ա任��8λ�޷�������
////
////	//cout << scaledImage << endl;
////
////	//����⵽�ģ� �ҷ�����ֵ�����Ľǵ���Ƴ���
////	for (int j = 0; j < normImage.rows; j++){     //normImage
////		for (int i = 0; i < normImage.cols; i++){   //normImage
////			if ((int)normImage.at<float>(j, i) > thresh + 1){
////				circle(srcImage, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
////				circle(scaledImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);   //(0, 10, 255)
////			}
////		}
////	}
////	imshow("��ͼ1", srcImage);
////	imshow("��ͼ2", scaledImage);
////
////
////	Mat harrisCorner;
////	threshold(dstImage, harrisCorner, 0.000001, 255, THRESH_BINARY);
////	//harrisCorner = 255 - harrisCorner;
////	imshow("��ֵ��", harrisCorner);
////
////	/*ROIComDenoise(harrisCorner, harrisCorner, AreaLimit);
////	imshow("ȥ��", harrisCorner);*/
////
////	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////	Mat element = getStructuringElement(MORPH_RECT, Size(3,3)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
////	morphologyEx(harrisCorner, harrisCorner, MORPH_OPEN, element);
////	//morphologyEx(mor_input, morph_out, MORPH_DILATE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
////	//morphologyEx(morph_out, morph_out, MORPH_DILATE, element);
////	imshow("��ʴ", harrisCorner);
////
////	//����⵽�ģ� �ҷ�����ֵ�����Ľǵ���Ƴ���
////	for (int j = 0; j < harrisCorner.rows; j++){     //normImage
////		for (int i = 0; i < harrisCorner.cols; i++){   //normImage
////			if ((int)harrisCorner.at<float>(j, i) > thresh + 30){
////				circle(g_srcImage1, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);  //(10, 10, 255)
////				//circle(scaledImage, Point(j, i), 5, Scalar(0, 10, 255), 2, 8, 0);   //(0, 10, 255)
////			}
////		}
////	}
////	imshow("��ͼ3", g_srcImage1);
////	//imshow("��ͼ2", scaledImage);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////
////// ȥ������������   
////void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
////{
////	int RemoveCount = 0;
////	//�½�һ����ǩͼ���ʼ��Ϊ0���ص㣬Ϊ�˼�¼ÿ�����ص����״̬�ı�ǩ��0����δ��飬1�������ڼ��,2�����鲻�ϸ���Ҫ��ת��ɫ����3������ϸ������   
////	//��ʼ����ͼ��ȫ��Ϊ0��δ���  
////	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
////	//ȥ��С��ͨ����İ�ɫ��  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (Src.at<uchar>(i, j) < 10)
////			{
////				PointLabel.at<uchar>(i, j) = 3;//��������ɫ����Ϊ�ϸ�����Ϊ3  
////			}
////		}
////	}
////
////	vector<Point2i>NeihborPos;//������ѹ������  
////	NeihborPos.push_back(Point2i(-1, 0));
////	NeihborPos.push_back(Point2i(1, 0));
////	NeihborPos.push_back(Point2i(0, -1));
////	NeihborPos.push_back(Point2i(0, 1));
////	//cout << "Neighbor mode: 8����." << endl;
////	NeihborPos.push_back(Point2i(-1, -1));
////	NeihborPos.push_back(Point2i(-1, 1));
////	NeihborPos.push_back(Point2i(1, -1));
////	NeihborPos.push_back(Point2i(1, 1));
////
////	int NeihborCount = 8;
////	int CurrX = 0, CurrY = 0;
////	//��ʼ���  
////	for (int i = 0; i < Src.rows; i++)
////	{
////		for (int j = 0; j < Src.cols; j++)
////		{
////			if (PointLabel.at<uchar>(i, j) == 0)//��ǩͼ�����ص�Ϊ0����ʾ��δ���Ĳ��ϸ��  
////			{   //��ʼ���  
////				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
////				GrowBuffer.push_back(Point2i(j, i));
////				PointLabel.at<uchar>(i, j) = 1;//���Ϊ���ڼ��  
////				int CheckResult = 0;
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					for (int q = 0; q < NeihborCount; q++)
////					{
////						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
////						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
////						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //��ֹԽ��    
////						{
////							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
////							{
////								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //��������buffer    
////								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //���������ļ���ǩ�������ظ����    
////							}
////						}
////					}
////				}
////				if (GrowBuffer.size()>AreaLimit) //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����    
////					CheckResult = 2;
////				else
////				{
////					CheckResult = 1;
////					RemoveCount++;//��¼�ж�������ȥ��  
////				}
////
////				for (int z = 0; z < GrowBuffer.size(); z++)
////				{
////					CurrX = GrowBuffer.at(z).x;
////					CurrY = GrowBuffer.at(z).y;
////					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//��ǲ��ϸ�����ص㣬����ֵΪ2  
////				}
////				//********�����õ㴦�ļ��**********    
////			}
////		}
////	}
////	//��ʼ��ת�����С������    
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