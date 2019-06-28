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
////Gamma�ҶȽ���
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
//			(*it)[0] = lut[((*it)[0])];   ///LUT���ұ�
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
//#define NUM_COL 11  //��ά������У� ÿһ����ȱ����Ϣ����ϸ��Ϣ
//#define MINAREA 0   //���С�ڸ���ֵ��������Ҫ��ɾ��
//#define MAXAREA 2000   //������ڸ���ֵ��������Ҫ��ɾ��
//
//RNG g_rng(12345);  //�����������
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
//	//����canny���Ӽ���Ե 
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
//		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
//		Point2f vertices[4];    //������ε��ĸ�����
//		rect.points(vertices);   //������ε��ĸ�����
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
//// �����ȹ��ղ���
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
////Gamma�ҶȽ���
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
////#define NUM_COL 11  //��ά������У� ÿһ����ȱ����Ϣ����ϸ��Ϣ
////#define MINAREA 0   //���С�ڸ���ֵ��������Ҫ��ɾ��
////#define MAXAREA 2000   //������ڸ���ֵ��������Ҫ��ɾ��
////
////Mat morph_out;
////
////RNG g_rng(12345);  //�����������
////  // �ɹ�  //�����Ѿ������������
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
////	//////////////////////////��������///////////////////////////////
////	////resize
////	//src_sz.width = src.rows * picture.scale;
////	//src_sz.height = SrcImage_origin.cols * picture.scale;
////	//SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
////	//resize(SrcImage_origin, SrcImage_or, src_sz, CV_INTER_CUBIC);
////
////	//imshow("ԭͼ", SrcImage_origin);
////
////	////��ͨ���ҶȻ�����
////	//g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////	//cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
////
////	////������ֵ��ԭͼ
////	//g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////	//threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
////
////	////��ʾ��ֵ�����ͼƬ
////	//imshow("��ֵ��", g_BinaryImage);
////
////	///////////////////////////////////////////////////////////////////////////////////////////////////////////
////	//double length = arcLength(g_vContours[i], true);  //�������������ܳ������ߵĳ��ȣ�Ĭ��closed
////	//double area = contourArea(g_vContours[i]);   //���ڼ������������򲿷������������ �����ŵ����ֵ��ʾ����
////
////	vector<Rect> boundRect(g_vContours.size());
////
////	Mat SrcImage;
////	Size sz;
////
////	//sz.width = dst.cols * SCALE;
////	//sz.height = dst.rows * SCALE;
////
////	//����canny���Ӽ���Ե 
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
////		//	cvSeqRemove(contour, 0); //ɾ�����С���趨ֵ������   
////		//	continue;
////		//}
////		//else
////		//{
////		//	liantong_all_area = liantong_all_area + tmparea;
////		//}
////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
////		Point2f vertices[4];    //������ε��ĸ�����
////		rect.points(vertices);   //������ε��ĸ�����
////		for (int i = 0; i < 4; i++){
////			cout << "����" << i << "���꣺" << vertices[i] << endl;
////			//////////////////////////////////////////////////////////////////////
////
////			///////////////////////////////////////////////////////////////////////
////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
////			imshow("juxing", src);
////			imwrite("D:\\roiImgForTest\\huahen\\juxing.jpg", src);
////		}
////
////		//��ΪcvPolyLineҪ��㼯������������CvPoint**
////		//����Ҫ�� CvPoint2D32f �͵� rect_pts0 ת��Ϊ CvPoint �͵� rect_pts
////		//������һ����Ӧ��ָ�� *pt
////		//int npts = 4;  //һ���м������㣬����һ���Ի������
////		//CvPoint rect_pts[4], *pt = rect_pts; //�ĸ�����
////
////		int temp = 0;
////		int sum_rect_x = 0, sum_rect_y = 0;
////		int rect_height = 0, rect_width = 0;
////		int rect_area = 0;
////		int rect_all_area = 0;
////
////		cout << "��ţ�" << contour_num << "��ͨ������С��Ӿ��ζ�������ֱ�Ϊ��" << endl;
////
////		//feature��һ����ά���飬��ȱ�ݵĸ�����ÿ��ȱ�ݵ�һЩ��Ϣ
////		int** feature = 0;
////		feature = new int*[130];
////		feature[contour_num] = new int[NUM_COL];
////
////		for (int i = 0; i < 4; i++){
////			feature[contour_num][i] = vertices[i].x;  //����ֵ�����0-3����
////			feature[contour_num][i + 4] = vertices[i].y;  //����ֵ�����4-7����
////
////			cout << "��" << i << "����������꣺" << vertices[i].x << ", " << vertices[i].y << endl;
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
////		cout << "��С��Ӿ��εĳ�Ϊ��" << rect_height << "����Ϊ��" << rect_width << "�������" << rect_area << endl;
////		feature[contour_num][8] = rect_height;   //����ֵ�����8����
////		feature[contour_num][9] = rect_width;   //����ֵ�����8����
////		feature[contour_num][10] = rect_area;   //����ֵ�����8����
////
////		rect_all_area += rect_area; //��С��Ӿ����ܵ����
////
////		int font_face = FONT_HERSHEY_COMPLEX;
////		Point origin;
////		origin.x = sum_rect_x / 4;
////		origin.y = sum_rect_y / 4;
////
////		char number_buf[10];  //������ʾ�����ֱ�Ŵ������飬puttext
////
////		double font_scale = 0.6;
////		int font_thickness = 0.8;
////
////		//���ֱ��
////		sprintf(number_buf, "%3d", contour_num);
////		string number_buf_string = number_buf;
////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
////
////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //���㲢����ָ���㼯������ľ��α߽�
////
////		Scalar color = Scalar(g_rng.uniform(0, 255));
////		//����Box
////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
////		contour_num++;       //��ͨ����������������ֱ��
////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////		imshow("drawing", drawing);
////		imwrite("D:\\roiImgForTest\\huahen\\drawing.jpg", drawing);
////	}
////
////	//������Ҳ��֪��ΪʲôҪ��ֱ�߼����һ��
////
////	//��֪��Ϊʲô����ͼ����Ϳ��Լ�⵽ֱ�ߣ������ο�ͼ����Ͳ��ܻ�ֱ�ߣ�����
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
//////////������
//////����任���ֱ��
////void hough_line(Mat src_hough){
////	Mat canny_out;
////	Mat color_dst;
////
////	Canny(src_hough, canny_out, 50, 200, 3);
////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
////
////	vector<Vec2f> lines;  //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
////
////	//������ͼ�л��Ƴ�ÿ���߶�
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
////		//���������ֻ�ֱ�ߵķ����� ��color_dst��ֻ��ֱ��, ��dst_min_rec�ϼ���ֱ�����о���
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
////	//��ȡͼƬ��һЩ����
////	int height2 = dst.rows;
////	int width2 = dst.cols;
////	int np = dst.channels();
////
////	cout << "tongdaoshu :" << np << endl;
////
////	//��ɫ����
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
////	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
////	imshow("fushi", morph_out);
////	//imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
////}
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
////////#define NUM_COL 11  //��ά������У� ÿһ����ȱ����Ϣ����ϸ��Ϣ
////////#define MINAREA 80   //���С�ڸ���ֵ��������Ҫ��ɾ��
////////#define MAXAREA 2000   //������ڸ���ֵ��������Ҫ��ɾ��
////////
////////RNG g_rng(12345);  //�����������
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
////////	//////////////////////////��������///////////////////////////////
////////	//resize
////////	src_sz.width = src.rows * picture.scale;
////////	src_sz.height = SrcImage_origin.cols * picture.scale;
////////	SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
////////	resize(SrcImage_origin, SrcImage_or, src_sz,  CV_INTER_CUBIC);
////////	
////////	imshow("ԭͼ",  SrcImage_origin);
////////	
////////	//��ͨ���ҶȻ�����
////////	g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////////	cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
////////	
////////	//������ֵ��ԭͼ
////////	g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
////////	threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
////////	
////////	//��ʾ��ֵ�����ͼƬ
////////	imshow("��ֵ��", g_BinaryImage);
////////	
////////	///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////	//double length = arcLength(g_vContours[i], true);  //�������������ܳ������ߵĳ��ȣ�Ĭ��closed
////////	//double area = contourArea(g_vContours[i]);   //���ڼ������������򲿷������������ �����ŵ����ֵ��ʾ����
////////		
////////	vector<Rect> boundRect(g_vContours.size());
////////	
////////	Mat SrcImage;
////////	Size sz;
////////
////////	//sz.width = dst.cols * SCALE;
////////	//sz.height = dst.rows * SCALE;
////////
////////	//����canny���Ӽ���Ե 
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
////////		//	cvSeqRemove(contour, 0); //ɾ�����С���趨ֵ������   
////////		//	continue;
////////		//}
////////		//else
////////		//{
////////		//	liantong_all_area = liantong_all_area + tmparea;
////////		//}
////////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
////////		Point2f vertices[4];    //������ε��ĸ�����
////////		rect.points(vertices);   //������ε��ĸ�����
////////		for (int i = 0; i < 4; i++){
////////			cout << "����" << i << "���꣺" << vertices[i] << endl;
////////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
////////			imshow("juxing", src);
////////		}
////////
////////		//��ΪcvPolyLineҪ��㼯������������CvPoint**
////////		//����Ҫ�� CvPoint2D32f �͵� rect_pts0 ת��Ϊ CvPoint �͵� rect_pts
////////		//������һ����Ӧ��ָ�� *pt
////////		//int npts = 4;  //һ���м������㣬����һ���Ի������
////////		//CvPoint rect_pts[4], *pt = rect_pts; //�ĸ�����
////////
////////		int temp = 0;
////////		int sum_rect_x = 0, sum_rect_y = 0;
////////		int rect_height = 0, rect_width = 0;
////////		int rect_area = 0;
////////		int rect_all_area = 0;
////////		
////////		cout << "��ţ�" << contour_num << "��ͨ������С��Ӿ��ζ�������ֱ�Ϊ��" << endl;
////////
////////		//feature��һ����ά���飬��ȱ�ݵĸ�����ÿ��ȱ�ݵ�һЩ��Ϣ
////////		int** feature = 0;
////////		feature = new int*[130];
////////		feature[contour_num] = new int[NUM_COL];
////////
////////		for (int i = 0; i < 4; i++){
////////			feature[contour_num][i] = vertices[i].x;  //����ֵ�����0-3����
////////			feature[contour_num][i + 4] = vertices[i].y;  //����ֵ�����4-7����
////////
////////			cout << "��" << i << "����������꣺" << vertices[i].x << ", " << vertices[i].y << endl;
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
////////		cout << "��С��Ӿ��εĳ�Ϊ��" << rect_height << "����Ϊ��" << rect_width << "�������" << rect_area << endl;
////////		feature[contour_num][8] = rect_height;   //����ֵ�����8����
////////		feature[contour_num][9] = rect_width;   //����ֵ�����8����
////////		feature[contour_num][10] = rect_area;   //����ֵ�����8����
////////
////////		rect_all_area += rect_area; //��С��Ӿ����ܵ����
////////
////////		int font_face = FONT_HERSHEY_COMPLEX;
////////		Point origin;
////////		origin.x = sum_rect_x / 4;
////////		origin.y = sum_rect_y / 4;
////////
////////		char number_buf[10];  //������ʾ�����ֱ�Ŵ������飬puttext
////////
////////		double font_scale = 0.6;
////////		int font_thickness = 0.8;
////////
////////		//���ֱ��
////////		sprintf(number_buf, "%3d", contour_num);
////////		string number_buf_string = number_buf;
////////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
////////
////////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //���㲢����ָ���㼯������ľ��α߽�
////////
////////		Scalar color = Scalar(g_rng.uniform(0, 255));
////////		//����Box
////////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
////////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
////////		contour_num++;       //��ͨ����������������ֱ��
////////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////////		imshow("drawing", drawing);
////////	}
////////
////////	//������Ҳ��֪��ΪʲôҪ��ֱ�߼����һ��
////////
////////	//��֪��Ϊʲô����ͼ����Ϳ��Լ�⵽ֱ�ߣ������ο�ͼ����Ͳ��ܻ�ֱ�ߣ�����
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
////////////������
//////////����任���ֱ��
////////void hough_line(Mat src_hough){
////////	Mat canny_out;
////////	Mat color_dst;
////////
////////	Canny(src_hough, canny_out, 50, 200, 3);
////////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
////////
////////	vector<Vec2f> lines;  //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
////////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
////////
////////	//������ͼ�л��Ƴ�ÿ���߶�
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
////////		//���������ֻ�ֱ�ߵķ����� ��color_dst��ֻ��ֱ��, ��dst_min_rec�ϼ���ֱ�����о���
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
////////	//��ȡͼƬ��һЩ����
////////	int height2 = dst.rows;
////////	int width2 = dst.cols;
////////	int np = dst.channels();
////////
////////	cout << "tongdaoshu :" << np << endl;
////////
////////	//��ɫ����
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
//////////ǰ��ͼ��Ԥ��������ԭͼ��resize�� �ҶȻ�����ֵ����
//////////ͼ��ʴ���� ���Ѷ��ѵĲ���������һ��
//////////�����ͨ����   �������ͨ��ɾ����߱���С���趨ֵ��������
//////////����С��Ӿ���  ����б����С��Ӿ��Σ�
//////////Houghֱ�߼��    ����֪��Ϊʲô��Ҫ��ֱ�߼�⣿��
//////////ͼ��ɫ    ��ͻ��ȱ�ݻ��ۣ�
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
//////////#define NUM_COL 11  //��ά������У� ÿһ����ȱ����Ϣ����ϸ��Ϣ
//////////#define MINAREA 80   //���С�ڸ���ֵ��������Ҫ��ɾ��
//////////#define MAXAREA 2000   //������ڸ���ֵ��������Ҫ��ɾ��
//////////
//////////RNG g_rng(12345);  //�����������
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
//////////	//double length = arcLength(g_vContours[i], true);  //�������������ܳ������ߵĳ��ȣ�Ĭ��closed
//////////	//double area = contourArea(g_vContours[i]);   //���ڼ������������򲿷������������ �����ŵ����ֵ��ʾ����
//////////		
//////////	vector<Rect> boundRect(g_vContours.size());
//////////	
//////////	Mat SrcImage;
//////////	Size sz;
//////////
//////////	//sz.width = dst.cols * SCALE;
//////////	//sz.height = dst.rows * SCALE;
//////////
//////////	//����canny���Ӽ���Ե 
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
//////////		//	cvSeqRemove(contour, 0); //ɾ�����С���趨ֵ������   
//////////		//	continue;
//////////		//}
//////////		//else
//////////		//{
//////////		//	liantong_all_area = liantong_all_area + tmparea;
//////////		//}
//////////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
//////////		Point2f vertices[4];    //������ε��ĸ�����
//////////		rect.points(vertices);   //������ε��ĸ�����
//////////		for (int i = 0; i < 4; i++){
//////////			cout << "����" << i << "���꣺" << vertices[i] << endl;
//////////			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//////////			imshow("juxing", src);
//////////		}
//////////
//////////		//��ΪcvPolyLineҪ��㼯������������CvPoint**
//////////		//����Ҫ�� CvPoint2D32f �͵� rect_pts0 ת��Ϊ CvPoint �͵� rect_pts
//////////		//������һ����Ӧ��ָ�� *pt
//////////		//int npts = 4;  //һ���м������㣬����һ���Ի������
//////////		//CvPoint rect_pts[4], *pt = rect_pts; //�ĸ�����
//////////
//////////		int temp = 0;
//////////		int sum_rect_x = 0, sum_rect_y = 0;
//////////		int rect_height = 0, rect_width = 0;
//////////		int rect_area = 0;
//////////		int rect_all_area = 0;
//////////		
//////////		cout << "��ţ�" << contour_num << "��ͨ������С��Ӿ��ζ�������ֱ�Ϊ��" << endl;
//////////
//////////		//feature��һ����ά���飬��ȱ�ݵĸ�����ÿ��ȱ�ݵ�һЩ��Ϣ
//////////		int** feature = 0;
//////////		feature = new int*[130];
//////////		feature[contour_num] = new int[NUM_COL];
//////////
//////////		for (int i = 0; i < 4; i++){
//////////			feature[contour_num][i] = vertices[i].x;  //����ֵ�����0-3����
//////////			feature[contour_num][i + 4] = vertices[i].y;  //����ֵ�����4-7����
//////////
//////////			cout << "��" << i << "����������꣺" << vertices[i].x << ", " << vertices[i].y << endl;
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
//////////		cout << "��С��Ӿ��εĳ�Ϊ��" << rect_height << "����Ϊ��" << rect_width << "�������" << rect_area << endl;
//////////		feature[contour_num][8] = rect_height;   //����ֵ�����8����
//////////		feature[contour_num][9] = rect_width;   //����ֵ�����8����
//////////		feature[contour_num][10] = rect_area;   //����ֵ�����8����
//////////
//////////		rect_all_area += rect_area; //��С��Ӿ����ܵ����
//////////
//////////		int font_face = FONT_HERSHEY_COMPLEX;
//////////		Point origin;
//////////		origin.x = sum_rect_x / 4;
//////////		origin.y = sum_rect_y / 4;
//////////
//////////		char number_buf[10];  //������ʾ�����ֱ�Ŵ������飬puttext
//////////
//////////		double font_scale = 0.6;
//////////		int font_thickness = 0.8;
//////////
//////////		//���ֱ��
//////////		sprintf(number_buf, "%3d", contour_num);
//////////		string number_buf_string = number_buf;
//////////		putText(src, number_buf_string, origin, font_face, 0.6, Scalar(0, 255, 255), 0.8, 8, 0);
//////////
//////////		//boundRect[i] = boundingRect(Mat(g_vContours[i]));    //���㲢����ָ���㼯������ľ��α߽�
//////////
//////////		Scalar color = Scalar(g_rng.uniform(0, 255));
//////////		//����Box
//////////		//cvPolyLine(drawing, &pt, &npts, 1, 1, CV_RGB(255, 0, 0), 1);
//////////		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
//////////		contour_num++;       //��ͨ����������������ֱ��
//////////		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//////////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//////////		imshow("drawing", drawing);
//////////
//////////		waitKey(0);
//////////	}
//////////
//////////	//������Ҳ��֪��ΪʲôҪ��ֱ�߼����һ��
//////////
//////////	//��֪��Ϊʲô����ͼ����Ϳ��Լ�⵽ֱ�ߣ������ο�ͼ����Ͳ��ܻ�ֱ�ߣ�����
//////////	hough_line(src);
//////////	hough_line(drawing);
//////////	
//////////	system("pause");
//////////	return 0;
//////////}
//////////
//////////
////////////����任���ֱ��
//////////void hough_line(Mat src_hough){
//////////	Mat canny_out;
//////////	Mat color_dst;
//////////
//////////	Canny(src_hough, canny_out, 50, 200, 3);
//////////	cvtColor(canny_out, color_dst, COLOR_GRAY2BGR);
//////////
//////////	vector<Vec2f> lines;  //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
//////////	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
//////////
//////////	//������ͼ�л��Ƴ�ÿ���߶�
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
//////////		//���������ֻ�ֱ�ߵķ����� ��color_dst��ֻ��ֱ��, ��dst_min_rec�ϼ���ֱ�����о���
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
////////////���ۼ��
//////////
//////////#include <opencv2\opencv.hpp>
//////////#include <iostream>
//////////
//////////using namespace cv;
//////////using namespace std;
//////////
//////////#define			WINDOW_NAME_BINARY "����ֵ��ͼƬ��"  //�����ֵ�����ڱ���
//////////#define			WINDOW_NAME_SRC "���Ҷ�ͼ��"   //����ԭͼ�񴰿ڱ������
//////////#define			WINDOW_NAME_SLIDER "����ֵ����ֵ��"  //��������������
//////////
//////////#define			num_col 11   //��ά������У�ÿһ����ȱ����Ϣ����ϸ��Ϣ
//////////
////////////����ͼƬ����
//////////Mat				g_GrayImage;
//////////Mat				g_BinaryImage;
//////////Mat				g_pGrayImage_liantong;
//////////Mat				g_pBinaryImage_liantong;
//////////
////////////��������
//////////int						contour_num = 0;  //�������ֱ��
//////////char					number_buf[10];  //���ֱ�Ŵ������飬puttext
//////////long int				liantong_all_area = 0;  //��ͨ���������
//////////long int				Rect_all_area = 0; //������С��Ӿ����ܵ����
//////////
////////////����ͼƬ·��
//////////string				srcPath = "1.jpg";
//////////
////////////////////////��ؽṹ�� ////////////////////////
//////////struct my_struct1{
//////////	double				scale;    //������ʾͼ��ı���
//////////	const int			threshold_value_binaryzation;   //�����һ�ζ�ֵ����ֵ
//////////	const int			threshold_value_second_binaryzation;  //����ڶ��ζ�ֵ����ֵ
//////////};
//////////my_struct1 picture = { 0.3, 50, 100 };
//////////
//////////struct my_struct2{
//////////	int				Model1_k1;   //ͼ��ʴ����
//////////	int				Model1_k2;   //ͼ��ʴ����
//////////	int				Model2_k1;   //ͼ��ʴ����
//////////	int				Model2_k2;   //ͼ��ʴ����
//////////};
//////////my_struct2 value = { 5, 2, 3, 2 };
//////////
//////////struct my_struct3{
//////////	double				maxarea;   //���ȱ�����
//////////	double				minarea;   //��С��ʾ������ȱ�����
//////////
//////////	double				font_scale;   //�����С
//////////	int						font_thickness;   //�����ϸ
//////////
//////////	const int			Feature_value2_number;   //����һ����ά������У���ȱ�ݵĸ���
//////////};
//////////my_struct3 value2 = { 0, 4, 0.6, 0.8, 100 };
//////////
//////////struct my_struct4{
//////////	const int			hough_Canny_thresh1;
//////////	const int			hough_Canny_thresh2;
//////////	const int			hough_Canny_kernel;
//////////
//////////	const int			cvHoughLines2_thresh;    //����ֵ���ڶ��ٲ���ʾ��ֵԽ����ʾ���߶�Խ��
//////////	const int			cvHoughLines2_param1;     //��ʾ�߶ε���С����
//////////	const int			cvHoughLines2_param2;     //�߶�֮�����С���
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
//////////	//����������Ķ�ά���飬����ָ������
//////////	int** Feature_value2 = 0;
//////////	Feature_value2 = new int*[value2.Feature_value2_number];
//////////
//////////	Mat SrcImage_or;
//////////	CvSize src_sz;
//////////
//////////	//////////////////////////��������///////////////////////////////
//////////	Mat SrcImage_origin = imread(srcPath);   //����ԭͼ
//////////
//////////	//resize
//////////	src_sz.width = SrcImage_origin.rows * picture.scale;
//////////	src_sz.height = SrcImage_origin.cols * picture.scale;
//////////	SrcImage_or = cvCreateImage(src_sz, SrcImage_origin.depth(), SrcImage_origin.channels());
//////////	resize(SrcImage_origin, SrcImage_or, src_sz,  CV_INTER_CUBIC);
//////////
//////////	imshow("ԭͼ",  SrcImage_origin);
//////////
//////////	//��ͨ���ҶȻ�����
//////////	g_GrayImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	cvtColor(SrcImage_or, g_GrayImage, CV_BGR2GRAY);
//////////
//////////	//������ֵ��ԭͼ
//////////	g_BinaryImage = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	threshold(g_GrayImage, g_BinaryImage, picture.threshold_value_binaryzation, 255, CV_THRESH_BINARY);
//////////
//////////	//��ʾ��ֵ�����ͼƬ
//////////	imshow("��ֵ��", g_BinaryImage);
//////////
//////////	///////////////////////////// ͼ��ʴ���� ////////////////////////////
//////////	// �����ͺ�ʴ�����Ϊ�պϲ�����ͼƬ�ж��Ѵ����ϡ�
//////////	// ������������������ϸС�ն��������ٽ����壬ƽ�������Ե��ͬʱ�����Ըı��������
//////////
//////////	Mat temp_cvDilate = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	//Mat temp_cvErode = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	Mat temp_cvErode_cvErode = cvCreateImage(src_sz, IPL_DEPTH_8U, 1);
//////////	
//////////	Mat element1 = getStructuringElement(MORPH_ELLIPSE,  Size(value.Model1_k1, value.Model1_k1), Point(value.Model1_k2, value.Model1_k2));
//////////	Mat element2 = getStructuringElement(MORPH_RECT, Size(value.Model2_k1, value.Model2_k1), Point(value.Model2_k2, value.Model2_k2));
//////////
//////////	//�����ͺ�ʴ
//////////	dilate(g_BinaryImage, temp_cvDilate, element1);
//////////	erode(temp_cvDilate, temp_cvErode_cvErode, element2);
//////////
//////////	imshow("��ʴ����", temp_cvErode_cvErode);
//////////	////////////////////////////////////////////////////////////////////////////////////
//////////
//////////	////////////////////////////�����ͨ���� //////////////////////////////////
//////////	g_BinaryImage = temp_cvErode_cvErode.clone();   //�����뿽���ģ����ǻ��������
//////////
//////////	Mat liantong_dst = Mat::zeros(src_sz, CV_8UC1);
//////////
//////////	//��ȡ����
//////////	findContours(g_BinaryImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
//////////
//////////	int n = -1, m = 0;   //nΪ���������������� mΪ����������
//////////
//////////	///------------------------------------------ ����ͨ���������� 
//////////	//��ȡ����������������ж������С��
//////////	//��1��ɾ�����С���趨ֵ����������2��ɾ����߱�С���趨ֵ�������� 
//////////	//����¼������������Ǹ�����������
//////////
//////////
//////////	//////////////////////////����С��Ӿ��� //////////////////////////////
//////////
//////////	double length = arcLength(contours[i], true);  //�������������ܳ������ߵĳ��ȣ�Ĭ��closed
//////////	double area = contourArea(contours[i]);   //���ڼ������������򲿷������������ �����ŵ����ֵ��ʾ����
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
//////////	///////////////////////////////////��ӡȱ�����ռ��////////////////
//////////	float temp_percent = 0.0;
//////////
//////////	cout << "��ͨ���������" << liantong_all_area << endl;   //��ӡ��ͨ��������� ����ǰ�汻�ڸǣ� ���Է��ں���
//////////	cout << "ͼ����������" << Rect_all_area << endl;
//////////	cout << "����ͼ�������" << sizeof_pic << endl;
//////////
//////////	temp_percent = (float)liantong_all_area / sizeof_pic * 100;
//////////	cout << "ȱ�����ռ�ȣ�" << temp_percent << endl;
//////////
//////////
//////////
//////////	////Hough�任���ֱ��
//////////
//////////
//////////	////////////////
//////////	//////ͼ��ɫ ///////////////
//////////
//////////	return Feature_value2; //ԭ�����Է�������
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
//////////	for (int i = 0; i < contour_num; i++){   //�ͷ��ڴ�
//////////		delete[] Tan_return[i];
//////////	}
//////////	delete[] Tan_return; 
//////////	waitKey(0);
//////////
//////////	////���ٴ��ڣ� �ͷ�ͼƬ��ʵ�������˳�ʱһ��Ҫ���ٴ��ڣ�
//////////	//destroyWindow();
//////////	//destroyWindow();
//////////	//cvReleaseImage();
//////////	//cvReleaseImage();
//////////	//cvReleaseImage();
//////////
//////////	system("pause");
//////////	return 0; 
//////////}