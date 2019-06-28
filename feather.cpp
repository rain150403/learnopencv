/////https://blog.csdn.net/qq_37059483/article/details/78018539    二值图像连通域分析
////我怎么觉得使用连通区域的方法不好呢，还不如最小外接矩形， 以及最小外接多边形。
////可能是我没弄懂连通域在图像中的概念，而且我觉得求面积是一个不错的方法
#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using namespace cv;

typedef struct _Feather
{
	int label;              // 连通域的label值
	int area;               // 连通域的面积
	Rect boundingbox;       // 连通域的外接矩形框
} Feather;

/*
Input:
src: 待检测连通域的二值化图像
Output:
dst: 标记后的图像
featherList: 连通域特征的清单
return：
连通域数量。
*/
int bwLabel(Mat & src, Mat & dst, vector<Feather> & featherList)
{
	int rows = src.rows;
	int cols = src.cols;

	int labelValue = 0;
	Point seed, neighbor;
	stack<Point> pointStack;    // 堆栈

	int area = 0;               // 用于计算连通域的面积
	int leftBoundary = 0;       // 连通域的左边界，即外接最小矩形的左边框，横坐标值，依此类推
	int rightBoundary = 0;
	int topBoundary = 0;
	int bottomBoundary = 0;
	Rect box;                   // 外接矩形框
	Feather feather;

	featherList.clear();    // 清除数组

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
				labelValue++;           // labelValue最大为254，最小为1.
				seed = Point(j, i);     // Point（横坐标，纵坐标）
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

////D:\\样品图片\\sample9\\ng\\00051.JPG

int main3(int argc, char *argv[])
{
	Mat src(imread("D:\\roiImage_2\\00002.JPG", 0));
	if (src.empty())
		exit(-1);
	threshold(src, src, 127, 255, THRESH_BINARY);   // 二值化图像
	vector<Feather> featherList;                    // 存放连通域特征
	Mat dst;
	cout << "连通域数量： " << bwLabel(src, dst, featherList) << endl;

	// 为了方便观察，可以将label“放大”
	for (int i = 0; i < dst.rows; i++)
	{
		uchar *p = dst.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			p[j] = 30 * p[j];
		}
	}

	cout << "标号" << "\t" << "面积" << endl;
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