//#ifndef __FINAL_H__
//#define __FINAL_H__
//
//#include <opencv2/opencv.hpp>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <opencv2\contrib\contrib.hpp>
//#include <iostream>
//#include <windows.h>
//
//using namespace std;
//using namespace cv;
//
//#define ERROR 1234
//
//#define TEMPL_X 270   //ģ���x���꣬��������չ�߽�
//#define TEMPL_Y 140   //ģ���y���꣬��������չ�߽�
//
//#define EXTD_EDGE 20       //��չ�߽���, //����Ҳ����д������Ҫ���ñ�������ѡ����Ƭ֮��ľ���/2������Ϊ�����Ҳ����ƫ�������Χ������ʵ�ڲ��У��ͻ��ɣ��������룩
//#define TEMPL_WIDTH 100        //ģ����
//
///// Global Variables
//Mat img_src_ok;   //ԭʼokͼ��
//Mat img_src_ng;   //ԭʼngͼ��
//Mat rotated_ng;     //��תngͼ��
//Mat templ_ok;       //okͼ��ģ��
//Mat result;             //ģ��ƥ����
//Mat extd_ok;         //okͼ����չ���
//Mat extd_rotated_ng;       //ngͼ����ת֮������չ�Ľ��
//Mat move_rotated_ng;     //ngͼ����תƽ��֮��Ľ���������ջ�����okͼ���غϵ�ngͼƬ
//Mat extd_src;              //ƽ��֮ǰ�Ŀ���ͼ��
//Mat diff_dst;              //����ͼ��֮��
//Mat morph_out;         //������������ 
//Mat thr_img;
//
//Mat drawing;
//
//
//char* image_window = "Source Image";
//char* result_window = "Result window";
//
////Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//int match_method;   
//int max_Trackbar = 5;
//
//int ng_num = 0;    //ng��Ƭ����
//int num_contours = 0;    //һ����Ƭ����������
//
//int numDetectTh = 1000;
//bool m_resultDetectCom = 0;
//
//
//
//
///// Localizing the best match with minMaxLoc
//double minVal;
//double maxVal;
//Point minLoc;
//Point maxLoc;
//Point matchLoc;
//
//
//
//
//
//////-------------------------->ͼƬ�������������<----------------------------------------------
//bool  image_subtraction(Mat img_src_ng, int i);
//
//////------------------------->��Ե���<---------------------------------------
//void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole);
//
//////----------------------------->ģ��ƥ�䣬����ƽ��<----------------------------------------
//
////ģ��ƥ�䷽��
//void MatchingMethod(int, void*);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////------------------------------------>���ֱ�ߣ���תͼ��<-------------------------------------------
////ͨ������任����Ƕ�
//double CalcDegree(const Mat &srcImage, Mat &dst);
//
////����ת��
//double DegreeTrans(double theta);
//
////��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
////ֻҪ��ת�����Ժ���Ӱ��ͺܴ��������ַ�������Ҫ��ֱ�߼��Ҫ��ܸ�
////��ֱ�ߵķ������������Ҫ��һ�ģ���Ϊ����⵽�ܶ���ֱ�ߣ������ͻ�Ӱ����תЧ��
////������ƥ��ķ�����Ȼ�鷳�����ǿ���������ĽǶȱȽϹ̶�����һ
//void ImageRecify(Mat src, Mat& Img_resuly);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void translation(int matchLoc_x, int matchLoc_y);
//
//////------------------------------->ͼ����ǿ�����ӶԱȶ�<---------------------------------------------
////ͼ����ǿ����ͼ֮��Ľ����̫���ԣ���Ҫ���ӶԱȶ�
//void image_enhance(Mat image, Mat& enhance_img);
//
//////----------------------------->ͼ��ɫ<----------------------------------------------------
//Mat fanse(Mat thr_img);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void morph(Mat mor_input);
//void draw_contour(Mat canny_input);
//
//Mat convertTo3Channels(const Mat& binImg);
//
//
//int AreaLimit = 50;
//void ROIComDenoise(Mat &Src, Mat &Dst, int AreaLimit);
//
//#endif