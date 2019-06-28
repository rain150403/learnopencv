//////////#include<iostream>
//////////#include<opencv2/opencv.hpp>
//////////////顶帽
//////////using namespace std;
//////////using namespace cv;
//////////
//////////Mat srcImage, dstImage;
//////////int g_nOpenValue = 0;
//////////
////////////有滚动条事件时，可以进入回调函数
//////////void on_Trackbar(int, void *)
//////////{
//////////	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nOpenValue + 1, 2 * g_nOpenValue + 1));
//////////	morphologyEx(srcImage, dstImage, CV_MOP_TOPHAT, element);
//////////	imshow("【顶帽窗口】", dstImage);
//////////}
//////////
//////////int main()
//////////{
//////////	srcImage = imread("D:\\newSample\\0513\\b\\22.JPG");
//////////	imshow("【原图】", srcImage);
//////////	dstImage.create(srcImage.size(), srcImage.type());
//////////
//////////	namedWindow("【顶帽窗口】");
//////////	createTrackbar("Value", "【顶帽窗口】", &g_nOpenValue, 100, on_Trackbar);
//////////	on_Trackbar(g_nOpenValue, 0);
//////////
//////////	waitKey(0);
//////////
//////////	return 0;
//////////}
////////
////////
////////
////////#include <opencv2/opencv.hpp>
////////#include <opencv2/highgui/highgui.hpp>
////////#include <opencv2/imgproc/imgproc.hpp>
////////#include <iostream>
////////
////////using namespace cv;
////////using namespace std;
////////
////////int blockSize = 100;
////////
////////void unevenLightCompensate(Mat &image, int blockSize);
////////void RemoveLightUnevenDistribution(cv::Mat &image, int blockSize);
////////
////////int main(){
////////	Mat image = imread("D:\\newSample\\0513\\b\\20.JPG");
////////
////////	imshow("1", image);
////////
////////	RemoveLightUnevenDistribution(image, blockSize);
////////
////////	imshow("2", image);
////////	imwrite("D:\\roiImage_2\\sample3\\save\\image.jpg", image);
////////	Canny(image, image, 10, 50, 3);
////////	imshow("edge", image);
////////	waitKey(0);
////////	system("pause");
////////	return 0;
////////}
////////
////////void unevenLightCompensate(Mat &image, int blockSize)
////////{
////////	if (image.channels() == 3) cvtColor(image, image, 7);
////////	imshow("123", image);
////////	waitKey(0);
////////	double average = mean(image)[0];
////////	int rows_new = ceil(double(image.rows) / double(blockSize));
////////	int cols_new = ceil(double(image.cols) / double(blockSize));
////////	Mat blockImage;
////////	blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
////////	for (int i = 0; i < rows_new; i++)
////////	{
////////		for (int j = 0; j < cols_new; j++)
////////		{
////////			int rowmin = i*blockSize;
////////			int rowmax = (i + 1)*blockSize;
////////			if (rowmax > image.rows) rowmax = image.rows;
////////			int colmin = j*blockSize;
////////			int colmax = (j + 1)*blockSize;
////////			if (colmax > image.cols) colmax = image.cols;
////////			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
////////			double temaver = mean(imageROI)[0];
////////			blockImage.at<float>(i, j) = temaver;
////////		}
////////	}
////////	blockImage = blockImage - average;
////////	Mat blockImage2;
////////	resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
////////	Mat image2;
////////	image.convertTo(image2, CV_32FC1);
////////	Mat dst = image2 - blockImage2;
////////	dst.convertTo(image, CV_8UC1);
////////}
////////
////////void RemoveLightUnevenDistribution(cv::Mat &image, int blockSize)
////////{
////////	if (!image.data)
////////	{
////////		return;
////////	}
////////
////////	if (image.channels() == 3)
////////	{
////////		cvtColor(image, image, CV_RGB2GRAY);
////////		//cvtColor(image, image, CV_BGR2GRAY);
////////	}
////////	double average = mean(image)[0];
////////	int rows_block = ceil(double(image.rows) / double(blockSize));   //ceil  返回大于或者等于指定表达式的最小整数
////////	int cols_block = ceil(double(image.cols) / double(blockSize));
////////	int num = 0;
////////	cv::Mat blockImage;
////////	blockImage = cv::Mat::zeros(rows_block, cols_block, CV_32FC1);
////////	for (int i = 0; i < rows_block; i++)
////////	{
////////		for (int j = 0; j < cols_block; j++)
////////		{
////////			int rowmin = i*blockSize;
////////			int rowmax = (i + 1)*blockSize;
////////			if (rowmax > image.rows) rowmax = image.rows;
////////			int colmin = j*blockSize;
////////			int colmax = (j + 1)*blockSize;
////////			if (colmax > image.cols) colmax = image.cols;
////////			cv::Mat imageROI = image(cv::Range(rowmin, rowmax), cv::Range(colmin, colmax));
////////			if (imageROI.data)
////////				num++;
////////			double temaver = mean(imageROI)[0];  ////虽然图像是逐渐增大的，但其实是对每一个图片的第0通道自己求均值， 作为该位置的值
////////			blockImage.at<float>(i, j) = temaver;
////////		}
////////	}
////////	cout << "num" << num << endl;
////////
////////	//blockImage = blockImage - average;//subtract
////////	cv::Mat blockImageTemp = blockImage.clone();
////////	cv::convertScaleAbs(blockImage, blockImageTemp, 1 / average, 0);   //使用线性变换转换输入数组元素成8位无符号整型  ， 乘数因子，偏移量  对每一个像素做α*img+β
////////	//blockImage = blockImage - average
////////	cv::Mat blockImageResize;
////////	cv::resize(blockImage, blockImageResize, image.size(), (0, 0), (0, 0), cv::INTER_CUBIC);      //一个是剪完的尺寸，一个是在原图基础上缩放多少比例，两者不能同时使用
////////	cv::Mat imageFloat;
////////	image.convertTo(imageFloat, CV_32FC1);
////////	cv::Mat dst = imageFloat - blockImageResize;
////////	dst.convertTo(image, CV_8UC1);
////////
////////	return;
////////}
//////
//////
////
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
/////有一个难题，缺陷很明显，但是周围光照不均匀，有杂点该怎么办？？？
//Mat morph_out;
//int blockSize = 5;
//
//void unevenLightCompensate(Mat &image, int blockSize);
//
//int AreaLimit = 30;
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//void morph(Mat mor_input){
//	
//	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat element = getStructuringElement(MORPH_RECT, Size(7,7)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
//	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
//	//morphologyEx(mor_input, morph_out, MORPH_DILATE, element);   //以后慢慢考虑，现在看来open好一些
//	//morphologyEx(morph_out, morph_out, MORPH_DILATE, element);
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//}
//
//////大于8的时候，归为255，小于8，归为0。应该是8可以区分开小孔有无
//void image_enhance(Mat image, Mat& enhance_img){
//
//	Mat imageLog(image.size(), CV_32FC3);
//	for (int i = 0; i < image.rows; i++){
//		for (int j = 0; j < image.cols; j++){
//			imageLog.at<Vec3f>(i, j)[0] = log(1 + image.at<Vec3b>(i, j)[0]);
//			imageLog.at<Vec3f>(i, j)[1] = log(1 + image.at<Vec3b>(i, j)[1]);
//			imageLog.at<Vec3f>(i, j)[2] = log(1 + image.at<Vec3b>(i, j)[2]);
//		}
//	}
//	//归一化到0~255    
//	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
//	//转换成8bit图像显示    
//	convertScaleAbs(imageLog, enhance_img);
//	//imshow("Soure", image);
//	imshow("after", enhance_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg", enhance_img);
//}
//
//
/////对于打光不均匀的物体，不能用图像增强的方法，因为会产生很多干扰点
////////12， 345， 68
//
////但是对于缺胶问题不行
//
//int main(){
//	Mat src = imread("D:\\newSample\\0527\\2\\wmm\\3\\0.JPG");    //D:\\newSample\\mobileX\\1\\4.JPG
//	Mat dst = imread("D:\\newSample\\0527\\2\\wmm\\3\\3.JPG");
//	Mat diff_dst;
//
//	//unevenLightCompensate(src, blockSize);
//	//unevenLightCompensate(dst, blockSize);
//
//	cvtColor(src, src, CV_BGR2GRAY);
//	cvtColor(dst, dst, CV_BGR2GRAY);
//
//	Mat out;
//	//滤波方法
//
//	//boxFilter(src, out, -1, Size(5, 5));   //方框滤波
//	//blur(src, out, Size(11, 11));    //均值滤波
//	//GaussianBlur(src, out, Size(3, 3), 0, 0);    //高斯滤波
//
//	medianBlur(src, out, 7);   //中值滤波
//	//bilateralFilter(src, out, 25, 25*2, 25/2);     //双边滤波
//
//	Mat out2;
//	//滤波方法
//
//	//boxFilter(dst, out2, -1, Size(5, 5));   //方框滤波
//	//blur(dst, out2, Size(11, 11));    //均值滤波
//	//GaussianBlur(dst, out2, Size(3, 3), 0, 0);    //高斯滤波
//
//	medianBlur(dst, out2, 7);   //中值滤波
//	//bilateralFilter(dst, out2, 25, 25*2, 25/2);     //双边滤波
//
//	imshow("lvbo2", out2);
//	waitKey(0);
//
//
//	absdiff(out, out2, diff_dst);
//	//ROIComDenoise(diff_dst, diff_dst, AreaLimit);
//	imshow("cha", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff.jpg", diff_dst);
//	//waitKey(0);
//
//	Mat enhc_img;
//	//image_enhance(diff_dst, diff_dst);
//
//	Mat thr_img;
//	threshold(diff_dst, thr_img,8, 255, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img.jpg", thr_img);
//
//	Canny(thr_img, thr_img, 10, 10 * 3, 3);
//	imshow("123", diff_dst);
//	waitKey(0);
//
//	//ROIComDenoise(thr_img, thr_img, AreaLimit);
//	//imshow("erzhihua2", thr_img);
//	//imwrite("D:\\roiImage_2\\sample3\\save\\thr_img2.jpg", thr_img);
//
//	/*unevenLightCompensate(thr_img, blockSize);
//	imshow("erzhihua3", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\thr_img3.jpg", thr_img);*/
//
//	morph(thr_img);
//
//	//absdiff(src,morph_out, diff_dst);
//	//imshow("final", diff_dst);
//
//	/*for (int m = 0; m < diff_dst.rows; m++){
//		for (int n = 0; n < diff_dst.cols; n++){
//
//			int a = diff_dst.at<uchar>(m, n);
//			cout << a << ", ";
//		}
//		cout << endl;
//	}
//	cout << endl;*/
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
//// 去除孤立噪声点   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
//{
//	int RemoveCount = 0;
//	//新建一幅标签图像初始化为0像素点，为了记录每个像素点检验状态的标签，0代表未检查，1代表正在检查,2代表检查不合格（需要反转颜色），3代表检查合格或不需检查   
//	//初始化的图像全部为0，未检查  
//	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
//	//去除小连通区域的白色点  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (Src.at<uchar>(i, j) < 10)
//			{
//				PointLabel.at<uchar>(i, j) = 3;//将背景黑色点标记为合格，像素为3  
//			}
//		}
//	}
//
//	vector<Point2i>NeihborPos;//将邻域压进容器  
//	NeihborPos.push_back(Point2i(-1, 0));
//	NeihborPos.push_back(Point2i(1, 0));
//	NeihborPos.push_back(Point2i(0, -1));
//	NeihborPos.push_back(Point2i(0, 1));
//	//cout << "Neighbor mode: 8邻域." << endl;
//	NeihborPos.push_back(Point2i(-1, -1));
//	NeihborPos.push_back(Point2i(-1, 1));
//	NeihborPos.push_back(Point2i(1, -1));
//	NeihborPos.push_back(Point2i(1, 1));
//
//	int NeihborCount = 8;
//	int CurrX = 0, CurrY = 0;
//	//开始检测  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (PointLabel.at<uchar>(i, j) == 0)//标签图像像素点为0，表示还未检查的不合格点  
//			{   //开始检查  
//				vector<Point2i>GrowBuffer;//记录检查像素点的个数  
//				GrowBuffer.push_back(Point2i(j, i));
//				PointLabel.at<uchar>(i, j) = 1;//标记为正在检查  
//				int CheckResult = 0;
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					for (int q = 0; q < NeihborCount; q++)
//					{
//						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
//						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
//						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //防止越界    
//						{
//							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
//							{
//								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //邻域点加入buffer    
//								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //更新邻域点的检查标签，避免重复检查    
//							}
//						}
//					}
//				}
//				if (GrowBuffer.size()>AreaLimit) //判断结果（是否超出限定的大小），1为未超出，2为超出    
//					CheckResult = 2;
//				else
//				{
//					CheckResult = 1;
//					RemoveCount++;//记录有多少区域被去除  
//				}
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					CurrX = GrowBuffer.at(z).x;
//					CurrY = GrowBuffer.at(z).y;
//					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//标记不合格的像素点，像素值为2  
//				}
//				//********结束该点处的检查**********    
//			}
//		}
//	}
//	//开始反转面积过小的区域    
//	for (int i = 0; i < Src.rows; ++i)
//	{
//		for (int j = 0; j < Src.cols; ++j)
//		{
//			if (PointLabel.at<uchar>(i, j) == 2)
//			{
//				Dst.at<uchar>(i, j) = 0;
//			}
//			else if (PointLabel.at<uchar>(i, j) == 3)
//			{
//				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);
//
//			}
//		}
//	}
//}
//
//void unevenLightCompensate(Mat &image, int blockSize)
//{
//	if (image.channels() == 3) cvtColor(image, image, 7);
//	double average = mean(image)[0];
//	int rows_new = ceil(double(image.rows) / double(blockSize));
//	int cols_new = ceil(double(image.cols) / double(blockSize));
//	Mat blockImage;
//	blockImage = Mat::zeros(rows_new, cols_new, CV_32FC1);
//	for (int i = 0; i < rows_new; i++)
//	{
//		for (int j = 0; j < cols_new; j++)
//		{
//			int rowmin = i*blockSize;
//			int rowmax = (i + 1)*blockSize;
//			if (rowmax > image.rows) rowmax = image.rows;
//			int colmin = j*blockSize;
//			int colmax = (j + 1)*blockSize;
//			if (colmax > image.cols) colmax = image.cols;
//			Mat imageROI = image(Range(rowmin, rowmax), Range(colmin, colmax));
//			double temaver = mean(imageROI)[0];
//			blockImage.at<float>(i, j) = temaver;
//		}
//	}
//	blockImage = blockImage - average;
//	Mat blockImage2;
//	resize(blockImage, blockImage2, image.size(), (0, 0), (0, 0), INTER_CUBIC);
//	Mat image2;
//	image.convertTo(image2, CV_32FC1);
//	Mat dst = image2 - blockImage2;
//	dst.convertTo(image, CV_8UC1);
//}


//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main(){
//	Mat src = imread("D:\\roiImage\\1\\31.JPG");    //D:\\newSample\\mobileX\\1\\4.JPG
//	Mat dst = imread("D:\\roiImage\\1\\30.JPG");
//	Mat diff_dst;
//
//	//unevenLightCompensate(src, blockSize);
//	//unevenLightCompensate(dst, blockSize);
//
//	cvtColor(src, src, CV_BGR2GRAY);
//	cvtColor(dst, dst, CV_BGR2GRAY);
//
//	//Mat out;
//	//滤波方法
//
//	//boxFilter(src, out, -1, Size(5, 5));   //方框滤波
//	//blur(src, out, Size(11, 11));    //均值滤波
//	//GaussianBlur(src, out, Size(3, 3), 0, 0);    //高斯滤波
//
//	//medianBlur(src, out, 7);   //中值滤波
//	//bilateralFilter(src, out, 25, 25*2, 25/2);     //双边滤波
//	//imshow("lvbo", out);
//
//	//Mat out2;
//	//滤波方法
//
//	//boxFilter(dst, out2, -1, Size(5, 5));   //方框滤波
//	//blur(dst, out2, Size(11, 11));    //均值滤波
//	//GaussianBlur(dst, out2, Size(3, 3), 0, 0);    //高斯滤波
//
//	//medianBlur(dst, out2, 7);   //中值滤波
//	//bilateralFilter(dst, out2, 25, 25*2, 25/2);     //双边滤波
//
//	//imshow("lvbo2", out2);
//
//	//absdiff(out, out2, diff_dst);
//	absdiff(src, dst, diff_dst);
//	imshow("cha", diff_dst);
//
//	Mat thr_img;
//	threshold(diff_dst, thr_img,15, 255, CV_THRESH_BINARY);  ///180, 255      //30 针对89勉强可以
//	imshow("erzhihua", thr_img);
//
//	Mat morph_out;
//	Mat element = getStructuringElement(MORPH_RECT, Size(7,7));
//	morphologyEx(thr_img, morph_out, MORPH_OPEN, element);
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//
//	waitKey(0);
//
//	system("pause");
//	return 0;
//}