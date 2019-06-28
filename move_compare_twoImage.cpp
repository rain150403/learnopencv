//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <algorithm>
//
//using namespace cv;
//using namespace std;
//
//char max(char a, char b){
//	return a > b ? a : b;
//}
//
//char min(char a, char b){
//	return a < b ? a : b;
//}
//
//void ROIComEdge(cv::Mat &srcImg, cv::Mat &edgeImg, int offset, int grayTh);
//void ROIComLocationX(cv::Mat &srcImg, cv::Mat &detectImg, int &locCol, int grayTh, int rectWidthLR, int rectHeightLR);
//void ROIComLocationMarkerY(cv::Mat &srcImg, cv::Mat &detectImg, int &locRow, int grayTh, int rectWidthAB, int rectHeightAB);
//void ROIComABPlace(cv::Mat &abEdgeImg, vector<int> &xypAB);
//void ROIComLRPlace(cv::Mat &lrEdgeImg, vector<int> &xypLR);
//
//// Com--Detect  
//int main2()
//{
//	////获取待处理图像
//	// 读入源图像  
//	Mat ImgOK = imread("D:\\roiImage_2\\00001.JPG");
//	int row11 = ImgOK.rows;
//	int col11= ImgOK.cols;
//
//	Mat detectImg = imread("D:\\roiImage_2\\00003.JPG");
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//
//	int  safePix = 9;      // 安全像素个数    
//	int  numModel = 5;     // 扫描模板大小  
//	int dataSafe = int(float(numModel*numModel) / 2);
//	int  numDetectTh = 5;   // 允许不同像素个数  
//	int grayTh = int(255 / 3);  // 计算图像边缘阈值  
//
//	// 计算源图像及待检测图像的边缘图像
//	int offset = 1;  // 求边界偏移量
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//	ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
//	imwrite("D:\\roiImage_1\\1 edgeImgSrc.jpg", edgeImgSrc);   //////  
//
//	//偏移量
//	int locRow = 0;
//	int locCol = 0;  
//	
//	// 移动X轴（列）  
//	ROIComLocationX(ImgOK, detectImg, locCol, grayTh, row, col);
//
//	// 移动Y轴（行）  
//	ROIComLocationMarkerY(ImgOK, detectImg, locRow, grayTh, row, col);
//
//	//// 沿X轴（列）移动主框、左右框、上下框  
//	//stCamera[camIndex].stDistance[0].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[0].stLineDistance[1].nxCenter - locCol;
//	//stCamera[camIndex].stDistance[1].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[1].stLineDistance[1].nxCenter - locCol;
//	//stCamera[camIndex].stDistance[2].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[2].stLineDistance[1].nxCenter - locCol;
//
//	//// 沿Y轴（列）移动主框、左右框、上下框  
//	//stCamera[camIndex].stDistance[0].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[0].stLineDistance[1].nyCenter - locRow;
//	//stCamera[camIndex].stDistance[1].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[1].stLineDistance[1].nyCenter - locRow;
//	//stCamera[camIndex].stDistance[2].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[2].stLineDistance[1].nyCenter - locRow;
//
//
//	// 由新的主框截图检测图像
//	cv::Mat detectImgNew(row, col, CV_8UC1);
//	//imwrite("D:/roiImage/0 detectImgNew.jpg", detectImgNew);   //////  
//
//	// 计算图像边缘  
//	ROIComEdge(detectImgNew, edgeImgDetect, offset, grayTh);
//	imwrite("D:\\roiImage_2\\2 edgeImgDetect.jpg", edgeImgDetect);   //////  
//
//
//	// ---------- 方法一 两图的边缘图像相减 ----------
//	// --- 在边缘位置设置安全范围，留下不同的像素点  
//	// --- 用5*5模板去扫描， 
//	// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//	// --- 像素个数小于10，去除，计数加0     
//	// --- 计数值>0，则NG； 计数值=0, 则OK     
//
//	// 1 沿源图像边缘区域设置安全范围
//	// 把边缘图像变成二值化图像   
//	Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
//	for (int i = 1; i < rowe; i++){
//		for (int j = 1; j < cole; j++){
//			if (edgeImgSrc.at <uchar>(i, j) > 0){
//				edgeImgSrcTh.at <uchar>(i, j) = 255;
//			}
//			if (edgeImgDetect.at <uchar>(i, j) > 0){
//				edgeImgDetectTh.at <uchar>(i, j) = 255;
//			}
//		}
//	}
//	imwrite("D:\\roiImage_2\\3 edgeImgSrcTh.jpg", edgeImgSrcTh);   ////// 
//	imwrite("D:\\roiImage_2\\3 edgeImgDetectTh.jpg", edgeImgDetectTh);   ////// 
//
//	// 用膨胀法，扩展边缘亮区域
//	//获取自定义核
//	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//膨胀操作
//	Mat edgeImgSafe;
//	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//	// 反色，且归一化到[0, 1]; 
//	edgeImgSafe = (255 - edgeImgSafe) / 255;
//	imwrite("D:\\roiImage_2\\4 edgeImgSafe.jpg", edgeImgSafe * 255);   ////// 
//
//	// 2 两幅边缘图像相减
//	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	imwrite("D:\\roiImage_2\\5 edgeImgSub.jpg", edgeImgSub);   //////     
//
//	// 用5*5模板去扫描， 
//	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//	int resultNum = 0;
//	int dataTem = 0;
//	int dataZong = 0;
//	int dataNum = 0;
//	//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
//	for (int i = numModel; i < rowe - numModel; i++){
//		for (int j = numModel; j < cole - numModel; j++){
//			dataTem = 0;
//			dataZong = 0;
//			dataNum = 0;
//			for (int m = 0; m < numModel; m++){
//				for (int n = 0; n < numModel; n++){
//					dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//					if (dataTem > 0){
//						dataZong = dataZong + 1;
//					}
//				}
//			}
//			if (dataZong > dataSafe){
//				resultImg.at<uchar>(i, j) = 255;
//				resultNum++;
//			}
//		}
//	}
//	imwrite("D:\\roiImage_2\\6 resultImg.jpg", resultImg);   //////  
//
//	// 不同的区域，中心点标记为红色  
//	Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
//	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//	for (int i = offset; i<row - offset; i++){
//		for (int j = offset; j < col - offset; j++){
//			resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
//			if (resultImgTem.at<uchar>(i, j) == 255){
//				for (int m = 0; m < offset; m++){
//					for (int n = 0; n < offset; n++){
//						//cv::Point centerPoint, int rectWidth, int rectHeight,
//						ImgOK.at<Vec3b>(row/2.0 + i - int(float(row) / 2.0) + m,
//							col/2.0 + j - int(float(col) / 2.0) + n)[0] = 0;
//						ImgOK.at<Vec3b>(row/2.0 + i - int(float(row) / 2.0) + m,
//							col/2.0 + j - int(float(col) / 2.0) + n)[1] = 0;
//						ImgOK.at<Vec3b>(row/2.0 + i - int(float(row) / 2.0) + m,
//							col/2.0 + j - int(float(col) / 2.0) + n)[2] = 255;
//					}
//				}
//			}
//		}
//	}
//
//	// 计数值>0，则NG； 计数值=0, 则OK 
//	if (resultNum <= numDetectTh){
//		cout << "OK" << endl;
//	}
//	else{
//		cout << "NG" << endl;
//	}
//}
//
//void ROIComEdge(cv::Mat &srcImg, cv::Mat &edgeImg, int offset, int grayTh){
//	int row = srcImg.rows;
//	int col = srcImg.cols;
//	//int offset = 1;  // 求边界偏移量
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//	//int grayTh = int(255 / 4);  
//
//	// 处理第 1 幅图像
//	// 差分法求边缘		
//	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
//	for (int i = offset; i < row - offset; i++){
//		for (int j = offset; j < col - offset; j++){
//			edgeImg.at<uchar>(i - offset, j - offset) =
//				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
//				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
//		}
//	}
//	// 把边缘图像像素值映射到[0, 255]
//	int  minEdgeImg = 255;
//	int  maxEdgeImg = 0;
//	for (int i = 0; i < rowe; i++){
//		for (int j = 0; j < cole; j++){
//			minEdgeImg = min(minEdgeImg, edgeImg.at<uchar>(i, j));
//			maxEdgeImg = max(maxEdgeImg, edgeImg.at<uchar>(i, j));
//		}
//	}
//	for (int i = 0; i < rowe; i++){
//		for (int j = 0; j < cole; j++){
//			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
//				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
//		}
//	}
//
//	// 把边缘图像，去掉过小的边缘  	
//	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
//	for (int i = 0; i < rowe; i++){
//		for (int j = 0; j < cole; j++){
//			if (edgeImg.at<uchar>(i, j) < grayTh){
//				edgeImg.at<uchar>(i, j) = 0;
//			}
//		}
//	}
//}
//
//// X轴（列）偏移量计算  	// 移动X轴（列）  
//void ROIComLocationX(cv::Mat &srcImg, cv::Mat &detectImg, int &locCol, int grayTh, int rectWidthLR, int rectHeightLR){
//	
//	int  offset = 1;  // 求边界偏移量    
//
//	// ------ 获取原图的定位信息 ------      
//	// 剪切左右边缘区域
//	cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
//	int rowroiLR = roiImgLR.rows;
//	int colroiLR = roiImgLR.cols;
//	int roweLR = rowroiLR - 2 * offset;
//	int coleLR = colroiLR - 2 * offset;
//
//	// 获取左右边缘图
//	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\11 roiImgLR.jpg", roiImgLR);   //////  
//	imwrite("D:\\roiImage_2\\12 lrEdgeImg.jpg", lrEdgeImg);   //////  
//
//	// 找到左右边缘位置     
//	vector<int>     xypLRsrc(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//
//	// ------ 获取待检测图像定位信息 ------      
//	// 剪切左右边缘区域  
//	// 获取左右边缘图
//	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\13 roiImgLR.jpg", roiImgLR);   //////     
//	imwrite("D:\\roiImage_2\\14 lrEdgeImg.jpg", lrEdgeImg);   //////   
//
//	// 找到左右边缘位置     
//	vector<int>     xypLRdetect(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//
//	//------ 计算偏移 ------
//	//int locCol = 0; 
//	locCol = 0;
//	for (int i = 0; i < roweLR; i++){
//		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
//	}
//	locCol = int(0.5 + float(locCol) / float(roweLR));
//}
//
//// Y轴（行）偏移量计算  
//void ROIComLocationMarkerY(cv::Mat &srcImg, cv::Mat &detectImg, int &locRow, int grayTh, int rectWidthAB, int rectHeightAB){
//	
//	int  offset = 1;  // 求边界偏移量    
//
//	// ------ 获取原图的定位信息 ------      
//	// 剪切上下边缘区域
//	cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);
//	int rowroiAB = roiImgAB.rows;
//	int colroiAB = roiImgAB.cols;
//	int roweAB = rowroiAB - 2 * offset;
//	int coleAB = colroiAB - 2 * offset;
//	// 获取上下边缘图
//	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\21 roiImgAB.jpg", roiImgAB);   //////  
//	imwrite("D:\\roiImage_2\\22 abEdgeImg.jpg", abEdgeImg);   //////  
//
//	// 找到上下边缘位置     
//	vector<int>     xypABsrc(coleAB);
//	ROIComABPlace(abEdgeImg, xypABsrc);
//
//	// ------ 获取待检测图像定位信息 ------      
//	// 剪切上下边缘区域
//	// 获取上下边缘图
//	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\23 roiImgAB.jpg", roiImgAB);     //////  
//	imwrite("D:\\roiImage_2\\24 abEdgeImg.jpg", abEdgeImg);   //////  
//
//	// 找到上下边缘位置     
//	vector<int>     xypABdetect(coleAB);
//	ROIComABPlace(abEdgeImg, xypABdetect);
//
//	//------ 计算偏移 ------
//	//int locRow = 0; 
//	locRow = 0;
//	for (int i = 0; i < coleAB; i++){
//		locRow = locRow + xypABsrc[i] - xypABdetect[i];
//	}
//	locRow = int(0.5 + float(locRow) / float(coleAB));
//}
//
//
//// 找边缘图像上下位置  
//void ROIComABPlace(cv::Mat &abEdgeImg, vector<int> &xypAB){
//	int rowe = abEdgeImg.rows;
//	int cole = abEdgeImg.cols;
//	imwrite("D:\\roiImage_2\\25 abEdgeImg.jpg", abEdgeImg);   //////   
//
//	// 找到上下边缘位置
//	//vector<int>     xypAB(cole);
//	int maxval = 0;
//	int pixval = 0;
//	for (int j = 0; j < cole; j++){
//		maxval = 0;
//		xypAB[j] = 0;
//		for (int i = 0; i < rowe; i++){
//			pixval = abEdgeImg.at<uchar>(i, j);
//			if (pixval > maxval){
//				maxval = pixval;
//				xypAB[j] = i;
//			}
//		}
//	}
//}
//
//// 找边缘图像左右位置  
//void ROIComLRPlace(cv::Mat &lrEdgeImg, vector<int> &xypLR)
//{
//	int rowe = lrEdgeImg.rows;
//	int cole = lrEdgeImg.cols;
//	imwrite("D:\\roiImage_2\\15 lrEdgeImg.jpg", lrEdgeImg);   //////   
//
//	// 找到左右边缘位置
//	//vector<int>     xypLR(rowe);  
//	int pixval = 0;
//	int maxval = 0;
//	for (int i = 0; i < rowe; i++){
//		maxval = 0;
//		xypLR[i] = 0;
//		for (int j = 0; j < cole; j++){
//			pixval = lrEdgeImg.at<uchar>(i, j);
//			if (pixval > maxval){
//				maxval = pixval;
//				xypLR[i] = j;
//			}
//		}
//	}
//}
//
////////ROIComMoveImg 函数没用到
//
