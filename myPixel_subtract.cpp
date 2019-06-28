//bool CVisionFun::ROIComDetectMethod(cv::Mat &srcImg, cv::Mat &showImg, int camIndex, cv::Point centerPoint,
//	int rectWidth, int rectHeight, int rectRotAngle, int distIndex, int detectThr)     //思考一下有哪些参数需要传进去
//{
//	//这里就是读取原图像
//	//获取边缘，边缘相减
//	//判断ok， ng
//	//返回ok， ng标志
//	//这里没有图像旋转过程，处理的是已经旋转好的图像
//
//	////------------------>时间统计<-------------------------------------
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	double dtime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);
//	////////////////////////////////////////////////////////////////////////////////////////////
//
//	img_src_ok = imread("D:\\roiImage_2\\sample3\\1.JPG");      ///8
//	imshow("原图", img_src_ok);
//	img_src_ng = imread("D:\\roiImage_2\\sample3\\9.JPG");  ///14的效果非常好     ////12
//	imshow("缺陷图", img_src_ng);
//
//	////------------------>旋转 <-----------------------------
//	ImageRecify(img_src_ng, rotated_ng);
//
//	int extRows = EXTD_EDGE;
//	int extCols = EXTD_EDGE;
//	copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("extended ok image", extd_ok);
//
//	int extRows2 = EXTD_EDGE;
//	int extCols2 = EXTD_EDGE;
//	copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);
//	imshow("extended ng image", extd_rotated_ng);
//
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//
//	////------------------>模板匹配<--------------------------------------------------------------------------
//
//	MatchingMethod(extd_rotated_ng);   ///模板匹配里传的是扩展并旋转之后的图像，通过模板匹配来平移
//
//	////----------------->两图之差<-----------------------------------------------------
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("两图之差", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//	////----------------->中值滤波<-----------------------------------------------------------
//	medianBlur(diff_dst, diff_dst, 3);
//
//	////----------------->图像增强<------------------------------------------------------------
//	Mat enhc_img;
//	image_enhance(diff_dst, enhc_img);
//
//	////----------------->二值化<-------------------------------------------------------------
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 150, 250, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//
//	////----------------->开运算<-----------------------
//	morph(thr_img);
//
//	////----------------->裁剪回原尺寸<---------------------------
//	Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	//Mat ROI = morph_out(m_select);
//	Mat ROI = thr_img(m_select);
//	imshow("剪裁图", ROI);
//
//	////----------------->画轮廓，圈出缺陷，首先转换成彩色图像就能画颜色框了
//	draw_contour(ROI);
//
//	if (num_contours = 0){
//		m_resultDetectCom = 1;      //ok
//		//putText(showImg, "OK", cv::Point(TOTAL_IMAG_WIDTH - 300, 100), CV_FONT_HERSHEY_COMPLEX,
//		//	stCamera[camIndex].nFontSize, cv::Scalar(0, 255, 0), 3);
//	}
//	else{
//		m_resultDetectCom = 0;     //ng
//		//putText(showImg, "NG", cv::Point(TOTAL_IMAG_WIDTH - 300, 100), CV_FONT_HERSHEY_COMPLEX,
//		//	stCamera[camIndex].nFontSize, cv::Scalar(0, 0, 255), 3);
//	}
//
//	////----------------->时间统计<--------------------------------------------------------------
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "代码的运行时间为" << dtime << "毫秒!" << endl;
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	return m_resultDetectCom;
//}
//
//void MatchingMethod(Mat extd_rotated_ng){
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
//	matchTemplate(extd_rotated_ng, templ_ok, result, 0);
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
//	string a = "123";
//
//	/// Show me what you got
//	rectangle(img_display, matchLoc, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), Scalar(0, 255, 150), 2, 8, 0);
//	rectangle(result, matchLoc, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), Scalar(0, 255, 150), 2, 8, 0);
//	cout << "matchLoc.x: " << matchLoc.x << ", " << templ_ok.cols << ", " << matchLoc.y << ", " << templ_ok.rows << endl;
//	//在图像上写字
//	putText(img_display, a, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	imshow(image_window, img_display);      //需要调整显示窗口，才能让图像按正常比例显示
//	imshow(result_window, result);
//
//	//////-------------------------->模板匹配之后，得到平移坐标，进行平移操作<-----------------
//	translation(matchLoc.x, matchLoc.y);   //平移之所以放在模板匹配里面是因为，match函数不能返回坐标点
//}
//
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
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
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
//	//float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
//	float average = lines[0][1]; //印刷品选择这个
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
//void translation(int matchLoc_x, int matchLoc_y){
//	extd_src = extd_rotated_ng.clone();
//	Size dst_sz = extd_src.size();
//
//	//定义平移矩阵
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = TEMPL_X + EXTD_EDGE - matchLoc_x; //水平平移量   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = TEMPL_Y + EXTD_EDGE - matchLoc_y; //竖直平移量     ///12   这里的25， 80， 需要随模板的设定， 而改变， 别忘了
//	////牵一发而动全身， 一个地方改了，涉及到它的地方都要改， 所以要细心
//
//	//////  （25， 80）  30   黑条 ； （200， 40）  80  sample1；
//
//
//	//根据平移矩阵进行仿射变换
//	warpAffine(extd_src, move_rotated_ng, t_mat, dst_sz);
//	imshow("move_rotated_ng", move_rotated_ng);
//	imwrite("D:\\roiImage_2\\sample3\\save\\move_rotated_ng.jpg", move_rotated_ng);
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
//
//void morph(Mat mor_input){
//	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
//	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
//	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //以后慢慢考虑，现在看来open好一些
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//}
//
//void draw_contour(Mat canny_input){
//	int g_nThresh = 80;
//	RNG g_rng(12345);
//	Mat canny_out;
//	vector<vector<Point> > g_vContours;
//	vector<Vec4i> g_vHierarchy;
//
//	//调用canny算子检测边缘 
//	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//寻找轮廓 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("缺陷轮廓图", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	num_contours = g_vContours.size();
//}
