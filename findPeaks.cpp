//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//#define WINDOW_NAME "�����򴰿�1��"
//
//Mat g_maskImage, g_srcImage;
//Point prevPt(-1, -1);
//
//static void ShowHelpText();
//static void on_Mouse(int event, int x, int y, int flags, void*);
//
//int main(int argc, char** argv){
//	//����ԭͼ����ʾ����ʼ����Ĥ�ͻҶ�ͼ
//	g_srcImage = imread("1.jpg", 1);
//	imshow(WINDOW_NAME, g_srcImage);
//	Mat srcImage, grayImage;
//	g_srcImage.copyTo(srcImage);
//	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
//	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
//	g_maskImage = Scalar::all(0);
//
//	//�������ص�����
//	setMouseCallback(WINDOW_NAME, on_Mouse, 0);
//
//	//��ѯ������ ���д���
//	while (1){
//		//��ȡ��ֵ
//		int c = waitKey(0);
//
//		//��������ֵΪESCʱ���˳�
//		if ((char)c == 27)
//			break;
//
//		//��������ֵΪ2ʱ�� �ָ�
//
//
//
//	}
//
//}