////Ѱ����С�������ͨ����
////D:\\��ƷͼƬ\\sample8\\ng\\00043.JPG
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

using namespace std;
using namespace cv;

Mat img_src, smallImg, gray, bw;
vector<Vec4i> hierarchy;
vector<vector<Point> > contours;
int threshval = 128;
Rect r;
Rect maxrect, brect;
int idx, n;

const static Scalar colors[15] = {
	CV_RGB(0, 0, 128),
	CV_RGB(0, 128, 0),
	CV_RGB(0, 128, 128),
	CV_RGB(128, 0, 0),
	CV_RGB(128, 0, 128),
	CV_RGB(128, 128, 0),
	CV_RGB(128, 128, 128),
	CV_RGB(160, 160, 160),
	CV_RGB(0, 0, 255),
	CV_RGB(0, 255, 0),
	CV_RGB(0, 255, 255),
	CV_RGB(255, 0, 0),
	CV_RGB(255, 0, 255),
	CV_RGB(255, 255, 0),
	CV_RGB(255, 255, 255),
};
Scalar color;

void gamma_correct(Mat& img, Mat& dst, double gamma) {
	Mat    temp;
	CvMat tmp;

	img.convertTo(temp, CV_32FC1, 1.0 / 255.0, 0.0);
	tmp = temp;
	cvPow(&tmp, &tmp, gamma);
	temp.convertTo(dst, CV_8UC1, 255.0, 0.0);
}

int main6() {
	cvNamedWindow("display", 1);
	img_src = imread("D:\\roiImage_2\\00002.JPG", 1);
	r.x = img_src.cols / 10;
	r.y = img_src.rows / 3;
	r.width = img_src.cols * 8 / 10;
	r.height = img_src.rows * 2 / 3;
	smallImg = img_src(r);
	cvtColor(smallImg, gray, CV_BGR2GRAY);
	//  medianBlur(gray,gray,5);
	equalizeHist(gray, gray);
	gamma_correct(gray, gray, 4.0);
	imshow("display", gray);
	waitKey(0);

	bw = (gray>threshval);
	imshow("display", bw);
	waitKey(0);

	Mat    Structure0 = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(bw, bw, Structure0, Point(-1, -1));
	Mat    Structure1 = getStructuringElement(MORPH_RECT, Size(6, 6));
	dilate(bw, bw, Structure1, Point(-1, -1));
	imshow("display", bw);
	waitKey(0);

	findContours(bw, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	if (!contours.empty() && !hierarchy.empty()) {
		idx = 0;
		n = 0;
		vector<Point> approx;
		for (; idx >= 0; idx = hierarchy[idx][0]) {
			color = colors[idx % 15];
			//          drawContours(smallImg,contours,idx,color,1,8,hierarchy);
			approxPolyDP(Mat(contours[idx]), approx, arcLength(Mat(contours[idx]), true)*0.005, true);//0.005Ϊ��ë����ֱ��ϵ��
			const Point* p = &approx[0];
			int m = (int)approx.size();
			polylines(smallImg, &p, &m, 1, true, color);
			circle(smallImg, Point(p[0].x, p[0].y), 3, color);
			circle(smallImg, Point(p[1].x, p[1].y), 2, color);
			for (int i = 2; i<m; i++) circle(smallImg, Point(p[i].x, p[i].y), 1, color);
			n++;
			if (1 == n) {
				maxrect = boundingRect(Mat(contours[idx]));
			}
			else {
				brect = boundingRect(Mat(contours[idx]));
				CvRect mr(maxrect), br(brect);
				maxrect = cvMaxRect(&mr, &br);
			}
		}
		circle(smallImg, Point(maxrect.x + maxrect.width / 2, maxrect.y + maxrect.height / 2), 2, CV_RGB(255, 0, 0));
	}
	imshow("display", smallImg);
	waitKey(0);
	cvDestroyWindow("display");
	return 0;
}
