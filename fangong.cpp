//#include <opencv2/opencv.hpp>        
//#include <opencv2/highgui/highgui.hpp> 
//#include <opencv2/imgproc/imgproc.hpp> 
//
//#include <iostream> 
//#include<cmath>
//
//using namespace cv;
//using namespace std;
//
//double e, sigma, eta = 8;     //eta���ӣ�sigma����  ͼ���ǰ׵�    ///����С����ֻ��0.2�е�Ч����         //���ں���0.8���Էֿ�ȱ��
////eta���ӣ�sigmaҲ�����ӣ�����ʵ��׼ͼҲ����Ӱ�죬�����Խ�����ж�Ҳ��Ӱ�죬����˵����ֻ��ǰ���ߵĹ�ϵ������Ҳ������ٻ���Ӱ��
////eta���ӣ���׼ͼ���ɰ�ɫ��Ҳ���Ǻ���������ô�仯���ǰ�ɫ�ˣ���������Ȼ���µĺڵ������ˣ�����sigma����Ҳ���ǿ����̵ķ�ΧҲ�����ˡ�
//int mn, mx, ntrain = 40, w = 100, h = 100;///////w = 5, h = 5  eta=0.162;    //ntest = 20;
//Mat_<double> img(h, w), imge(h, w);
//Mat_<uchar> img1, imgs;
//
//
//// ���ڵȼ����ȡͼ������
//Mat imageReduction(Mat &srcImage, double kx, double ky)
//{
//	// ��ȡ���ͼ��ֱ���
//	int nRows = cvRound(srcImage.rows * kx);
//	int nCols = cvRound(srcImage.cols * ky);
//	Mat resultImage(nRows, nCols, srcImage.type());
//	for (int i = 0; i < nRows; ++i)
//	{
//		for (int j = 0; j < nCols; ++j)
//		{
//			// ����ˮƽ���Ӽ�������
//			int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
//			// ���ݴ�ֱ���Ӽ�������
//			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
//			resultImage.at<uchar>(i, j) =
//				srcImage.at<uchar>(x, y);
//		}
//	}
//	return resultImage;
//}
///*Vec3b areaAverage(const Mat &srcImage,
//Point_<int> leftPoint, Point_<int> rightPoint)
//{
//int temp1 = 0, temp2 = 0, temp3 = 0;
//// ���������ӿ����ص����
//int nPix = (rightPoint.x - leftPoint.x + 1)*
//(rightPoint.y - leftPoint.y + 1);
//// �����ӿ����ͨ��������ֵ���
//for (int i = leftPoint.x; i <= rightPoint.x; i++){
//for (int j = leftPoint.y; j <= rightPoint.y; j++){
//temp1 += srcImage.at<Vec3b>(i, j)[0];
//temp2 += srcImage.at<Vec3b>(i, j)[1];
//temp3 += srcImage.at<Vec3b>(i, j)[2];
//}
//}
//// ��ÿ��ͨ�����ֵ
//Vec3b vecTemp;
//vecTemp[0] = temp1 / nPix;
//vecTemp[1] = temp2 / nPix;
//vecTemp[2] = temp3 / nPix;
//return vecTemp;
//}*/
//
//void train()
//{
//	int i, j, k, s, num = 0;
//	double s1 = 0;
//	char filename[50];
//	Mat srcImage, srcGray, m = Mat::zeros(h, w, CV_8UC1), m1 = Mat::zeros(h, w, CV_64FC1);
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		m += srcGray;
//	}
//	imshow("һ�ŻҶ�ͼsrcGray", srcGray);   /////////here
//
//	img1 = m;
//	imshow("�ܺ�ͼ��img1", img1);          ///////////here
//	
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//			imge(j, k) = (double)img1(j, k) / ntrain;
//	}
//
//	imshow("��ֵͼ��imge", imge);     //////////////////here
//
//	/*cout << "****************************" << endl;
//	cout << imge << endl;
//	cout << "****************************" << endl;*/
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//				img(j, k) = (imgs(j, k) - imge(j, k))*(imgs(j, k) - imge(j, k)) / (ntrain - 1);
//		}
//		m1 += img;
//	}
//	img = m1;
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//			img(j, k) = eta*sqrt(img(j, k));
//	}
//
//	imshow("��׼ͼ��img", img);      ////////// here
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//					s++;
//			}
//		}
//		num += s;
//	}
//
//	cout << "ѵ��ͼƬһ���ķ��������ĵ���" << num << endl;    ///// here
//
//
//	for (i = 1; i <= ntrain; i++)
//	{
//		s = 0;
//		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
//		srcImage = imread(filename);
//		if (!srcImage.data)
//			return;
//		srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//		imgs = srcGray;
//		for (j = 0; j < srcImage.rows; j++)
//		{
//			for (k = 0; k < srcImage.cols; k++)
//			{
//				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//					s++;
//			}
//		}
//		cout << i << ".jpg" << "->" << s << endl;
//		s1 += (s - (double)num / ntrain)*(s - (double)num / ntrain);
//		if (i == 1)
//			mn = mx = s;
//		else
//		{
//			if (s < mn)
//				mn = s;
//			if (s > mx)
//				mx = s;
//		}
//	}
//	e = (double)num / ntrain;
//	sigma = sqrt(s1 / (ntrain - 1));
//	cout << "min:" << mn << endl;
//	cout << "max:" << mx << endl;
//	cout << "e:" << e << ' ' << "sigma:" << sigma << endl;
//
//	//waitKey(0);
//}
//
//int fasttest(Mat srcImage)
//{
//	int j, k, result, s = 0;
//	Mat srcGray;
//	if (!srcImage.data)
//		return 1;
//	srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
//	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
//	imgs = srcGray;
//
//	//Mat diff_dst;
//	//absdiff(double(imgs), imge, diff_dst);
//
//	for (j = 0; j < srcImage.rows; j++)
//	{
//		for (k = 0; k < srcImage.cols; k++)
//		{
//			if (abs(imgs(j, k) - imge(j, k))>img(j, k))
//			{
//				s++;
//				imgs(j, k) = 255;
//			}
//			else
//				imgs(j, k) = 0;
//		}
//	}
//
//	imshow("���ͼ", imgs);
//	//waitKey(0);
//
//	cout <<"����ֵ��" << s << endl;
//	if (s > e)
//		result = 0;
//	else
//		result = 1;
//	return result;
//}
//
//int main()
//{
//	int i, result;
//	char filename[50];
//	Mat srcImage;
//	cout << "Now, beginning to preprocess..." << endl;
//	train();
//	cout << "The preparation work is over, now beginning to test..." << endl;
//	for (i = 41; i <= 60; i++)
//	{
//		sprintf_s(filename, "D:\\roiImage_1\\test\\%05d.jpg", i);
//		srcImage = imread(filename);
//		result = fasttest(srcImage);
//		cout << i << ".jpg" << "->" << result << endl;
//		if (result == 0)
//		{
//			sprintf_s(filename, "D:\\roiImage_1\\ng\\%05d.jpg", i);
//			//imwrite(filename, srcImage);
//			imwrite(filename, imgs);
//		}
//		else
//		{
//			sprintf_s(filename, "D:\\roiImage_1\\ok\\%d.jpg", i);
//			imwrite(filename, imgs);
//		}
//	}
//	waitKey(0);
//	system("pause");
//	return 0;
//}
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
//
//
//
////#include <opencv2/opencv.hpp>        
////#include <opencv2/highgui/highgui.hpp> 
////#include <opencv2/imgproc/imgproc.hpp> 
////
////#include <iostream> 
////#include<cmath>
////
////using namespace cv;
////using namespace std;
////
////double e, sigma, eta = 0.6;     //eta���ӣ�sigma����  ͼ���ǰ׵�    ///����С����ֻ��0.2�е�Ч����         //���ں���0.8���Էֿ�ȱ��
//////eta���ӣ�sigmaҲ�����ӣ�����ʵ��׼ͼҲ����Ӱ�죬�����Խ�����ж�Ҳ��Ӱ�죬����˵����ֻ��ǰ���ߵĹ�ϵ������Ҳ������ٻ���Ӱ��
//////eta���ӣ���׼ͼ���ɰ�ɫ��Ҳ���Ǻ���������ô�仯���ǰ�ɫ�ˣ���������Ȼ���µĺڵ������ˣ�����sigma����Ҳ���ǿ����̵ķ�ΧҲ�����ˡ�
////int mn, mx, ntrain = 40, w = 1116, h = 239;///////w = 50, h = 50;    //ntest = 20;
////Mat_<double> img(h, w), imge(h, w);
////Mat_<uchar> img1, imgs;
////
////
////// ���ڵȼ����ȡͼ������
////Mat imageReduction(Mat &srcImage, double kx, double ky)
////{
////	// ��ȡ���ͼ��ֱ���
////	int nRows = cvRound(srcImage.rows * kx);
////	int nCols = cvRound(srcImage.cols * ky);
////	Mat resultImage(nRows, nCols, srcImage.type());
////	for (int i = 0; i < nRows; ++i)
////	{
////		for (int j = 0; j < nCols; ++j)
////		{
////			// ����ˮƽ���Ӽ�������
////			int x = static_cast<int>((i + 1) / kx + 0.5) - 1;
////			// ���ݴ�ֱ���Ӽ�������
////			int y = static_cast<int>((j + 1) / ky + 0.5) - 1;
////			resultImage.at<uchar>(i, j) =
////				srcImage.at<uchar>(x, y);
////		}
////	}
////	return resultImage;
////}
/////*Vec3b areaAverage(const Mat &srcImage,
////Point_<int> leftPoint, Point_<int> rightPoint)
////{
////int temp1 = 0, temp2 = 0, temp3 = 0;
////// ���������ӿ����ص����
////int nPix = (rightPoint.x - leftPoint.x + 1)*
////(rightPoint.y - leftPoint.y + 1);
////// �����ӿ����ͨ��������ֵ���
////for (int i = leftPoint.x; i <= rightPoint.x; i++){
////for (int j = leftPoint.y; j <= rightPoint.y; j++){
////temp1 += srcImage.at<Vec3b>(i, j)[0];
////temp2 += srcImage.at<Vec3b>(i, j)[1];
////temp3 += srcImage.at<Vec3b>(i, j)[2];
////}
////}
////// ��ÿ��ͨ�����ֵ
////Vec3b vecTemp;
////vecTemp[0] = temp1 / nPix;
////vecTemp[1] = temp2 / nPix;
////vecTemp[2] = temp3 / nPix;
////return vecTemp;
////}*/
////
////void train()
////{
////	int i, j, k, s, num = 0;
////	double s1 = 0;
////	char filename[50];
////	Mat srcImage, srcGray, m = Mat::zeros(h, w, CV_8UC1), m1 = Mat::zeros(h, w, CV_64FC1);
////	for (i = 1; i <= ntrain; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		m += srcGray;
////	}
////	imshow("һ�ŻҶ�ͼsrcGray", srcGray);   /////////here
////
////	img1 = m;
////	imshow("�ܺ�ͼ��img1", img1);          ///////////here
////	
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////			imge(j, k) = (double)img1(j, k) / ntrain;
////	}
////
////	imshow("��ֵͼ��imge", imge);     //////////////////here
////
////	/*cout << "****************************" << endl;
////	cout << imge << endl;
////	cout << "****************************" << endl;*/
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		// srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////				img(j, k) = (imgs(j, k) - imge(j, k))*(imgs(j, k) - imge(j, k)) / (ntrain - 1);
////		}
////		m1 += img;
////	}
////	img = m1;
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////			img(j, k) = eta*sqrt(img(j, k));
////	}
////
////	imshow("��׼ͼ��img", img);      ////////// here
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		s = 0;
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////			{
////				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////					s++;
////			}
////		}
////		num += s;
////	}
////
////	cout << "ѵ��ͼƬһ���ķ��������ĵ���" << num << endl;    ///// here
////
////
////	for (i = 1; i <= ntrain; i++)
////	{
////		s = 0;
////		sprintf_s(filename, "D:\\roiImage_1\\%05d.jpg", i);
////		srcImage = imread(filename);
////		if (!srcImage.data)
////			return;
////		//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////		cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////		imgs = srcGray;
////		for (j = 0; j < srcImage.rows; j++)
////		{
////			for (k = 0; k < srcImage.cols; k++)
////			{
////				if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////					s++;
////			}
////		}
////		cout << i << ".jpg" << "->" << s << endl;
////		s1 += (s - (double)num / ntrain)*(s - (double)num / ntrain);
////		if (i == 1)
////			mn = mx = s;
////		else
////		{
////			if (s < mn)
////				mn = s;
////			if (s > mx)
////				mx = s;
////		}
////	}
////	e = (double)num / ntrain;
////	sigma = sqrt(s1 / (ntrain - 1));
////	cout << "min:" << mn << endl;
////	cout << "max:" << mx << endl;
////	cout << "e:" << e << ' ' << "sigma:" << sigma << endl;
////
////	//waitKey(0);
////}
////
////int fasttest(Mat srcImage)
////{
////	int j, k, result, s = 0;
////	Mat srcGray;
////	if (!srcImage.data)
////		return 1;
////	//srcImage = imageReduction(srcImage, (double)h / srcImage.rows, (double)w / srcImage.cols);
////	cvtColor(srcImage, srcGray, CV_RGB2GRAY);
////	imgs = srcGray;
////
////	//Mat diff_dst;
////	//absdiff(double(imgs), imge, diff_dst);
////
////	for (j = 0; j < srcImage.rows; j++)
////	{
////		for (k = 0; k < srcImage.cols; k++)
////		{
////			if (abs(imgs(j, k) - imge(j, k))>img(j, k))
////			{
////				s++;
////				imgs(j, k) = 255;
////			}
////			else
////				imgs(j, k) = 0;
////		}
////	}
////
////	imshow("���ͼ", imgs);
////	//waitKey(0);
////
////	cout <<"����ֵ��" << s << endl;
////	if (s > e + sigma || s < e - sigma)
////		result = 0;
////	else
////		result = 1;
////	return result;
////}
////
////int main()
////{
////	int i, result;
////	char filename[50];
////	Mat srcImage;
////	cout << "Now, beginning to preprocess..." << endl;
////	train();
////	cout << "The preparation work is over, now beginning to test..." << endl;
////	for (i = 41; i <= 60; i++)
////	{
////		sprintf_s(filename, "D:\\roiImage_1\\test\\%05d.jpg", i);
////		srcImage = imread(filename);
////		result = fasttest(srcImage);
////		cout << i << ".jpg" << "->" << result << endl;
////		if (result == 0)
////		{
////			sprintf_s(filename, "D:\\roiImage_1\\ng\\%05d.jpg", i);
////			//imwrite(filename, srcImage);
////			imwrite(filename, imgs);
////		}
////		else
////		{
////			sprintf_s(filename, "D:\\roiImage_1\\ok\\%d.jpg", i);
////			imwrite(filename, imgs);
////		}
////	}
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////
////
////
////
