//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//#define ERROR 1234
//
////度数转换
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
////逆时针旋转图像degree角度（原尺寸）    
//void rotateImage(Mat src, Mat& img_rotate, double degree)
//{
//	//旋转中心为图像中心    
//	Point2f center;
//	center.x = float(src.cols / 2.0);
//	center.y = float(src.rows / 2.0);
//	int length = 0;
//	length = sqrt(src.cols*src.cols + src.rows*src.rows);
//	//计算二维旋转的仿射变换矩阵  
//	Mat M = getRotationMatrix2D(center, degree, 1);     ////degree 度数， 大于零就逆时针转，小于零就顺时针转
//	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
//}
//
////霍夫变换返回的是弧度， 而1弧度 = 360°， 也就是计算出来的旋转角度有问题？
//
////通过霍夫变换计算角度
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 50, 100, 3);
//	imshow("midImage", midImage);
//	cvtColor(midImage, dstImage, CV_GRAY2BGR);
//
//	//通过霍夫变换检测直线
//	vector<Vec2f> lines;
//	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);//第5个参数就是阈值，阈值越大，检测精度越高
//	//cout << lines.size() << endl;
//
//	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
//	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。
//
//	if (!lines.size())
//	{
//		HoughLines(midImage, lines, 1, CV_PI / 180, 200, 0, 0);
//	}
//	//cout << lines.size() << endl;
//
//	if (!lines.size())
//	{
//		HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
//	}
//	//cout << lines.size() << endl;
//	if (!lines.size())
//	{
//		cout << "没有检测到直线！" << endl;
//		return ERROR;
//	}
//
//	int zeroLine = 0;
//	float sum = 0;
//	//依次画出每条线段
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		float rho = lines[i][0];
//		float theta = lines[i][1];
//
//		cout << "角度：" << theta << endl;
//
//		Point pt1, pt2;
//		//cout << theta << endl;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//
//		if (theta == 0){
//			zeroLine++;
//		}
//
//		//只选角度最小的作为旋转角度
//		sum += theta;
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar函数用于调节线段颜色
//
//		imshow("直线探测效果图", dstImage);
//		imwrite("D:\\roiImgForTest\\lineSave\\line.jpg", dstImage);
//	}
//	float average = 0;
//
//	if (sum == 0){
//		average = 0;
//	}
//	else{
//		average = sum / (lines.size() - zeroLine);
//	}
//
//	//float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
//	//float average = lines[0][1];    //因为有很多直线的时候（如印刷字）， 会影响图像的旋转，而其实我们只需要其中一条独立的清晰的直线。
//	cout << "average theta:" << average << endl;
//
//	double angle = DegreeTrans(average) - 180;
//	//double angle = 0;
//
//	cout << "实测angle:" << DegreeTrans(average) << endl;
//
//	//我的目的就是不想让它转动大的角度，也就是小于90.
//	/*if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}*/
//
//
//	//rotateImage(dstImage, dst, angle);
//	//imshow("直线探测效果图2", dstImage);
//	return angle;
//}
//
//
//void ImageRecify(const char* pInFileName, const char* pOutFileName)
//{
//	double degree;
//	Mat src = imread(pInFileName);
//	imshow("原始图", src);
//	imwrite("D:\\roiImgForTest\\lineSave\\src.jpg", src);
//	Mat dst;
//	//倾斜角度矫正
//	degree = CalcDegree(src, dst);
//	if (degree == ERROR)
//	{
//		cout << "矫正失败！" << endl;
//		return;
//	}
//	rotateImage(src, dst, degree);
//	cout << "最终angle:" << degree << endl;
//	imshow("旋转调整后", dst);
//	imwrite("D:\\roiImgForTest\\lineSave\\afterRotated.jpg", dst);
//
//	//Mat resulyImage = dst(Rect(0, 0, dst.cols - 100, 500));   //这个尺寸裁剪的效果比较好
//	Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
//	imshow("裁剪之后", resulyImage);
//	imwrite("D:\\roiImgForTest\\lineSave\\recified.jpg", resulyImage);
//}
//
//
////还有就是我想着是不是可以提取任意形状的ROI区域，那样，提取样品形状的ROI区域，就可以完全在样品区域内部进行各种操作。
//
////不知道为啥，一张图会画那么多外接矩形？？？？
////我想应该自己写一个能框出样片的矩形框
//
//int main()
//{
//	//1
//	ImageRecify("D:\\newSample\\BlackT\\NG\\nan\\00187.JPG", "FinalImage.jpg");
//	waitKey();
//	return 0;
//}
//
//
//
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <iostream>
////
////using namespace cv;
////using namespace std;
////
//////第一个参数：输入图片名称；第二个参数：输出图片名称
////void GetContoursPic(const char* pSrcFileName, const char* pDstFileName)
////{
////	Mat srcImg = imread(pSrcFileName);
////	imshow("原始图", srcImg);
////	Mat gray, binImg;
////	//灰度化
////	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
////	imshow("灰度图", gray);
////	//二值化
////	threshold(gray, binImg, 180, 220, CV_THRESH_BINARY);
////	imshow("二值化", binImg);
////
////	vector<vector<Point> > contours;
////	vector<Rect> boundRect(contours.size());
////	//注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
////	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
////	cout << contours.size() << endl;
////	for (int i = 0; i < contours.size(); i++)
////	{
////		//需要获取的坐标  
////		CvPoint2D32f rectpoint[4];
////		CvBox2D rect = minAreaRect(Mat(contours[i]));
////
////		cvBoxPoints(rect, rectpoint); //获取4个顶点坐标  
////		//与水平线的角度  
////		float angle = rect.angle;
////		cout << angle << endl;
////
////		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
////		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
////		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
////		//面积太小的直接pass
////		if (line1 * line2 < 600)
////		{
////			continue;
////		}
////
////		//为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来  
////		if (line1 > line2)
////		{
////			angle = 90 + angle;
////		}
////
////		//新建一个感兴趣的区域图，大小跟原图一样大  
////		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //注意这里必须选CV_8UC3
////		RoiSrcImg.setTo(0); //颜色都设置为黑色  
////		//imshow("新建的ROI", RoiSrcImg);
////		//对得到的轮廓填充一下  
////		drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);
////
////		//抠图到RoiSrcImg
////		srcImg.copyTo(RoiSrcImg, binImg);
////
////
////		//再显示一下看看，除了感兴趣的区域，其他部分都是黑色的了  
////		namedWindow("RoiSrcImg", 1);
////		imshow("RoiSrcImg", RoiSrcImg);
////
////		//创建一个旋转后的图像  
////		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
////		RatationedImg.setTo(0);
////		//对RoiSrcImg进行旋转  
////		Point2f center = rect.center;  //中心点  
////		Mat M2 = getRotationMatrix2D(center, angle, 1);//计算旋转加缩放的变换矩阵 
////		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//仿射变换 
////		imshow("旋转之后", RatationedImg);
////		imwrite("r.jpg", RatationedImg); //将矫正后的图片保存下来
////	}
////
////#if 1
////	//对ROI区域进行抠图
////
////	//对旋转后的图片进行轮廓提取  
////	vector<vector<Point> > contours2;
////	Mat raw = imread("r.jpg");
////	Mat SecondFindImg;
////	//SecondFindImg.setTo(0);
////	cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
////	threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
////	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
////	//cout << "sec contour:" << contours2.size() << endl;
////
////	for (int j = 0; j < contours2.size(); j++)
////	{
////		//这时候其实就是一个长方形了，所以获取rect  
////		Rect rect = boundingRect(Mat(contours2[j]));
////		//面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
////		if (rect.area() < 600)
////		{
////			continue;
////		}
////		Mat dstImg = raw(rect);
////		imshow("dst", dstImg);
////		imwrite(pDstFileName, dstImg);
////	}
////#endif
////
////
////}
////
////
////void main()
////{
////	GetContoursPic("D:\\样品图片\\sample3\\ng\\00098.JPG", "FinalImage.jpg");
////	waitKey();
////}
//
//
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/imgproc/imgproc.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <iostream>
////
////using namespace cv;
////using namespace std;
////
////#define ERROR 1234
////
//////度数转换
////double DegreeTrans(double theta)
////{
////	double res = theta / CV_PI * 180;
////	return res;
////}
////
////
//////逆时针旋转图像degree角度（原尺寸）    
////void rotateImage(Mat src, Mat& img_rotate, double degree)
////{
////	//旋转中心为图像中心    
////	Point2f center;
////	center.x = float(src.cols / 2.0);
////	center.y = float(src.rows / 2.0);
////	int length = 0;
////	length = sqrt(src.cols*src.cols + src.rows*src.rows);
////	//计算二维旋转的仿射变换矩阵  
////	Mat M = getRotationMatrix2D(center, degree, 1);
////	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
////}
////
//////通过霍夫变换计算角度
////double CalcDegree(const Mat &srcImage, Mat &dst)
////{
////	Mat midImage, dstImage;
////
////	Canny(srcImage, midImage, 50, 100, 3);
////	imshow("midImage", midImage);
////	cvtColor(midImage, dstImage, CV_GRAY2BGR);
////
////	//通过霍夫变换检测直线
////	vector<Vec2f> lines;
////	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);//第5个参数就是阈值，阈值越大，检测精度越高
////	//cout << lines.size() << endl;
////
////	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
////	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。
////
////	if (!lines.size())
////	{
////		HoughLines(midImage, lines, 1, CV_PI / 180, 200, 0, 0);
////	}
////	//cout << lines.size() << endl;
////
////	if (!lines.size())
////	{
////		HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
////	}
////	//cout << lines.size() << endl;
////	if (!lines.size())
////	{
////		cout << "没有检测到直线！" << endl;
////		return ERROR;
////	}
////
////	float sum = 0;
////	//依次画出每条线段
////	for (size_t i = 0; i < lines.size(); i++)
////	{
////		float rho = lines[i][0];
////		float theta = lines[i][1];
////		Point pt1, pt2;
////		//cout << theta << endl;
////		double a = cos(theta), b = sin(theta);
////		double x0 = a*rho, y0 = b*rho;
////		pt1.x = cvRound(x0 + 1000 * (-b));
////		pt1.y = cvRound(y0 + 1000 * (a));
////		pt2.x = cvRound(x0 - 1000 * (-b));
////		pt2.y = cvRound(y0 - 1000 * (a));
////		//只选角度最小的作为旋转角度
////		sum += theta;
////
////		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar函数用于调节线段颜色
////
////		imshow("直线探测效果图", dstImage);
////	}
////	//float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
////	float average = lines[0][1];    //因为有很多直线的时候（如印刷字）， 会影响图像的旋转，而其实我们只需要其中一条独立的清晰的直线。
////	cout << "average theta:" << average << endl;
////
////	//double angle = DegreeTrans(average) - 90;
////	double angle = 0;
////
////	cout << "实测angle:" << DegreeTrans(average) << endl;
////
////	//我的目的就是不想让它转动大的角度，也就是小于90.
////	if (DegreeTrans(average) > 90){
////		angle = DegreeTrans(average) - 90;
////	}
////	else{
////		angle = DegreeTrans(average);
////	}
////
////
////	rotateImage(dstImage, dst, angle);
////	//imshow("直线探测效果图2", dstImage);
////	return angle;
////}
////
////
////void ImageRecify(const char* pInFileName, const char* pOutFileName)
////{
////	double degree;
////	Mat src = imread(pInFileName);
////	imshow("原始图", src);
////	Mat dst;
////	//倾斜角度矫正
////	degree = CalcDegree(src, dst);
////	if (degree == ERROR)
////	{
////		cout << "矫正失败！" << endl;
////		return;
////	}
////	rotateImage(src, dst, degree);
////	cout << "最终angle:" << degree << endl;
////	imshow("旋转调整后", dst);
////
////	//Mat resulyImage = dst(Rect(0, 0, dst.cols - 100, 500));   //这个尺寸裁剪的效果比较好
////	Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
////	imshow("裁剪之后", resulyImage);
////	imwrite("recified.jpg", resulyImage);
////
////	//Mat drawImg;
////	//drawImg = resulyImage.clone();
////
////	////灰度化
////	//cvtColor(drawImg, drawImg, COLOR_RGB2GRAY);
////	//imshow("灰度图", drawImg);
////	////二值化
////	//threshold(drawImg, drawImg, 180, 200, CV_THRESH_BINARY);
////	//imshow("二值化", drawImg);
////
////	//Canny(drawImg, drawImg, 10, 100, 3);    ///sample1   (10, 100)
////	//imshow("canny", drawImg);
////
////	//vector<vector<Point> > contours;
////
////	////注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
////	//findContours(drawImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
////	//cout << contours.size() << endl;
////	//for (int i = 0; i < contours.size(); i++){
////	//	drawContours(drawImg, contours, -1, Scalar(255), 3);
////	//}
////	//imshow("轮廓", drawImg);
////
////	//cvtColor(drawImg, drawImg, COLOR_GRAY2BGR);
////
////	////接下来想画最小外接矩形， 并在旋转图的对应位置也画上。
////	//Rect boundRect;  //定义外接矩形
////	//RotatedRect box; //定义最小外接矩形
////
////	//vector<vector<Point>>::iterator itc = contours.begin();
////	//Point2f rect_point[4];
////	//int i = 0;
////	//for (; itc != contours.end(); itc++)
////	//{
////	//	cout << i << "个轮廓面积： " << contourArea(contours[i]) << endl;
////	//	box = minAreaRect(Mat(*itc));  //计算每个轮廓最小外接矩形(旋转)
////	//	boundRect = box.boundingRect();
////	//	//boundRect = boundingRect(Mat(*itc));
////	//	circle(drawImg, Point(box.center.x, box.center.y), 5, Scalar(255, 0, 0), -1, 8);  //绘制最小外接矩形的中心点
////	//	// rectangle(dstImg, Point(boundRect.x, boundRect.y), Point(boundRect.x + boundRect.width, boundRect.y + boundRect.height), Scalar(0, 255, 0), 2, 8);
////	//	rectangle(drawImg, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 3, 8);
////	//	box.points(rect_point);  //把最小外接矩形四个端点复制给rect数组
////	//	for (int j = 0; j < 4; j++)
////	//	{
////	//		line(drawImg, rect_point[j], rect_point[(j + 1) % 4], Scalar(0, 0, 255), 3, 8);  //绘制最小外接矩形每条边
////	//	}
////	//}
////	//namedWindow("rec_dst", 0);
////	//imshow("rec_dst", drawImg);
////}
////
////
//////还有就是我想着是不是可以提取任意形状的ROI区域，那样，提取样品形状的ROI区域，就可以完全在样品区域内部进行各种操作。
////
//////不知道为啥，一张图会画那么多外接矩形？？？？
//////我想应该自己写一个能框出样片的矩形框
////
////int main()
////{
////	//1
////	ImageRecify("D:\\newSample\\BlueBar\\OK\\00001.JPG", "FinalImage.jpg");
////	waitKey();
////	return 0;
////}
//
//
//
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>
////#include <>
//
//
//
////////不好用，就是不知道有没有可借鉴之处
////#include <opencv2/opencv.hpp>
////#include <opencv2/highgui/highgui.hpp>    
////#include <opencv2/imgproc/imgproc.hpp>
////#include <iostream>  
////
////using namespace std;
////using namespace cv;
////
////int main(int argc, char *argv[])
////{
////	Mat imageSource = imread("000.JPG", 0);   //D:\\样品图片\\sample1\\ng\\14.JPG
////	imshow("Source Image", imageSource);
////	vector<Point> contour;
////	Point p1(800, 400), p2(1100, 605), p3(902, 970), p4(802, 780);//随意给了4个点
////	contour.push_back(p1);
////	contour.push_back(p2);
////	contour.push_back(p3);
////	contour.push_back(p4);
////	RotatedRect rect = minAreaRect(contour);//外接矩形
////	Point2f vertices[4];
////	rect.points(vertices);//外接矩形的4个顶点
////	for (int i = 0; i < 4; i++)//画矩形
////		line(imageSource, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0));
////
////	/*Rect brect = rect.boundingRect();
////	rectangle(imageSource, brect, Scalar(255, 0, 0));*/
////	imshow("Source Image1", imageSource);
////	Point2f center = rect.center;//外接矩形中心点坐标
////	Mat rot_mat = getRotationMatrix2D(center, rect.angle, 1.0);//求旋转矩阵
////	Mat rot_image;
////	Size dst_sz(imageSource.size());
////	warpAffine(imageSource, rot_image, rot_mat, dst_sz);//原图像旋转
////	imshow("rot_image", rot_image);
////	Mat result1 = rot_image(Rect(0, 0, 100, 100));//提取ROI , center.x - (rect.size.width / 2), center.y - (rect.size.height / 2),
////	imshow("result", result1);
////
////	waitKey(0);
////	return 0;
////}
//
//
//
////#include "opencv2/opencv.hpp"
////#include <iostream>
////using namespace cv;
////using namespace std;
////void main19()
////{
////	//轮廓最小外接矩形的绘制
////	Mat srcImg = imread("D:\\样品图片\\sample1\\ng\\14.JPG");
////	//srcImg = srcImg(Rect(10,10,1000,690));
////	namedWindow("scr", 0);
////	imshow("scr", srcImg);
////	Mat dstImg = srcImg.clone();
////	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
////	threshold(srcImg, srcImg, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY_INV); //二值化
////	//medianBlur(srcImg, srcImg, 9);
////	imshow("threshold", srcImg);
////
////	vector<vector<Point>> contours;
////	findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
////	Rect boundRect;  //定义外接矩形
////	RotatedRect box; //定义最小外接矩形
////
////	vector<vector<Point>>::iterator itc = contours.begin();
////	Point2f rect_point[4];
////	int i = 0;
////	for (; itc != contours.end(); itc++)
////	{
////
////		box = minAreaRect(Mat(*itc));  //计算每个轮廓最小外接矩形(旋转)
////		boundRect = box.boundingRect();
////		//boundRect = boundingRect(Mat(*itc));
////		circle(dstImg, Point(box.center.x, box.center.y), 5, Scalar(255, 0, 0), -1, 8);  //绘制最小外接矩形的中心点
////		// rectangle(dstImg, Point(boundRect.x, boundRect.y), Point(boundRect.x + boundRect.width, boundRect.y + boundRect.height), Scalar(0, 255, 0), 2, 8);
////		rectangle(dstImg, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 3, 8);
////		box.points(rect_point);  //把最小外接矩形四个端点复制给rect数组
////		for (int j = 0; j<4; j++)
////		{
////			line(dstImg, rect_point[j], rect_point[(j + 1) % 4], Scalar(0, 0, 255), 3, 8);  //绘制最小外接矩形每条边
////		}
////		cout << "angle " << i << " :" << box.angle << endl;
////		cout << "width " << i << " :" << box.size.width << endl;
////		cout << "height " << i << " :" << box.size.height << endl << endl;
////		char width[20], height[20];
////		sprintf(width, "width=%0.2f", box.size.width);//
////		sprintf(height, "height=%0.2f", box.size.height);//
////		putText(dstImg, width, box.center, CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
////		putText(dstImg, height, box.center + Point2f(0, 20), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
////	}
////	namedWindow("rec_dst", 0);
////	imshow("rec_dst", dstImg);
////
////
////	//旋转校正
////	float angle_rotation;
////	if ((box.size.width / box.size.height) < 1)
////		angle_rotation = 90 + box.angle;//正数，逆时针旋转
////	else
////		angle_rotation = box.angle; //负数，顺时针旋转
////
////	double scale = 0.78;//缩放比例
////	Mat rot_m = getRotationMatrix2D(box.center, angle_rotation, scale);//获得旋转矩阵
////	warpAffine(dstImg, dstImg, rot_m, dstImg.size());//仿射变换
////
////	namedWindow("dst", 0);
////	imshow("dst", dstImg);
////
////	waitKey(0);
////}