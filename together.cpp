//#include "final.h"
//
//int thrNum = 100;
//
//int main(int argc, char* argv[])
//{
//	//21
//	string dir_path = "D:\\newSample\\0513\\b\\";
//	Directory dir;
//	vector<string> fileNames = dir.GetListFiles(dir_path, "*.jpg", false);
//	bool flag = 0;
//
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	double dtime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);
//
//	for (int i = 0; i < fileNames.size(); i++){
//		//get image name
//		string fileName = fileNames[i];
//		string fileFullName = dir_path + fileName;
//		cout << "Full path:" << fileFullName << endl;
//
//		/*LARGE_INTEGER nFreq;
//		LARGE_INTEGER nBeginTime;
//		LARGE_INTEGER nEndTime;
//		double dtime;
//		QueryPerformanceFrequency(&nFreq);
//		QueryPerformanceCounter(&nBeginTime);*/
//
//		//load image
//		Mat srcImg = imread(fileFullName.c_str());
//		flag = image_subtraction(srcImg, i);
//
//		string strImg;
//
//		if (flag == 1){
//			strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//			imwrite(strImg, thr_img);
//			cout << "此样片为ok片！" << endl;
//		}
//		else{
//			cout << "此样片为ng片！" << endl;
//			strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//			imwrite(strImg, thr_img);
//			ng_num++;
//		}
//
//		/*QueryPerformanceCounter(&nEndTime);
//		dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//		cout << "代码的运行时间为" << dtime << "秒!" << endl;*/
//	}
//
//	cout << "总图片数：" << fileNames.size() << ", ng图片数:" << ng_num << endl;
//
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "代码的运行时间为" << dtime << "秒!" << endl;
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//////问题1：往哪偏，哪就有一条线
//////问题2：必须得找一个区分度很高的匹配模块，负责重合不对就会出错！！！
//////相减之后再做裁剪，或者说最后用于判断的一定要是裁剪之后的图，且必须在画轮廓之前裁剪
//////修改之后，紧贴边的图片判断不出来
////我感觉这样会出现更严重的问题
//
//bool image_subtraction(Mat img_src_ng, int i){
//	img_src_ok = imread("D:\\newSample\\0513\\b\\3.JPG");      ///8  D:\\newSample\\canndy\\00001.JPG
//	//imshow("原图", img_src_ok);
//	//imshow("缺陷图", img_src_ng);
//	//waitKey(0);
//	rotated_ng = img_src_ng.clone();
//	////------------------>旋转 <-----------------------------
//	//ImageRecify(img_src_ng, rotated_ng);
//
//	int extRows = EXTD_EDGE;
//	int extCols = EXTD_EDGE;
//	copyMakeBorder(img_src_ok, extd_ok, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	//imshow("extended ok image", extd_ok);
//
//	int extRows2 = EXTD_EDGE;
//	int extCols2 = EXTD_EDGE;
//	copyMakeBorder(rotated_ng, extd_rotated_ng, extRows2, extRows2, extCols2, extCols2, BORDER_CONSTANT);
//	//imshow("extended ng image", extd_rotated_ng);
//	//waitKey(0);
//
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///如此，就可以在指定的图片上自动截取模板，而不是人工截取， 并且可以计算出偏移量了。
//	imwrite("D:\\roiImage_2\\sample3\\save\\moban.jpg", templ_ok);
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	///////-------------->边缘检测<-----------------------------------------
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////
//	//// 计算源图像及待检测图像的边缘图像
//	//int  safePix = 9;      // 安全像素个数   9 
//	//int  numModel = 7;     // 扫描模板大小  
//	//int dataSafe = int(float(numModel*numModel) / 2);
//	//int grayTh_1 = 50;
//
//
//	////// 截图待检测图像  
//	//int row = img_src_ok.rows;
//	//int col = img_src_ok.cols;
//
//	////平移之后图像大小不同，但是这里处理的是变换后的图像，需要修改？？？
//
//
//	/////////////////////////////////////////////////
//	//int offset = 2;  // 求边界偏移量
//	//int rowe = row - 2 * offset;
//	//int cole = col - 2 * offset;
//
//	//Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//
//	//ROIComEdge(img_src_ok, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//	////imshow("ok边缘图", edgeImgSrc);
//
//	//////////////////////////////////////////////////
//	//// ---------- 方法一 两图的边缘图像相减 ----------
//	//// --- 在边缘位置设置安全范围，留下不同的像素点  
//	//// --- 用5*5模板去扫描， 
//	//// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//	//// --- 像素个数小于10，去除，计数加0     
//	//// --- 计数值>0，则NG； 计数值=0, 则OK     
//	//////////////////////////////////////////////////
//	//// 1 沿源图像边缘区域设置安全范围
//	//// 把边缘图像变成二值化图像   
//	//Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//	//for (int i = 1; i < rowe; i++)
//	//{
//	//	for (int j = 1; j < cole; j++)
//	//	{
//	//		if (edgeImgSrc.at <uchar>(i, j) > 0)
//	//		{
//	//			edgeImgSrcTh.at <uchar>(i, j) = 255;
//	//		}
//	//	}
//	//}
//
//	////imshow("srcEdge", edgeImgSrcTh);
//	////waitKey(0);
//
//	//////////////////////////////////////////////////
//	//// 用膨胀法，扩展边缘亮区域
//	////获取自定义核
//	////第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	//Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	////膨胀操作
//	//Mat edgeImgSafe;
//	//dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//
//	//imshow("pengzhang", edgeImgSafe);
//	////waitKey(0);
//
//	////imshow("fanseqian", edgeImgSafe);
//
//	//// 反色，且归一化到[0, 1]; 
//	//edgeImgSafe = (255 - edgeImgSafe) / 255;   //反色操作有什么效果，还没搞清楚
//	//imshow("safe", edgeImgSafe);
//	//imwrite("D:\\roiImage_2\\sample3\\save\\fanse.jpg", edgeImgSafe);
//	////waitKey(0);
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////
//
//	////------------------>模板匹配<--------------------------------------------------------------------------
//	// Create windows
//	namedWindow(image_window, CV_WINDOW_NORMAL); ////0
//	namedWindow(result_window, CV_WINDOW_NORMAL);  //CV_WINDOW_AUTOSIZE
//
//	// Create Trackbar
//	char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);
//
//	MatchingMethod(0, 0);
//
//	////----------------->两图之差<-----------------------------------------------------
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("两图之差", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//
//	/*
//	在画轮廓之前的图像裁剪，
//	if (y >= tempy){
//		Rect(edge, edge, cols, rows - abs(y - tempy));
//	}
//	if (y < tempy) {
//		Rect(edge, edge - abs(y - tempy), cols, rows - abs(y - tempy));
//	}
//	if (x >= tempx){
//		Rect(edge, edge, cols - abs(x - tempx), rows);
//	}
//	if (x < tempx) {
//		Rect(edge - abs(x - tempx), edge, cols - abs(x - tempx), rows);
//	}
//	
//	TEMPL_X
//	TEMPL_Y
//	TEMPL_WIDTH
//	*/
//
//	/*Rect m_select;
//	int row = img_src_ok.rows;
//	int col = img_src_ok.cols;
//	int deltaX = matchLoc.x - TEMPL_X;
//	int deltaY = matchLoc.y - TEMPL_Y;
//
//	if (deltaX >= 0 && deltaY >= 0){
//		m_select = Rect(EXTD_EDGE, EXTD_EDGE, col - abs(deltaX), row - abs(deltaY));
//	}
//	else if (deltaX >= 0 && deltaY < 0){
//		m_select = Rect(EXTD_EDGE, EXTD_EDGE - abs(deltaY), col - abs(deltaX), row - abs(deltaY));
//	}
//	else if (deltaX < 0 && deltaY >= 0){
//		m_select = Rect(EXTD_EDGE - abs(deltaX), EXTD_EDGE, col - abs(deltaX), row - abs(deltaY));
//	}
//	else{
//		m_select = Rect(EXTD_EDGE - abs(deltaX), EXTD_EDGE - abs(deltaY), col - abs(deltaX), row - abs(deltaY));
//	}*/
//
//	
//
//	Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	Mat ROI = diff_dst(m_select);
//	imshow("剪裁图", ROI);
//	imwrite("D:\\roiImage_2\\sample3\\save\\ROI.jpg", ROI);
//
//	////----------------->中值滤波<-----------------------------------------------------------
//	//medianBlur(diff_dst, diff_dst, 3);
//
//	////----------------->图像增强<------------------------------------------------------------
//	Mat enhc_img;
//	image_enhance(ROI, enhc_img);
//	imshow("zengqiang", enhc_img);
//
//	////----------------->二值化<-------------------------------------------------------------
//	//Mat thr_img;
//	threshold(enhc_img, thr_img, thrNum, 255, CV_THRESH_BINARY);  ///180, 255    CV_THRESH_BINARY    CV_THRESH_BINARY_INV
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//	//waitKey(0);
//
//  ROIComDenoise(thr_img, thr_img, AreaLimit);
//
//	//////////////////////////////////////////////////
//	//// 用5*5模板去扫描， 
//	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//	//int resultNum = 0;
//	//int dataTem = 0;
//	//int dataZong = 0;
//	//int dataNum = 0;
//
//	//for (int i = numModel; i < rowe - numModel; i++)
//	//{
//	//	for (int j = numModel; j < cole - numModel; j++)
//	//	{
//	//		dataTem = 0;
//	//		dataZong = 0;
//	//		dataNum = 0;
//	//		for (int m = 0; m < numModel; m++)
//	//		{
//	//			for (int n = 0; n < numModel; n++)
//	//			{
//	//				dataTem = thr_img.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//	//				//cout << dataTem << ",";
//	//				if (dataTem > 0)
//	//				{
//	//					dataZong = dataZong + 1;
//	//				}
//	//			}
//	//		}
//	//		if (dataZong > dataSafe)
//	//		{
//	//			//cout << dataZong << ",";
//	//			//只要有不同，都会标出来的，而且不只是它们不同的地方，最主要是边界，边界没重合，有红点，那就表示坏片。
//	//			//resultImg.at<uchar>(i, j) = 255;
//	//			resultImg.at<Vec3b>(i, j)[0] = 0;
//	//			resultImg.at<Vec3b>(i, j)[1] = 0;
//	//			resultImg.at<Vec3b>(i, j)[2] = 255;
//
//	//			//showImg.at<Vec3b>(m, n)[2] = 255;
//	//			resultNum++;
//	//		}
//	//	}
//	//}
//
//	//imshow("滤波结果", resultImg);   ///滤波结果其实保留的是原图， 然后与detect图重合的部分不显示
//	//imwrite("D:\\roiImage_2\\sample3\\save\\result.jpg", resultImg);
//	////waitKey(0);
//
//	//string strImg;
//	//cout << "像素差：" << resultNum << endl;
//
//	//if (resultNum <= numDetectTh){
//	//	m_resultDetectCom = 1;  // OK 
//	//	strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//	//	imwrite(strImg, diff_dst);
//	//	cout << "此样片为ok片！" << endl;
//	//}
//	//else{
//	//	m_resultDetectCom = 0;  // NG 
//	//	cout << "此样片为ng片！" << endl;
//	//	cout << "轮廓数：" << num_contours << endl;
//	//	strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//	//	imwrite(strImg, diff_dst);
//
//	//	ng_num++;
//	//}
//	//return  m_resultDetectCom;
//
//	//cvtColor(thr_img, thr_img, CV_BGR2GRAY);  
//
//	////图像反色
//	//thr_img = fanse(thr_img);
//
//	//////----------------->开运算<-----------------------
//	morph(thr_img);
//
//	//////----------------->裁剪回原尺寸<---------------------------
//	//Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	//Mat ROI = morph_out(m_select);
//	////imshow("剪裁图", ROI);
//
//	//////----------------->画轮廓，圈出缺陷，首先转换成彩色图像就能画颜色框了
//	draw_contour(morph_out);
//	/*string strImg;
//	if (num_contours > 0){
//		cout << "此样片为ng片！" << endl;
//		cout <<"轮廓数：" << num_contours << endl;
//		strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//		imwrite(strImg, diff_dst);
//
//		ng_num++;
//	}
//	else{
//		strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//		imwrite(strImg, diff_dst);
//		cout << "此样片为ok片！" << endl;
//	}*/
//	//thr_img = fanse(thr_img);
//	//imshow("xiangkan", thr_img);
//	imshow("xiangkan", drawing);
//	waitKey(0);
//
//	if (num_contours == 0){
//		m_resultDetectCom = 1;
//	}
//	else{
//		m_resultDetectCom = 0;
//	}
//	//thr_img = convertTo3Channels(thr_img);
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//int pixNum = 0;
//	//int pixVal = 0;
//	//Mat resultImg = Mat::zeros(thr_img.rows, thr_img.cols, CV_8UC3);
//	//for (int i = 0; i < thr_img.rows; i++){
//	//	for (int j = 0; j < thr_img.cols; j++){
//	//		//pixVal = thr_img.at<uchar>(i, j);
//	//		//if (pixVal > 0){ 
//	//		//	pixNum++;
//	//		//	//cout << pixVal << ","; 
//	//		//	if (pixNum >= 200){
//	//		//		pixNum = 0;
//	//		//		m_resultDetectCom = 0;
//	//		//		//return m_resultDetectCom;
//	//		//	}
//	//		//}
//	//		//else{
//	//		//	pixNum = 0;
//	//		//}
//	//		
//	//		if (pixVal > 0 ){
//	//			
//	//			resultImg.at<Vec3b>(i, j)[0] = 255 - thr_img.at<Vec3b>(i, j)[0];
//	//			resultImg.at<Vec3b>(i, j)[1] = 255 - thr_img.at<Vec3b>(i, j)[1];
//	//			resultImg.at<Vec3b>(i, j)[2] = 255 - thr_img.at<Vec3b>(i, j)[2];
//	//			pixNum++;
//	//		}
//	//	}
//	//}
//	//imshow("滤波结果", resultImg);   ///滤波结果其实保留的是原图， 然后与detect图重合的部分不显示
//	//imwrite("D:\\roiImage_2\\sample3\\save\\result.jpg", resultImg);
//	//waitKey(0);
//
//	////waitKey(0);
//	return m_resultDetectCom;
//}
//
//Mat convertTo3Channels(const Mat& binImg) { 
//	Mat three_channel = Mat::zeros(binImg.rows, binImg.cols, CV_8UC3);     
//	vector<Mat> channels;     
//	
//	for (int i = 0; i<3; i++)     { 
//		channels.push_back(binImg); 
//	}     
//	
//	merge(channels, three_channel);     
//	return three_channel; 
//}
//
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
//	result.create(result_rows, result_cols, CV_8UC1);  ///CV_32FC1
//
//
//	//对于空白片要事先做一个判断，因为找不到模板，无法匹配
//	//找不到匹配模板的样片直接判为ng
//
//	//如果第一个片是空白片，那么会出现问题，如果不是就没问题？？
//
//	/// Do the Matching and Normalize
//	matchTemplate(extd_rotated_ng, templ_ok, result, match_method);
//	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//
//	/*/// Localizing the best match with minMaxLoc
//	double minVal;
//	double maxVal;
//	Point minLoc;
//	Point maxLoc;
//	Point matchLoc;*/
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
//	//waitKey(0);
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
//		Img_resuly = src.clone();   ////???
//		return;
//	}
//	rotateImage(src, dst, degree);      //逆时针旋转图像degree角度（原尺寸）
//	cout << "angle:" << degree << endl;
//	//imshow("旋转调整后", dst);
//
//	Img_resuly = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
//	//imshow("裁剪之后", Img_resuly);
//	imwrite("recified.jpg", Img_resuly);
//	//waitKey(0);
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
// //用这种方法找直线计算倾角方法不稳定
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 150, 250, 3);    ///直线检测这里，因为是不同的图片，灰度值不同，所以必须要在界面上设定阈值，首先让工人找到直线（清晰的轮廓，再工作）
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
//		if (theta == 0){
//			zeroLine++;
//		}
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar函数用于调节线段颜色
//
//		//imshow("直线探测效果图", dstImage);
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
//	//float average = lines[0][1]; //印刷品选择这个
//	cout << "average theta:" << DegreeTrans(average) << endl;
//	
//	double angle = 0;
//	if (DegreeTrans(average) >= 90){
//		angle = DegreeTrans(average) - 180;
//	}
//	else if (DegreeTrans(average) > 0 && DegreeTrans(average) < 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = 0;
//	}
//
//	angle = 0;
//	//double angle = DegreeTrans(average) - 180;
//	//double angle = 0;
//	//我的目的就是不想让它转动大的角度，也就是小于90.
//	/*if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}
//
//	angle = 1;*/
//
//	//rotateImage(dstImage, dst, angle);
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
//	//imshow("move_rotated_ng", move_rotated_ng);
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
//	//imshow("Soure", image);
//	//imshow("after", enhance_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg", enhance_img);
//}
//
//Mat fanse(Mat thr_img){
//	int height = thr_img.rows;
//	int width = thr_img.cols;
//
//	for (int row = 0; row < height; row++){
//		for (int col = 0; col < width; col++){
//			thr_img.at<uchar>(row, col) = 255 - thr_img.at<uchar>(row, col);
//		}
//	}
//	imwrite("D:\\roiImage_2\\sample3\\save\\fanse.jpg", thr_img);
//	return thr_img;
//}
//
//void morph(Mat mor_input){
//	//获取自定义核 第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat element = getStructuringElement(MORPH_RECT, Size(13,13)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
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
//	drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	//imshow("缺陷轮廓图", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	num_contours = g_vContours.size();
//}
//
//void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
//{
//	//int row = srcImg.rows;
//	//int col = srcImg.cols;
//	////int offset = 1;  // 求边界偏移量
//	//int rowe = row - 2 * offset;
//	//int cole = col - 2 * offset;
//	////int grayTh = int(255 / 4);  
//
//	// 处理第 1 幅图像
//	// 差分法求边缘		
//	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
//	for (int i = offset; i < row - offset; i++)
//	{
//		for (int j = offset; j < col - offset; j++)
//		{
//			edgeImg.at<uchar>(i - offset, j - offset) =
//				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
//
//			//又有一个问题，老是在这里出错，但是呢，在不同的图片处出错，比如有的时候是4， 有的时候是6， 也有89， 128， 57，好奇怪
//			//难不成是内存泄露，需要检查各个图像参数的传递情况
//		}
//	}
//	// 把边缘图像像素值映射到[0, 255]
//	int  minEdgeImg = 255;
//	int  maxEdgeImg = 0;
//	for (int i = 0; i < rowe; i++)
//	{
//		for (int j = 0; j < cole; j++)
//		{
//			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
//			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
//		}
//	}
//	for (int i = 0; i < rowe; i++)
//	{
//		for (int j = 0; j < cole; j++)
//		{
//			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
//				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
//		}
//	}
//
//	// 把边缘图像，去掉过小的边缘  	
//	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
//	for (int i = 0; i < rowe; i++)
//	{
//		for (int j = 0; j < cole; j++)
//		{
//			if (edgeImg.at<uchar>(i, j) < grayTh)
//			{
//				edgeImg.at<uchar>(i, j) = 0;
//			}
//		}
//	}
//
//	//imshow("边缘图", edgeImg);
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