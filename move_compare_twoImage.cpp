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
//	////��ȡ������ͼ��
//	// ����Դͼ��  
//	Mat ImgOK = imread("D:\\roiImage_2\\00001.JPG");
//	int row11 = ImgOK.rows;
//	int col11= ImgOK.cols;
//
//	Mat detectImg = imread("D:\\roiImage_2\\00003.JPG");
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//
//	int  safePix = 9;      // ��ȫ���ظ���    
//	int  numModel = 5;     // ɨ��ģ���С  
//	int dataSafe = int(float(numModel*numModel) / 2);
//	int  numDetectTh = 5;   // ����ͬ���ظ���  
//	int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
//
//	// ����Դͼ�񼰴����ͼ��ı�Եͼ��
//	int offset = 1;  // ��߽�ƫ����
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//	ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
//	imwrite("D:\\roiImage_1\\1 edgeImgSrc.jpg", edgeImgSrc);   //////  
//
//	//ƫ����
//	int locRow = 0;
//	int locCol = 0;  
//	
//	// �ƶ�X�ᣨ�У�  
//	ROIComLocationX(ImgOK, detectImg, locCol, grayTh, row, col);
//
//	// �ƶ�Y�ᣨ�У�  
//	ROIComLocationMarkerY(ImgOK, detectImg, locRow, grayTh, row, col);
//
//	//// ��X�ᣨ�У��ƶ��������ҿ����¿�  
//	//stCamera[camIndex].stDistance[0].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[0].stLineDistance[1].nxCenter - locCol;
//	//stCamera[camIndex].stDistance[1].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[1].stLineDistance[1].nxCenter - locCol;
//	//stCamera[camIndex].stDistance[2].stLineDistance[0].nxCenter =
//	//	stCamera[camIndex].stDistance[2].stLineDistance[1].nxCenter - locCol;
//
//	//// ��Y�ᣨ�У��ƶ��������ҿ����¿�  
//	//stCamera[camIndex].stDistance[0].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[0].stLineDistance[1].nyCenter - locRow;
//	//stCamera[camIndex].stDistance[1].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[1].stLineDistance[1].nyCenter - locRow;
//	//stCamera[camIndex].stDistance[2].stLineDistance[0].nyCenter =
//	//	stCamera[camIndex].stDistance[2].stLineDistance[1].nyCenter - locRow;
//
//
//	// ���µ������ͼ���ͼ��
//	cv::Mat detectImgNew(row, col, CV_8UC1);
//	//imwrite("D:/roiImage/0 detectImgNew.jpg", detectImgNew);   //////  
//
//	// ����ͼ���Ե  
//	ROIComEdge(detectImgNew, edgeImgDetect, offset, grayTh);
//	imwrite("D:\\roiImage_2\\2 edgeImgDetect.jpg", edgeImgDetect);   //////  
//
//
//	// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
//	// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
//	// --- ��5*5ģ��ȥɨ�裬 
//	// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
//	// --- ���ظ���С��10��ȥ����������0     
//	// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
//
//	// 1 ��Դͼ���Ե�������ð�ȫ��Χ
//	// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
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
//	// �����ͷ�����չ��Ե������
//	//��ȡ�Զ����
//	//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//���Ͳ���
//	Mat edgeImgSafe;
//	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//	// ��ɫ���ҹ�һ����[0, 1]; 
//	edgeImgSafe = (255 - edgeImgSafe) / 255;
//	imwrite("D:\\roiImage_2\\4 edgeImgSafe.jpg", edgeImgSafe * 255);   ////// 
//
//	// 2 ������Եͼ�����
//	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	imwrite("D:\\roiImage_2\\5 edgeImgSub.jpg", edgeImgSub);   //////     
//
//	// ��5*5ģ��ȥɨ�裬 
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
//	// ��ͬ���������ĵ���Ϊ��ɫ  
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
//	// ����ֵ>0����NG�� ����ֵ=0, ��OK 
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
//	//int offset = 1;  // ��߽�ƫ����
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//	//int grayTh = int(255 / 4);  
//
//	// ����� 1 ��ͼ��
//	// ��ַ����Ե		
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
//	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
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
//	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
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
//// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
//void ROIComLocationX(cv::Mat &srcImg, cv::Mat &detectImg, int &locCol, int grayTh, int rectWidthLR, int rectHeightLR){
//	
//	int  offset = 1;  // ��߽�ƫ����    
//
//	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//	// �������ұ�Ե����
//	cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
//	int rowroiLR = roiImgLR.rows;
//	int colroiLR = roiImgLR.cols;
//	int roweLR = rowroiLR - 2 * offset;
//	int coleLR = colroiLR - 2 * offset;
//
//	// ��ȡ���ұ�Եͼ
//	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\11 roiImgLR.jpg", roiImgLR);   //////  
//	imwrite("D:\\roiImage_2\\12 lrEdgeImg.jpg", lrEdgeImg);   //////  
//
//	// �ҵ����ұ�Եλ��     
//	vector<int>     xypLRsrc(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//
//	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//	// �������ұ�Ե����  
//	// ��ȡ���ұ�Եͼ
//	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\13 roiImgLR.jpg", roiImgLR);   //////     
//	imwrite("D:\\roiImage_2\\14 lrEdgeImg.jpg", lrEdgeImg);   //////   
//
//	// �ҵ����ұ�Եλ��     
//	vector<int>     xypLRdetect(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//
//	//------ ����ƫ�� ------
//	//int locCol = 0; 
//	locCol = 0;
//	for (int i = 0; i < roweLR; i++){
//		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
//	}
//	locCol = int(0.5 + float(locCol) / float(roweLR));
//}
//
//// Y�ᣨ�У�ƫ��������  
//void ROIComLocationMarkerY(cv::Mat &srcImg, cv::Mat &detectImg, int &locRow, int grayTh, int rectWidthAB, int rectHeightAB){
//	
//	int  offset = 1;  // ��߽�ƫ����    
//
//	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//	// �������±�Ե����
//	cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);
//	int rowroiAB = roiImgAB.rows;
//	int colroiAB = roiImgAB.cols;
//	int roweAB = rowroiAB - 2 * offset;
//	int coleAB = colroiAB - 2 * offset;
//	// ��ȡ���±�Եͼ
//	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\21 roiImgAB.jpg", roiImgAB);   //////  
//	imwrite("D:\\roiImage_2\\22 abEdgeImg.jpg", abEdgeImg);   //////  
//
//	// �ҵ����±�Եλ��     
//	vector<int>     xypABsrc(coleAB);
//	ROIComABPlace(abEdgeImg, xypABsrc);
//
//	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//	// �������±�Ե����
//	// ��ȡ���±�Եͼ
//	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
//	imwrite("D:\\roiImage_2\\23 roiImgAB.jpg", roiImgAB);     //////  
//	imwrite("D:\\roiImage_2\\24 abEdgeImg.jpg", abEdgeImg);   //////  
//
//	// �ҵ����±�Եλ��     
//	vector<int>     xypABdetect(coleAB);
//	ROIComABPlace(abEdgeImg, xypABdetect);
//
//	//------ ����ƫ�� ------
//	//int locRow = 0; 
//	locRow = 0;
//	for (int i = 0; i < coleAB; i++){
//		locRow = locRow + xypABsrc[i] - xypABdetect[i];
//	}
//	locRow = int(0.5 + float(locRow) / float(coleAB));
//}
//
//
//// �ұ�Եͼ������λ��  
//void ROIComABPlace(cv::Mat &abEdgeImg, vector<int> &xypAB){
//	int rowe = abEdgeImg.rows;
//	int cole = abEdgeImg.cols;
//	imwrite("D:\\roiImage_2\\25 abEdgeImg.jpg", abEdgeImg);   //////   
//
//	// �ҵ����±�Եλ��
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
//// �ұ�Եͼ������λ��  
//void ROIComLRPlace(cv::Mat &lrEdgeImg, vector<int> &xypLR)
//{
//	int rowe = lrEdgeImg.rows;
//	int cole = lrEdgeImg.cols;
//	imwrite("D:\\roiImage_2\\15 lrEdgeImg.jpg", lrEdgeImg);   //////   
//
//	// �ҵ����ұ�Եλ��
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
////////ROIComMoveImg ����û�õ�
//
