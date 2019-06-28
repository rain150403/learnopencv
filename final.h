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
//#define TEMPL_X 270   //模板的x坐标，不包含扩展边界
//#define TEMPL_Y 140   //模板的y坐标，不包含扩展边界
//
//#define EXTD_EDGE 20       //扩展边界宽度, //这里也不能写死，需要设置变量，就选择（两片之间的距离/2），因为他最多也不会偏出这个范围，或者实在不行，就换成（整个距离）
//#define TEMPL_WIDTH 100        //模板宽度
//
///// Global Variables
//Mat img_src_ok;   //原始ok图像
//Mat img_src_ng;   //原始ng图像
//Mat rotated_ng;     //旋转ng图像
//Mat templ_ok;       //ok图像模板
//Mat result;             //模板匹配结果
//Mat extd_ok;         //ok图像扩展结果
//Mat extd_rotated_ng;       //ng图像旋转之后，再扩展的结果
//Mat move_rotated_ng;     //ng图像旋转平移之后的结果，即最终基本与ok图像重合的ng图片
//Mat extd_src;              //平移之前的拷贝图像
//Mat diff_dst;              //两个图像之差
//Mat morph_out;         //开运算输出结果 
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
//int ng_num = 0;    //ng样片数量
//int num_contours = 0;    //一个样片轮廓的数量
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
//////-------------------------->图片相减方法主函数<----------------------------------------------
//bool  image_subtraction(Mat img_src_ng, int i);
//
//////------------------------->边缘检测<---------------------------------------
//void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole);
//
//////----------------------------->模板匹配，方便平移<----------------------------------------
//
////模板匹配方法
//void MatchingMethod(int, void*);
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////------------------------------------>检测直线，旋转图像<-------------------------------------------
////通过霍夫变换计算角度
//double CalcDegree(const Mat &srcImage, Mat &dst);
//
////度数转换
//double DegreeTrans(double theta);
//
////逆时针旋转图像degree角度（原尺寸）    
//void rotateImage(Mat src, Mat& img_rotate, double degree);
//
////只要旋转出错，对后面影响就很大，所以这种方法就需要对直线检测要求很高
////画直线的方法可能真的需要改一改，因为它会测到很多条直线，这样就会影响旋转效果
////而特征匹配的方法虽然麻烦，但是可能算出来的角度比较固定，单一
//void ImageRecify(Mat src, Mat& Img_resuly);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//void translation(int matchLoc_x, int matchLoc_y);
//
//////------------------------------->图像增强，增加对比度<---------------------------------------------
////图像增强，两图之差的结果不太明显，需要增加对比度
//void image_enhance(Mat image, Mat& enhance_img);
//
//////----------------------------->图像反色<----------------------------------------------------
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