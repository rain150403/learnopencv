#include<iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

Mat src, dst;
#define WINDOW_NAME "canny"
int g_nThreash = 30;
int g_nMaxThreash = 300;

static void on_Track_Canny(int, void *)
{

	Canny(src, dst, g_nThreash, g_nThreash * 3, 3);
	imshow(WINDOW_NAME, dst);
}


int main16(int argc, char** argv)
{
	/*if (argc<2)
	{
	return -1;
	cout << "Error!please input the path of image!!!" << endl;
	}*/

	src = imread("D:\\ÑùÆ·Í¼Æ¬\\sample8\\ng\\00043.JPG");
	imshow("src", src);

	if (src.empty())
	{
		cout << "Load image error!!!" << endl;
		return -1;
	}
	GaussianBlur(src, src, Size(3, 3), 0, 0);

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("Threath:", WINDOW_NAME, &g_nThreash, g_nMaxThreash, on_Track_Canny);
	waitKey();
	return 0;
}