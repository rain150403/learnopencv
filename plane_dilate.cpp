//#include<opencv2\opencv.hpp>
//#include<iostream>
//using namespace std;
//using namespace cv;
//
//Point ptStart;
//
//
///***************************************************
//���ܣ���ptStartΪ����ͼ��������
//������src-�߽�ͼ��
//ptStart-���ӵ������
//****************************************************/
//void BoundarySeedFill(Mat &src, Point ptStart)
//{
//	Mat dst = Mat::zeros(src.size(), src.type());
//	int se[3][3] = { { -1, 1, -1 }, { 1, 1, 1 }, { -1, 1, -1 } };//ʮ���νṹԪ��
//	Mat tempImg = Mat::ones(src.size(), src.type()) * 255;
//	Mat revImg = tempImg - src;//ԭͼ��Ĳ���
//	dst.at<uchar>(ptStart.y, ptStart.x) = 255;//�������ӵ�
//	while (true)//ѭ������ͼ��ֱ��ͼ���ڲ����仯
//	{
//		Mat temp;
//		dst.copyTo(temp);
//		dilate(dst, dst, se); //��ʮ�ֽṹԪ������
//		dst = dst&revImg; //�������Ͳ��ᳬ��ԭʼ�߽�
//		if (equalImg(dst, temp)) //���ڱ仯ʱֹͣ
//		{
//			break;
//		}
//	}
//	src = dst;
//
//}
//void on_MouseHandle(int event, int x, int y, int flag, void* param)
//{
//	Mat& image = *(cv::Mat*)param;
//	switch (event)
//	{
//	case EVENT_LBUTTONDOWN:
//		ptStart.x = x;
//		ptStart.y = y;
//		break;
//	case EVENT_LBUTTONUP:
//		BoundarySeedFill(image, ptStart);
//		imshow("�߽�ͼ��", image);
//		break;
//	}
//}
//
//int main()
//{
//	//��ȡ��ֵͼ�񣨴˲����Ժ��ԣ�
//	Mat src = imread("test1.jpg", 0);
//	imshow("ԭʼͼ��", src);
//
//	//����ģ��
//	int se[3][3] = { { -1, 1, -1 }, { 1, 1, 1 }, { 1, 1, 1 } };
//
//	//�������
//	setMouseCallback("�߽�ͼ��", on_MouseHandle, (void*)&src);
//	waitKey(0);
//	return 0;
//}
//
////https ://blog.csdn.net/wxplol/article/details/73137397 
