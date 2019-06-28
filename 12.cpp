//////////#include<iostream>
//////////#include<opencv2/opencv.hpp>
//////////////��ñ
//////////using namespace std;
//////////using namespace cv;
//////////
//////////Mat srcImage, dstImage;
//////////int g_nOpenValue = 0;
//////////
////////////�й������¼�ʱ�����Խ���ص�����
//////////void on_Trackbar(int, void *)
//////////{
//////////	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nOpenValue + 1, 2 * g_nOpenValue + 1));
//////////	morphologyEx(srcImage, dstImage, CV_MOP_TOPHAT, element);
//////////	imshow("����ñ���ڡ�", dstImage);
//////////}
//////////
//////////int main()
//////////{
//////////	srcImage = imread("D:\\newSample\\0513\\b\\22.JPG");
//////////	imshow("��ԭͼ��", srcImage);
//////////	dstImage.create(srcImage.size(), srcImage.type());
//////////
//////////	namedWindow("����ñ���ڡ�");
//////////	createTrackbar("Value", "����ñ���ڡ�", &g_nOpenValue, 100, on_Trackbar);
//////////	on_Trackbar(g_nOpenValue, 0);
//////////
//////////	waitKey(0);
//////////
//////////	return 0;
//////////}
////////
////////
////////
////////#include <opencv2/opencv.hpp>
////////#include <opencv2/highgui/highgui.hpp>
////////#include <opencv2/imgproc/imgproc.hpp>
////////#include <iostream>
////////
////////using namespace cv;
////////using namespace std;
////////
////////int blockSize = 100;
////////
////////void unevenLightCompensate(Mat &image, int blockSize);
////////void RemoveLightUnevenDistribution(cv::Mat &image, int blockSize);
////////
////////int main(){
////////	Mat image = imread("D:\\newSample\\0513\\b\\20.JPG");
////////
////////	imshow("1", image);
////////
////////	RemoveLightUnevenDistribution(image, blockSize);
////////
////////	imshow("2", image);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\image.jpg", image);
////////	Canny(image, image, 10, 50, 3);
////////	imshow("edge", image);
////////	waitKey(0);
////////	system("pause");
////////	return 0;
////////}
////////
////////void unevenLightCompensate(Mat &image, int blockSize)
////////{
////////	if (image.channels() == 3) cvtColor(image, image, 7);
////////	imshow("123", image);
////////	waitKey(0);
////////	double average = mean(image)[0];
////////	int rows_new = ceil(double(image.rows) / double(blockSize));
////////	int cols_new = ceil(double(image.cols) / double(blockSize));
////////	Mat blockImage;
////////	blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
////////	for (int i = 0; i < rows_new; i++)
////////	{
////////		for (int j = 0; j < cols_new; j++)
////////		{
////////			int rowmin = i*blockSize;
////////			int rowmax = (i + 1)*blockSize;
////////			if (rowmax > image.rows) rowmax = image.rows;
////////			int colmin = j*blockSize;
////////			int colmax = (j + 1)*blockSize;
////////			if (colmax > image.cols) colmax = image.cols;
////////			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
////////			double temaver = mean(imageROI)[0];
////////			blockImage.at<float>(i, j) = temaver;
////////		}
////////	}
////////	blockImage = blockImage - average;
////////	Mat blockImage2;
////////	resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
////////	Mat image2;
////////	image.convertTo(image2, CV_32FC1);
////////	Mat dst = image2 - blockImage2;
////////	dst.convertTo(image, CV_8UC1);
////////}
////////
////////void RemoveLightUnevenDistribution(cv::Mat &image, int blockSize)
////////{
////////	if (!image.data)
////////	{
////////		return;
////////	}
////////
////////	if (image.channels() == 3)
////////	{
////////		cvtColor(image, image, CV_RGB2GRAY);
////////		//cvtColor(image, image, CV_BGR2GRAY);
////////	}
////////	double average = mean(image)[0];
////////	int rows_block = ceil(double(image.rows) / double(blockSize));   //ceil  ���ش��ڻ��ߵ���ָ�����ʽ����С����
////////	int cols_block = ceil(double(image.cols) / double(blockSize));
////////	int num = 0;
////////	cv::Mat blockImage;
////////	blockImage = cv::Mat::zeros(rows_block, cols_block, CV_32FC1);
////////	for (int i = 0; i < rows_block; i++)
////////	{
////////		for (int j = 0; j < cols_block; j++)
////////		{
////////			int rowmin = i*blockSize;
////////			int rowmax = (i + 1)*blockSize;
////////			if (rowmax > image.rows) rowmax = image.rows;
////////			int colmin = j*blockSize;
////////			int colmax = (j + 1)*blockSize;
////////			if (colmax > image.cols) colmax = image.cols;
////////			cv::Mat imageROI = image(cv::Range(rowmin, rowmax), cv::Range(colmin, colmax));
////////			if (imageROI.data)
////////				num++;
////////			double temaver = mean(imageROI)[0];  ////��Ȼͼ����������ģ�����ʵ�Ƕ�ÿһ��ͼƬ�ĵ�0ͨ���Լ����ֵ�� ��Ϊ��λ�õ�ֵ
////////			blockImage.at<float>(i, j) = temaver;
////////		}
////////	}
////////	cout << "num" << num << endl;
////////
////////	//blockImage = blockImage - average;//subtract
////////	cv::Mat blockImageTemp = blockImage.clone();
////////	cv::convertScaleAbs(blockImage, blockImageTemp, 1 / average, 0);   //ʹ�����Ա任ת����������Ԫ�س�8λ�޷�������  �� �������ӣ�ƫ����  ��ÿһ����������*img+��
////////	//blockImage = blockImage - average
////////	cv::Mat blockImageResize;
////////	cv::resize(blockImage, blockImageResize, image.size(), (0, 0), (0, 0), cv::INTER_CUBIC);      //һ���Ǽ���ĳߴ磬һ������ԭͼ���������Ŷ��ٱ��������߲���ͬʱʹ��
////////	cv::Mat imageFloat;
////////	image.convertTo(imageFloat, CV_32FC1);
////////	cv::Mat dst = imageFloat - blockImageResize;
////////	dst.convertTo(image, CV_8UC1);
////////
////////	return;
////////}
//////
//////
////
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
/////��һ�����⣬ȱ�ݺ����ԣ�������Χ���ղ����ȣ����ӵ����ô�죿����
//Mat morph_out;
//int blockSize = 5;
//
//void unevenLightCompensate(Mat &image, int blockSize);
//
//int AreaLimit = 30;
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//void morph(Mat mor_input){
//	
//	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	Mat element = getStructuringElement(MORPH_RECT, Size(7,7)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
//	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
//	//morphologyEx(mor_input, morph_out, MORPH_DILATE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
//	//morphologyEx(morph_out, morph_out, MORPH_DILATE, element);
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//}
//
//////����8��ʱ�򣬹�Ϊ255��С��8����Ϊ0��Ӧ����8�������ֿ�С������
//void image_enhance(Mat image, Mat& enhance_img){
//
//	Mat imageLog(image.size(), CV_32FC3);
//	for (int i = 0; i < image.rows; i++){
//		for (int j = 0; j < image.cols; j++){
//			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
//			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
//			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
//		}
//	}
//	//��һ����0~255    
//	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
//	//ת����8bitͼ����ʾ    
//	convertScaleAbs(imageLog, enhance_img);
//	//imshow("Soure", image);
//	imshow("after", enhance_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg", enhance_img);
//}
//
//
/////���ڴ�ⲻ���ȵ����壬������ͼ����ǿ�ķ�������Ϊ������ܶ���ŵ�
////////12�� 345�� 68
//
////���Ƕ���ȱ�����ⲻ��
//
//int main(){
//	Mat src = imread("D:\\newSample\\0527\\2\\wmm\\3\\0.JPG");    //D:\\newSample\\mobileX\\1\\4.JPG
//	Mat dst = imread("D:\\newSample\\0527\\2\\wmm\\3\\3.JPG");
//	Mat diff_dst;
//
//	//unevenLightCompensate(src, blockSize);
//	//unevenLightCompensate(dst, blockSize);
//
//	cvtColor(src, src, CV_BGR2GRAY);
//	cvtColor(dst, dst, CV_BGR2GRAY);
//
//	Mat out;
//	//�˲�����
//
//	//boxFilter(src, out, -1, Size(5, 5));   //�����˲�
//	//blur(src, out, Size(11, 11));    //��ֵ�˲�
//	//GaussianBlur(src, out, Size(3, 3), 0, 0);    //��˹�˲�
//
//	medianBlur(src, out, 7);   //��ֵ�˲�
//	//bilateralFilter(src, out, 25, 25*2, 25/2);     //˫���˲�
//
//	Mat out2;
//	//�˲�����
//
//	//boxFilter(dst, out2, -1, Size(5, 5));   //�����˲�
//	//blur(dst, out2, Size(11, 11));    //��ֵ�˲�
//	//GaussianBlur(dst, out2, Size(3, 3), 0, 0);    //��˹�˲�
//
//	medianBlur(dst, out2, 7);   //��ֵ�˲�
//	//bilateralFilter(dst, out2, 25, 25*2, 25/2);     //˫���˲�
//
//	imshow("lvbo2", out2);
//	waitKey(0);
//
//
//	absdiff(out, out2, diff_dst);
//	//ROIComDenoise(diff_dst, diff_dst, AreaLimit);
//	imshow("cha", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff.jpg", diff_dst);
//	//waitKey(0);
//
//	Mat enhc_img;
//	//image_enhance(diff_dst, diff_dst);
//
//	Mat thr_img;
//	threshold(diff_dst, thr_img,8, 255, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img.jpg", thr_img);
//
//	Canny(thr_img, thr_img, 10, 10 * 3, 3);
//	imshow("123", diff_dst);
//	waitKey(0);
//
//	//ROIComDenoise(thr_img, thr_img, AreaLimit);
//	//imshow("erzhihua2", thr_img);
//	//imwrite("D:\\roiImage_2\\sample3\\save\\thr_img2.jpg", thr_img);
//
//	/*unevenLightCompensate(thr_img, blockSize);
//	imshow("erzhihua3", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img3.jpg", thr_img);*/
//
//	morph(thr_img);
//
//	//absdiff(src,morph_out, diff_dst);
//	//imshow("final", diff_dst);
//
//	/*for (int m = 0; m < diff_dst.rows; m++){
//		for (int n = 0; n < diff_dst.cols; n++){
//
//			int a = diff_dst.at<uchar>(m, n);
//			cout << a << ", ";
//		}
//		cout << endl;
//	}
//	cout << endl;*/
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


//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(){
//	Mat src = imread("D:\\roiImage\\1\\31.JPG");    //D:\\newSample\\mobileX\\1\\4.JPG
//	Mat dst = imread("D:\\roiImage\\1\\30.JPG");
//	Mat diff_dst;
//
//	//unevenLightCompensate(src, blockSize);
//	//unevenLightCompensate(dst, blockSize);
//
//	cvtColor(src, src, CV_BGR2GRAY);
//	cvtColor(dst, dst, CV_BGR2GRAY);
//
//	//Mat out;
//	//�˲�����
//
//	//boxFilter(src, out, -1, Size(5, 5));   //�����˲�
//	//blur(src, out, Size(11, 11));    //��ֵ�˲�
//	//GaussianBlur(src, out, Size(3, 3), 0, 0);    //��˹�˲�
//
//	//medianBlur(src, out, 7);   //��ֵ�˲�
//	//bilateralFilter(src, out, 25, 25*2, 25/2);     //˫���˲�
//	//imshow("lvbo", out);
//
//	//Mat out2;
//	//�˲�����
//
//	//boxFilter(dst, out2, -1, Size(5, 5));   //�����˲�
//	//blur(dst, out2, Size(11, 11));    //��ֵ�˲�
//	//GaussianBlur(dst, out2, Size(3, 3), 0, 0);    //��˹�˲�
//
//	//medianBlur(dst, out2, 7);   //��ֵ�˲�
//	//bilateralFilter(dst, out2, 25, 25*2, 25/2);     //˫���˲�
//
//	//imshow("lvbo2", out2);
//
//	//absdiff(out, out2, diff_dst);
//	absdiff(src, dst, diff_dst);
//	imshow("cha", diff_dst);
//
//	Mat thr_img;
//	threshold(diff_dst, thr_img,15, 255, CV_THRESH_BINARY);  ///180, 255      //30 ���89��ǿ����
//	imshow("erzhihua", thr_img);
//
//	Mat morph_out;
//	Mat element = getStructuringElement(MORPH_RECT, Size(7,7));
//	morphologyEx(thr_img, morph_out, MORPH_OPEN, element);
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//
//	waitKey(0);
//
//	system("pause");
//	return 0;
//}