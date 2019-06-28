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
//	//��ֵ��
//	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
//	threshold(grayImg, thrImg, 200, 255, 3);    //170 ����, ����a\\3.jpg,,ȥ�������Ϊ10 Ҳ����
//
//	imshow("erzhihua", thrImg);
//	imwrite("D:\\roiImage_2\\sample3\\save\\��ֵ��.jpg", thrImg);
//
//	ROIComDenoise(thrImg, thrImg, AreaLimit);
//
//	//��ʴ
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
//	//����canny���Ӽ���Ե 
//	Canny(thrImg, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//Ѱ������ 
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
//		cout << "����ƬΪokƬ��" << endl;
//	}
//	else{
//		m_resultDetectCom = 0;
//		cout << "����ƬΪngƬ��" << endl;
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
//////			cout << "����ƬΪokƬ��" << endl;
//////		}
//////		else{
//////			cout << "����ƬΪngƬ��" << endl;
//////			strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//////			//imwrite(strImg, thrImg);
//////			//ng_num++;
//////		}
//////	}
//////
//////	//cout << "��ͼƬ����" << fileNames.size() << ", ngͼƬ��:" << ng_num << endl;
//////
//////	QueryPerformanceCounter(&nEndTime);
//////	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//////	cout << "���������ʱ��Ϊ" << dtime << "��!" << endl;
//////
//////	waitKey(0);
//////	system("pause");
//////	return 0;
//////}
//////
////////bool binaryThreshold(Mat srcImg, int i){
////////	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
////////	threshold(grayImg, thrImg, 200, 255, 3);    //170 ����
////////	imshow("��ֵ��", thrImg);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\��ֵ��.jpg", thrImg);
////////	//waitKey(0);
////////
////////	morph(thrImg);
////////	
////////	//////----------------->��������Ȧ��ȱ�ݣ�����ת���ɲ�ɫͼ����ܻ���ɫ����
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
////////	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////////	Mat element = getStructuringElement(MORPH_RECT, Size(3,3)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
////////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
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
////////	//����canny���Ӽ���Ե 
////////	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
////////	imshow("��Եͼ", canny_out);
////////	//Ѱ������ 
////////	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
////////	drawing = Mat::zeros(canny_out.size(), CV_8UC3);
////////	for (int i = 0; i < g_vContours.size(); i++) {
////////		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////////	}
////////	imshow("ȱ������ͼ", drawing);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
////////
////////	num_contours = g_vContours.size();
////////}