///////�������Ը���һЩ����Ƭ����������⣬��Ҫ�ǶԲ���
//////ģ������������ܶ���
/////����1��ȷ��ģ��λ��    ���Ͻǣ��м䣿  2��������ģ��    3�� ����˵���ⲻ�ǳ���ģ�壬���ǳ�����ת��
////��ʱģ��ƥ�����Ҳ����΢���
//
//////�����ƶ�ģ��ƥ�䷽���ܺã����Ƕ���ϸС�Ĳ���ⲻ����������û��һ�ַ������԰�ϸС��Ҳ�����ֳ�����
////�������룬��ģ��ƥ��Ч����ã���Ȼ������һ����ȱ�ݣ���ⲻ����
////�˲���������ͼ��ģ������֮���ղ����ȣ���ֵ����ͼƬ����Ч�����ã� ��Ե��⣬��ģ��ƥ��Ч�����á�
////�����ַ���TM_COEFF������С�Ĳдο������������Ƕ��ڴ���кܴ�Ӧ
////���ַ�������ӡˢƷ��ģ��ƥ����Ч
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
//#define TEMPL_X 740   //��������չ�߽�
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
//void ImageRecify(Mat src, Mat& Img_resuly);     ///��ֱ�ߵķ������������Ҫ��һ�ģ���Ϊ����⵽�ܶ���ֱ�ߣ������ͻ�Ӱ����תЧ��
////���о���ͼ����ת���������Ϊֱ����Ȼ�򵥣����ǻ��⵽�ܶ�ֱ�ߣ�������ƥ��ķ�����Ȼ�鷳�� ���ǿ���������ĽǶȱȽϹ̶�����һ
//double CalcDegree(const Mat &srcImage, Mat &dst);
////����ת��
//double DegreeTrans(double theta);
////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
//void image_enhance(Mat image, Mat& enhance_img);
//
////WRAP: �������ҵߵ�
////REPLICATE: ��Ȼ����û���� ���к����Ե�һ������
////���һ�ϣ������ת����ɫ�ǲ��ָĵ�������Ҫ֪����ô��ȡĳλ�õ�����ֵ�����ڱ߽���������ֵ
//
////�ǵð�ʱ�����ȥ
////���о�������ģ��ɲ����ԣ������Ժ��ٿ�������ģ�������
////���������ô��ok�� ng�����ֿ���������
//
////���Ҫ�����е�ģ�鶼�����ɺ�������Ҫ�޸���������Ҫ���޴���
////������Ҫ����ڶ���������
////����1����Ҫͼ����ǿ������ͼ��Աȶ�
////����2����Ҫ��ͼ��ƽ�Ʋ������ں���
//int main21(int argc, char** argv){
//
//	//D:\\��ƷͼƬ\\sample8\\ok\\00046.JPG
//	//"D:\\��ƷͼƬ\\sample8\\ng\\00043.JPG"
//
//	//D:\\waitDelete\\roiImage\\louxiaxinpai\\��ɫ����\\ok_train_1\\00013.JPG
//	//D:\\waitDelete\\roiImage\\louxiaxinpai\\��ɫ����\\ng_test_1\\00032.JPG
//
//	/////////////////////ʱ��ͳ��////////////
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
//	imshow("ԭͼ", img_src_ok);
//	rotated_ng = imread("D:\\roiImage_2\\sample12\\3.JPG");  ///14��Ч���ǳ���     ////12
//	//imshow("ȱ��ͼ", img_src_ng);
//	imshow("ȱ��ͼ", rotated_ng);
//
//	////////////�����ټ�һ����ת���� //////////
//	//ImageRecify(img_src_ng, rotated_ng);
//	//////////////////////////////////////////////////
//
//	///////////////////////��ֵ�˲�/////
//	/*medianBlur(img_src_ok, img_src_ok, 3);
//	medianBlur(rotated_ng, rotated_ng, 3);*/
//	//�����׻������ղ�������˲�Ҳ�����ã� ��������Ӱ��Ч��
//	///////////////////////
//
//	int extRows = EXTD_EDGE;    //����Ҳ����д������Ҫ���ñ�������ѡ����Ƭ֮��ľ���/2���� ��Ϊ�����Ҳ����ƫ�������Χ������ʵ�ڲ��У��ͻ��ɣ��������룩
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
//	templ_ok = extd_ok(Rect(TEMPL_X + EXTD_EDGE, TEMPL_Y + EXTD_EDGE, TEMPL_WIDTH, TEMPL_WIDTH));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
//	//��������Ϳ�Ĵ�Сʱ��Ҫ�����Լ�����Ƭ�ĳߴ����޸�
//	//���ģ�������Ϊ�����������ڽ���������һ�����ù����Լ�ȥȦ�������Ե�����, ��������д����ԣ���������ĵĸպ���ȫ�����򣬾ͺܴ����ƥ�����
//	//��ȻҪ����һ���޶����������ƶ������ͼƬ��������
//	//ע������߽�Ŀ�ȱ�����
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
//	//////////////////ʱ��ͳ��/////////////////////
//	QueryPerformanceCounter(&nEndTime);
//	dtime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
//	cout << "���������ʱ��Ϊ" << dtime << "����!" << endl;
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
//	//195+ 70, 24+67  �����½ǣ� 70�� 67 ���ҵ�ģ��Ŀ�ߣ� ���ԣ� ��195�� 24�������Ͻ�
//
//	imshow(image_window, img_display);      //����֣��ڲ��Ժ�����ʱ��Ȼ����ͼƬ����
//	imshow(result_window, result);
//
//	////////////////////ģ��ƥ��֮�󣬵õ�ƽ�����꣬����ƽ�Ʋ���/////////////
//	extd_src = extd_rotated_ng.clone();
//	Size dst_sz = extd_src.size();
//
//	//����ƽ�ƾ���
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = TEMPL_X + EXTD_EDGE - matchLoc.x; //ˮƽƽ����   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = TEMPL_Y + EXTD_EDGE - matchLoc.y; //��ֱƽ����     ///12   �����25�� 80�� ��Ҫ��ģ����趨�� ���ı䣬 ������
//	////ǣһ������ȫ�� һ���ط����ˣ��漰�����ĵط���Ҫ�ģ� ����Ҫϸ��
//
//	//////  ��25�� 80��  30   ���� �� ��200�� 40��  80  sample1��
//
//
//	//����ƽ�ƾ�����з���任
//	warpAffine(extd_src, move_rotated_ng, t_mat, dst_sz);
//	imshow("move_rotated_ng", move_rotated_ng);
//	imwrite("D:\\roiImage_2\\sample3\\save\\move_rotated_ng.jpg", move_rotated_ng);
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("��ͼ֮��", diff_dst);
//	imwrite("D:\\roiImage_2\\sample3\\save\\diff_dst.jpg", diff_dst);
//
//	medianBlur(diff_dst, diff_dst, 3);
//
//	Mat enhc_img;
//
//	image_enhance(diff_dst, enhc_img);
//
//	//���뵽һ���ǣ���ͬһ��ͼ����Ĵ������࣬�ǲ��Ƿ�����ʧȥһЩ������Ϣ�����߾ʹﲻ����ԭͼ�����ִ���Ч������
//	//���һ���뵽�Ƕ�ֵ��������Ч���������ԣ�����Ҫ��Ҫ�� �ڶ�ֵ����������һ����ʴ���ͣ���һЩϸС�������������һ��
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 100, 250, CV_THRESH_BINARY);  ///180, 255
//	imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//
//	Mat morph_out; //��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵� 
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
//	morphologyEx(thr_img, morph_out, MORPH_OPEN, element);
//	//morphologyEx(thr_img, morph_out, MORPH_CLOSE, element);   //�Ժ��������ǣ����ڿ���open��һЩ
//	imshow("fushi", morph_out);
//	imwrite("D:\\roiImage_2\\sample3\\save\\fushi.jpg", morph_out);
//
//	////��ֵ����ֵ�޸�һЩ������������ʾЧ��
//	////��ʴ������Ҫ��һ��
//
//	//��ʵ��Ȼǰ��Ч������ô���������һ��Ǿ�������ƽ�ƣ���ù⣬Ч��Ӧ�û��ǲ����
//
//
//	////////////�������� Ȧ��ȱ�ݣ� ����ת���ɲ�ɫͼ����ܻ���ɫ����
//	int g_nThresh = 80;
//	RNG g_rng(12345);
//	Mat canny_out; 
//	vector<vector<Point> > g_vContours; 
//	vector<Vec4i> g_vHierarchy;
//
//	//����canny���Ӽ���Ե 
//	Canny(enhc_img, canny_out, g_nThresh, g_nThresh * 2, 3); 
//	//Ѱ������ 
//	findContours(canny_out, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)); 
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3); 
//	for (int i = 0; i < g_vContours.size(); i++) { 
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)); 
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point()); 
//	}
//	imshow("ȱ������ͼ", drawing);
//
//	//Ч����������������̫�࣬������ô�˳�
//
//	//////////////floodfill///////////////////////////////////////
//	//Rect ccomp;
//	//floodFill(diff_dst, Point(50, 300), Scalar(155, 255, 55), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
//	//imshow("ˮ����ɽ", diff_dst);
//	/////ˮ����ɽҲ������Ҫ�󣬲�������������������Щ����
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	////////���濼����ͨ�򷽷�/////////////////////////////
//
//	//////����һ�㣬������ô�࣬���˴�����������ܲ������˲�����ȥ��������
//
//
//	///seedfill��ȻҲ���԰���ֻ�ǹ��յ�����̫��
//
//	////////////////////////////////////////////////////////////////////
//	waitKey(0);
//
//	cout << "123" << endl;
//}
//
////ֻҪ��ת�����Ժ���Ӱ��ͺܴ��������ַ�������Ҫ��ֱ�߼��Ҫ��ܸߡ�
////void ImageRecify(const char* pInFileName, const char* pOutFileName)
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
////����ת��
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
//
////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
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
////ͨ������任����Ƕ�
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
//	float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
//	//float average = lines[0][1]; //ӡˢƷѡ�����
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


///////����Ѿ��ܺ��ˣ������ﵽĿ�꣬�ڴ˻�����ȥ�Ľ��ͺ���
//////�����ƶ�ģ��ƥ�䷽���ܺã����Ƕ���ϸС�Ĳ���ⲻ����������û��һ�ַ������԰�ϸС��Ҳ�����ֳ�����
////�������룬��ģ��ƥ��Ч����ã���Ȼ������һ����ȱ�ݣ���ⲻ����
////�˲���������ͼ��ģ������֮���ղ����ȣ���ֵ����ͼƬ����Ч�����ã� ��Ե��⣬��ģ��ƥ��Ч�����á�
////�����ַ���TM_COEFF������С�Ĳдο������������Ƕ��ڴ���кܴ�Ӧ
////���ַ�������ӡˢƷ��ģ��ƥ����Ч
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
////����ת��
//double DegreeTrans(double theta);
////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
//void image_enhance(Mat image, Mat& enhance_img);
//
////����1����Ҫͼ����ǿ������ͼ��Աȶ�
////����2����Ҫ��ͼ��ƽ�Ʋ������ں���
//int main(int argc, char** argv){
//
//	//21
//	img_src_ok = imread("D:\\��ƷͼƬ\\sample1\\ok\\8.JPG");
//	imshow("yuantu", img_src_ok);
//	img_src_ng = imread("D:\\��ƷͼƬ\\sample1\\ng\\7.JPG");  ///14��Ч���ǳ���
//	imshow("yu", img_src_ng);
//
//	////////////�����ټ�һ����ת���� //////////
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
//	//����ƽ�ƾ���
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = -12; //ˮƽƽ����   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 8; //��ֱƽ����     ///12
//
//	//����ƽ�ƾ�����з���任
//	warpAffine(extd_src, move_rotated_ng, t_mat, dst_sz);
//
//	//��ʾƽ��Ч��
//	//imshow("image", extd_src);
//	//imshow("result", extd_dst);
//
//	templ = extd_ok(Rect(200, 40, 80, 80));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
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
//	//195+ 70, 24+67  �����½ǣ� 70�� 67 ���ҵ�ģ��Ŀ�ߣ� ���ԣ� ��195�� 24�������Ͻ�
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	absdiff(extd_ok, move_rotated_ng, diff_dst);
//	imshow("��ͼ֮��", diff_dst);
//
//	Mat enhc_img;
//
//	image_enhance(diff_dst, enhc_img);
//
//	//���뵽һ���ǣ���ͬһ��ͼ����Ĵ������࣬�ǲ��Ƿ�����ʧȥһЩ������Ϣ�����߾ʹﲻ����ԭͼ�����ִ���Ч������
//	//���һ���뵽�Ƕ�ֵ��������Ч���������ԣ�����Ҫ��Ҫ�� �ڶ�ֵ����������һ����ʴ���ͣ���һЩϸС�������������һ��
//	Mat thr_img;
//	threshold(enhc_img, thr_img, 10, 50, CV_THRESH_BINARY);
//	imshow("erzhihua", thr_img);
//
//	Mat out; //��ȡ�Զ���� ��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵� 
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //����Ҫѡ�����ֲ��������޸ĵ����������Ϳ����ˡ�������ʾ������̬ѧ�����㴦�� 
//	morphologyEx(thr_img, out, MORPH_OPEN, element);
//	imshow("fushi", out);
//
//	//��ʵ��Ȼǰ��Ч������ô���������һ��Ǿ�������ƽ�ƣ���ù⣬Ч��Ӧ�û��ǲ����
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
////����ת��
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
//
//
////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
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
////ͨ������任����Ƕ�
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 50, 200, 3);
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
//	float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
//
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
//void image_enhance(Mat image, Mat& enhance_img){
//
//	imshow("ԭͼ��", image);
//	Mat imageRGB[3];
//	split(image, imageRGB);
//	for (int i = 0; i < 3; i++)
//	{
//		equalizeHist(imageRGB[i], imageRGB[i]);
//	}
//	merge(imageRGB, 3, enhance_img);
//	imshow("ֱ��ͼ���⻯ͼ����ǿЧ��", enhance_img);
//}

//////�����ƶ�ģ��ƥ�䷽���ܺã����Ƕ���ϸС�Ĳ���ⲻ����������û��һ�ַ������԰�ϸС��Ҳ�����ֳ�����
////�������룬��ģ��ƥ��Ч����ã���Ȼ������һ����ȱ�ݣ���ⲻ����
////�˲���������ͼ��ģ������֮���ղ����ȣ���ֵ����ͼƬ����Ч�����ã� ��Ե��⣬��ģ��ƥ��Ч�����á�
////�����ַ���TM_COEFF������С�Ĳдο������������Ƕ��ڴ���кܴ�Ӧ
////���ַ�������ӡˢƷ��ģ��ƥ����Ч
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
//	img_src_ok = imread("D:\\��ƷͼƬ\\sample1\\ok\\8.JPG");
//	img_src_ng = imread("D:\\��ƷͼƬ\\sample1\\ng\\12.JPG");
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
//	//����ƽ�ƾ���
//	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 19; //ˮƽƽ����   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 12; //��ֱƽ����     ///12
//
//	//����ƽ�ƾ�����з���任
//	warpAffine(extd_src, extd_dst, t_mat, dst_sz);
//
//	////////////�����ټ�һ����ת���� //////////
//
//	//////////////////////////////////////////////////
//
//	//��ʾƽ��Ч��
//	//imshow("image", extd_src);
//	//imshow("result", extd_dst);
//
//	templ = extd_ok(Rect(200, 40, 80, 80));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
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
//	//195+ 70, 24+67  �����½ǣ� 70�� 67 ���ҵ�ģ��Ŀ�ߣ� ���ԣ� ��195�� 24�������Ͻ�
//
//	imshow(image_window, img_display);
//	imshow(result_window, result);
//
//	absdiff(extd_ok, extd_dst, diff_dst);
//	imshow("��ͼ֮��", diff_dst);
//
//	waitKey(0);
//
//	system("pause");
//	return;
//}


//ͻȻ�뵽���뵽���ܲü����ü�֮���ֻع�ԭͼ�ˣ������������������ͼ���ڣ�λ����һ���ġ�
//�� ���������֮���ͼ����ֱ��������ķ���������Ч����



////////�����ƶ�ģ��ƥ�䷽���ܺã����Ƕ���ϸС�Ĳ���ⲻ����������û��һ�ַ������԰�ϸС��Ҳ�����ֳ�����
////�������룬��ģ��ƥ��Ч����ã���Ȼ������һ����ȱ�ݣ���ⲻ����
////�˲���������ͼ��ģ������֮���ղ����ȣ���ֵ����ͼƬ����Ч�����ã� ��Ե��⣬��ģ��ƥ��Ч�����á�
////�����ַ���TM_COEFF������С�Ĳдο������������Ƕ��ڴ���кܴ�Ӧ
////���ַ�������ӡˢƷ��ģ��ƥ����Ч
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
//	img = imread("D:\\��ƷͼƬ\\sample1\\ng\\12.JPG");
//	imgOk = imread("D:\\��ƷͼƬ\\sample1\\ok\\8.JPG");
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
//	//����ƽ�ƾ���
//	cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 0; //ˮƽƽ����   ///19
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 0; //��ֱƽ����     ///12
//
//	//����ƽ�ƾ�����з���任
//	cv::warpAffine(src, dst, t_mat, dst_sz);
//
//	//��ʾƽ��Ч��
//	cv::imshow("image", src);
//	cv::imshow("result", dst);
//
//	templ = extendedIm2(Rect(200, 40, 80, 80));     ///��ˣ��Ϳ�����ָ����ͼƬ���Զ���ȡģ�壬�������˹���ȡ�� ���ҿ��Լ����ƫ�����ˡ�
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
//	//195+ 70, 24+67  �����½ǣ� 70�� 67 ���ҵ�ģ��Ŀ�ߣ� ���ԣ� ��195�� 24�������Ͻ�
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
//	Mat orgIm = imread("D:\\��ƷͼƬ\\sample1\\ng\\12.JPG");
//	int extRows = 50;
//	int extCols = 50;
//	Mat extendedIm;
//	copyMakeBorder(orgIm, extendedIm, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image", orgIm);
//	imshow("extended image", extendedIm);
//
//	Mat orgIm2 = imread("D:\\��ƷͼƬ\\sample1\\ok\\8.JPG");
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
//	//����ƽ�ƾ���
//	cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
//
//	t_mat.at<float>(0, 0) = 1;
//	t_mat.at<float>(0, 2) = 50; //ˮƽƽ����
//	t_mat.at<float>(1, 1) = 1;
//	t_mat.at<float>(1, 2) = 50; //��ֱƽ����
//
//	//����ƽ�ƾ�����з���任
//	cv::warpAffine(src, dst, t_mat, dst_sz);
//
//	//��ʾƽ��Ч��
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
//	Mat orgIm = imread("D:\\��ƷͼƬ\\sample1\\ng\\12.JPG");
//	int extRows = 19;
//	int extCols = 15;
//	Mat extendedIm;
//	copyMakeBorder(orgIm, extendedIm, extRows, extRows, extCols, extCols, BORDER_CONSTANT);  ////BORDER_REFLECT_101
//	imshow("original image", orgIm);
//	imshow("extended image", extendedIm);
//	waitKey();
//	return 0;
//}