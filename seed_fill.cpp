#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stack>

using namespace std;
using namespace cv;

//#########################���������ɫ######################### 
Scalar icvprGetRandomColor() { 
	uchar r = 255 * (rand() / (1.0 + RAND_MAX)); 
	uchar g = 255 * (rand() / (1.0 + RAND_MAX)); 
	uchar b = 255 * (rand() / (1.0 + RAND_MAX)); 
	return Scalar(b, g, r); 
} 
//#########################���������ɫ######################### 

//########################������䷨��######################### 
void ConnectedCountBySeedFill(const Mat& _binImg, Mat& _lableImg, int &iConnectedAreaCount) { 
	//�ؿ�1�����ص�ԭ���ǣ������ͨ���ڱ�Ե�����д˺������쳣������������Ҫ����Χ��һȦ0ֵ��ȷ����ͨ���ڱ��� 
	//==========ͼ����Χ�ؿ�1������============================================ 
	int top, bottom; //����ӱ߽���ͼ��ߴ硿 
	int leftImage, rightImage; 
	int borderType = BORDER_CONSTANT; //BORDER_REPLICATE 
	//����ʼ�������� 
	top = (int)(1); bottom = (int)(1); 
	leftImage = (int)(1); rightImage = (int)(1); 
	Mat _binImg2, _binImg3; 
	_binImg.copyTo(_binImg2); 
	//��ʼ������value 
	Scalar value(0); //���ֵ 
	//����ͼ��߽� 
	copyMakeBorder(_binImg2, _binImg3, top, bottom, leftImage, rightImage, borderType, value); 
	
	//==========ͼ����Χ�ؿ�1������============================================ 
	
	// connected component analysis (4-component) 
	// use seed filling algorithm 
	// 1. begin with a foreground pixel and push its foreground neighbors into a stack; 
	// 2. pop the top pixel on the stack and label it with the same label until the stack is empty 
	// 
	// foreground pixel: _binImg(x,y) = 1 
	// background pixel: _binImg(x,y) = 0 
	
	if (_binImg3.empty() || _binImg3.type() != CV_8UC1) { return; } 
	
	_lableImg.release(); 
	_binImg3.convertTo(_lableImg, CV_32SC1); 
	int icount = 0; 
	int label = 1; // start by 2 
	
	int rows = _binImg3.rows - 1; 
	int cols = _binImg3.cols - 1; 
	for (int i = 1; i < rows - 1; i++) { 
		int* data = _lableImg.ptr<int>(i); //ȡһ������ 
		for (int j = 1; j < cols - 1; j++) { 
			if (data[j] == 1) //���ز�Ϊ0 
			{ 
				stack<pair<int, int>> neighborPixels; //�½�һ��ջ 
				neighborPixels.push(pair<int, int>(i, j)); // ��������: <i,j> ���Ը�����Ϊ��㣬Ѱ����ͨ�� 
				++label; // ��ʼһ���±�ǩ������ͨ������ı�־ 
				while (!neighborPixels.empty()) { 
					// ��ȡ��ջ�еĶ������ز�ʹ����ͬ�ı�ǩ������б�� 
					pair<int, int> curPixel = neighborPixels.top(); 
					int curX = curPixel.first; 
					int curY = curPixel.second; 
					_lableImg.at<int>(curX, curY) = label; //��ͼ���Ӧλ�õĵ���б�� 
					
					// ������������ ���������س�ջ�� 
					neighborPixels.pop(); 
					
					// ����8����� 
					if (_lableImg.at<int>(curX, curY - 1) == 1) {
						// ��� 
						neighborPixels.push(pair<int, int>(curX, curY - 1)); //��ߵ���ջ 
					} 
					if (_lableImg.at<int>(curX, curY + 1) == 1) {
						// �ҵ� 
						neighborPixels.push(pair<int, int>(curX, curY + 1)); //�ұߵ���ջ 
					} 
					if (_lableImg.at<int>(curX - 1, curY) == 1) {
						// �ϵ� 
						neighborPixels.push(pair<int, int>(curX - 1, curY)); //�ϱߵ���ջ 
					} 
					if (_lableImg.at<int>(curX + 1, curY) == 1) {
						// �µ� 
						neighborPixels.push(pair<int, int>(curX + 1, curY)); //�±ߵ���ջ 
					} 
					
					//===============���䵽8��ͨ��====================================================== 
					
					if (_lableImg.at<int>(curX - 1, curY - 1) == 1) {
						// ���ϵ� 
						neighborPixels.push(pair<int, int>(curX - 1, curY - 1)); //���ϵ���ջ 
					} 
					if (_lableImg.at<int>(curX - 1, curY + 1) == 1) {
						// ���ϵ� 
						neighborPixels.push(pair<int, int>(curX - 1, curY + 1)); //���ϵ���ջ 
					} 
					if (_lableImg.at<int>(curX + 1, curY - 1) == 1) {
						// ���µ� 
						neighborPixels.push(pair<int, int>(curX + 1, curY - 1)); //���µ���ջ 
					} 
					if (_lableImg.at<int>(curX + 1, curY + 1) == 1) {
						// ���µ� 
						neighborPixels.push(pair<int, int>(curX + 1, curY + 1)); //���µ���ջ 
					} 
					
					//===============���䵽8��ͨ��====================================================== 
				} 
			} 
		} 
	} 
	iConnectedAreaCount = label - 1; //��Ϊlabel��2��ʼ������ 
	int a = 0; 
} 

//#############�����ɫ##################################### 
Mat PaintColor(Mat src, int iConnectedAreaCount) { 
	int rows = src.rows; 
	int cols = src.cols; 
	
	//Scalar(b, g, r); 
	map<int, Scalar> colors; 
	for (int n = 1; n <= iConnectedAreaCount + 1; n++) { 
		colors[n] = icvprGetRandomColor(); //���ݲ�ͬ��־λ���������ɫ 
		Scalar color = colors[n]; 
		int a = color[0]; 
		int b = color[1]; 
		int c = color[2]; 
		int d = 0; 
	} 
	
	Mat dst2(rows, cols, CV_8UC3); 
	dst2 = Scalar::all(0); 
	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < cols; j++) { 
			int value = src.at<int>(i, j); 
			if (value>1) { 
				Scalar color = colors[value]; 
				int a = color[0]; 
				int b = color[1]; 
				int c = color[2]; 
				dst2.at<Vec3b>(i, j)[0] = color[0]; 
				dst2.at<Vec3b>(i, j)[1] = color[1]; 
				dst2.at<Vec3b>(i, j)[2] = color[2]; 
			} 
		} 
	} 
	
	return dst2; 
} 

//#############�����ɫ################################## 
//########����########################################## 
int main24(){
	////D:\\waitDelete\\VS_project\\GetPlateArea\\GetPlateArea\\circle.JPG
	////D:\\��ƷͼƬ\\sample1\\ng\\5.JPG

	Mat binImage = imread("D:\\roiImage_2\\tuxiangzengqiang\\log��.JPG", 0); 
	threshold(binImage, binImage, 80, 230, CV_THRESH_BINARY_INV); 
	// ��ͨ���� 
	Mat labelImg; 
	int iConnectedAreaCount = 0; //��ͨ����� 
	ConnectedCountBySeedFill(binImage, labelImg, iConnectedAreaCount);//��Ժڵװ��� 
	int a=iConnectedAreaCount; 
	
	// ��ʾ��� 
	Mat dstColor2=PaintColor(labelImg,iConnectedAreaCount); 
	imshow("colorImg", dstColor2); 
	Mat grayImg; 
	labelImg *= 10; 
	labelImg.convertTo(grayImg, CV_8UC1); 
	imshow("labelImg", grayImg); 
	waitKey(0); 
	return 0;
}