#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int num = 10;  //����������Χ
int pix = 100;  //ֱ��ͼ�ķ��

int main(){
	Mat srcImage = imread("D:\\newSample\\0619\\50.jpg",0);
	imshow("src", srcImage);
	if (!srcImage.data){
		cout << "fail to load image" << endl;
		return 0;
	}

	MatND dstHist;   //��CV����CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };    //������ҪΪconst����

	int size = 256;
	int channels = 0;

	//����ͼ���ֱ��ͼ
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;

	//cout << "dstHist : " << dstHist << endl;

	int row = dstHist.rows;
	int col = dstHist.cols;

	float *h = (float*)dstHist.data;
	double hh[256];
	if (h) {
		for (int i = 0; i < 256; ++i) {
			hh[i] = h[i];
		}
	}

	for (int i = 0; i < 256; i++){
		cout << hh[i] << ",";
	}
	cout << endl;
	
	vector<int> peakA, peakB;
	int k = 0;

	for (int i = 1; i < 255; i++){
		if ((hh[i] > hh[i - 1]) && (hh[i] > hh[i + 1])){
			peakA.push_back(i);
		}
	}
	cout << "size:" << peakA.size() << endl;

	for (int i = 0; i<peakA.size(); i++)
		cout << "λ�ã� " << peakA.at(i) << ", ����ֵ��" << hh[peakA.at(i)] << endl;

	//������
	for (auto it = peakA.begin(); it != peakA.end(); ++it){
		int flag = 0;
		for (int j = 1; j <= num; j++){
			if ((hh[*it - j] > hh[*it]) || (hh[*it + j] > hh[*it])){    //(hh[*it - j] > hh[*it]) || (hh[*it + j] > hh[*it]),(hh[*it - j] < hh[*it]) && (hh[*it + j] < hh[*it]) && (hh[*it] > pix)
				break;
			}
			else{
				//cout << hh[*it - j] << "," << h[*it] << "," << h[*it + j] << endl;
				//cout << "****************" << endl;
				flag++;
			}
		}

		if ((flag >= num - 3) && (hh[*it] > pix)){
			peakB.push_back(*it);
		}
	}
	
	cout << "peakB.size: " << peakB.size() << endl;

	cout << "******************************" << endl;

	for (int i = 0; i<peakB.size(); i++)
		cout << peakB.at(i) << endl;

	cout << "���շ�ĸ��� :" << peakB.size() << endl;

	Mat dstImage(size *scale, size, CV_8U, Scalar(0));

	//��ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//���Ƴ�ֱ��ͼ
	int hpt = saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++){
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("һάֱ��ͼ", dstImage);



	waitKey(0);
	system("pause");
	return 0;
}
//
//vector<int> peakA, peakB;
//for (int a = 0; a < peakA.size())



//
//
//
//
//
//
//
//
//
//
//

/*
����256��ֵ���Ƚϸ�ֵ�Ƿ�����Ҷ����������Ҳ�����п����Ƿ�ֵ��������

�ٱ�����Щ�������Ľ��Ʒ�ֵ���������������ʮ��ֵ�ķ�Χ�����������ģ���ô�������������ķ�ֵ��������

�Ƚ�����ͼ���ֱ��ͼ�ķ�ֵ�ĸ���
*/

//
//
//
//
//
//
//
//
//
//
//////////////////////////////////////////////////////////
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int main(){
////	Mat srcImage = imread("1.jpg", 0);
////	imshow("src", srcImage);
////	if (!srcImage.data)
////
////		waitKey(0);
////	system("pause");
////	return 0;
////}

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(){
//	Mat srcImage = imread("D:\\newSample\\0619\\50.jpg", 0);
//	imshow("src", srcImage);
//	if (!srcImage.data){
//		cout << "fail to load image" << endl;
//		return 0;
//	}
//
//	MatND dstHist;   //��CV����CvHistogram *hist = cvCreateHist
//	int dims = 1;
//	float hranges[] = { 0, 255 };
//	const float *ranges[] = { hranges };    //������ҪΪconst����
//	int size = 256;
//	int channels = 0;
//
//	//����ͼ���ֱ��ͼ
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
//	int scale = 1;
//
//	//cout << "dstHist : " << dstHist << endl;
//
//	int row = dstHist.rows;
//	int col = dstHist.cols;
//
//	float *h = (float*)dstHist.data;
//	double hh[256];
//	if (h) {
//		for (int i = 0; i < 256; ++i) {
//			hh[i] = h[i];
//		}
//	}
//
//	for (int i = 0; i < 256; i++){
//		cout << hh[i] << ",";
//	}
//	cout << endl;
//
//	vector<int> peakA;
//	int k = 0;
//
//	for (int i = 1; i < 255; i++){
//		if (hh[i] > hh[i - 1] && hh[i] < hh[i + 1]){
//			peakA.push_back(hh[i]);
//		}
//	}
//
//	/*for (int i = 0; i<peakA.size(); i++)
//	cout << peakA.at(i) << endl;*/
//
//	vector<int>::iterator ite, itj;
//	for (ite = peakA.begin(); ite != peakA.end(); ++ite){
//		for (itj = ite; itj < ite + 10; itj++)
//			if (*ite < *itj)
//				ite = peakA.erase(ite);
//	}
//
//
//
//	cout << "peakA.size: " << peakA.size() << endl;
//
//	cout << "******************************" << endl;
//
//	for (int i = 0; i<peakA.size(); i++)
//		cout << peakA.at(i) << endl;
//
//	cout << "jkj :" << peakA.size() << endl;
//	/*for (int i = 0; i < peakA.size(); i++){
//	for (int j = i; j < i + 10; j++){
//	if (peakA.at(j) > peakA.at(i)){
//
//	}
//	}
//	}*/
//
//	Mat dstImage(size *scale, size, CV_8U, Scalar(0));
//
//	//��ȡ���ֵ����Сֵ
//	double minValue = 0;
//	double maxValue = 0;
//	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
//
//	//���Ƴ�ֱ��ͼ
//	int hpt = saturate_cast<int>(0.9*size);
//	for (int i = 0; i < 256; i++){
//		float binValue = dstHist.at<float>(i);
//		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
//		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
//	}
//	imshow("һάֱ��ͼ", dstImage);
//
//
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}