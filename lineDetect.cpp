//ֱ�߼�⺯��

//���һ������Σ� һ���Ǿ��μ�ֱ�ߣ���С����ͼ���� һ����ֻ��ֱ�ߣ���ɫͼ��
//�ڴ��޸Ĵ������棬�޷Ǿ����ڼ�����ʱ�򣬻�����Ҫ�ĵ㣬 ��һ��㲻ͬ
//�޷Ǿ��ǻҶȱ仯����Ե��⣬ֱ�߼�⣬ ���ߣ��ж���������������
//��hough�任Ҳ�ã�canny����Ҳ�ã���ֵ���ǿɵ����ģ�����һ��Ҫ���ϻ�����ȥ������ֵ��
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

int main8()
{
	Mat Image = imread("D:\\roiImage_2\\sample1\\00018.JPG", 0);
	Mat CannyImg;
	Canny(Image, CannyImg, 50, 200, 3);   ///140, 250
	imshow("CannyImg", CannyImg);

	Mat DstImg;
	cvtColor(Image, DstImg, CV_GRAY2BGR);

	vector<Vec4i> Lines;
	HoughLinesP(CannyImg, Lines, 1, CV_PI / 360, 170, 30, 15);
	for (size_t i = 0; i < Lines.size(); i++)
	{
		line(DstImg, Point(Lines[i][0], Lines[i][1]), Point(Lines[i][2], Lines[i][3]), Scalar(0, 0, 255), 2, 8);
	}
	imshow("HoughLines_Detect", DstImg);
	//imwrite(".//res//HoughLines_Detect.jpg", DstImg);
	waitKey(0);
	return 0;
}