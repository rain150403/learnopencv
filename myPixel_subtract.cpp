//bool CVisionFun::ROIComDetectMethod(cv::Mat &srcImg, cv::Mat &showImg, int camIndex, cv::Point centerPoint,
//	int rectWidth, int rectHeight, int rectRotAngle, int distIndex, int detectThr)     //˼��һ������Щ������Ҫ����ȥ
//{
//	//������Ƕ�ȡԭͼ��
//	//��ȡ��Ե����Ե���
//	//�ж�ok�� ng
//	//����ok�� ng��־
//	//����û��ͼ����ת���̣���������Ѿ���ת�õ�ͼ��
//
//	////------------------>ʱ��ͳ��<-------------------------------------
//	LARGE_INTEGER nFreq;
//	LARGE_INTEGER nBeginTime;
//	LARGE_INTEGER nEndTime;
//	double dtime;
//	QueryPerformanceFrequency(&nFreq);
//	QueryPerformanceCounter(&nBeginTime);
//	////////////////////////////////////////////////////////////////////////////////////////////
//
//	img_src_ok = imread("D:\\roiImage_2\\sample3\\1.JPG");      ///8
//	imshow("ԭͼ", img_src_ok);
//	img_src_ng = imread("D:\\roiImage_2\\sample3\\9.JPG");  ///14��Ч���ǳ���     ////12
//	imshow("ȱ��ͼ", img_src_ng);
//
//	////------------------>��ת <-----------------------------
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
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
//
//	////------------------>ģ��ƥ��<--------------------------------------------------------------------------
//
//	MatchingMethod(extd_rotated_ng);   ///ģ��ƥ���ﴫ������չ����ת֮���ͼ��ͨ��ģ��ƥ����ƽ��
//
//	////----------------->��ͼ֮��<-----------------------------------------------------
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("��ͼ֮��", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//	////----------------->��ֵ�˲�<-----------------------------------------------------------
//	medianBlur(diff_dst, diff_dst, 3);
//
//	////----------------->ͼ����ǿ<------------------------------------------------------------
//	Mat enhc_img;
//	image_enhance(diff_dst, enhc_img);
//
//	////----------------->��ֵ��<-------------------------------------------------------------
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 150, 250, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//
//	////----------------->������<-----------------------
//	morph(thr_img);
//
//	////----------------->�ü���ԭ�ߴ�<---------------------------
//	Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	//Mat ROI = morph_out(m_select);
//	Mat ROI = thr_img(m_select);
//	imshow("����ͼ", ROI);
//
//	////----------------->��������Ȧ��ȱ�ݣ�����ת���ɲ�ɫͼ����ܻ���ɫ����
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
//	////----------------->ʱ��ͳ��<--------------------------------------------------------------
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "���������ʱ��Ϊ" << dtime << "����!" << endl;
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
//	//��ͼ����д��
//	putText(img_display, a, Point(matchLoc.x + templ_ok.cols, matchLoc.y + templ_ok.rows), CV_FONT_HERSHEY_COMPLEX_SMALL, 0.85, Scalar(0, 0, 255));
//
//	imshow(image_window, img_display);      //��Ҫ������ʾ���ڣ�������ͼ������������ʾ
//	imshow(result_window, result);
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
//		return;
//	}
//	rotateImage(src, dst, degree);      //��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩
//	cout << "angle:" << degree << endl;
//	imshow("��ת������", dst);
//
//	Img_resuly = dst(Rect(0, 0, src.cols, src.rows)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
//	imshow("�ü�֮��", Img_resuly);
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
//
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 30, 100, 3);    ///ֱ�߼�������Ϊ�ǲ�ͬ��ͼƬ���Ҷ�ֵ��ͬ�����Ա���Ҫ�ڽ������趨��ֵ�������ù����ҵ�ֱ�ߣ��������������ٹ�����
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
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar�������ڵ����߶���ɫ
//
//		imshow("ֱ��̽��Ч��ͼ", dstImage);
//	}
//	//float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
//	float average = lines[0][1]; //ӡˢƷѡ�����
//	cout << "average theta:" << average << endl;
//
//	//double angle = DegreeTrans(average) - 90;
//	double angle = 0;
//	//�ҵ�Ŀ�ľ��ǲ�������ת����ĽǶȣ�Ҳ����С��90.
//	if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}
//
//	rotateImage(dstImage, dst, angle);
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
//	//��һ����0~255    
//	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
//	//ת����8bitͼ����ʾ    
//	convertScaleAbs(imageLog, enhance_img);
//	imshow("Soure", image);
//	imshow("after", enhance_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\enhance_img.jpg", enhance_img);
//}
//
//void morph(Mat mor_input){
//	//��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
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
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("ȱ������ͼ", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	num_contours = g_vContours.size();
//}
