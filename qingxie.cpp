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
////����ת��
//double DegreeTrans(double theta)
//{
//	double res = theta / CV_PI * 180;
//	return res;
//}
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
//	Mat M = getRotationMatrix2D(center, degree, 1);     ////degree ������ ���������ʱ��ת��С�����˳ʱ��ת
//	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//����任������ɫ���Ϊ��ɫ  
//}
//
////����任���ص��ǻ��ȣ� ��1���� = 360�㣬 Ҳ���Ǽ����������ת�Ƕ������⣿
//
////ͨ������任����Ƕ�
//double CalcDegree(const Mat &srcImage, Mat &dst)
//{
//	Mat midImage, dstImage;
//
//	Canny(srcImage, midImage, 50, 100, 3);
//	imshow("midImage", midImage);
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
//
//		cout << "�Ƕȣ�" << theta << endl;
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
//		//ֻѡ�Ƕ���С����Ϊ��ת�Ƕ�
//		sum += theta;
//
//		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar�������ڵ����߶���ɫ
//
//		imshow("ֱ��̽��Ч��ͼ", dstImage);
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
//	//float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
//	//float average = lines[0][1];    //��Ϊ�кܶ�ֱ�ߵ�ʱ����ӡˢ�֣��� ��Ӱ��ͼ�����ת������ʵ����ֻ��Ҫ����һ��������������ֱ�ߡ�
//	cout << "average theta:" << average << endl;
//
//	double angle = DegreeTrans(average) - 180;
//	//double angle = 0;
//
//	cout << "ʵ��angle:" << DegreeTrans(average) << endl;
//
//	//�ҵ�Ŀ�ľ��ǲ�������ת����ĽǶȣ�Ҳ����С��90.
//	/*if (DegreeTrans(average) > 90){
//		angle = DegreeTrans(average) - 90;
//	}
//	else{
//		angle = DegreeTrans(average);
//	}*/
//
//
//	//rotateImage(dstImage, dst, angle);
//	//imshow("ֱ��̽��Ч��ͼ2", dstImage);
//	return angle;
//}
//
//
//void ImageRecify(const char* pInFileName, const char* pOutFileName)
//{
//	double degree;
//	Mat src = imread(pInFileName);
//	imshow("ԭʼͼ", src);
//	imwrite("D:\\roiImgForTest\\lineSave\\src.jpg", src);
//	Mat dst;
//	//��б�ǶȽ���
//	degree = CalcDegree(src, dst);
//	if (degree == ERROR)
//	{
//		cout << "����ʧ�ܣ�" << endl;
//		return;
//	}
//	rotateImage(src, dst, degree);
//	cout << "����angle:" << degree << endl;
//	imshow("��ת������", dst);
//	imwrite("D:\\roiImgForTest\\lineSave\\afterRotated.jpg", dst);
//
//	//Mat resulyImage = dst(Rect(0, 0, dst.cols - 100, 500));   //����ߴ�ü���Ч���ȽϺ�
//	Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
//	imshow("�ü�֮��", resulyImage);
//	imwrite("D:\\roiImgForTest\\lineSave\\recified.jpg", resulyImage);
//}
//
//
////���о����������ǲ��ǿ�����ȡ������״��ROI������������ȡ��Ʒ��״��ROI���򣬾Ϳ�����ȫ����Ʒ�����ڲ����и��ֲ�����
//
////��֪��Ϊɶ��һ��ͼ�ử��ô����Ӿ��Σ�������
////����Ӧ���Լ�дһ���ܿ����Ƭ�ľ��ο�
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
//////��һ������������ͼƬ���ƣ��ڶ������������ͼƬ����
////void GetContoursPic(const char* pSrcFileName, const char* pDstFileName)
////{
////	Mat srcImg = imread(pSrcFileName);
////	imshow("ԭʼͼ", srcImg);
////	Mat gray, binImg;
////	//�ҶȻ�
////	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
////	imshow("�Ҷ�ͼ", gray);
////	//��ֵ��
////	threshold(gray, binImg, 180, 220, CV_THRESH_BINARY);
////	imshow("��ֵ��", binImg);
////
////	vector<vector<Point> > contours;
////	vector<Rect> boundRect(contours.size());
////	//ע���5������ΪCV_RETR_EXTERNAL��ֻ�������  
////	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
////	cout << contours.size() << endl;
////	for (int i = 0; i < contours.size(); i++)
////	{
////		//��Ҫ��ȡ������  
////		CvPoint2D32f rectpoint[4];
////		CvBox2D rect = minAreaRect(Mat(contours[i]));
////
////		cvBoxPoints(rect, rectpoint); //��ȡ4����������  
////		//��ˮƽ�ߵĽǶ�  
////		float angle = rect.angle;
////		cout << angle << endl;
////
////		int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
////		int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
////		//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
////		//���̫С��ֱ��pass
////		if (line1 * line2 < 600)
////		{
////			continue;
////		}
////
////		//Ϊ���������κ��ŷţ�������ת�Ƕ��ǲ�һ���ġ����ŵģ�������90�ȣ�������  
////		if (line1 > line2)
////		{
////			angle = 90 + angle;
////		}
////
////		//�½�һ������Ȥ������ͼ����С��ԭͼһ����  
////		Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //ע���������ѡCV_8UC3
////		RoiSrcImg.setTo(0); //��ɫ������Ϊ��ɫ  
////		//imshow("�½���ROI", RoiSrcImg);
////		//�Եõ����������һ��  
////		drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);
////
////		//��ͼ��RoiSrcImg
////		srcImg.copyTo(RoiSrcImg, binImg);
////
////
////		//����ʾһ�¿��������˸���Ȥ�������������ֶ��Ǻ�ɫ����  
////		namedWindow("RoiSrcImg", 1);
////		imshow("RoiSrcImg", RoiSrcImg);
////
////		//����һ����ת���ͼ��  
////		Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
////		RatationedImg.setTo(0);
////		//��RoiSrcImg������ת  
////		Point2f center = rect.center;  //���ĵ�  
////		Mat M2 = getRotationMatrix2D(center, angle, 1);//������ת�����ŵı任���� 
////		warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//����任 
////		imshow("��ת֮��", RatationedImg);
////		imwrite("r.jpg", RatationedImg); //���������ͼƬ��������
////	}
////
////#if 1
////	//��ROI������п�ͼ
////
////	//����ת���ͼƬ����������ȡ  
////	vector<vector<Point> > contours2;
////	Mat raw = imread("r.jpg");
////	Mat SecondFindImg;
////	//SecondFindImg.setTo(0);
////	cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //�ҶȻ�  
////	threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
////	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
////	//cout << "sec contour:" << contours2.size() << endl;
////
////	for (int j = 0; j < contours2.size(); j++)
////	{
////		//��ʱ����ʵ����һ���������ˣ����Ի�ȡrect  
////		Rect rect = boundingRect(Mat(contours2[j]));
////		//���̫С������ֱ��pass,ͨ�����ù��������С�����Ա�ֻ֤�õ����
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
////	GetContoursPic("D:\\��ƷͼƬ\\sample3\\ng\\00098.JPG", "FinalImage.jpg");
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
//////����ת��
////double DegreeTrans(double theta)
////{
////	double res = theta / CV_PI * 180;
////	return res;
////}
////
////
//////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
////void rotateImage(Mat src, Mat& img_rotate, double degree)
////{
////	//��ת����Ϊͼ������    
////	Point2f center;
////	center.x = float(src.cols / 2.0);
////	center.y = float(src.rows / 2.0);
////	int length = 0;
////	length = sqrt(src.cols*src.cols + src.rows*src.rows);
////	//�����ά��ת�ķ���任����  
////	Mat M = getRotationMatrix2D(center, degree, 1);
////	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(255, 255, 255));//����任������ɫ���Ϊ��ɫ  
////}
////
//////ͨ������任����Ƕ�
////double CalcDegree(const Mat &srcImage, Mat &dst)
////{
////	Mat midImage, dstImage;
////
////	Canny(srcImage, midImage, 50, 100, 3);
////	imshow("midImage", midImage);
////	cvtColor(midImage, dstImage, CV_GRAY2BGR);
////
////	//ͨ������任���ֱ��
////	vector<Vec2f> lines;
////	HoughLines(midImage, lines, 1, CV_PI / 180, 300, 0, 0);//��5������������ֵ����ֵԽ�󣬼�⾫��Խ��
////	//cout << lines.size() << endl;
////
////	//����ͼ��ͬ����ֵ�����趨����Ϊ��ֵ�趨���ߵ����޷����ֱ�ߣ���ֵ����ֱ��̫�࣬�ٶȺ���
////	//���Ը�����ֵ�ɴ�С������������ֵ�����������������󣬿��Թ̶�һ���ʺϵ���ֵ��
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
////		cout << "û�м�⵽ֱ�ߣ�" << endl;
////		return ERROR;
////	}
////
////	float sum = 0;
////	//���λ���ÿ���߶�
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
////		//ֻѡ�Ƕ���С����Ϊ��ת�Ƕ�
////		sum += theta;
////
////		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, 8); //Scalar�������ڵ����߶���ɫ
////
////		imshow("ֱ��̽��Ч��ͼ", dstImage);
////	}
////	//float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
////	float average = lines[0][1];    //��Ϊ�кܶ�ֱ�ߵ�ʱ����ӡˢ�֣��� ��Ӱ��ͼ�����ת������ʵ����ֻ��Ҫ����һ��������������ֱ�ߡ�
////	cout << "average theta:" << average << endl;
////
////	//double angle = DegreeTrans(average) - 90;
////	double angle = 0;
////
////	cout << "ʵ��angle:" << DegreeTrans(average) << endl;
////
////	//�ҵ�Ŀ�ľ��ǲ�������ת����ĽǶȣ�Ҳ����С��90.
////	if (DegreeTrans(average) > 90){
////		angle = DegreeTrans(average) - 90;
////	}
////	else{
////		angle = DegreeTrans(average);
////	}
////
////
////	rotateImage(dstImage, dst, angle);
////	//imshow("ֱ��̽��Ч��ͼ2", dstImage);
////	return angle;
////}
////
////
////void ImageRecify(const char* pInFileName, const char* pOutFileName)
////{
////	double degree;
////	Mat src = imread(pInFileName);
////	imshow("ԭʼͼ", src);
////	Mat dst;
////	//��б�ǶȽ���
////	degree = CalcDegree(src, dst);
////	if (degree == ERROR)
////	{
////		cout << "����ʧ�ܣ�" << endl;
////		return;
////	}
////	rotateImage(src, dst, degree);
////	cout << "����angle:" << degree << endl;
////	imshow("��ת������", dst);
////
////	//Mat resulyImage = dst(Rect(0, 0, dst.cols - 100, 500));   //����ߴ�ü���Ч���ȽϺ�
////	Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
////	imshow("�ü�֮��", resulyImage);
////	imwrite("recified.jpg", resulyImage);
////
////	//Mat drawImg;
////	//drawImg = resulyImage.clone();
////
////	////�ҶȻ�
////	//cvtColor(drawImg, drawImg, COLOR_RGB2GRAY);
////	//imshow("�Ҷ�ͼ", drawImg);
////	////��ֵ��
////	//threshold(drawImg, drawImg, 180, 200, CV_THRESH_BINARY);
////	//imshow("��ֵ��", drawImg);
////
////	//Canny(drawImg, drawImg, 10, 100, 3);    ///sample1   (10, 100)
////	//imshow("canny", drawImg);
////
////	//vector<vector<Point> > contours;
////
////	////ע���5������ΪCV_RETR_EXTERNAL��ֻ�������  
////	//findContours(drawImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //������
////	//cout << contours.size() << endl;
////	//for (int i = 0; i < contours.size(); i++){
////	//	drawContours(drawImg, contours, -1, Scalar(255), 3);
////	//}
////	//imshow("����", drawImg);
////
////	//cvtColor(drawImg, drawImg, COLOR_GRAY2BGR);
////
////	////�������뻭��С��Ӿ��Σ� ������תͼ�Ķ�Ӧλ��Ҳ���ϡ�
////	//Rect boundRect;  //������Ӿ���
////	//RotatedRect box; //������С��Ӿ���
////
////	//vector<vector<Point>>::iterator itc = contours.begin();
////	//Point2f rect_point[4];
////	//int i = 0;
////	//for (; itc != contours.end(); itc++)
////	//{
////	//	cout << i << "����������� " << contourArea(contours[i]) << endl;
////	//	box = minAreaRect(Mat(*itc));  //����ÿ��������С��Ӿ���(��ת)
////	//	boundRect = box.boundingRect();
////	//	//boundRect = boundingRect(Mat(*itc));
////	//	circle(drawImg, Point(box.center.x, box.center.y), 5, Scalar(255, 0, 0), -1, 8);  //������С��Ӿ��ε����ĵ�
////	//	// rectangle(dstImg, Point(boundRect.x, boundRect.y), Point(boundRect.x + boundRect.width, boundRect.y + boundRect.height), Scalar(0, 255, 0), 2, 8);
////	//	rectangle(drawImg, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 3, 8);
////	//	box.points(rect_point);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����
////	//	for (int j = 0; j < 4; j++)
////	//	{
////	//		line(drawImg, rect_point[j], rect_point[(j + 1) % 4], Scalar(0, 0, 255), 3, 8);  //������С��Ӿ���ÿ����
////	//	}
////	//}
////	//namedWindow("rec_dst", 0);
////	//imshow("rec_dst", drawImg);
////}
////
////
//////���о����������ǲ��ǿ�����ȡ������״��ROI������������ȡ��Ʒ��״��ROI���򣬾Ϳ�����ȫ����Ʒ�����ڲ����и��ֲ�����
////
//////��֪��Ϊɶ��һ��ͼ�ử��ô����Ӿ��Σ�������
//////����Ӧ���Լ�дһ���ܿ����Ƭ�ľ��ο�
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
////////�����ã����ǲ�֪����û�пɽ��֮��
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
////	Mat imageSource = imread("000.JPG", 0);   //D:\\��ƷͼƬ\\sample1\\ng\\14.JPG
////	imshow("Source Image", imageSource);
////	vector<Point> contour;
////	Point p1(800, 400), p2(1100, 605), p3(902, 970), p4(802, 780);//�������4����
////	contour.push_back(p1);
////	contour.push_back(p2);
////	contour.push_back(p3);
////	contour.push_back(p4);
////	RotatedRect rect = minAreaRect(contour);//��Ӿ���
////	Point2f vertices[4];
////	rect.points(vertices);//��Ӿ��ε�4������
////	for (int i = 0; i < 4; i++)//������
////		line(imageSource, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0));
////
////	/*Rect brect = rect.boundingRect();
////	rectangle(imageSource, brect, Scalar(255, 0, 0));*/
////	imshow("Source Image1", imageSource);
////	Point2f center = rect.center;//��Ӿ������ĵ�����
////	Mat rot_mat = getRotationMatrix2D(center, rect.angle, 1.0);//����ת����
////	Mat rot_image;
////	Size dst_sz(imageSource.size());
////	warpAffine(imageSource, rot_image, rot_mat, dst_sz);//ԭͼ����ת
////	imshow("rot_image", rot_image);
////	Mat result1 = rot_image(Rect(0, 0, 100, 100));//��ȡROI , center.x - (rect.size.width / 2), center.y - (rect.size.height / 2),
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
////	//������С��Ӿ��εĻ���
////	Mat srcImg = imread("D:\\��ƷͼƬ\\sample1\\ng\\14.JPG");
////	//srcImg = srcImg(Rect(10,10,1000,690));
////	namedWindow("scr", 0);
////	imshow("scr", srcImg);
////	Mat dstImg = srcImg.clone();
////	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
////	threshold(srcImg, srcImg, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY_INV); //��ֵ��
////	//medianBlur(srcImg, srcImg, 9);
////	imshow("threshold", srcImg);
////
////	vector<vector<Point>> contours;
////	findContours(srcImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
////	Rect boundRect;  //������Ӿ���
////	RotatedRect box; //������С��Ӿ���
////
////	vector<vector<Point>>::iterator itc = contours.begin();
////	Point2f rect_point[4];
////	int i = 0;
////	for (; itc != contours.end(); itc++)
////	{
////
////		box = minAreaRect(Mat(*itc));  //����ÿ��������С��Ӿ���(��ת)
////		boundRect = box.boundingRect();
////		//boundRect = boundingRect(Mat(*itc));
////		circle(dstImg, Point(box.center.x, box.center.y), 5, Scalar(255, 0, 0), -1, 8);  //������С��Ӿ��ε����ĵ�
////		// rectangle(dstImg, Point(boundRect.x, boundRect.y), Point(boundRect.x + boundRect.width, boundRect.y + boundRect.height), Scalar(0, 255, 0), 2, 8);
////		rectangle(dstImg, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 3, 8);
////		box.points(rect_point);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����
////		for (int j = 0; j<4; j++)
////		{
////			line(dstImg, rect_point[j], rect_point[(j + 1) % 4], Scalar(0, 0, 255), 3, 8);  //������С��Ӿ���ÿ����
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
////	//��תУ��
////	float angle_rotation;
////	if ((box.size.width / box.size.height) < 1)
////		angle_rotation = 90 + box.angle;//��������ʱ����ת
////	else
////		angle_rotation = box.angle; //������˳ʱ����ת
////
////	double scale = 0.78;//���ű���
////	Mat rot_m = getRotationMatrix2D(box.center, angle_rotation, scale);//�����ת����
////	warpAffine(dstImg, dstImg, rot_m, dstImg.size());//����任
////
////	namedWindow("dst", 0);
////	imshow("dst", dstImg);
////
////	waitKey(0);
////}