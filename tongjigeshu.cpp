////ͭƬ��Ե���
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
//	//namedWindow("��Ե���", WINDOW_NORMAL);
//	//createTrackbar("��ֵ��", "��Ե���", &thresholds, 255, canny_track);//����������
//	//canny_track(0, 0);//�ص�����*****���ﲻҪ����д�������ܵ��ã�������
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
//	vector<Vec2f> lines;  //����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
//	HoughLines(canny_out, lines, 1, CV_PI / 180, 150, 0, 0);
//
//	//������ͼ�л��Ƴ�ÿ���߶�
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
//		//���������ֻ�ֱ�ߵķ����� ��color_dst��ֻ��ֱ��, ��dst_min_rec�ϼ���ֱ�����о���
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
//		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
//		Point2f vertices[4];    //������ε��ĸ�����
//		rect.points(vertices);   //������ε��ĸ�����
//		for (int i = 0; i < 4; i++){
//			line(src1, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//			imshow("juxing", src1);
//		}	
//	}
//
//	cout << "��������" << g_vContours.size() << endl;
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
//////////�������жϰװ߸���
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
////// ȥ������������   
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
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
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
////// �װ߸�����ȥ�����������㺯���Ľ�   
////void ROIWhiteCircle(Mat &Src, Mat &Dst, int AreaLimit)
////{
////	int num = 0;   //��¼��ͨ�������
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
////			{
////				//��ʼ���  
////				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
////
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
////
////				num++;  
////			}
////		}
////	}
////
////	cout << "�װ߸�����" << num << endl;
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
//////////�������жϰװ߸���
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
////// ȥ������������   
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
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
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
////			{   
////				//cout << "*******************************************************************" << endl;
////				//��ʼ���  
////				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
////				
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
////
////				num++;
////				//if (GrowBuffer.size()>AreaLimit) //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����    
////				//	CheckResult = 2;
////				//else
////				//{
////				//	CheckResult = 1;
////				//	RemoveCount++;//��¼�ж�������ȥ��  
////				//}
////
////				//for (int z = 0; z < GrowBuffer.size(); z++)
////				//{
////				//	CurrX = GrowBuffer.at(z).x;
////				//	CurrY = GrowBuffer.at(z).y;
////				//	PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//��ǲ��ϸ�����ص㣬����ֵΪ2  
////				//}
////				
////				//********�����õ㴦�ļ��**********    
////			}
////		}
////	}
////
////	cout << "�װ߸�����" << num << endl;
////
////	//cout << "�װ߸�����" << num << endl;
////
////	////��ʼ��ת�����С������    
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
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
////	morphologyEx(src, src, MORPH_ELLIPSE, element);
////
////	vector<vector<Point> > g_vContours;
////	vector<Vec4i> g_vHierarchy;
////	int contour_num = 0;
////
////	vector<Rect> boundRect(g_vContours.size());
////
////	//����canny���Ӽ���Ե 
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
////		cout << "�װ߸�����" << g_vContours.size() << endl;
////
////		Scalar color = Scalar(0, 255, 0);
////		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
////		imshow("drawing", drawing);
////		imwrite("D:\\roiImgForTest\\huahen\\drawing.jpg", drawing);
////
////		RotatedRect rect = minAreaRect(Mat(g_vContours[i]));   //���ڶԸ�����2D�㼯��Ѱ�ҿ���ת����С����İ�Χ����
////		Point2f vertices[4];    //������ε��ĸ�����
////		rect.points(vertices);   //������ε��ĸ�����
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
////	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
////	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
////	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
////	imshow("fushi", morph_out);
////	//imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
////}