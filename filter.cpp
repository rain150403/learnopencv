#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

const int MAX_KERNEL_LENGTH = 10;

const char *wn_name = "Smoothing";


static void salt(Mat &I, int n);
static void disp_caption(const char *wn_name, Mat src, const char *caption);
static void disp_image(const char *wn_name, Mat I);

/*
* @brief
* @inputs
* @outputs
* @retval
*/
int main23(int argc, char *argv[])
{
	//23
	/*if (argc<2) {
		cout << "Usage: ./image_smoothing [file name]" << endl;
		return -1;
	}
*/
	Mat I = imread("D:\\样品图片\\sample1\\ng\\7.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	salt(I, 6000);
	imshow(wn_name, I);
	waitKey(0);

	Mat dst;  // Result

	/* Homogeneous blur */
	disp_caption(wn_name, I, "Homogeneous blur");
	for (int i = 1; i<MAX_KERNEL_LENGTH; i += 2) {
		blur(I, dst, Size(i, i), Point(-1, -1));
		disp_image(wn_name, dst);
	}

	/* Guassian blur */
	disp_caption(wn_name, I, "Gaussian blur");
	for (int i = 1; i<MAX_KERNEL_LENGTH; i += 2) {
		GaussianBlur(I, dst, Size(i, i), 0, 0);
		disp_image(wn_name, dst);
	}

	/* Median blur */
	disp_caption(wn_name, I, "Median blur");
	for (int i = 1; i<MAX_KERNEL_LENGTH; i += 2) {
		medianBlur(I, dst, i);
		disp_image(wn_name, dst);
	}

	/* Bilatrial blur */
	disp_caption(wn_name, I, "Bilatrial blur");
	for (int i = 1; i<MAX_KERNEL_LENGTH; i += 2) {
		bilateralFilter(I, dst, i, i * 2, i / 2);
		disp_image(wn_name, dst);
	}
	waitKey(0);
	system("pause");
	return 0;
}

/*
* @brief   显示提示文字（滤波方法）
* @inputs
* @outputs
* @retval
*/
static void disp_caption(const char *wn_name, Mat src, const char *caption)
{
	Mat dst = Mat::zeros(src.size(), src.type());

	putText(dst, caption, Point(src.cols / 4, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar

		(255, 255, 255));

	imshow(wn_name, dst);
	waitKey(0);
}

/*
* @brief   显示图像
* @inputs
* @outputs
* @retval
*/
static void disp_image(const char *wn_name, Mat I)
{
	imshow(wn_name, I);
	waitKey(1000);
}

/*
* @brief   添加椒盐噪声
* @inputs
* @outputs
* @retval
*/
static void salt(Mat &I, int n = 3000)
{
	for (int k = 0; k<n; k++) {
		int i = rand() % I.cols;
		int j = rand() % I.rows;


		if (I.channels()) {
			I.at<uchar>(j, i) = 255;
		}
		else {
			I.at<Vec3b>(j, i)[0] = 255;
			I.at<Vec3b>(j, i)[1] = 255;
			I.at<Vec3b>(j, i)[2] = 255;
		}
	}
}