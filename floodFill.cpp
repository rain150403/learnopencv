//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
////int main(){
////	Mat src = imread("D:\\newSample\\0508\\a\\7.jpg");
////	
////	//Mat src = imread("1.jpg");
////
////	//cvtColor(src, src, CV_BGR2GRAY);
////	threshold(src, src, 200, 255, 3);
////	imshow("yuanshitu", src);
////	Rect ccomp;
////	//floodFill(src, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
////	floodFill(src, Point(120, 120), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(80, 80, 80));
////	imshow("xiaoguotu", src);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
//////���˿�����ž���ѡȡһ�����ӵ㣬�õ���Χ�ĺ�����������ģ���low�� up��Χ�ڣ��� ��Ϳ��ͬ������ɫ�����������ط�����ͬ����ֵ�ģ��������ͨ��Ҳ���ܡ�
//
//Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;
//int g_nFillMode = 1;    //��ˮ����ģʽ
//int g_nLowDifference = 20, g_nUpDifference = 20;    //�������ֵ���������ֵ
//int g_nConnectivity = 4;   //��ʾfloodfill������ʶ���Ͱ�λ����ֵͨ
//int g_bIsColor = true;      //�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
//bool g_bUseMask = false;    //�Ƿ���ʾ��ģ���ڵĲ���ֵ
//int g_nNewMaskVal = 255;    //�µ����»��Ƶ�����ֵ
//
//
//static void onMouse(int event, int x, int y, int, void*){
//	
//	// ��������û�а��£� �㷵��
//	if (event != EVENT_LBUTTONDOWN)
//		return;
//
//	////////////����flood Fill����֮ǰ�Ĳ���׼������
//	Point seed = Point(x, y);
//	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference; //�շ�Χ����ˮ��䣬 ��ֵ��Ϊ0�� ������Ϊȫ�ֵ�g_nLowDifference
//	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;   //�շ�Χ����ˮ��䣬 ��ֵ��Ϊ0�� ������Ϊȫ�ֵ�g_nUpDifference
//
//
//	//��ʶ����0-7λΪg_nConnectivity�� 8-15λΪg_nNewMaskVal����8λ��ֵ
//	//16-23λΪCV_FLOODFILL_FIXED_RANGE����0
//	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
//
//	//�������RGBֵ
//	int b = (unsigned)theRNG() & 255;   //�������һ��0-255֮���ֵ
//	int g = (unsigned)theRNG() & 255;
//	int r = (unsigned)theRNG() & 255;
//	Rect ccomp;    //�����ػ��������С�߽��������
//
//	//���ػ��������ص���ֵ�����ǲ�ɫģʽȡ�� ���ǻҶ�ͼģʽ��ȡ
//	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
//
//	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
//	int area;
//
//	///��ʽ���� flood fill����
//	if (g_bUseMask){
//		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
//
//		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference), Scalar(UpDifference, UpDifference, UpDifference), flags);
//		imshow("mask", g_maskImage);
//	}
//	else{
//		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference), Scalar(UpDifference, UpDifference, UpDifference), flags);
//
//	}
//
//	imshow("Ч��ͼ", dst);
//	cout << area << "�����ر��ػ�\n";
//	waitKey(0);
//}
//
//
//int main(int argc, char** argv){
//	g_srcImage = imread("D:\\newSample\\0508\\a\\3.jpg", 1); //D:\\newSample\\0508\\a\\3.jpg
//	if (!g_srcImage.data){
//		return false;
//	}
//
//	g_srcImage.copyTo(g_dstImage);
//	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);   //ת����ͨ����image0���Ҷ�ͼ
//	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);   //����image0�ĳߴ�����ʼ����Ĥmask
//
//	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);
//
//	createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
//	createTrackbar("�������ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);
//
//	setMouseCallback("Ч��ͼ", onMouse, 0);
//
//	//ѭ����ѯ����
//	while (1){
//		imshow("", g_bIsColor?g_dstImage:g_grayImage);
//		
//		//��ȡ���̰���
//		int c = waitKey(0);
//		//�ж�ESC �Ƿ��£� �����±��˳�
//		if ((c & 255) == 27){
//			cout << "...\n";
//			break;
//		}
//
//		//���ݰ����Ĳ�ͬ�� ���и��ֲ���
//		switch ((char)c){
//		
//		//������̡�1�������£� Ч��ͼ�ڻҶ�ͼ����ɫͼ֮�以��
//		case '1':
//			if (g_bIsColor){   //��Ϊ��ɫ����תΪ�Ҷ�ͼ�� ���ҽ���Ĥmask����Ԫ������Ϊ0
//				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ\n"; 
//				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
//				g_maskImage = Scalar::all(0);
//				g_bIsColor = false;   //�Ҷ�ͼ
//			}
//			else{  //��ԭ��Ϊ�Ҷ�ͼ�� �㽫ԭ���Ĳ�ͼimage0�ٴθ��Ƹ�image�� ���ҽ���Ĥmask����Ԫ������Ϊ0
//				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ\n";
//				g_srcImage.copyTo(g_dstImage);
//				g_maskImage = Scalar::all(0);
//				g_bIsColor = true;    //��ɫͼ
//			}
//			break;
//		//������̰�����2�������£� ��ʾ/������Ĥ����
//		case '2':
//			if (g_bUseMask){
//				destroyWindow("mask");
//				g_bUseMask = false;
//			}
//			else{
//				namedWindow("mask", 0);
//				g_maskImage = Scalar::all(0);
//				imshow("mask", g_maskImage);
//				g_bUseMask = true;
//			}
//			break;
//		case '3':
//			cout << "�ָ�ԭʼͼ��\n";
//			g_srcImage.copyTo(g_dstImage);
//			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
//			g_maskImage = Scalar::all(0);
//			break;
//		case '4':
//			cout << "������4�������£� ʹ�ÿշ�Χ����ˮ���\n";
//			g_nFillMode = 0;
//			break;
//		case '5':
//			cout << "������5�������£� ʹ�ý��䡢�̶���Χ����ˮ���\n";
//			g_nFillMode = 1;
//			break;
//		case '6':
//			cout << "������6�������£� ʹ�ý��䡢������Χ����ˮ���\n";
//			g_nFillMode = 2;
//			break;
//		case '7':
//			cout << "���¡�7���� ������ʶ���ĵͰ�λʹ��4λ������ģʽ\n";
//			g_nConnectivity = 4;
//			break;
//		case '8':
//			cout << "���¡�8���� ������ʶ���ĵͰ�λʹ��8λ������ģʽ\n";
//			g_nConnectivity = 8;
//			break;
//		}
//	}
//	return 0;
//}