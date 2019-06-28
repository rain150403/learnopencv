//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//#define WINDOW_NAME "【程序窗口1】"
//
//Mat g_maskImage, g_srcImage;
//Point prevPt(-1, -1);
//
//static void ShowHelpText();
//static void on_Mouse(int event, int x, int y, int flags, void*);
//
//int main(int argc, char** argv){
//	//载入原图并显示，初始化掩膜和灰度图
//	g_srcImage = imread("1.jpg", 1);
//	imshow(WINDOW_NAME, g_srcImage);
//	Mat srcImage, grayImage;
//	g_srcImage.copyTo(srcImage);
//	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
//	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
//	g_maskImage = Scalar::all(0);
//
//	//设置鼠标回调函数
//	setMouseCallback(WINDOW_NAME, on_Mouse, 0);
//
//	//轮询按键， 进行处理
//	while (1){
//		//获取键值
//		int c = waitKey(0);
//
//		//若按键键值为ESC时，退出
//		if ((char)c == 27)
//			break;
//
//		//若按键键值为2时， 恢复
//
//
//
//	}
//
//}