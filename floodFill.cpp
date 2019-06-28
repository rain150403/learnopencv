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
//////看了看，大概就是选取一个种子点，该点周围的和它像素相近的（在low， up范围内）， 就涂上同样的颜色，至于其他地方有相同像素值的，如果不连通，也不管。
//
//Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;
//int g_nFillMode = 1;    //漫水填充的模式
//int g_nLowDifference = 20, g_nUpDifference = 20;    //负差最大值，正差最大值
//int g_nConnectivity = 4;   //表示floodfill函数标识符低八位的连通值
//int g_bIsColor = true;      //是否为彩色图的标识符布尔值
//bool g_bUseMask = false;    //是否显示掩模窗口的布尔值
//int g_nNewMaskVal = 255;    //新的重新绘制的像素值
//
//
//static void onMouse(int event, int x, int y, int, void*){
//	
//	// 若鼠标左键没有按下， 便返回
//	if (event != EVENT_LBUTTONDOWN)
//		return;
//
//	////////////调用flood Fill函数之前的参数准备部分
//	Point seed = Point(x, y);
//	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference; //空范围的漫水填充， 此值设为0， 否则设为全局的g_nLowDifference
//	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;   //空范围的漫水填充， 此值设为0， 否则设为全局的g_nUpDifference
//
//
//	//标识符的0-7位为g_nConnectivity， 8-15位为g_nNewMaskVal左移8位的值
//	//16-23位为CV_FLOODFILL_FIXED_RANGE或者0
//	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
//
//	//随机生成RGB值
//	int b = (unsigned)theRNG() & 255;   //随机返回一个0-255之间的值
//	int g = (unsigned)theRNG() & 255;
//	int r = (unsigned)theRNG() & 255;
//	Rect ccomp;    //定义重绘区域的最小边界矩形区域
//
//	//在重绘区域像素的新值，若是彩色模式取， 若是灰度图模式，取
//	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);
//
//	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
//	int area;
//
//	///正式调用 flood fill函数
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
//	imshow("效果图", dst);
//	cout << area << "个像素被重绘\n";
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
//	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);   //转换三通道的image0到灰度图
//	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1);   //利用image0的尺寸来初始化掩膜mask
//
//	namedWindow("效果图", WINDOW_AUTOSIZE);
//
//	createTrackbar("负差最大值", "效果图", &g_nLowDifference, 255, 0);
//	createTrackbar("正差最大值", "效果图", &g_nUpDifference, 255, 0);
//
//	setMouseCallback("效果图", onMouse, 0);
//
//	//循环轮询按键
//	while (1){
//		imshow("", g_bIsColor?g_dstImage:g_grayImage);
//		
//		//获取键盘按键
//		int c = waitKey(0);
//		//判断ESC 是否按下， 若按下便退出
//		if ((c & 255) == 27){
//			cout << "...\n";
//			break;
//		}
//
//		//根据按键的不同， 进行各种操作
//		switch ((char)c){
//		
//		//如果键盘“1”被按下， 效果图在灰度图、彩色图之间互换
//		case '1':
//			if (g_bIsColor){   //若为彩色，先转为灰度图， 并且将掩膜mask所有元素设置为0
//				cout << "键盘“1”被按下，切换彩色/灰度模式\n"; 
//				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
//				g_maskImage = Scalar::all(0);
//				g_bIsColor = false;   //灰度图
//			}
//			else{  //若原来为灰度图， 便将原来的彩图image0再次复制给image， 并且将掩膜mask所有元素设置为0
//				cout << "键盘“1”被按下，切换彩色/灰度模式\n";
//				g_srcImage.copyTo(g_dstImage);
//				g_maskImage = Scalar::all(0);
//				g_bIsColor = true;    //彩色图
//			}
//			break;
//		//如果键盘按键“2”被按下， 显示/隐藏掩膜窗口
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
//			cout << "恢复原始图像\n";
//			g_srcImage.copyTo(g_dstImage);
//			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
//			g_maskImage = Scalar::all(0);
//			break;
//		case '4':
//			cout << "按键‘4’被按下， 使用空范围的漫水填充\n";
//			g_nFillMode = 0;
//			break;
//		case '5':
//			cout << "按键‘5’被按下， 使用渐变、固定范围的漫水填充\n";
//			g_nFillMode = 1;
//			break;
//		case '6':
//			cout << "按键‘6’被按下， 使用渐变、浮动范围的漫水填充\n";
//			g_nFillMode = 2;
//			break;
//		case '7':
//			cout << "按下‘7’， 操作标识符的低八位使用4位的连接模式\n";
//			g_nConnectivity = 4;
//			break;
//		case '8':
//			cout << "按下‘8’， 操作标识符的低八位使用8位的连接模式\n";
//			g_nConnectivity = 8;
//			break;
//		}
//	}
//	return 0;
//}