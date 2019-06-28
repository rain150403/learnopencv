///////对于稍稍复杂一些的样片，会出现问题，主要是对不齐
//////模板在哪里，哪里能对齐
/////所以1：确定模板位置    左上角？中间？  2：用两个模板    3： 还是说问题不是出在模板，而是出在旋转？
////有时模板匹配可能也有轻微误差
//
//////用相似度模板匹配方法很好，但是对于细小的差别检测不出来，那有没有一种方法可以把细小的也给区分出来呢
////现在想想，就模板匹配效果最好，当然，对于一点点的缺陷，检测不出来
////滤波操作，让图像模糊，加之光照不均匀，二值化对图片处理效果不好， 边缘检测，对模板匹配效果不好。
////第四种方法TM_COEFF，对于小的残次看不出来，但是对于大的有很大反应
////此种方法对于印刷品的模板匹配有效
////opencv2410
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <windows.h>
//
//using namespace std;
//using namespace cv;
//
//#define ERROR 1234
//
//#define TEMPL_X 740   //不包含扩展边界
//#define TEMPL_Y 455
//
//#define EXTD_EDGE 20
//#define TEMPL_WIDTH 130
//
///// Global Variables
//Mat img_src_ok;   ///img
//Mat img_src_ng;    ///imgOk
//Mat rotated_ng;
//Mat templ_ok;          ////templ
//Mat result;
//Mat extd_ok;
//Mat extd_rotated_ng;
//Mat move_rotated_ng;
//
//Mat extd_src;
//
//Mat diff_dst;
//
//char* image_window = "Source Image";
//char* result_window = "Result window";
//
//int match_method;   ////Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//int max_Trackbar = 5;
//
///// Function Headers
//void MatchingMethod(int, void*);
//
//void ImageRecify(Mat src, Mat& Img_resuly);     ///画直线的方法可能真的需要改一改，因为它会测到很多条直线，这样就会影响旋转效果
////还有就是图像旋转的这个，因为直线虽然简单，但是会检测到很多直线，而特征匹配的方法虽然麻烦， 但是可能算出来的角度比较固定，单一
//double CalcDegree(const Mat &srcImage, Mat &dst);
////度数转换
//double DegreeTrans(double theta);
////逆时针旋转图像degree角度（原尺寸）    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
//void image_enhance(Mat image, Mat& enhance_img);
//
////WRAP: 上下左右颠倒
////REPLICATE: 虽然方向没反， 但有很明显的一条条线
////而且还希望把旋转填充白色那部分改掉，所以要知道怎么获取某位置的像素值，并在边界填充该像素值
//
////记得把时间加上去
////还有就是两个模板可不可以？？？以后再考虑两个模板的问题
////下面就是怎么把ok， ng给区分开啦？？？
//
////最后要把所有的模块都独立成函数，还要修改命名，还要精修代码
////下面我要解决第二个问题啦
////问题1：需要图像增强，增加图像对比度
////问题2：需要把图像平移操作放在后面
//int main21(int argc, char** argv){
//
//	//D:\\样品图片\\sample8\\ok\\00046.JPG
//	//"D:\\样品图片\\sample8\\ng\\00043.JPG"
//
//	//D:\\waitDelete\\roiImage\\louxiaxinpai\\黑色胶条\\ok_train_1\\00013.JPG
//	//D:\\waitDelete\\roiImage\\louxiaxinpai\\黑色胶条\\ng_test_1\\00032.JPG
//
//	/////////////////////时间统计////////////
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	double dtime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);
//	////////////////////////////////////////////////////////////
//
//	//21
//	img_src_ok = imread("D:\\roiImage_2\\sample12\\1.JPG");      ///8
//	imshow("原图", img_src_ok);
//	rotated_ng = imread("D:\\roiImage_2\\sample12\\3.JPG");  ///14的效果非常好     ////12
//	//imshow("缺陷图", img_src_ng);
//	imshow("缺陷图", rotated_ng);
//
//	////////////这里再加一个旋转操作 //////////
//	//ImageRecify(img_src_ng, rotated_ng);
//	//////////////////////////////////////////////////
//
//	///////////////////////中值滤波/////
//	/*medianBlur(img_src_ok, img_src_ok, 3);
//	medianBlur(rotated_ng, rotated_ng, 3);*/
//	//归根结底还是拍照不清楚，滤波也不管用， 反倒更加影响效果
//	///////////////////////
//
//	int extRows = EXTD_EDGE;    //这里也不能写死，需要设置变量，就选择（两片之间的距离/2）， 因为他最多也不会偏出这个范围，或者实在不行，就换成（整个距离）
//	int extCols = EXTD_EDGE;
//	copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ok image", img_src_ok);
//	imshow("extended ok image", extd_ok);
//
//	int extRows2 = EXTD_EDGE;
//	int extCols2 = EXTD_EDGE;
//	copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);
//	//copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ng image", img_src_ng);
//	imshow("extended ng image", extd_rotated_ng);
//
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//	//给定坐标和框的大小时需要根据自己的样片的尺寸来修改
//	//这个模板可以人为给定，就是在界面上设置一个框，让工人自己去圈有区分性的区域, 如果不具有代表性，比如黑条拍的刚好是全黑区域，就很大可能匹配错误
//	//当然要给他一个限定区域，以免移动过后的图片超出界限
//	//注意扩充边界的宽度别忘了
//
//
//	/// Create windows
//	namedWindow(image_window, CV_WINDOW_NORMAL); ////0
//	namedWindow(result_window, CV_WINDOW_NORMAL);  //CV_WINDOW_AUTOSIZE
//
//	/// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	//////////////////时间统计/////////////////////
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "代码的运行时间为" << dtime << "毫秒!" << endl;
//	//////////////////////////////////////////////////////////////////////////
//	cout << "456" << endl;
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//void MatchingMethod(int, void*){
//
//	/// Source image to display
//	Mat img_display;
//
//	extd_rotated_ng.copyTo(img_display);
//
//	/// Create the result matrix
//	int result_cols = extd_rotated_ng.cols - templ_ok.cols + 1;
//	int result_rows = extd_rotated_ng.rows - templ_ok.rows + 1;
//
//	result.create(result_rows, result_cols, CV_32FC1);
//
//	/// Do the Matching and Normalize
//	matchTemplate(extd_rotated_ng, templ_ok, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/// Localizing the best match with minMaxLoc
//	double minVal;
//	double maxVal;
//	Point minLoc;
//	Point maxLoc;
//	Point matchLoc;
//
//	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
//	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED){
//		matchLoc = minLoc;
//	}
//	else{
//		matchLoc = maxLoc;
//	}
//
//	Point p1, p2;
//	p1.x = 150;
//	p1.y = 150;
//
//	p1.x = matchLoc.x;
//	p1.y = matchLoc.y;
//
//	ellipse(img_display, p1, Size(5, 5), 0, 0, 360, Scalar(0, 255, 255), 2, 8);
//
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), Scalar(0, 255, 150), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), Scalar(0, 255, 150), 2, 8, 0);
//	cout << "matchLoc.x: " << matchLoc.x << ", " << templ_ok.cols << ", " << matchLoc.y << ", " << templ_ok.rows << endl;
//	//putText(img_display, a, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	//195+ 70, 24+67  是右下角， 70， 67 是我的模板的宽高， 所以， （195， 24）是左上角
//
//	imshow(image_window, img_display);      //好奇怪，在测试黑条的时候竟然发生图片变形
//	imshow(result_window, result);
//
//	////////////////////模板匹配之后，得到平移坐标，进行平移操作/////////////
//	extd_src = extd_rotated_ng.clone();
//	Size dst_sz = extd_src.size();
//
//	//定义平移矩阵
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = TEMPL_X + EXTD_EDGE - matchLoc.x; //水平平移量   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = TEMPL_Y + EXTD_EDGE - matchLoc.y; //竖直平移量     ///12   这里的25， 80， 需要随模板的设定， 而改变， 别忘了
//	////牵一发而动全身， 一个地方改了，涉及到它的地方都要改， 所以要细心
//
//	//////  （25， 80）  30   黑条 ； （200， 40）  80  sample1；
//
//
//	//根据平移矩阵进行仿射变换
//	warpAffine(extd_src, move_rotated_ng, t_mat, dst_sz);
//	imshow("move_rotated_ng", move_rotated_ng);
//	imwrite("D:\\roiImage_2\\sample3\\save\\move_rotated_ng.jpg", move_rotated_ng);
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("两图之差", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//	medianBlur(diff_dst, diff_dst, 3);
//
//	Mat enhc_img;
//
//	image_enhance(diff_dst, enhc_img);
//
//	//还想到一点是，对同一张图像处理的次数过多，是不是反倒会失去一些有用信息，或者就达不到对原图的那种处理效果啦？
//	//最后一步想到是二值化，但是效果并不明显，考虑要不要， 在二值化过后再来一个腐蚀膨胀，把一些细小的区域给连接在一起
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 100, 250, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//
//	Mat morph_out; //获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的 
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
//	morphologyEx(thr_img, morph_out, MORPH_OPEN, element);
//	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //以后慢慢考虑，现在看来open好一些
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//
//	////二值化阈值修改一些，可以增加显示效果
//	////腐蚀膨胀需要改一下
//
//	//其实虽然前面效果不怎么样，后面我还是觉得做好平移，打好光，效果应该还是不错的
//
//
//	////////////画轮廓， 圈出缺陷， 首先转换成彩色图像就能画颜色框了
//	int g_nThresh = 80;
//	RNG g_rng(12345);
//	Mat canny_out; 
//	vector<vector<Point> > g_vContours; 
//	vector<Vec4i> g_vHierarchy;
//
//	//调用canny算子检测边缘 
//	Canny(enhc_img, canny_out, g_nThresh, g_nThresh * 2, 3); 
//	//寻找轮廓 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); 
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3); 
//	for (int i = 0; i < g_vContours.size(); i++) { 
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)); 
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point()); 
//	}
//	imshow("缺陷轮廓图", drawing);
//
//	//效果还不错，就是杂质太多，考虑怎么滤除
//
//	//////////////floodfill///////////////////////////////////////
//	//Rect ccomp;
//	//floodFill(diff_dst, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
//	//imshow("水漫金山", diff_dst);
//	/////水漫金山也不满足要求，不能消除，或者填充掉那些杂质
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	////////下面考虑连通域方法/////////////////////////////
//
//	//////还有一点，杂质这么多，除了打光消除，还能不能用滤波方法去除？？？
//
//
//	///seedfill当然也可以啊，只是光照的杂质太多
//
//	////////////////////////////////////////////////////////////////////
//	waitKey(0);
//
//	cout << "123" << endl;
//}
//
////只要旋转出错，对后面影响就很大，所以这种方法就需要对直线检测要求很高。
////void ImageRecify(const char* pInFileName, const char* pOutFileName)
//void ImageRecify(Mat src, Mat& Img_resuly)
//{
//	double degree;
//
//	Mat dst;
//	//倾斜角度矫正
//	degree = CalcDegree(src, dst);      //通过霍夫变换计算角度
//	if (degree == ERROR)
//	{
//		cout << "矫正失败！" << endl;
//		return;
//	}
//	rotateImage(src, dst, degree);      //逆时针旋转图像degree角度（原尺寸）
//	cout << "angle:" << degree << endl;
//	imshow("旋转调整后", dst);
//
//	Img_resuly = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
//	imshow("裁剪之后", Img_resuly);
//	imwrite("recified.jpg", Img_resuly);
//}
//
////度数转换
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
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
//	Mat M = getRotationMatrix2D(center, degree, 1);
//	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
//}
//
////通过霍夫变换计算角度
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 30, 100, 3);    ///直线检测这里，因为是不同的图片，灰度值不同，所以必须要在界面上设定阈值，首先让工人找到直线（清晰的轮廓，再工作）
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
//	float sum = 0;
//	//依次画出每条线段
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		float rho = lines[i][0];
//		float theta = lines[i][1];
//		Point pt1, pt2;
//		//cout << theta << endl;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//		//只选角度最小的作为旋转角度
//		sum += theta;
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar函数用于调节线段颜色
//
//		imshow("直线探测效果图", dstImage);
//	}
//	float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
//	//float average = lines[0][1]; //印刷品选择这个
//	cout << "average theta:" << average << endl;
//
//	//double angle = DegreeTrans(average) - 90;
//	double angle = 0;
//	//我的目的就是不想让它转动大的角度，也就是小于90.
//	if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}
//
//	rotateImage(dstImage, dst, angle);
//	//imshow("直线探测效果图2", dstImage);
//	return angle;
//}
//
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
//	imshow("Soure", image);
//	imshow("after", enhance_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg", enhance_img);
//}


///////这个已经很好了，基本达到目标，在此基础上去改进就好了
//////用相似度模板匹配方法很好，但是对于细小的差别检测不出来，那有没有一种方法可以把细小的也给区分出来呢
////现在想想，就模板匹配效果最好，当然，对于一点点的缺陷，检测不出来
////滤波操作，让图像模糊，加之光照不均匀，二值化对图片处理效果不好， 边缘检测，对模板匹配效果不好。
////第四种方法TM_COEFF，对于小的残次看不出来，但是对于大的有很大反应
////此种方法对于印刷品的模板匹配有效
////opencv2410
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//#define ERROR 1234
//
///// Global Variables
//Mat img_src_ok;   ///img
//Mat img_src_ng;    ///imgOk
//Mat rotated_ng;
//Mat templ;          ////templ
//Mat result;
//Mat extd_ok;
//Mat extd_rotated_ng;
//Mat move_rotated_ng;
//
//Mat extd_src;
//Mat extd_dst;
//
//Mat diff_dst;
//
//char* image_window = "Source Image";
//char* result_window = "Result window";
//
//int match_method;   ////Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//int max_Trackbar = 5;
//
///// Function Headers
//void MatchingMethod(int, void*);
//
//void ImageRecify(Mat src, Mat& Img_resuly);
//double CalcDegree(const Mat &srcImage, Mat &dst);
////度数转换
//double DegreeTrans(double theta);
////逆时针旋转图像degree角度（原尺寸）    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
//void image_enhance(Mat image, Mat& enhance_img);
//
////问题1：需要图像增强，增加图像对比度
////问题2：需要把图像平移操作放在后面
//int main(int argc, char** argv){
//
//	//21
//	img_src_ok = imread("D:\\样品图片\\sample1\\ok\\8.JPG");
//	imshow("yuantu", img_src_ok);
//	img_src_ng = imread("D:\\样品图片\\sample1\\ng\\7.JPG");  ///14的效果非常好
//	imshow("yu", img_src_ng);
//
//	////////////这里再加一个旋转操作 //////////
//	ImageRecify(img_src_ng, rotated_ng);
//	//////////////////////////////////////////////////
//
//	int extRows = 20;
//	int extCols = 20;
//	copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ok image", img_src_ok);
//	imshow("extended ok image", extd_ok);
//
//	int extRows2 = 20;
//	int extCols2 = 20;
//	copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);
//	//copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ng image", img_src_ng);
//	imshow("extended ng image", extd_rotated_ng);
//
//	extd_src = extd_rotated_ng.clone();
//
//	Size dst_sz = extd_src.size();
//
//	//定义平移矩阵
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = -12; //水平平移量   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 8; //竖直平移量     ///12
//
//	//根据平移矩阵进行仿射变换
//	warpAffine(extd_src, move_rotated_ng, t_mat, dst_sz);
//
//	//显示平移效果
//	//imshow("image", extd_src);
//	//imshow("result", extd_dst);
//
//	templ = extd_ok(Rect(200, 40, 80, 80));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//
//	/*blur(img, img, Size(7, 7));
//	imshow("lvbo", img);
//	blur(templ, templ, Size(7, 7));
//	imshow("mobanlvbo", templ);*/
//
//	/*threshold(img, img, 50, 255, THRESH_BINARY);
//	imshow("erzhihua", img);*/
//
//	/*Canny(img, img, 70, 100, 3);
//	imshow("yuanshitu", img);
//	Canny(templ, templ, 70, 100, 3);
//	imshow("mobantu", templ);*/
//
//	/// Create windows
//	namedWindow(image_window, 0);
//	namedWindow(result_window, 0);  //CV_WINDOW_AUTOSIZE
//
//	/// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void MatchingMethod(int, void*){
//
//	/// Source image to display
//	Mat img_display;
//
//	move_rotated_ng.copyTo(img_display);
//
//	/// Create the result matrix
//	int result_cols = move_rotated_ng.cols - templ.cols + 1;
//	int result_rows = move_rotated_ng.rows - templ.rows + 1;
//
//	result.create(result_rows, result_cols, CV_32FC1);
//
//	/// Do the Matching and Normalize
//	matchTemplate(move_rotated_ng, templ, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/// Localizing the best match with minMaxLoc
//	double minVal;
//	double maxVal;
//	Point minLoc;
//	Point maxLoc;
//	Point matchLoc;
//
//	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
//	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED){
//		matchLoc = minLoc;
//	}
//	else{
//		matchLoc = maxLoc;
//	}
//
//	Point p1, p2;
//	p1.x = 150;
//	p1.y = 150;
//
//	p1.x = matchLoc.x;
//	p1.y = matchLoc.y;
//
//	ellipse(img_display, p1, Size(5, 5), 0, 0, 360, Scalar(0, 255, 255), 2, 8);
//
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	cout << "matchLoc.x: " << matchLoc.x << ", " << templ.cols << ", " << matchLoc.y << ", " << templ.rows << endl;
//	//putText(img_display, a, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	//195+ 70, 24+67  是右下角， 70， 67 是我的模板的宽高， 所以， （195， 24）是左上角
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("两图之差", diff_dst);
//
//	Mat enhc_img;
//
//	image_enhance(diff_dst, enhc_img);
//
//	//还想到一点是，对同一张图像处理的次数过多，是不是反倒会失去一些有用信息，或者就达不到对原图的那种处理效果啦？
//	//最后一步想到是二值化，但是效果并不明显，考虑要不要， 在二值化过后再来一个腐蚀膨胀，把一些细小的区域给连接在一起
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 10, 50, CV_THRESH_BINARY);
//	imshow("erzhihua", thr_img);
//
//	Mat out; //获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的 
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
//	morphologyEx(thr_img, out, MORPH_OPEN, element);
//	imshow("fushi", out);
//
//	//其实虽然前面效果不怎么样，后面我还是觉得做好平移，打好光，效果应该还是不错的
//
//
//	waitKey(0);
//
//	system("pause");
//	return;
//}
//
////void ImageRecify(const char* pInFileName, const char* pOutFileName)
//void ImageRecify(Mat src, Mat& Img_resuly)
//{
//	double degree;
//	
//	Mat dst;
//	//倾斜角度矫正
//	degree = CalcDegree(src, dst);      //通过霍夫变换计算角度
//	if (degree == ERROR)
//	{
//		cout << "矫正失败！" << endl;
//		return;
//	}
//	rotateImage(src, dst, degree);      //逆时针旋转图像degree角度（原尺寸）
//	cout << "angle:" << degree << endl;
//	imshow("旋转调整后", dst);
//
//	Img_resuly = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
//	imshow("裁剪之后", Img_resuly);
//	imwrite("recified.jpg", Img_resuly);
//}
//
////度数转换
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
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
//	Mat M = getRotationMatrix2D(center, degree, 1);
//	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//仿射变换，背景色填充为白色  
//}
//
////通过霍夫变换计算角度
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 50, 200, 3);
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
//	float sum = 0;
//	//依次画出每条线段
//	for (size_t i = 0; i < lines.size(); i++)
//	{
//		float rho = lines[i][0];
//		float theta = lines[i][1];
//		Point pt1, pt2;
//		//cout << theta << endl;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000 * (-b));
//		pt1.y = cvRound(y0 + 1000 * (a));
//		pt2.x = cvRound(x0 - 1000 * (-b));
//		pt2.y = cvRound(y0 - 1000 * (a));
//		//只选角度最小的作为旋转角度
//		sum += theta;
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar函数用于调节线段颜色
//
//		imshow("直线探测效果图", dstImage);
//	}
//	float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
//
//	cout << "average theta:" << average << endl;
//
//	//double angle = DegreeTrans(average) - 90;
//	double angle = 0;
//	//我的目的就是不想让它转动大的角度，也就是小于90.
//	if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}
//
//	rotateImage(dstImage, dst, angle);
//	//imshow("直线探测效果图2", dstImage);
//	return angle;
//}
//
//void image_enhance(Mat image, Mat& enhance_img){
//
//	imshow("原图像", image);
//	Mat imageRGB[3];
//	split(image, imageRGB);
//	for (int i = 0; i < 3; i++)
//	{
//		equalizeHist(imageRGB[i], imageRGB[i]);
//	}
//	merge(imageRGB, 3, enhance_img);
//	imshow("直方图均衡化图像增强效果", enhance_img);
//}

//////用相似度模板匹配方法很好，但是对于细小的差别检测不出来，那有没有一种方法可以把细小的也给区分出来呢
////现在想想，就模板匹配效果最好，当然，对于一点点的缺陷，检测不出来
////滤波操作，让图像模糊，加之光照不均匀，二值化对图片处理效果不好， 边缘检测，对模板匹配效果不好。
////第四种方法TM_COEFF，对于小的残次看不出来，但是对于大的有很大反应
////此种方法对于印刷品的模板匹配有效
////opencv2410
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
///// Global Variables
//Mat img_src_ok;   ///img
//Mat img_src_ng;    ///imgOk
//Mat templ;          ////templ
//Mat result;
//Mat extd_ok;
//Mat extd_ng;
//Mat move_ng;
//
//Mat extd_src;
//Mat extd_dst;
//
//Mat diff_dst;
//
//char* image_window = "Source Image";
//char* result_window = "Result window";
//
//int match_method;   ////Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//int max_Trackbar = 5;
//
///// Function Headers
//void MatchingMethod(int, void*);
//
//int main21(int argc, char** argv){
//
//	//21
//	img_src_ok = imread("D:\\样品图片\\sample1\\ok\\8.JPG");
//	img_src_ng = imread("D:\\样品图片\\sample1\\ng\\12.JPG");
//	
//	int extRows = 20;
//	int extCols = 20;
//	copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ok image", img_src_ok);
//	//imshow("extended ok image", extd_ok);
//
//	int extRows2 = 20;
//	int extCols2 = 20;
//	copyMakeBorder(img_src_ng, extd_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("original ng image", img_src_ng);
//	//imshow("extended ng image", extd_ng);
//
//	extd_src = extd_ng.clone();
//
//	Size dst_sz = extd_src.size();
//
//	//定义平移矩阵
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 19; //水平平移量   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 12; //竖直平移量     ///12
//
//	//根据平移矩阵进行仿射变换
//	warpAffine(extd_src, extd_dst, t_mat, dst_sz);
//
//	////////////这里再加一个旋转操作 //////////
//
//	//////////////////////////////////////////////////
//
//	//显示平移效果
//	//imshow("image", extd_src);
//	//imshow("result", extd_dst);
//
//	templ = extd_ok(Rect(200, 40, 80, 80));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//
//	/*blur(img, img, Size(7, 7));
//	imshow("lvbo", img);
//	blur(templ, templ, Size(7, 7));
//	imshow("mobanlvbo", templ);*/
//
//	/*threshold(img, img, 50, 255, THRESH_BINARY);
//	imshow("erzhihua", img);*/
//
//	/*Canny(img, img, 70, 100, 3);
//	imshow("yuanshitu", img);
//	Canny(templ, templ, 70, 100, 3);
//	imshow("mobantu", templ);*/
//
//	/// Create windows
//	namedWindow(image_window, 0);
//	namedWindow(result_window, 0);  //CV_WINDOW_AUTOSIZE
//
//	/// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void MatchingMethod(int, void*){
//
//	/// Source image to display
//	Mat img_display;
//
//	extd_dst.copyTo(img_display);
//
//	/// Create the result matrix
//	int result_cols = extd_dst.cols - templ.cols + 1;
//	int result_rows = extd_dst.rows - templ.rows + 1;
//
//	result.create(result_rows, result_cols, CV_32FC1);
//
//	/// Do the Matching and Normalize
//	matchTemplate(extd_dst, templ, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/// Localizing the best match with minMaxLoc
//	double minVal;
//	double maxVal;
//	Point minLoc;
//	Point maxLoc;
//	Point matchLoc;
//
//	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
//	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED){
//		matchLoc = minLoc;
//	}
//	else{
//		matchLoc = maxLoc;
//	}
//
//	Point p1, p2;
//	p1.x = 150;
//	p1.y = 150;
//
//	p1.x = matchLoc.x;
//	p1.y = matchLoc.y;
//
//	ellipse(img_display, p1, Size(5, 5), 0, 0, 360, Scalar(0, 255, 255), 2, 8);
//	
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	cout << "matchLoc.x: " << matchLoc.x << ", " << templ.cols << ", " << matchLoc.y << ", " << templ.rows << endl;
//	//putText(img_display, a, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	//195+ 70, 24+67  是右下角， 70， 67 是我的模板的宽高， 所以， （195， 24）是左上角
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	absdiff(extd_ok, extd_dst, diff_dst);
//	imshow("两图之差", diff_dst);
//
//	waitKey(0);
//
//	system("pause");
//	return;
//}


//突然想到，想到不能裁剪，裁剪之后又回归原图了，，这里就是在扩充后的图像内，位置是一样的。
//， 在这个扩充之后的图像中直接用相减的方法，看看效果。



////////用相似度模板匹配方法很好，但是对于细小的差别检测不出来，那有没有一种方法可以把细小的也给区分出来呢
////现在想想，就模板匹配效果最好，当然，对于一点点的缺陷，检测不出来
////滤波操作，让图像模糊，加之光照不均匀，二值化对图片处理效果不好， 边缘检测，对模板匹配效果不好。
////第四种方法TM_COEFF，对于小的残次看不出来，但是对于大的有很大反应
////此种方法对于印刷品的模板匹配有效
////opencv2410
//
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
///// Global Variables
//Mat img;
//Mat imgOk;
//Mat templ;
//Mat result;
//Mat extendedIm;
//Mat extendedIm2;
//
//char* image_window = "Source Image";
//char* result_window = "Result window";
//
//int match_method;   ////Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//int max_Trackbar = 5;
//
///// Function Headers
//void MatchingMethod(int, void*);
//
//int main(int argc, char** argv){
//
//	//21
//
//	img = imread("D:\\样品图片\\sample1\\ng\\12.JPG");
//	imgOk = imread("D:\\样品图片\\sample1\\ok\\8.JPG");
//
//	int extRows = 20;
//	int extCols = 20;
//	copyMakeBorder(img, extendedIm, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image", img);
//	imshow("extended image", extendedIm);
//
//	int extRows2 = 20;
//	int extCols2 = 20;
//	copyMakeBorder(imgOk, extendedIm2, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image2", imgOk);
//	imshow("extended image2", extendedIm2);
//
//	cv::Mat src = extendedIm.clone();
//	cv::Mat dst;
//
//	cv::Size dst_sz = src.size();
//
//	//定义平移矩阵
//	cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 0; //水平平移量   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 0; //竖直平移量     ///12
//
//	//根据平移矩阵进行仿射变换
//	cv::warpAffine(src, dst, t_mat, dst_sz);
//
//	//显示平移效果
//	cv::imshow("image", src);
//	cv::imshow("result", dst);
//
//	templ = extendedIm2(Rect(200, 40, 80, 80));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//
//	/*blur(img, img, Size(7, 7));
//	imshow("lvbo", img);
//	blur(templ, templ, Size(7, 7));
//	imshow("mobanlvbo", templ);*/
//
//	/*threshold(img, img, 50, 255, THRESH_BINARY);
//	imshow("erzhihua", img);*/
//
//	/*Canny(img, img, 70, 100, 3);
//	imshow("yuanshitu", img);
//	Canny(templ, templ, 70, 100, 3);
//	imshow("mobantu", templ);*/
//
//	/// Create windows
//	namedWindow(image_window, 0);
//	namedWindow(result_window, 0);  //CV_WINDOW_AUTOSIZE
//
//	/// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	waitKey(0);
//	return 0;
//}
//
//void MatchingMethod(int, void*){
//
//	/// Source image to display
//	Mat img_display;
//
//	extendedIm.copyTo(img_display);
//
//	/// Create the result matrix
//	int result_cols = extendedIm.cols - templ.cols + 1;
//	int result_rows = extendedIm.rows - templ.rows + 1;
//
//	result.create(result_rows, result_cols, CV_32FC1);
//
//	/// Do the Matching and Normalize
//	matchTemplate(extendedIm, templ, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/// Localizing the best match with minMaxLoc
//	double minVal;
//	double maxVal;
//	Point minLoc;
//	Point maxLoc;
//	Point matchLoc;
//
//	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//
//	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
//	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED){
//		matchLoc = minLoc;
//	}
//	else{
//		matchLoc = maxLoc;
//	}
//
//	Point p1, p2;
//	p1.x = 150;
//	p1.y = 150;
//
//	p1.x = matchLoc.x;
//	p1.y = matchLoc.y;
//
//	ellipse(img_display, p1, Size(5, 5), 0, 0, 360, Scalar(0, 255, 255), 2, 8);
//	//string a = "123";
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 150), 2, 8, 0);
//	cout << "matchLoc.x: " << matchLoc.x << ", " << templ.cols << ", " << matchLoc.y << ", " << templ.rows << endl;
//	//putText(img_display, a, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	//195+ 70, 24+67  是右下角， 70， 67 是我的模板的宽高， 所以， （195， 24）是左上角
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	return;
//}


//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(){
//
//	Mat orgIm = imread("D:\\样品图片\\sample1\\ng\\12.JPG");
//	int extRows = 50;
//	int extCols = 50;
//	Mat extendedIm;
//	copyMakeBorder(orgIm, extendedIm, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image", orgIm);
//	imshow("extended image", extendedIm);
//
//	Mat orgIm2 = imread("D:\\样品图片\\sample1\\ok\\8.JPG");
//	int extRows2 = 50;
//	int extCols2 = 50;
//	Mat extendedIm2;
//	copyMakeBorder(orgIm2, extendedIm2, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image2", orgIm2);
//	imshow("extended image2", extendedIm2);
//
//	cv::Mat src = extendedIm.clone();
//	cv::Mat dst;
//
//	cv::Size dst_sz = src.size();
//
//	//定义平移矩阵
//	cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 50; //水平平移量
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 50; //竖直平移量
//
//	//根据平移矩阵进行仿射变换
//	cv::warpAffine(src, dst, t_mat, dst_sz);
//
//	//显示平移效果
//	cv::imshow("image", src);
//	cv::imshow("result", dst);
//
//	cv::waitKey(0);
//
//	return 0;
//}


//#include <iostream>  
//#include <opencv2/opencv.hpp>  
//using namespace std;
//using namespace cv;
//int main(int argc, char**argv){
//	Mat orgIm = imread("D:\\样品图片\\sample1\\ng\\12.JPG");
//	int extRows = 19;
//	int extCols = 15;
//	Mat extendedIm;
//	copyMakeBorder(orgIm, extendedIm, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image", orgIm);
//	imshow("extended image", extendedIm);
//	waitKey();
//	return 0;
//}