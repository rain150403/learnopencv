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
//			cout << "����ƬΪokƬ��" << endl;
//		}
//		else{
//			cout << "����ƬΪngƬ��" << endl;
//			strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//			imwrite(strImg, thr_img);
//			ng_num++;
//		}
//
//		/*QueryPerformanceCounter(&nEndTime);
//		dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//		cout << "���������ʱ��Ϊ" << dtime << "��!" << endl;*/
//	}
//
//	cout << "��ͼƬ����" << fileNames.size() << ", ngͼƬ��:" << ng_num << endl;
//
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "���������ʱ��Ϊ" << dtime << "��!" << endl;
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//////����1������ƫ���ľ���һ����
//////����2���������һ�����ֶȺܸߵ�ƥ��ģ�飬�����غϲ��Ծͻ��������
//////���֮�������ü�������˵��������жϵ�һ��Ҫ�ǲü�֮���ͼ���ұ����ڻ�����֮ǰ�ü�
//////�޸�֮�󣬽����ߵ�ͼƬ�жϲ�����
////�Ҹо���������ָ����ص�����
//
//bool image_subtraction(Mat img_src_ng, int i){
//	img_src_ok = imread("D:\\newSample\\0513\\b\\3.JPG");      ///8  D:\\newSample\\canndy\\00001.JPG
//	//imshow("ԭͼ", img_src_ok);
//	//imshow("ȱ��ͼ", img_src_ng);
//	//waitKey(0);
//	rotated_ng = img_src_ng.clone();
//	////------------------>��ת <-----------------------------
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
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
//	imwrite("D:\\roiImage_2\\sample3\\save\\moban.jpg", templ_ok);
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	///////-------------->��Ե���<-----------------------------------------
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////
//	//// ����Դͼ�񼰴����ͼ��ı�Եͼ��
//	//int  safePix = 9;      // ��ȫ���ظ���   9 
//	//int  numModel = 7;     // ɨ��ģ���С  
//	//int dataSafe = int(float(numModel*numModel) / 2);
//	//int grayTh_1 = 50;
//
//
//	////// ��ͼ�����ͼ��  
//	//int row = img_src_ok.rows;
//	//int col = img_src_ok.cols;
//
//	////ƽ��֮��ͼ���С��ͬ���������ﴦ����Ǳ任���ͼ����Ҫ�޸ģ�����
//
//
//	/////////////////////////////////////////////////
//	//int offset = 2;  // ��߽�ƫ����
//	//int rowe = row - 2 * offset;
//	//int cole = col - 2 * offset;
//
//	//Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//
//	//ROIComEdge(img_src_ok, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//	////imshow("ok��Եͼ", edgeImgSrc);
//
//	//////////////////////////////////////////////////
//	//// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
//	//// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
//	//// --- ��5*5ģ��ȥɨ�裬 
//	//// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
//	//// --- ���ظ���С��10��ȥ����������0     
//	//// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
//	//////////////////////////////////////////////////
//	//// 1 ��Դͼ���Ե�������ð�ȫ��Χ
//	//// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
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
//	//// �����ͷ�����չ��Ե������
//	////��ȡ�Զ����
//	////��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	//Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	////���Ͳ���
//	//Mat edgeImgSafe;
//	//dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//
//	//imshow("pengzhang", edgeImgSafe);
//	////waitKey(0);
//
//	////imshow("fanseqian", edgeImgSafe);
//
//	//// ��ɫ���ҹ�һ����[0, 1]; 
//	//edgeImgSafe = (255 - edgeImgSafe) / 255;   //��ɫ������ʲôЧ������û�����
//	//imshow("safe", edgeImgSafe);
//	//imwrite("D:\\roiImage_2\\sample3\\save\\fanse.jpg", edgeImgSafe);
//	////waitKey(0);
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////
//
//	////------------------>ģ��ƥ��<--------------------------------------------------------------------------
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
//	////----------------->��ͼ֮��<-----------------------------------------------------
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("��ͼ֮��", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//
//	/*
//	�ڻ�����֮ǰ��ͼ��ü���
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
//	imshow("����ͼ", ROI);
//	imwrite("D:\\roiImage_2\\sample3\\save\\ROI.jpg", ROI);
//
//	////----------------->��ֵ�˲�<-----------------------------------------------------------
//	//medianBlur(diff_dst, diff_dst, 3);
//
//	////----------------->ͼ����ǿ<------------------------------------------------------------
//	Mat enhc_img;
//	image_enhance(ROI, enhc_img);
//	imshow("zengqiang", enhc_img);
//
//	////----------------->��ֵ��<-------------------------------------------------------------
//	//Mat thr_img;
//	threshold(enhc_img, thr_img, thrNum, 255, CV_THRESH_BINARY);  ///180, 255    CV_THRESH_BINARY    CV_THRESH_BINARY_INV
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//	//waitKey(0);
//
//  ROIComDenoise(thr_img, thr_img, AreaLimit);
//
//	//////////////////////////////////////////////////
//	//// ��5*5ģ��ȥɨ�裬 
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
//	//			//ֻҪ�в�ͬ�����������ģ����Ҳ�ֻ�����ǲ�ͬ�ĵط�������Ҫ�Ǳ߽磬�߽�û�غϣ��к�㣬�Ǿͱ�ʾ��Ƭ��
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
//	//imshow("�˲����", resultImg);   ///�˲������ʵ��������ԭͼ�� Ȼ����detectͼ�غϵĲ��ֲ���ʾ
//	//imwrite("D:\\roiImage_2\\sample3\\save\\result.jpg", resultImg);
//	////waitKey(0);
//
//	//string strImg;
//	//cout << "���ز" << resultNum << endl;
//
//	//if (resultNum <= numDetectTh){
//	//	m_resultDetectCom = 1;  // OK 
//	//	strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//	//	imwrite(strImg, diff_dst);
//	//	cout << "����ƬΪokƬ��" << endl;
//	//}
//	//else{
//	//	m_resultDetectCom = 0;  // NG 
//	//	cout << "����ƬΪngƬ��" << endl;
//	//	cout << "��������" << num_contours << endl;
//	//	strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//	//	imwrite(strImg, diff_dst);
//
//	//	ng_num++;
//	//}
//	//return  m_resultDetectCom;
//
//	//cvtColor(thr_img, thr_img, CV_BGR2GRAY);  
//
//	////ͼ��ɫ
//	//thr_img = fanse(thr_img);
//
//	//////----------------->������<-----------------------
//	morph(thr_img);
//
//	//////----------------->�ü���ԭ�ߴ�<---------------------------
//	//Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	//Mat ROI = morph_out(m_select);
//	////imshow("����ͼ", ROI);
//
//	//////----------------->��������Ȧ��ȱ�ݣ�����ת���ɲ�ɫͼ����ܻ���ɫ����
//	draw_contour(morph_out);
//	/*string strImg;
//	if (num_contours > 0){
//		cout << "����ƬΪngƬ��" << endl;
//		cout <<"��������" << num_contours << endl;
//		strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//		imwrite(strImg, diff_dst);
//
//		ng_num++;
//	}
//	else{
//		strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//		imwrite(strImg, diff_dst);
//		cout << "����ƬΪokƬ��" << endl;
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
//	//imshow("�˲����", resultImg);   ///�˲������ʵ��������ԭͼ�� Ȼ����detectͼ�غϵĲ��ֲ���ʾ
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
//	//���ڿհ�ƬҪ������һ���жϣ���Ϊ�Ҳ���ģ�壬�޷�ƥ��
//	//�Ҳ���ƥ��ģ�����Ƭֱ����Ϊng
//
//	//�����һ��Ƭ�ǿհ�Ƭ����ô��������⣬������Ǿ�û���⣿��
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
//	//��ͼ����д��
//	putText(img_display, a, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	imshow(image_window, img_display);      //��Ҫ������ʾ���ڣ�������ͼ������������ʾ
//	imshow(result_window, result);
//
//	//waitKey(0);
//
//	//////-------------------------->ģ��ƥ��֮�󣬵õ�ƽ�����꣬����ƽ�Ʋ���<-----------------
//	translation(matchLoc.x, matchLoc.y);   //ƽ��֮���Է���ģ��ƥ����������Ϊ��match�������ܷ��������
//}
//
//void ImageRecify(Mat src, Mat& Img_resuly)
//{
//	double degree;
//
//	Mat dst;
//	//��б�ǶȽ���
//	degree = CalcDegree(src, dst);      //ͨ������任����Ƕ�
//	if (degree == ERROR)
//	{
//		cout << "����ʧ�ܣ�" << endl;
//		Img_resuly = src.clone();   ////???
//		return;
//	}
//	rotateImage(src, dst, degree);      //��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩
//	cout << "angle:" << degree << endl;
//	//imshow("��ת������", dst);
//
//	Img_resuly = dst(Rect(0, 0, src.cols, src.rows)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
//	//imshow("�ü�֮��", Img_resuly);
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
//	//��ת����Ϊͼ������    
//	Point2f center;
//	center.x = float(src.cols / 2.0);
//	center.y = float(src.rows / 2.0);
//	int length = 0;
//	length = sqrt(src.cols*src.cols + src.rows*src.rows);
//	//�����ά��ת�ķ���任����  
//	Mat M = getRotationMatrix2D(center, degree, 1);
//	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//����任������ɫ���Ϊ��ɫ  
//}
// //�����ַ�����ֱ�߼�����Ƿ������ȶ�
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 150, 250, 3);    ///ֱ�߼�������Ϊ�ǲ�ͬ��ͼƬ���Ҷ�ֵ��ͬ�����Ա���Ҫ�ڽ������趨��ֵ�������ù����ҵ�ֱ�ߣ��������������ٹ�����
//	cvtColor(midImage, dstImage, CV_GRAY2BGR);
//
//	//ͨ������任���ֱ��
//	vector<Vec2f> lines;
//	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);//��5������������ֵ����ֵԽ�󣬼�⾫��Խ��
//	//cout << lines.size() << endl;
//
//	//����ͼ��ͬ����ֵ�����趨����Ϊ��ֵ�趨���ߵ����޷����ֱ�ߣ���ֵ����ֱ��̫�࣬�ٶȺ���
//	//���Ը�����ֵ�ɴ�С������������ֵ�����������������󣬿��Թ̶�һ���ʺϵ���ֵ��
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
//		cout << "û�м�⵽ֱ�ߣ�" << endl;
//		return ERROR;
//	}
//
//	int zeroLine = 0;
//	float sum = 0;
//	//���λ���ÿ���߶�
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
//		//ֻѡ�Ƕ���С����Ϊ��ת�Ƕ�
//		sum += theta;
//
//		if (theta == 0){
//			zeroLine++;
//		}
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar�������ڵ����߶���ɫ
//
//		//imshow("ֱ��̽��Ч��ͼ", dstImage);
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
//	//float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
//	//float average = lines[0][1]; //ӡˢƷѡ�����
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
//	//�ҵ�Ŀ�ľ��ǲ�������ת����ĽǶȣ�Ҳ����С��90.
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
//	//imshow("ֱ��̽��Ч��ͼ2", dstImage);
//	return angle;
//}
//
//void translation(int matchLoc_x, int matchLoc_y){
//	extd_src = extd_rotated_ng.clone();
//	Size dst_sz = extd_src.size();
//
//	//����ƽ�ƾ���
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = TEMPL_X + EXTD_EDGE - matchLoc_x; //ˮƽƽ����   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = TEMPL_Y + EXTD_EDGE - matchLoc_y; //��ֱƽ����     ///12   �����25�� 80�� ��Ҫ��ģ����趨�� ���ı䣬 ������
//	////ǣһ������ȫ�� һ���ط����ˣ��漰�����ĵط���Ҫ�ģ� ����Ҫϸ��
//
//	//////  ��25�� 80��  30   ���� �� ��200�� 40��  80  sample1��
//
//
//	//����ƽ�ƾ�����з���任
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
//	//��һ����0~255    
//	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
//	//ת����8bitͼ����ʾ    
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
//	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	Mat element = getStructuringElement(MORPH_RECT, Size(13,13)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
//	morphologyEx(mor_input, morph_out, MORPH_OPEN, element);
//	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
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
//	//����canny���Ӽ���Ե 
//	Canny(canny_input, canny_out, g_nThresh, g_nThresh * 2, 3);
//	//Ѱ������ 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
//	drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	//imshow("ȱ������ͼ", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	num_contours = g_vContours.size();
//}
//
//void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
//{
//	//int row = srcImg.rows;
//	//int col = srcImg.cols;
//	////int offset = 1;  // ��߽�ƫ����
//	//int rowe = row - 2 * offset;
//	//int cole = col - 2 * offset;
//	////int grayTh = int(255 / 4);  
//
//	// ����� 1 ��ͼ��
//	// ��ַ����Ե		
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
//			//����һ�����⣬������������������أ��ڲ�ͬ��ͼƬ�����������е�ʱ����4�� �е�ʱ����6�� Ҳ��89�� 128�� 57�������
//			//�Ѳ������ڴ�й¶����Ҫ������ͼ������Ĵ������
//		}
//	}
//	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
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
//	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
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
//	//imshow("��Եͼ", edgeImg);
//}
//
//
//// ȥ������������   
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit)
//{
//	int RemoveCount = 0;
//	//�½�һ����ǩͼ���ʼ��Ϊ0���ص㣬Ϊ�˼�¼ÿ�����ص����״̬�ı�ǩ��0����δ��飬1�������ڼ��,2�����鲻�ϸ���Ҫ��ת��ɫ����3������ϸ������   
//	//��ʼ����ͼ��ȫ��Ϊ0��δ���  
//	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
//	//ȥ��С��ͨ����İ�ɫ��  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (Src.at<uchar>(i, j) < 10)
//			{
//				PointLabel.at<uchar>(i, j) = 3;//��������ɫ����Ϊ�ϸ�����Ϊ3  
//			}
//		}
//	}
//
//	vector<Point2i>NeihborPos;//������ѹ������  
//	NeihborPos.push_back(Point2i(-1, 0));
//	NeihborPos.push_back(Point2i(1, 0));
//	NeihborPos.push_back(Point2i(0, -1));
//	NeihborPos.push_back(Point2i(0, 1));
//	//cout << "Neighbor mode: 8����." << endl;
//	NeihborPos.push_back(Point2i(-1, -1));
//	NeihborPos.push_back(Point2i(-1, 1));
//	NeihborPos.push_back(Point2i(1, -1));
//	NeihborPos.push_back(Point2i(1, 1));
//
//	int NeihborCount = 8;
//	int CurrX = 0, CurrY = 0;
//	//��ʼ���  
//	for (int i = 0; i < Src.rows; i++)
//	{
//		for (int j = 0; j < Src.cols; j++)
//		{
//			if (PointLabel.at<uchar>(i, j) == 0)//��ǩͼ�����ص�Ϊ0����ʾ��δ���Ĳ��ϸ��  
//			{   //��ʼ���  
//				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
//				GrowBuffer.push_back(Point2i(j, i));
//				PointLabel.at<uchar>(i, j) = 1;//���Ϊ���ڼ��  
//				int CheckResult = 0;
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					for (int q = 0; q < NeihborCount; q++)
//					{
//						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
//						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
//						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //��ֹԽ��    
//						{
//							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
//							{
//								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //��������buffer    
//								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //���������ļ���ǩ�������ظ����    
//							}
//						}
//					}
//				}
//				if (GrowBuffer.size()>AreaLimit) //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����    
//					CheckResult = 2;
//				else
//				{
//					CheckResult = 1;
//					RemoveCount++;//��¼�ж�������ȥ��  
//				}
//
//				for (int z = 0; z < GrowBuffer.size(); z++)
//				{
//					CurrX = GrowBuffer.at(z).x;
//					CurrY = GrowBuffer.at(z).y;
//					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//��ǲ��ϸ�����ص㣬����ֵΪ2  
//				}
//				//********�����õ㴦�ļ��**********    
//			}
//		}
//	}
//	//��ʼ��ת�����С������    
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