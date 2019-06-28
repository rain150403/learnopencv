/////https://blog.csdn.net/qq_37059483/article/details/78018539    ��ֵͼ����ͨ�����
////����ô����ʹ����ͨ����ķ��������أ���������С��Ӿ��Σ� �Լ���С��Ӷ���Ρ�
////��������ûŪ����ͨ����ͼ���еĸ�������Ҿ����������һ������ķ���
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using namespace cv;

typedef struct _Feather
{
	int label;              // ��ͨ���labelֵ
	int area;               // ��ͨ������
	Rect boundingbox;       // ��ͨ�����Ӿ��ο�
} Feather;

/*
Input:
src: �������ͨ��Ķ�ֵ��ͼ��
Output:
dst: ��Ǻ��ͼ��
featherList: ��ͨ���������嵥
return��
��ͨ��������
*/
int bwLabel(Mat & src, Mat & dst, vector<Feather> & featherList)
{
	int rows = src.rows;
	int cols = src.cols;

	int labelValue = 0;
	Point seed, neighbor;
	stack<Point> pointStack;    // ��ջ

	int area = 0;               // ���ڼ�����ͨ������
	int leftBoundary = 0;       // ��ͨ�����߽磬�������С���ε���߿򣬺�����ֵ����������
	int rightBoundary = 0;
	int topBoundary = 0;
	int bottomBoundary = 0;
	Rect box;                   // ��Ӿ��ο�
	Feather feather;

	featherList.clear();    // �������

	dst.release();
	dst = src.clone();
	for (int i = 0; i < rows; i++)
	{
		uchar *pRow = dst.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			if (pRow[j] == 255)
			{
				area = 0;
				labelValue++;           // labelValue���Ϊ254����СΪ1.
				seed = Point(j, i);     // Point�������꣬�����꣩
				dst.at<uchar>(seed) = labelValue;
				pointStack.push(seed);

				area++;
				leftBoundary = seed.x;
				rightBoundary = seed.x;
				topBoundary = seed.y;
				bottomBoundary = seed.y;

				while (!pointStack.empty())
				{
					neighbor = Point(seed.x + 1, seed.y);
					if ((seed.x != (cols - 1)) && (dst.at<uchar>(neighbor) == 255))
					{
						dst.at<uchar>(neighbor) = labelValue;
						pointStack.push(neighbor);

						area++;
						if (rightBoundary < neighbor.x)
							rightBoundary = neighbor.x;
					}

					neighbor = Point(seed.x, seed.y + 1);
					if ((seed.y != (rows - 1)) && (dst.at<uchar>(neighbor) == 255))
					{
						dst.at<uchar>(neighbor) = labelValue;
						pointStack.push(neighbor);

						area++;
						if (bottomBoundary < neighbor.y)
							bottomBoundary = neighbor.y;

					}

					neighbor = Point(seed.x - 1, seed.y);
					if ((seed.x != 0) && (dst.at<uchar>(neighbor) == 255))
					{
						dst.at<uchar>(neighbor) = labelValue;
						pointStack.push(neighbor);

						area++;
						if (leftBoundary > neighbor.x)
							leftBoundary = neighbor.x;
					}

					neighbor = Point(seed.x, seed.y - 1);
					if ((seed.y != 0) && (dst.at<uchar>(neighbor) == 255))
					{
						dst.at<uchar>(neighbor) = labelValue;
						pointStack.push(neighbor);

						area++;
						if (topBoundary > neighbor.y)
							topBoundary = neighbor.y;
					}

					seed = pointStack.top();
					pointStack.pop();
				}
				box = Rect(leftBoundary, topBoundary, rightBoundary - leftBoundary, bottomBoundary - topBoundary);
				rectangle(src, box, 255);
				feather.area = area;
				feather.boundingbox = box;
				feather.label = labelValue;
				featherList.push_back(feather);
			}
		}
	}
	return labelValue;
}

////D:\\��ƷͼƬ\\sample9\\ng\\00051.JPG

int main3(int argc, char *argv[])
{
	Mat src(imread("D:\\roiImage_2\\00002.JPG", 0));
	if (src.empty())
		exit(-1);
	threshold(src, src, 127, 255, THRESH_BINARY);   // ��ֵ��ͼ��
	vector<Feather> featherList;                    // �����ͨ������
	Mat dst;
	cout << "��ͨ�������� " << bwLabel(src, dst, featherList) << endl;

	// Ϊ�˷���۲죬���Խ�label���Ŵ�
	for (int i = 0; i < dst.rows; i++)
	{
		uchar *p = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			p[j] = 30 * p[j];
		}
	}

	cout << "���" << "\t" << "���" << endl;
	for (vector<Feather>::iterator it = featherList.begin(); it < featherList.end(); it++)
	{
		cout << it->label << "\t" << it->area << endl;
		rectangle(dst, it->boundingbox, 255);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();

	system("pause");
	return 0;
}