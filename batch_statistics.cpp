//#include <opencv2\opencv.hpp>
//
//#include <opencv2\highgui\highgui.hpp>
//
//#include <opencv2\imgproc\imgproc.hpp>
//
//#include <iostream>
//
//#include <windows.h>
//
//
//using namespace cv;
//using namespace std;
//
//int ng_num = 0;
//int detectThr = 2000;
////int num = 0;
//
//Mat morph_out;
//Mat resultImg;
//
//void image_enhance(Mat image, Mat& enhance_img);
//Mat fanse(Mat thr_img);
//void morph(Mat mor_input);
//void draw_contour(Mat canny_input);
//
//
//Mat imgTranslate(Mat &matSrc, int xOffset, int yOffset, bool bScale) { 
//	// �ж��Ƿ�ı�ͼ���С,���趨������ROI 
//	int nRows = matSrc.rows; 
//	int nCols = matSrc.cols; 
//	int nRowsRet = 0; 
//	int nColsRet = 0; 
//	Rect rectSrc; 
//	Rect rectRet; 
//	if (bScale) { 
//		nRowsRet = nRows + abs(yOffset); 
//		nColsRet = nCols + abs(xOffset); 
//		rectSrc.x = 0; 
//		rectSrc.y = 0; 
//		rectSrc.width = nCols; 
//		rectSrc.height = nRows; 
//	} 
//	else { 
//		nRowsRet = matSrc.rows; 
//		nColsRet = matSrc.cols; 
//		if (xOffset >= 0) { 
//			rectSrc.x = 0; 
//		} 
//		else { 
//			rectSrc.x = abs(xOffset); 
//		} 
//		
//		if (yOffset >= 0) { 
//			rectSrc.y = 0; 
//		} 
//		else { 
//			rectSrc.y = abs(yOffset); 
//		} 
//		
//		rectSrc.width = nCols - abs(xOffset); 
//		rectSrc.height = nRows - abs(yOffset); 
//	} 
//	
//	// ���������ROI 
//	if (xOffset >= 0) { 
//		rectRet.x = xOffset; 
//	} else { 
//		rectRet.x = 0; 
//	} 
//	
//	if (yOffset >= 0) { 
//		rectRet.y = yOffset; 
//	} 
//	else { 
//		rectRet.y = 0; 
//	} 
//	rectRet.width = rectSrc.width; 
//	rectRet.height = rectSrc.height; 
//	
//	// ����ͼ�� 
//	Mat matRet(nRowsRet, nColsRet, matSrc.type(), Scalar(0)); 
//	matSrc(rectSrc).copyTo(matRet(rectRet)); 
//	return matRet; 
//}
//
//
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
//// �ұ�Եͼ������λ��  
//void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
//{
//	int rowe = abEdgeImg.rows;
//	int cole = abEdgeImg.cols;
//
//	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//
//	// �ҵ����±�Եλ��
//	//vector<int>     xypAB(cole);
//	int maxval = 0;
//	int pixval = 0;
//	for (int j = 0; j < cole; j++)
//	{
//		maxval = 0;
//		xypAB[j] = 0;
//		for (int i = 0; i < rowe; i++)
//		{
//			pixval = abEdgeImg.at<uchar>(i, j);
//			if (pixval > maxval)
//			{
//				maxval = pixval;
//				xypAB[j] = i;
//			}
//		}
//		resultImg.at<Vec3b>(xypAB[j], j)[0] = 0;
//		resultImg.at<Vec3b>(xypAB[j], j)[1] = 0;
//		resultImg.at<Vec3b>(xypAB[j], j)[2] = 255;
//		//cout << xypAB[j] << ", ";
//	}
//	//cout << endl;
//	//imshow("���±�Եͼ", resultImg);
//}
//
//
//// Y�ᣨ�У�ƫ��������  
//int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
//{
//	int locRow = 0;
//	int  offset = 1;  // ��߽�ƫ����       ///offset�����ڼ���߽��ƫ���������ȸ����ҵı߽���ƫ���٣��� �����Ǽ��������locRow��ƫ�ƣ� �����߽�ͼ��ƫ�ƶ���
//	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//	// �������±�Ե����
//
//	int rowroiAB = srcImg.rows;
//	int colroiAB = srcImg.cols;
//	int roweAB = rowroiAB - 2 * offset;
//	int coleAB = colroiAB - 2 * offset;
//	// ��ȡ���±�Եͼ
//	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//	//imshow("��һ����Եͼ", abEdgeImg);
//
//	// �ҵ����±�Եλ��     
//	vector<int>     xypABsrc(coleAB);
//	ROIComABPlace(abEdgeImg, xypABsrc);
//
//	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//	// �������±�Ե����
//	// ��ȡ���±�Եͼ
//	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//	//imshow("�ڶ�����Եͼ", abEdgeImg);
//
//	// �ҵ����±�Եλ��     
//	vector<int>     xypABdetect(coleAB);
//	ROIComABPlace(abEdgeImg, xypABdetect);
//
//	//------ ����ƫ�� ------
//	//int locRow = 0; 
//	locRow = 0;
//	for (int i = 0; i < coleAB; i++)
//	{
//		locRow = locRow + xypABsrc[i] - xypABdetect[i];
//	}
//	locRow = int(0.5 + float(locRow) / float(coleAB));
//	return locRow;
//}
//
//
////�������������ұ�Ե�ķ������Ҿ��û�������Ϊ�ҵ������ֵ��һ����ͬһ����Ե�ϵģ�
////��ô��ͬ��ͼƬ�ҵ������ֵ�����±�Ե�����Ҳ������ͬ�����п������ϱ�Ե�ĵ��ȥ�±�Ե�ĵ������ƫ������
////�������кܴ�ƫ� ��ʹ�����ƽ����Ӱ�컹�ǻ��е�
////��֪���Բ��ԣ�����
//
////����˵�ҵ�ƽ�Ʒ��������⣿����
//
//// �ұ�Եͼ������λ��  
//void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
//{
//	int rowe = lrEdgeImg.rows;
//	int cole = lrEdgeImg.cols;
//
//	// �ҵ����ұ�Եλ��
//	//vector<int>     xypLR(rowe);  
//	int pixval = 0;
//	int maxval = 0;
//
//	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//
//	for (int i = 0; i < rowe; i++)
//	{
//		maxval = 0;
//		xypLR[i] = 0;
//		for (int j = 0; j < cole; j++)
//		{
//			pixval = lrEdgeImg.at<uchar>(i, j);
//			if (pixval > maxval)
//			{
//				maxval = pixval;
//				xypLR[i] = j;
//				//�����ǣ���һ���������кܶ�߽磬������һ�����ֵ��ֻ���ҵ�����һ���߽磬��һ����ͬһ���߽�����ô�죿
//				
//			}
//		}
//		
//		resultImg.at<Vec3b>(i, xypLR[i])[0] = 0;
//		resultImg.at<Vec3b>(i, xypLR[i])[1] = 0;
//		resultImg.at<Vec3b>(i, xypLR[i])[2] = 255;
//		//cout << xypLR[i] << ", ";
//	}
//	//cout << endl;
//	//imshow("���ұ�Եͼ", resultImg);   //��ͼ�������������ҵľ��ǵ�һ����
//}
//
//// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
//int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
//	int locCol = 0;
//	int  offset = 1;  // ��߽�ƫ����    
//	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//	// �������ұ�Ե����
//	int rowroiLR = srcImg.rows;
//	int colroiLR = srcImg.cols;
//	int roweLR = rowroiLR - 2 * offset;
//	int coleLR = colroiLR - 2 * offset;
//	// ��ȡ���ұ�Եͼ
//	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//	//imshow("���ҵ�һ��Եͼ", lrEdgeImg);
//
//	// �ҵ����ұ�Եλ��     
//	vector<int>     xypLRsrc(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//
//
//	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//	// �������ұ�Ե����  
//	// ��ȡ���ұ�Եͼ
//	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//	//imshow("���ҵڶ�����Եͼ", lrEdgeImg);
//
//	// �ҵ����ұ�Եλ��     
//	vector<int>     xypLRdetect(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//
//	//------ ����ƫ�� ------
//	//int locCol = 0; 
//	locCol = 0;
//	for (int i = 0; i < roweLR; i++)
//	{
//		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
//	}
//	locCol = int(0.5 + float(locCol) / float(roweLR));
//
//	return locCol;
//}
//
//// ��λ����
//Mat ROIComLocation(Mat srcImg, Mat detectImg)
//{
//	Mat detectImg_move;
//	//// ���ǰ��ʼ��λ      
//	int offsetx = 0;
//	int offsety = 0;
//	int grayTh = 50;
//	
//	// �ƶ�X�ᣨ�У�  ����   
//	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
//	cout << offsetx << endl;
//
//		// �ƶ�Y�ᣨ�У�  �ϡ���   
//	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
//	cout << offsety << endl;
//	////�²��ǲ���Y��ƫ����̫��ͻ����
//	//if (offsety > 5){
//	//	offsety = 5;
//	//}
//
//	detectImg_move = imgTranslate(detectImg, offsetx, offsety, 1);
//
//	if (offsetx >= 0 && offsety >= 0){
//		detectImg_move = detectImg_move(Rect(offsetx, offsety, srcImg.cols, srcImg.rows));
//	}
//	else if (offsetx >= 0 && offsety < 0){
//		detectImg_move = detectImg_move(Rect(offsetx, 0, srcImg.cols, srcImg.rows));
//	}
//	else if (offsetx < 0 && offsety < 0){
//		detectImg_move = detectImg_move(Rect(0, 0, srcImg.cols, srcImg.rows));
//	}
//	else{
//		detectImg_move = detectImg_move(Rect(0, offsety, srcImg.cols, srcImg.rows));
//	}
//
//	imshow("ƽ�ƴ����ͼƬ", detectImg_move);
//	//imwrite("D:\\roiImgForTest\\move.jpg", detectImg_move);
//	//waitKey(0);
//	return detectImg_move;
//}
//
////�����ػ��������ַ������������ƫ�������ԡ�
////��Ҫ����������ǣ�ƽ��֮��ͼ��϶���Ҫ��չ���ⲿ����ô���������Զ���չ��
//
//// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
//bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
//{
//	bool  m_resultDetectCom = 0;
//	//// �ȽϷ�ʶ��ȱ�ݴ���  
//
//	// ����Դͼ�񼰴����ͼ��ı�Եͼ��
//	int  safePix = 9;      // ��ȫ���ظ���   9 
//	int  numModel = 5;     // ɨ��ģ���С  
//	int dataSafe = int(float(numModel*numModel) / 2);
//	//int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
//	int grayTh_1 = 50;
//	int grayTh_2 = 30;
//	int  numDetectTh = detectThr;   // ����ͬ���ظ���  
//
//	//// ��ͼ�����ͼ��  
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//
//	//ƽ��֮��ͼ���С��ͬ���������ﴦ����Ǳ任���ͼ����Ҫ�޸ģ�����
//
//
//	///////////////////////////////////////////////
//	int offset = 1;  // ��߽�ƫ����
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//
//	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//
//	ROIComEdge(srcImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//	//imshow("ok��Եͼ", edgeImgSrc);
//
//	////////////////////////////////////////////////
//	// ����ͼ���Ե  
//	ROIComEdge(detectImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
//	//imshow("ng��Եͼ", edgeImgDetect);
//	////////////////////////////////////////////////
//	// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
//	// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
//	// --- ��5*5ģ��ȥɨ�裬 
//	// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
//	// --- ���ظ���С��10��ȥ����������0     
//	// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
//	////////////////////////////////////////////////
//	// 1 ��Դͼ���Ե�������ð�ȫ��Χ
//	// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
//	Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
//	for (int i = 1; i < rowe; i++)
//	{
//		for (int j = 1; j < cole; j++)
//		{
//			if (edgeImgSrc.at <uchar>(i, j) > 0)
//			{
//				edgeImgSrcTh.at <uchar>(i, j) = 255;
//			}
//			if (edgeImgDetect.at <uchar>(i, j) > 0)
//			{
//				edgeImgDetectTh.at <uchar>(i, j) = 255;
//			}
//		}
//	}
//
//	imshow("srcEdge", edgeImgSrcTh);
//	imshow("detectTh", edgeImgDetectTh);
//	//waitKey(0);
//
//	////////////////////////////////////////////////
//	// �����ͷ�����չ��Ե������
//	//��ȡ�Զ����
//	//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//���Ͳ���
//	Mat edgeImgSafe;
//	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//	imshow("pengzhang", edgeImgSafe);
//	//waitKey(0);
//
//	imshow("fanseqian", edgeImgSafe);
//
//	// ��ɫ���ҹ�һ����[0, 1]; 
//	edgeImgSafe = (255 - edgeImgSafe) / 255;   //��ɫ������ʲôЧ������û�����
//	imshow("safe", edgeImgSafe);
//	//waitKey(0);
//
//	////////////////////////////////////////////////
//	// 2 ������Եͼ�����
//	//Mat edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	//imshow("������", edgeImgSub);
//	//waitKey(0);
//
//
//	///////////////////////////////////////////////
//	Mat diff_dst;
//	absdiff(srcImg, detectImg, diff_dst);
//	imshow("xiangjian", diff_dst);
//
//
//	//Mat enhc_img;
//	//image_enhance(diff_dst, enhc_img);
//	
//	////----------------->��ֵ��<-------------------------------------------------------------
//	Mat thr_img;
//	threshold(diff_dst, thr_img, 10, 250, CV_THRESH_BINARY);  ///180, 255
//	//imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//		
//	//cvtColor(thr_img, thr_img, CV_BGR2GRAY);  
//	
//	//ͼ��ɫ
//	//thr_img = fanse(thr_img);
//	
//	////----------------->������<-----------------------
//	//morph(thr_img);
//	
//	////----------------->�ü���ԭ�ߴ�<---------------------------
//	/*Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	Mat ROI = morph_out(m_select);*/
//	//imshow("����ͼ", ROI);
//	
//	////----------------->��������Ȧ��ȱ�ݣ�����ת���ɲ�ɫͼ����ܻ���ɫ����
//	//draw_contour(ROI);
//
//
//	////////////////////////////////////////////////
//	// ��5*5ģ��ȥɨ�裬 
//	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//	resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//	int resultNum = 0;
//	int dataTem = 0;
//	int dataZong = 0;
//	int dataNum = 0;
//
//	for (int i = numModel; i < rowe - numModel; i++)
//	{
//		for (int j = numModel; j < cole - numModel; j++)
//		{
//			dataTem = 0;
//			dataZong = 0;
//			dataNum = 0;
//			for (int m = 0; m < numModel; m++)
//			{
//				for (int n = 0; n < numModel; n++)
//				{
//					dataTem = thr_img.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//					//cout << dataTem << ",";
//					if (dataTem > 0)
//					{
//						dataZong = dataZong + 1;
//					}
//				}
//			}
//			if (dataZong > dataSafe)
//			{
//				//cout << dataZong << ",";
//				//ֻҪ�в�ͬ�����������ģ����Ҳ�ֻ�����ǲ�ͬ�ĵط�������Ҫ�Ǳ߽磬�߽�û�غϣ��к�㣬�Ǿͱ�ʾ��Ƭ��
//				//resultImg.at<uchar>(i, j) = 255;
//				resultImg.at<Vec3b>(i, j)[0] = 0;
//				resultImg.at<Vec3b>(i, j)[1] = 0;
//				resultImg.at<Vec3b>(i, j)[2] = 255;
//
//				//showImg.at<Vec3b>(m, n)[2] = 255;
//				resultNum++;
//			}
//		}
//	}
//
//	//cout << endl;
//
//	//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
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
//	//				dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//	//				if (dataTem > 0)
//	//				{
//	//					dataZong = dataZong + 1;
//	//				}
//	//			}
//	//		}
//	//		if (dataZong > dataSafe)
//	//		{
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
//	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
//	imshow("�˲����", resultImg);   ///�˲������ʵ��������ԭͼ�� Ȼ����detectͼ�غϵĲ��ֲ���ʾ
//	imwrite("D:\\roiImgForTest\\ngSave\\result.jpg", resultImg);
//	//waitKey(0);
//	////////////////////////////////////////////////
//
//	//��ͨ������ͨ��һ��Ҫ�ֿ�����Ȼ�����׳���
//	// ��ͬ���������ĵ���Ϊ��ɫ  
//	Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
//	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//	for (int i = offset; i<row - offset; i++)
//	{
//		for (int j = offset; j < col - offset; j++)
//		{
//			resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
//			if (resultImgTem.at<uchar>(i, j) == 255)
//			{
//				for (int m = 0; m < offset; m++)
//				{
//					for (int n = 0; n < offset; n++)
//					{
//						//cv::Point centerPoint, int rectWidth, int rectHeight,
//						showImg.at<Vec3b>(m, n)[0] = 0;
//						showImg.at<Vec3b>(m, n)[1] = 0;
//						showImg.at<Vec3b>(m, n)[2] = 255;
//					}
//				}
//			}
//		}
//	}
//
//	//imshow("���չʾ", showImg);
//	////////////////////////////////////////////////
//	// ����ֵ>0����NG�� ����ֵ=0, ��OK 
//	if (resultNum <= numDetectTh)
//	{
//		m_resultDetectCom = 1;  // OK  
//	}
//	else
//	{
//		m_resultDetectCom = 0;  // NG    
//	}
//	return  m_resultDetectCom;
//}
//
//int edge_subtraction(Mat detectImg, int i){
//
//	Mat srcImg = imread("D:\\oldSample\\sample1\\ok\\1.jpg", 0);
//	//imshow("ԭͼ", srcImg);
//	//imshow("�����ͼ", detectImg);
//
//	Mat showImg = imread("D:\\oldSample\\sample1\\ok\\1.jpg");
//
//	//�õ�ͼ���ȵ�ƽ����ȡƫ������ ��ƽ��
//	Mat detectMove = ROIComLocation(srcImg, detectImg);
//	
//	String strImg;
//
//	bool flag = 0;
//	flag = ROIComDetectMethod(srcImg, detectMove, showImg);
//	if (flag == 0){
//		cout << "ngͼƬ" << endl;
//		strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//		imwrite(strImg, resultImg);
//		ng_num++;
//	}
//	else{
//		strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//		cout << "����okͼƬ" << endl;
//		imwrite(strImg, resultImg);
//	}
//
//	return ng_num;
//}
//
////Ŀǰ��¼�ļ��һ��ͼƬ��ʱ��
//
//int main(){
//	//D:\\newSample\\BlackT\\OK
//	string dir_path = "D:\\oldSample\\sample1\\ok\\";   ////BlackBoat
//	Directory dir;
//	vector<string> fileNames = dir.GetListFiles(dir_path, "*.jpg", false);
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
//		Mat detectImg = imread(fileFullName.c_str(), 0);
//		edge_subtraction(detectImg, i);
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
//	destroyAllWindows();
//	system("pause");
//	return 0;
//}
//
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
//	//num_contours = g_vContours.size();
//}
//
//////////////////////////////////////////////////////����Ϊ����ר��////////////////////////////
//
//
//
//
//
////// �ұ�Եͼ������λ��  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////	imwrite("D:/roiImage/25 abEdgeImg.jpg", abEdgeImg);   //////   
////
////	// �ҵ����±�Եλ��
////	//vector<int>     xypAB(cole);
////	int maxval = 0;
////	int pixval = 0;
////	for (int j = 0; j < cole; j++)
////	{
////		maxval = 0;
////		xypAB[j] = 0;
////		for (int i = 0; i < rowe; i++)
////		{
////			pixval = abEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypAB[j] = i;
////			}
////		}
////	}
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////	imwrite("D:/roiImage/15 lrEdgeImg.jpg", lrEdgeImg);   //////   
////
////	// �ҵ����ұ�Եλ��
////	//vector<int>     xypLR(rowe);  
////	int pixval = 0;
////	int maxval = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		maxval = 0;
////		xypLR[i] = 0;
////		for (int j = 0; j < cole; j++)
////		{
////			pixval = lrEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypLR[i] = j;
////			}
////		}
////	}
////}
////
////// Y�ᣨ�У�ƫ��������  
////void ROIComLocationY(Mat &srcImg, Mat &detectImg, int &locRow)
//////, int grayTh, cv::Point centerPointAB, int rectWidthAB, int rectHeightAB, int rectRotAngleAB)
////{
////	int  offset = 1;  // ��߽�ƫ����    
////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	// �������±�Ե����
////	cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);   
////	ROIRotateImage(srcImg, centerPointAB, rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);  
////	int rowroiAB = roiImgAB.rows;
////	int colroiAB = roiImgAB.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// ��ȡ���±�Եͼ
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);   
////	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);        
////	imwrite("D:/roiImage/21 roiImgAB.jpg", roiImgAB);   //////  
////	imwrite("D:/roiImage/22 abEdgeImg.jpg", abEdgeImg);   //////  
////	String  strImg;
////	strImg = format("D:/roiImage/21 roiImgABSrc/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgAB);
////	
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABsrc(coleAB);      
////	ROIComABPlace(abEdgeImg, xypABsrc);    
////	
////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	// �������±�Ե����
////	ROIRotateImage(detectImg, cv::Point(centerPointAB.x - locCol, centerPointAB.y), rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);
////	// ��ȡ���±�Եͼ
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
////	imwrite("D:/roiImage/23 roiImgAB.jpg", roiImgAB);     //////  
////	imwrite("D:/roiImage/24 abEdgeImg.jpg", abEdgeImg);   //////  
////	strImg = format("D:/roiImage/23 roiImgABDetect/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgAB);
////	
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABdetect(coleAB);     
////	ROIComABPlace(abEdgeImg, xypABdetect);   
////	
////	//------ ����ƫ�� ------
////	//int locRow = 0; 
////	locRow = 0;  
////	for (int i = 0; i < coleAB; i++)
////	{
////		locRow = locRow + xypABsrc[i] - xypABdetect[i];   
////	}
////	locRow = int(0.5 + float(locRow) / float(coleAB));     
////}
////
//////��ֱ�߼�ⷽ���ͣ��Ͳ���Ҫȷ�����±߽磬 �Ƿ�������
//////��Ϊ����ֱ�ߵķ���һ�������ԣ���������ȷ����Ե�ķ������Ͳ���Ҫ����Ӽ��ֱ�ߵķ�����
////
////// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
////void ROIComLocationX(Mat &srcImg, Mat &detectImg, int &locCol){
////	//DistRectDetectOne(srcImg, detectThreshold, detectDirection);    //��Ϊ��distrectdetectone���Լ��������㣬��������ֱ�ӻ�ȡ����㣬����ȷ��ƫ������
////	//DistRectDetectOne(detectImg, detectThreshold, detectDirection);    //��ͬһ����ֱ���ԭͼ������ͼ��ͬһ��ֱ�ߣ�������ֱ�ߵľ��룬����ƫ����
////
////	int  offset = 1;  // ��߽�ƫ����    
////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	// �������ұ�Ե����
////	cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
////	ROIRotateImage(srcImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	int rowroiLR = roiImgLR.rows;
////	int colroiLR = roiImgLR.cols;
////	int roweLR = rowroiLR - 2 * offset;  
////	int coleLR = colroiLR - 2 * offset;  
////	// ��ȡ���ұ�Եͼ
////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);  
////	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);  
////	imwrite("D:/roiImage/11 roiImgLR.jpg", roiImgLR);   //////  
////	imwrite("D:/roiImage/12 lrEdgeImg.jpg", lrEdgeImg);   //////  
////	String  strImg;   
////	strImg = format("D:/roiImage/11 roiImgLRSrc/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgLR);
////	
////	// �ҵ����ұ�Եλ��     
////	vector<int>     xypLRsrc(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
////	
////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	// �������ұ�Ե����  
////	ROIRotateImage(detectImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	// ��ȡ���ұ�Եͼ
////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
////	imwrite("D:/roiImage/13 roiImgLR.jpg", roiImgLR);   //////     
////	imwrite("D:/roiImage/14 lrEdgeImg.jpg", lrEdgeImg);   //////   
////	strImg = format("D:/roiImage/13 roiImgLRDetect/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgLR);
////	
////	// �ҵ����ұ�Եλ��     
////	vector<int>     xypLRdetect(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
////	
////	//------ ����ƫ�� ------
////	//int locCol = 0; 
////	locCol = 0;  
////	for (int i = 0; i < roweLR; i++)
////	{
////		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
////	}
////	locCol = int(0.5 + float(locCol) / float(roweLR));   
////}
////
////// ��λ����
////void ROIComLocation(Mat &srcImg, Mat &showImg)
////{
////	//// ���ǰ��ʼ��λ      
////	//if (1 == m_flagComDetect)
////	{
////
////		// ����Դ����ͼ��    
////		Mat  comOKsrcImgTotal = imread("D:/roiImage/comOKsrcImgTotal.jpg", 0);
////		// ���е�����ͼ��    
////		Mat  detectImgTotal = srcImg;
////
////
////		// �ƶ����򲢼�������ͼ��
////		locRow = 0;
////		locCol = 0;
////		locRotAngle = 0;
////
////
////		//ֻ��Ҫ���������������ҳ�ƫ������ �ٸ�������ļ��������ƽ��ͼ�񼴿ɡ�
////		// �ƶ�X�ᣨ�У�  ����   
////		ROIComLocationX(comOKsrcImgTotal, detectImgTotal, locCol);
////
////		// �ƶ�Y�ᣨ�У�  �ϡ���   
////		ROIComLocationY(comOKsrcImgTotal, detectImgTotal, locRow);
////
////		//�ҵ�ƫ������ ����ƫ�������ƶ����߿� ��������ƽ�ƣ��������ڲ���Ҫ��ֻҪ�ƶ�ͼƬ
////
////		// ��X�ᣨ�У��ƶ��������ҿ����¿�  
////		//���������ĵ��ȥlocCol, ����locRow�Ϳ���ʵ��ƽ�ƣ� ��Ϊ���λ�ñ��˾��൱��ͼ��ƽ����
////		
////		// ��Y�ᣨ�У��ƶ��������ҿ����¿�  
////	}
////}
////
////int main(){
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////	Mat ngImg = imread("D:\\roiImage_2\\sample6\\9.JPG");
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
//
////////////////Դ����/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////#include <opencv2\opencv.hpp>
////#include <opencv2\highgui\highgui.hpp>
////#include <opencv2\imgproc\imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////#define Red 
////#define Blue 
////#define Green
////
////int threshold = 50;
////
////// ��λ����
////void ROIComLocation(Mat &srcImg, Mat &showImg);
////
////// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
////void ROIComLocationX(Mat &srcImg, Mat &detectImg, int &locCol);
////
////// Y�ᣨ�У�ƫ��������  
////void ROIComLocationY(Mat &srcImg, Mat &detectImg, int &locRow);
////
////// �ұ�Եͼ������λ��  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB);
////
////// �ұ�Եͼ������λ��  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR);
////
//////���ֱ��
////bool  DistRectDetectOne(Mat &srcImg, Point centerPoint, int rectWidth,
////	int rectHeight, int detectThreshold, int detectDirection,
////	float& x1CenterPoint, float& y1CenterPoint, int Red, int Green, int Blue);
////
//////���ֱ�߷���
////bool  LineDetectMethod(Mat &srcImg, int detectThreshold,
////	int detectDirection, float &aLine, float &bLine, float &cLine);
////
////// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
////bool ROIComDetectMethod(Mat &srcImg, Mat &showImg, cv::Point centerPoint,
////	int rectWidth, int rectHeight, int rectRotAngle, int detectThr);
////
//////��ַ����Ե
////void ROIComEdge(Mat &srcImg, Mat &edgeImg, int offset, int grayTh);
////
////
////int main(){
////
////	Mat src = imread("D:\\roiImage_2\\sample6\\4.JPG");
////	Mat ng_img = imread("D:\\roiImage_2\\sample6\\9.JPG");
////
////	//��λ������Ϊ����λ���غ�
////	ROIComLocation();
////
////	//��ʼ��⣬Ҳ���ǱȽϷ���
////	bool m_DetectResultFinal = ROIComDetectMethod();
////
////	// ��ʾ���
////	if (1 == m_DetectResultFinal)
////	{
////		cout << "ok!" << endl;
////	}
////	else
////	{
////		cout << "ng!" << endl;
////	}
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
////// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
////bool ROIComDetectMethod(Mat &srcImg, Mat &showImg, Point centerPoint,
////	int rectWidth, int rectHeight, int detectThr)
////{
////	bool  m_resultDetectCom = 0;
////	//// �ȽϷ�ʶ��ȱ�ݴ���  
////	//if (1 == m_flagComDetect)  
////	{
////		// ����Դͼ�񼰴����ͼ��ı�Եͼ��
////		int  safePix = 9;      // ��ȫ���ظ���    
////		int  numModel = 5;     // ɨ��ģ���С  
////		int dataSafe = int(float(numModel*numModel) / 2);
////		int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
////		int  numDetectTh = detectThr;   // ����ͬ���ظ���  
////		//countROIImage++;
////		//// ���������ͼ��  
////		Mat  detectImgTotal = srcImg.clone();
////		//// ��ͼ�����ͼ��  
////		cv::Mat detectImg(rectHeight, rectWidth, CV_8UC1);
////		ROIRotateImage(AdjustImage[camIndex], centerPoint, rectWidth, rectHeight, rectRotAngle, detectImg);
////		int row = detectImg.rows;
////		int col = detectImg.cols;
////		////////////////////////////////////////////////
////		// ����Դͼ��    
////		String strImg = format("D:/roiImage/%02d.jpg", distIndex);
////		Mat  ImgOK = imread(strImg, 0);
////		//imwrite("D:/roiImage/0 ImgOK.jpg", ImgOK);   //////  
////		//imwrite("D:/roiImage/0 detectImg.jpg", detectImg);   //////  
////		//strImg = format("D:/roiImage/0 ImgOk/%05d.jpg", countROIImage);
////		//imwrite(strImg, ImgOK);
////		//strImg = format("D:/roiImage/0 detectImg/%05d.jpg", countROIImage);
////		//imwrite(strImg, detectImg);
////		///////////////////////////////////////////////
////		int offset = 1;  // ��߽�ƫ����
////		int rowe = row - 2 * offset;
////		int cole = col - 2 * offset;
////		Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
////		Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
////		ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
////		//imwrite("D:/roiImage/1 edgeImgSrc.jpg", edgeImgSrc);   //////  
////		//strImg = format("D:/roiImage/1 edgeImgSrc/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgSrc);  
////		////////////////////////////////////////////////
////		// ����ͼ���Ե  
////		ROIComEdge(detectImg, edgeImgDetect, offset, grayTh);
////		//imwrite("D:/roiImage/2 edgeImgDetect.jpg", edgeImgDetect);   //////  
////		//strImg = format("D:/roiImage/2 edgeImgDetect/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgDetect);
////		////////////////////////////////////////////////
////		// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
////		// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
////		// --- ��5*5ģ��ȥɨ�裬 
////		// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
////		// --- ���ظ���С��10��ȥ����������0     
////		// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
////		////////////////////////////////////////////////
////		// 1 ��Դͼ���Ե�������ð�ȫ��Χ
////		// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
////		Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
////		Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
////		for (int i = 1; i < rowe; i++)
////		{
////			for (int j = 1; j < cole; j++)
////			{
////				if (edgeImgSrc.at <uchar>(i, j) > 0)
////				{
////					edgeImgSrcTh.at <uchar>(i, j) = 255;
////				}
////				if (edgeImgDetect.at <uchar>(i, j) > 0)
////				{
////					edgeImgDetectTh.at <uchar>(i, j) = 255;
////				}
////			}
////		}
////		//imwrite("D:/roiImage/3 edgeImgSrcTh.jpg", edgeImgSrcTh);   ////// 
////		//imwrite("D:/roiImage/3 edgeImgDetectTh.jpg", edgeImgDetectTh);   ////// 
////		//strImg = format("D:/roiImage/3 edgeImgSrcTh/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgSrcTh);
////		//strImg = format("D:/roiImage/3 edgeImgDetectTh/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgDetectTh);
////		////////////////////////////////////////////////
////		// �����ͷ�����չ��Ե������
////		//��ȡ�Զ����
////		//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////		Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
////		//���Ͳ���
////		Mat edgeImgSafe;
////		dilate(edgeImgSrc, edgeImgSafe, elementSafe);
////		// ��ɫ���ҹ�һ����[0, 1]; 
////		edgeImgSafe = (255 - edgeImgSafe) / 255;
////		//imwrite("D:/roiImage/4 edgeImgSafe.jpg", edgeImgSafe*255);   //////  
////		//strImg = format("D:/roiImage/4 edgeImgSafe/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgSafe);  
////		////////////////////////////////////////////////
////		// 2 ������Եͼ�����
////		Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
////		//imwrite("D:/roiImage/5 edgeImgSub.jpg", edgeImgSub);   //////     
////		//strImg = format("D:/roiImage/5 edgeImgSub/%05d.jpg", countROIImage);   
////		//imwrite(strImg, edgeImgSub);      
////		////////////////////////////////////////////////
////		// ��5*5ģ��ȥɨ�裬 
////		Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
////		int resultNum = 0;
////		int dataTem = 0;
////		int dataZong = 0;
////		int dataNum = 0;
////		//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
////		for (int i = numModel; i < rowe - numModel; i++)
////		{
////			for (int j = numModel; j < cole - numModel; j++)
////			{
////				dataTem = 0;
////				dataZong = 0;
////				dataNum = 0;
////				for (int m = 0; m < numModel; m++)
////				{
////					for (int n = 0; n < numModel; n++)
////					{
////						dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
////						if (dataTem > 0)
////						{
////							dataZong = dataZong + 1;
////						}
////					}
////				}
////				if (dataZong > dataSafe)
////				{
////					resultImg.at<uchar>(i, j) = 255;
////					resultNum++;
////				}
////			}
////		}
////		//imwrite("D:/roiImage/6 resultImg.jpg", resultImg);   //////  
////		//strImg = format("D:/roiImage/6 resultImg/%05d.jpg", countROIImage);
////		//imwrite(strImg, resultImg);
////		////////////////////////////////////////////////
////		// ��ͬ���������ĵ���Ϊ��ɫ  
////		Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
////		//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
////		for (int i = offset; i<row - offset; i++)
////		{
////			for (int j = offset; j < col - offset; j++)
////			{
////				resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
////				if (resultImgTem.at<uchar>(i, j) == 255)
////				{
////					for (int m = 0; m < offset; m++)
////					{
////						for (int n = 0; n < offset; n++)
////						{
////							//cv::Point centerPoint, int rectWidth, int rectHeight,
////							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
////								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[0] = 0;
////							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
////								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[1] = 0;
////							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
////								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[2] = 255;
////						}
////					}
////				}
////			}
////		}
////		////////////////////////////////////////////////
////		// ����ֵ>0����NG�� ����ֵ=0, ��OK 
////		if (resultNum <= numDetectTh)
////		{
////			m_resultDetectCom = 1;  // OK  
////		}
////		else
////		{
////			m_resultDetectCom = 0;  // NG    
////		}
////		////////////////////////////////////////////////
////		//countROIImage = countROIImage % 10000;   // ��ͼ����  
////	}
////	return  m_resultDetectCom;
////}
////
////void ROIComEdge(Mat &srcImg, Mat &edgeImg, int offset, int grayTh)
////{
////	int row = srcImg.rows;
////	int col = srcImg.cols;
////	//int offset = 1;  // ��߽�ƫ����
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////	//int grayTh = int(255 / 4);  
////
////	// ����� 1 ��ͼ��
////	// ��ַ����Ե		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
////	int  minEdgeImg = 255;
////	int  maxEdgeImg = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
////		}
////	}
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
////		}
////	}
////
////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			if (edgeImg.at<uchar>(i, j) < grayTh)
////			{
////				edgeImg.at<uchar>(i, j) = 0;
////			}
////		}
////	}
////}
////
////// ��λ����
////void ROIComLocation(Mat &srcImg, Mat &showImg)
////{
////	//// ���ǰ��ʼ��λ      
////	//if (1 == m_flagComDetect)
////	{
////
////		// ����Դ����ͼ��    
////		Mat  comOKsrcImgTotal = imread("D:/roiImage/comOKsrcImgTotal.jpg", 0);
////		// ���е�����ͼ��    
////		Mat  detectImgTotal = srcImg;
////
////
////		// �ƶ����򲢼�������ͼ��
////		locRow = 0;
////		locCol = 0;
////		locRotAngle = 0;
////
////		// �ƶ�X�ᣨ�У�  ����   
////		ROIComLocationX(comOKsrcImgTotal, detectImgTotal, locCol);
////
////		// �ƶ�Y�ᣨ�У�  �ϡ���   
////		ROIComLocationY(comOKsrcImgTotal, detectImgTotal, locRow);
////
////		// ��X�ᣨ�У��ƶ��������ҿ����¿�  
////		stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[1].nxCenter - locCol;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[1].nxCenter - locCol;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[1].nxCenter - locCol;
////		// ��Y�ᣨ�У��ƶ��������ҿ����¿�  
////		stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[0].nyCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[1].nyCenter - locRow;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[0].nyCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[1].nyCenter - locRow;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[0].nyCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[1].nyCenter - locRow;
////	}
////}
////
////
////// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
////void ROIComLocationX(Mat &srcImg, Mat &detectImg, int &locCol){
////	float  x1srcCenterPoint = 0.0;       // Height 
////	float  y1srcCenterPoint = 0.0;       // Width
////	DistRectDetectOne(srcImg, detectThreshold, detectDirection);
////		
////
////	float  x1detectCenterPoint = x1srcCenterPoint;    // Height     
////	float  y1detectCenterPoint = y1srcCenterPoint;    // Width      
////	DistRectDetectOne(detectImg, detectThreshold, detectDirection);
////
////	locCol = y1srcCenterPoint - y1detectCenterPoint;
////
////
////	//int  offset = 1;  // ��߽�ƫ����    
////	//// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	//// �������ұ�Ե����
////	//cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
////	//ROIRotateImage(srcImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	//int rowroiLR = roiImgLR.rows;
////	//int colroiLR = roiImgLR.cols;
////	//int roweLR = rowroiLR - 2 * offset;  
////	//int coleLR = colroiLR - 2 * offset;  
////	//// ��ȡ���ұ�Եͼ
////	//Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);  
////	//ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);  
////	//imwrite("D:/roiImage/11 roiImgLR.jpg", roiImgLR);   //////  
////	//imwrite("D:/roiImage/12 lrEdgeImg.jpg", lrEdgeImg);   //////  
////	//String  strImg;   
////	//strImg = format("D:/roiImage/11 roiImgLRSrc/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgLR);
////
////	//// �ҵ����ұ�Եλ��     
////	//vector<int>     xypLRsrc(roweLR);
////	//ROIComLRPlace(lrEdgeImg, xypLRsrc);
////
////
////	//// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	//// �������ұ�Ե����  
////	//ROIRotateImage(detectImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	//// ��ȡ���ұ�Եͼ
////	//lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	//ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
////	//imwrite("D:/roiImage/13 roiImgLR.jpg", roiImgLR);   //////     
////	//imwrite("D:/roiImage/14 lrEdgeImg.jpg", lrEdgeImg);   //////   
////	//strImg = format("D:/roiImage/13 roiImgLRDetect/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgLR);
////
////	//// �ҵ����ұ�Եλ��     
////	//vector<int>     xypLRdetect(roweLR);
////	//ROIComLRPlace(lrEdgeImg, xypLRdetect);
////
////	////------ ����ƫ�� ------
////	////int locCol = 0; 
////	//locCol = 0;  
////	//for (int i = 0; i < roweLR; i++)
////	//{
////	//	locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
////	//}
////	//locCol = int(0.5 + float(locCol) / float(roweLR));   
////
////}
////
////// Y�ᣨ�У�ƫ��������  
////void ROIComLocationY(Mat &srcImg, Mat &detectImg, int &locRow)
//////, int grayTh, cv::Point centerPointAB, int rectWidthAB, int rectHeightAB, int rectRotAngleAB)
////{
////	float  x1srcCenterPoint = 0.0;       // Height 
////	float  y1srcCenterPoint = 0.0;       // Width
////	DistRectDetectOne(srcImg, camIndex,
////		cv::Point(stCamera[camIndex].stDistance[j].stLineDistance[0].nxCenter,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nyCenter),
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nWidth,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nHeight,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nROIRotAngle,
////		j,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nAdjustValue,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nDir,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nNum,
////		x1srcCenterPoint, y1srcCenterPoint,
////		stCamera[camIndex].nRGB[0], stCamera[camIndex].nRGB[2], stCamera[camIndex].nRGB[1]);
////
////	float  x1detectCenterPoint = x1srcCenterPoint;    // Height     
////	float  y1detectCenterPoint = y1srcCenterPoint;    // Width      
////	DistRectDetectOne(detectImg, camIndex,
////		cv::Point(stCamera[camIndex].stDistance[j].stLineDistance[0].nxCenter,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nyCenter),
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nWidth,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nHeight,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nROIRotAngle,
////		j,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nAdjustValue,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nDir,
////		stCamera[camIndex].stDistance[j].stLineDistance[0].nNum,
////		x1detectCenterPoint, y1detectCenterPoint,
////		stCamera[camIndex].nRGB[2], stCamera[camIndex].nRGB[0], stCamera[camIndex].nRGB[1]);
////
////	locRow = x1srcCenterPoint - x1detectCenterPoint;
////
////
////
////	//int  offset = 1;  // ��߽�ƫ����    
////	//// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	//// �������±�Ե����
////	//cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);   
////	//ROIRotateImage(srcImg, centerPointAB, rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);  
////	//int rowroiAB = roiImgAB.rows;
////	//int colroiAB = roiImgAB.cols;
////	//int roweAB = rowroiAB - 2 * offset;
////	//int coleAB = colroiAB - 2 * offset;
////	//// ��ȡ���±�Եͼ
////	//Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);   
////	//ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);        
////	//imwrite("D:/roiImage/21 roiImgAB.jpg", roiImgAB);   //////  
////	//imwrite("D:/roiImage/22 abEdgeImg.jpg", abEdgeImg);   //////  
////	//String  strImg;
////	//strImg = format("D:/roiImage/21 roiImgABSrc/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgAB);
////
////	//// �ҵ����±�Եλ��     
////	//vector<int>     xypABsrc(coleAB);      
////	//ROIComABPlace(abEdgeImg, xypABsrc);    
////
////	//// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	//// �������±�Ե����
////	//ROIRotateImage(detectImg, cv::Point(centerPointAB.x - locCol, centerPointAB.y), rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);
////	//// ��ȡ���±�Եͼ
////	//abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	//ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
////	//imwrite("D:/roiImage/23 roiImgAB.jpg", roiImgAB);     //////  
////	//imwrite("D:/roiImage/24 abEdgeImg.jpg", abEdgeImg);   //////  
////	//strImg = format("D:/roiImage/23 roiImgABDetect/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgAB);
////
////	//// �ҵ����±�Եλ��     
////	//vector<int>     xypABdetect(coleAB);     
////	//ROIComABPlace(abEdgeImg, xypABdetect);   
////
////	////------ ����ƫ�� ------
////	////int locRow = 0; 
////	//locRow = 0;  
////	//for (int i = 0; i < coleAB; i++)
////	//{
////	//	locRow = locRow + xypABsrc[i] - xypABdetect[i];   
////	//}
////	//locRow = int(0.5 + float(locRow) / float(coleAB));   
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////	imwrite("D:/roiImage/25 abEdgeImg.jpg", abEdgeImg);   //////   
////
////	// �ҵ����±�Եλ��
////	//vector<int>     xypAB(cole);
////	int maxval = 0;
////	int pixval = 0;
////	for (int j = 0; j < cole; j++)
////	{
////		maxval = 0;
////		xypAB[j] = 0;
////		for (int i = 0; i < rowe; i++)
////		{
////			pixval = abEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypAB[j] = i;
////			}
////		}
////	}
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////	imwrite("D:/roiImage/15 lrEdgeImg.jpg", lrEdgeImg);   //////   
////
////	// �ҵ����ұ�Եλ��
////	//vector<int>     xypLR(rowe);  
////	int pixval = 0;
////	int maxval = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		maxval = 0;
////		xypLR[i] = 0;
////		for (int j = 0; j < cole; j++)
////		{
////			pixval = lrEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypLR[i] = j;
////			}
////		}
////	}
////}
////
////bool  DistRectDetectOne(Mat &srcImg, int detectThreshold, int detectDirection)
////{
////	Point2f point4Ver[4];      //����4���������
////
////	Point  rectLTPoint;
////	rectLTPoint.x = int(point4Ver[1].x);
////	rectLTPoint.y = int(point4Ver[1].y); 
////	
////	// ���Ϊ�棬���ֱ�߻�Բ����� 
////
////	float atLine = 0.0, btLine = 0.0, ctLine = 0.0;
////
////	bool mLineTest = 1;
////
////	int rectRotAngle = 0;
////	float  rectAngle = rectRotAngle * 2 * 3.141592654 / 360;
////	
////	// ���ֱ��
////	mLineTest = LineDetectMethod(srcImg, detectThreshold, detectDirection, atLine, btLine, ctLine);
////
////	if (mLineTest == 0)
////	{
////		// δ��⵽ֱ�ߣ�������
////		return false;
////	}
////	else
////	{
////		// ����ֱ��
////		Point2f  onePoint2f, twoPoint2f;
////		Point   onePoint, twoPoint;
////		float   edgePoint = 5.0;
////		switch (detectDirection)
////		{
////		case 0:  //������
////			// Point One  
////			onePoint2f.x = point4Ver[1].x + ctLine*cos(rectAngle);
////			onePoint2f.y = point4Ver[1].y + ctLine*sin(rectAngle);
////			// Point Two
////			twoPoint2f.x = point4Ver[0].x + ctLine*cos(rectAngle);
////			twoPoint2f.y = point4Ver[0].y + ctLine*sin(rectAngle);
////			if (onePoint2f.x > point4Ver[2].x - edgePoint || twoPoint2f.x > point4Ver[3].x - edgePoint){
////				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
////				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
////				return false;
////			}
////			else
////			{
////				// ���ĵ�
////				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
////				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
////				onePoint.x = int(onePoint2f.x);
////				onePoint.y = int(onePoint2f.y);
////				twoPoint.x = int(twoPoint2f.x);
////				twoPoint.y = int(twoPoint2f.y);
////				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
////				break;
////			}
////		case 1:  //���ҵ���
////			onePoint2f.x = point4Ver[1].x + ctLine*cos(rectAngle);
////			onePoint2f.y = point4Ver[1].y + ctLine*sin(rectAngle);
////			// Point Two
////			twoPoint2f.x = point4Ver[0].x + ctLine*cos(rectAngle);
////			twoPoint2f.y = point4Ver[0].y + ctLine*sin(rectAngle);
////			if (onePoint2f.x > point4Ver[2].x - edgePoint || twoPoint2f.x > point4Ver[3].x - edgePoint)
////			{
////				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
////				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
////				return false;
////			}
////			else{
////				// ���ĵ�
////				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
////				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
////				onePoint.x = int(onePoint2f.x);
////				onePoint.y = int(onePoint2f.y);
////				twoPoint.x = int(twoPoint2f.x);
////				twoPoint.y = int(twoPoint2f.y);
////				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
////				break;
////			}
////		case 2:  
////			//���ϵ���
////			onePoint2f.x = point4Ver[1].x - ctLine*sin(rectAngle);
////			onePoint2f.y = point4Ver[1].y + ctLine*cos(rectAngle);
////			
////			// Point Two
////			twoPoint2f.x = point4Ver[2].x - ctLine*sin(rectAngle);
////			twoPoint2f.y = point4Ver[2].y + ctLine*cos(rectAngle);
////			if (onePoint2f.y > point4Ver[0].y - edgePoint || onePoint2f.y > point4Ver[3].y - edgePoint)
////			{
////				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
////				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
////				return false;
////			}
////			else
////			{
////				// ���ĵ�
////				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
////				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
////				onePoint.x = int(onePoint2f.x);
////				onePoint.y = int(onePoint2f.y);
////				twoPoint.x = int(twoPoint2f.x);
////				twoPoint.y = int(twoPoint2f.y);
////				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
////				break;
////			}
////		case 3:  
////			//���µ���
////			onePoint2f.x = point4Ver[1].x - ctLine*sin(rectAngle);
////			onePoint2f.y = point4Ver[1].y + ctLine*cos(rectAngle);
////			// Point Two
////			twoPoint2f.x = point4Ver[2].x - ctLine*sin(rectAngle);
////			twoPoint2f.y = point4Ver[2].y + ctLine*cos(rectAngle);
////			if (onePoint2f.y > point4Ver[0].y - edgePoint || onePoint2f.y > point4Ver[3].y - edgePoint)
////			{
////				//putText(showImg, "No Line Found!", cv::Point(rectLTPoint.x, rectLTPoint.y + int(rectHeight / 2)),
////				//	CV_FONT_HERSHEY_COMPLEX, 1, cv::Scalar(Red, Green, Blue), 3);
////				return false;
////			}
////			else
////			{
////				// ���ĵ�
////				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
////				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
////				onePoint.x = int(onePoint2f.x);
////				onePoint.y = int(onePoint2f.y);
////				twoPoint.x = int(twoPoint2f.x);
////				twoPoint.y = int(twoPoint2f.y);
////				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
////				break;
////			}
////		default:
////			break;
////		}
////		return  true;
////	}
////}
////
//////���ֱ��ֻ�ܷ���true�� ����false�� �����з���
////bool  LineDetectMethod(Mat &srcImg, int detectThreshold, int detectDirection, float &aLine, float &bLine, float &cLine)
////{
////	const int grayValThr = 8;   //////////////////
////	const int pixelSet = detectThreshold;
////	int row = srcImg.rows;
////	int col = srcImg.cols;
////	Mat srcGray = srcImg;
////	int i = 0, j = 0;
////	//cvtColor(srcImg, srcGray, CV_BGR2GRAY);  
////	//srcGray = srcImg;  
////
////	// ����
////	if (detectDirection == 0 || detectDirection == 1)
////	{
////		// ��ÿ������ֵ�ܵı仯ֵ  
////		vector<int>  grayVerdiff(col);
////		for (j = 0; j < col; j++)
////		{
////			grayVerdiff[j] = 0;   // ��ʼ��Ϊ0
////		}
////		for (i = 0; i < row; i++)
////		{
////			for (j = 1 + detectThreshold; j < col; j++)
////			{
////				grayVerdiff[j] += abs(srcGray.at<uchar>(i, j) - srcGray.at<uchar>(i, j - 1 - detectThreshold));
////			}
////		}
////		for (j = 0; j < col; j++)
////		{
////			//grayVerdiff[j] = int(float(grayVerdiff[j]) / float(row));
////			grayVerdiff[j] = int(float(grayVerdiff[j]) / float(row) + 0.5);
////		}
////		int xypix = 1;
////		int xypixFirst = 1;
////		int xypixSecond = 1;
////		int gerrMax = 0;
////		int gerrMaxFirst = 0;
////		int gerrMaxSecond = 0;
////		int js = 1;
////		int jsFirst = 1;
////		int jsSecond = 1;
////		for (js = 1; js < col; js++)
////		{
////			if (gerrMax < grayVerdiff[js])
////			{
////				gerrMax = grayVerdiff[js];
////				xypix = js;
////			}
////		}
////		if (gerrMax < grayValThr)
////		{
////			return false;
////		}
////
////		for (jsFirst = 1; jsFirst < xypix - pixelSet; jsFirst++)
////		{
////			if (gerrMaxFirst <= grayVerdiff[jsFirst] && grayVerdiff[jsFirst] < gerrMax)
////			{
////				gerrMaxFirst = grayVerdiff[jsFirst];
////				xypixFirst = jsFirst;
////			}
////		}
////		for (jsSecond = col - 1; jsSecond > xypix + pixelSet; jsSecond--)
////		{
////			if (gerrMaxSecond < grayVerdiff[jsSecond] && grayVerdiff[jsSecond] < gerrMax)
////			{
////				gerrMaxSecond = grayVerdiff[jsSecond];
////				xypixSecond = jsSecond;
////			}
////		}
////		if (detectDirection == 0)  		// ������  
////		{
////			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixFirst;
////			}
////			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixSecond;
////			}
////		}
////		else if (detectDirection == 1)  // ���ҵ��� 
////		{
////			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixFirst;
////			}
////			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixSecond;
////			}
////		}
////		aLine = 0;
////		bLine = -1;
////		cLine = xypix;
////		//// �����ĵ�  
////		//xCenterPoint = int(float(row) / 2);
////		//yCenterPoint = xypix;
////		return true;
////	}
////
////	// ���±�Ե  
////	else if (detectDirection == 2 || detectDirection == 3)
////	{
////		// ��ÿ������ֵ�ܵı仯ֵ  
////		vector<int>  grayVerdiff(row);
////		for (i = 0; i < row; i++)
////		{
////			grayVerdiff[i] = 0;   // ��ʼ��Ϊ0
////		}
////		for (i = 1 + detectThreshold; i < row; i++)
////		{
////			for (j = 0; j < col; j++)
////			{
////				grayVerdiff[i] += abs(srcGray.at<uchar>(i, j) - srcGray.at<uchar>(i - 1 - detectThreshold, j));
////			}
////		}
////		for (i = 0; i < row; i++)
////		{
////			//grayVerdiff[i] = int(float(grayVerdiff[i]) / float(col));
////			grayVerdiff[i] = int(float(grayVerdiff[i]) / float(col) + 0.5);
////		}
////
////		int xypix = 1;
////		int xypixFirst = 1;
////		int xypixSecond = 1;
////		int gerrMax = 0;
////		int gerrMaxFirst = 0;
////		int gerrMaxSecond = 0;
////		int js = 1;
////		int jsFirst = 1;
////		int jsSecond = 1;
////		for (js = 1; js < row; js++)
////		{
////			if (gerrMax < grayVerdiff[js])
////			{
////				gerrMax = grayVerdiff[js];
////				xypix = js;
////			}
////		}
////		if (gerrMax < grayValThr)
////		{
////			return false;
////		}
////
////		for (jsFirst = 1; jsFirst < xypix - pixelSet; jsFirst++)
////		{
////			if (gerrMaxFirst <= grayVerdiff[jsFirst] && grayVerdiff[jsFirst] < gerrMax)
////			{
////				gerrMaxFirst = grayVerdiff[jsFirst];
////				xypixFirst = jsFirst;
////			}
////		}
////		for (jsSecond = row - 1; jsSecond > xypix + pixelSet; jsSecond--)
////		{
////			if (gerrMaxSecond <= grayVerdiff[jsSecond] && grayVerdiff[jsSecond] < gerrMax)
////			{
////				gerrMaxSecond = grayVerdiff[jsSecond];
////				xypixSecond = jsSecond;
////			}
////		}
////		if (detectDirection == 2)  //���ϵ���  
////		{
////			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixFirst;
////			}
////			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixSecond;
////			}
////		}
////		else if (detectDirection == 3)  // ���µ���  
////		{
////			if (gerrMaxFirst>gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixFirst;
////			}
////			else if (gerrMaxFirst <= gerrMaxSecond && gerrMaxFirst>grayValThr)
////			{
////				xypix = xypixSecond;
////			}
////		}
////		aLine = -1;
////		bLine = 0;
////		cLine = xypix;
////		//// �����ĵ�  
////		//yCenterPoint = int(float(col) / 2);
////		//xCenterPoint = xypix;
////		return true;
////	}
////}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
//////�����ȡͼ���Ե�ĺ���
////
////#include <opencv2\opencv.hpp>
////#include <opencv2\highgui\highgui.hpp>
////#include <opencv2\imgproc\imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
////{
////	//int row = srcImg.rows;
////	//int col = srcImg.cols;
////	////int offset = 1;  // ��߽�ƫ����
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// ����� 1 ��ͼ��
////	// ��ַ����Ե		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
////	int  minEdgeImg = 255;
////	int  maxEdgeImg = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
////		}
////	}
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
////		}
////	}
////
////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			if (edgeImg.at<uchar>(i, j) < grayTh)
////			{
////				edgeImg.at<uchar>(i, j) = 0;
////			}
////		}
////	}
////
////	imshow("��Եͼ", edgeImg);
////}
////
////int main(){
////
////	int grayTh = 50;
////	int offset = 1;
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////
////	int row = srcImg.rows;
////	int col = srcImg.cols;
////	//int offset = 1;  // ��߽�ƫ����
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////	//int grayTh = int(255 / 4);  
////
////	//Mat edgeImg = Mat::zeros(rowe, cole, CV_8UC1);
////
////	Mat src_edge = Mat::zeros(rowe, cole, CV_8UC1);
////	ROIComEdge(srcImg, src_edge, offset, grayTh, row, col, rowe, cole);
////	//imshow("ԭͼ��Ե", src_edge);
////	imwrite("D:\\roiImageForTest\\src_edge.jpg", src_edge);
////
////	Mat ngImg = imread("D:\\roiImage_2\\sample6\\9.JPG");
////	Mat ng_edge;
////	//ROIComEdge(ngImg, ng_edge, offset, grayTh);
////	//imshow("ng��Ե", ng_edge);
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
//
//////����������Եͼ��ģ�y�ᣬƫ������ x������
////
////#include <opencv2\opencv.hpp>
////#include <opencv2\highgui\highgui.hpp>
////#include <opencv2\imgproc\imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
////{
////	//int row = srcImg.rows;
////	//int col = srcImg.cols;
////	////int offset = 1;  // ��߽�ƫ����
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// ����� 1 ��ͼ��
////	// ��ַ����Ե		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
////	int  minEdgeImg = 255;
////	int  maxEdgeImg = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
////		}
////	}
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
////		}
////	}
////
////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			if (edgeImg.at<uchar>(i, j) < grayTh)
////			{
////				edgeImg.at<uchar>(i, j) = 0;
////			}
////		}
////	}
////
////	//imshow("��Եͼ", edgeImg);
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////
////	// �ҵ����±�Եλ��
////	//vector<int>     xypAB(cole);
////	int maxval = 0;
////	int pixval = 0;
////	for (int j = 0; j < cole; j++)
////	{
////		maxval = 0;
////		xypAB[j] = 0;
////		for (int i = 0; i < rowe; i++)
////		{
////			pixval = abEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypAB[j] = i;
////			}
////		}
////	}
////}
////
////
////// Y�ᣨ�У�ƫ��������  
////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
////{
////	int locRow = 0;
////	int  offset = 1;  // ��߽�ƫ����       ///offset�����ڼ���߽��ƫ���������ȸ����ҵı߽���ƫ���٣��� �����Ǽ��������locRow��ƫ�ƣ� �����߽�ͼ��ƫ�ƶ���
////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	// �������±�Ե����
////
////	int rowroiAB = srcImg.rows;
////	int colroiAB = srcImg.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// ��ȡ���±�Եͼ
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("��һ����Եͼ", abEdgeImg);
////
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABsrc(coleAB);
////	ROIComABPlace(abEdgeImg, xypABsrc);
////
////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	// �������±�Ե����
////	// ��ȡ���±�Եͼ
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("�ڶ�����Եͼ", abEdgeImg);
////
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABdetect(coleAB);
////	ROIComABPlace(abEdgeImg, xypABdetect);
////
////	//------ ����ƫ�� ------
////	//int locRow = 0; 
////	locRow = 0;
////	for (int i = 0; i < coleAB; i++)
////	{
////		locRow = locRow + xypABsrc[i] - xypABdetect[i];
////	}
////	locRow = int(0.5 + float(locRow) / float(coleAB));
////	return locRow;
////}
////
////int main(){
////
////	int offsety = 0;
////	int grayThreshold = 50;
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////	imshow("ԭͼ", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\9.JPG");
////	imshow("�����ͼ", detectImg);
////
////	offsety = ROIComLocationY(srcImg, detectImg, grayThreshold);
////	cout << "y��ƫ������" << offsety << endl;
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
////////�Ƚ�����Եͼ��Ĳ��죬����OK��ng�����жϽ��
////#include <opencv2\opencv.hpp>
////#include <opencv2\highgui\highgui.hpp>
////#include <opencv2\imgproc\imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////int detectThr = 500;
////
////void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
////{
////	//int row = srcImg.rows;
////	//int col = srcImg.cols;
////	////int offset = 1;  // ��߽�ƫ����
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// ����� 1 ��ͼ��
////	// ��ַ����Ե		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =    //�������ǳ�������Ϊ�����srcImgͼ������ͨ���ģ�����������Ҫ�ĵ�ͨ����������
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
////	int  minEdgeImg = 255;
////	int  maxEdgeImg = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
////		}
////	}
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
////		}
////	}
////
////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			if (edgeImg.at<uchar>(i, j) < grayTh)
////			{
////				edgeImg.at<uchar>(i, j) = 0;
////			}
////		}
////	}
////
////	//imshow("��Եͼ", edgeImg);
////}
////
////// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
////bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
////{
////	bool  m_resultDetectCom = 0;
////	//// �ȽϷ�ʶ��ȱ�ݴ���  
////
////	// ����Դͼ�񼰴����ͼ��ı�Եͼ��
////	int  safePix = 9;      // ��ȫ���ظ���    
////	int  numModel = 5;     // ɨ��ģ���С  
////	int dataSafe = int(float(numModel*numModel) / 2);
////	//int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
////	int grayTh_1 = 50;
////	int grayTh_2 = 30;
////	int  numDetectTh = detectThr;   // ����ͬ���ظ���  
////
////	//// ��ͼ�����ͼ��  
////	int row = detectImg.rows;
////	int col = detectImg.cols;
////
////	///////////////////////////////////////////////
////	int offset = 1;  // ��߽�ƫ����
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////
////	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
////	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
////
////	ROIComEdge(detectImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
////	imshow("ok��Եͼ", edgeImgSrc);
////
////	////////////////////////////////////////////////
////	// ����ͼ���Ե  
////	ROIComEdge(srcImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
////	imshow("ng��Եͼ", edgeImgDetect);
////	////////////////////////////////////////////////
////	// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
////	// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
////	// --- ��5*5ģ��ȥɨ�裬 
////	// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
////	// --- ���ظ���С��10��ȥ����������0     
////	// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
////	////////////////////////////////////////////////
////	// 1 ��Դͼ���Ե�������ð�ȫ��Χ
////	// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
////	Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
////	Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
////	for (int i = 1; i < rowe; i++)
////	{
////		for (int j = 1; j < cole; j++)
////		{
////			if (edgeImgSrc.at <uchar>(i, j) > 0)
////			{
////				edgeImgSrcTh.at <uchar>(i, j) = 255;
////			}
////			if (edgeImgDetect.at <uchar>(i, j) > 0)
////			{
////				edgeImgDetectTh.at <uchar>(i, j) = 255;
////			}
////		}
////	}
////	////////////////////////////////////////////////
////	// �����ͷ�����չ��Ե������
////	//��ȡ�Զ����
////	//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
////	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
////	//���Ͳ���
////	Mat edgeImgSafe;
////	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
////	// ��ɫ���ҹ�һ����[0, 1]; 
////	edgeImgSafe = (255 - edgeImgSafe) / 255;
////
////	////////////////////////////////////////////////
////	// 2 ������Եͼ�����
////	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
////	imshow("������", edgeImgSub);
////
////	////////////////////////////////////////////////
////	// ��5*5ģ��ȥɨ�裬 
////	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
////	int resultNum = 0;
////	int dataTem = 0;
////	int dataZong = 0;
////	int dataNum = 0;
////
////	//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
////	for (int i = numModel; i < rowe - numModel; i++)
////	{
////		for (int j = numModel; j < cole - numModel; j++)
////		{
////			dataTem = 0;
////			dataZong = 0;
////			dataNum = 0;
////			for (int m = 0; m < numModel; m++)
////			{
////				for (int n = 0; n < numModel; n++)
////				{
////					dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
////					if (dataTem > 0)
////					{
////						dataZong = dataZong + 1;
////					}
////				}
////			}
////			if (dataZong > dataSafe)
////			{
////				//ֻҪ�в�ͬ�����������ģ����Ҳ�ֻ�����ǲ�ͬ�ĵط�������Ҫ�Ǳ߽磬�߽�û�غϣ��к�㣬�Ǿͱ�ʾ��Ƭ��
////				//resultImg.at<uchar>(i, j) = 255;
////				resultImg.at<Vec3b>(i, j)[0] = 0;
////				resultImg.at<Vec3b>(i, j)[1] = 0;
////				resultImg.at<Vec3b>(i, j)[2] = 255;
////
////				//showImg.at<Vec3b>(m, n)[2] = 255;
////				resultNum++;
////			}
////		}
////	}
////	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
////	imshow("�˲����", resultImg);
////	////////////////////////////////////////////////
////
////	//��ͨ������ͨ��һ��Ҫ�ֿ�����Ȼ�����׳���
////	// ��ͬ���������ĵ���Ϊ��ɫ  
////	Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
////	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
////	for (int i = offset; i<row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
////			if (resultImgTem.at<uchar>(i, j) == 255)
////			{
////				for (int m = 0; m < offset; m++)
////				{
////					for (int n = 0; n < offset; n++)
////					{
////						//cv::Point centerPoint, int rectWidth, int rectHeight,
////						showImg.at<Vec3b>(m, n)[0] = 0;
////						showImg.at<Vec3b>(m, n)[1] = 0;
////						showImg.at<Vec3b>(m, n)[2] = 255;
////					}
////				}
////			}
////		}
////	}
////
////	//imshow("���չʾ", showImg);
////	////////////////////////////////////////////////
////	// ����ֵ>0����NG�� ����ֵ=0, ��OK 
////	if (resultNum <= numDetectTh)
////	{
////		m_resultDetectCom = 1;  // OK  
////	}
////	else
////	{
////		m_resultDetectCom = 0;  // NG    
////	}
////	return  m_resultDetectCom;
////}
////
//////��Ҫ����������ǣ�ƽ��֮��ͼ��϶���Ҫ��չ���ⲿ����ô���������Զ���չ��
////
////int main(){
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG", 0);
////	//imshow("ԭͼ", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
////	//imshow("�����ͼ", detectImg);
////
////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////
////	bool flag = 0;
////	flag = ROIComDetectMethod(srcImg, detectImg, showImg);
////	if (flag == 0){
////		cout << "ngͼƬ" << endl;
////	}
////	else{
////		cout << "����okͼƬ" << endl;
////	}
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*/*////123456
//////////��λ����,Ҳ���ǵõ�x�� y���ƫ����
////#include <opencv2\opencv.hpp>
////#include <opencv2\highgui\highgui.hpp>
////#include <opencv2\imgproc\imgproc.hpp>
////#include <iostream>
////
////using namespace std;
////using namespace cv;
////
////void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
////{
////	//int row = srcImg.rows;
////	//int col = srcImg.cols;
////	////int offset = 1;  // ��߽�ƫ����
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// ����� 1 ��ͼ��
////	// ��ַ����Ե		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
////	int  minEdgeImg = 255;
////	int  maxEdgeImg = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
////		}
////	}
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
////		}
////	}
////
////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = 0; i < rowe; i++)
////	{
////		for (int j = 0; j < cole; j++)
////		{
////			if (edgeImg.at<uchar>(i, j) < grayTh)
////			{
////				edgeImg.at<uchar>(i, j) = 0;
////			}
////		}
////	}
////
////	//imshow("��Եͼ", edgeImg);
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////
////	// �ҵ����±�Եλ��
////	//vector<int>     xypAB(cole);
////	int maxval = 0;
////	int pixval = 0;
////	for (int j = 0; j < cole; j++)
////	{
////		maxval = 0;
////		xypAB[j] = 0;
////		for (int i = 0; i < rowe; i++)
////		{
////			pixval = abEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypAB[j] = i;
////			}
////		}
////	}
////}
////
////
////// Y�ᣨ�У�ƫ��������  
////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
////{
////	int locRow = 0;
////	int  offset = 1;  // ��߽�ƫ����       ///offset�����ڼ���߽��ƫ���������ȸ����ҵı߽���ƫ���٣��� �����Ǽ��������locRow��ƫ�ƣ� �����߽�ͼ��ƫ�ƶ���
////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	// �������±�Ե����
////
////	int rowroiAB = srcImg.rows;
////	int colroiAB = srcImg.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// ��ȡ���±�Եͼ
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("��һ����Եͼ", abEdgeImg);
////
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABsrc(coleAB);
////	ROIComABPlace(abEdgeImg, xypABsrc);
////
////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	// �������±�Ե����
////	// ��ȡ���±�Եͼ
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("�ڶ�����Եͼ", abEdgeImg);
////
////	// �ҵ����±�Եλ��     
////	vector<int>     xypABdetect(coleAB);
////	ROIComABPlace(abEdgeImg, xypABdetect);
////
////	//------ ����ƫ�� ------
////	//int locRow = 0; 
////	locRow = 0;
////	for (int i = 0; i < coleAB; i++)
////	{
////		locRow = locRow + xypABsrc[i] - xypABdetect[i];
////	}
////	locRow = int(0.5 + float(locRow) / float(coleAB));
////	return locRow;
////}
////
////// �ұ�Եͼ������λ��  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////
////	// �ҵ����ұ�Եλ��
////	//vector<int>     xypLR(rowe);  
////	int pixval = 0;
////	int maxval = 0;
////	for (int i = 0; i < rowe; i++)
////	{
////		maxval = 0;
////		xypLR[i] = 0;
////		for (int j = 0; j < cole; j++)
////		{
////			pixval = lrEdgeImg.at<uchar>(i, j);
////			if (pixval > maxval)
////			{
////				maxval = pixval;
////				xypLR[i] = j;
////			}
////		}
////	}
////}
////
////// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
////int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
////	int locCol = 0;
////	int  offset = 1;  // ��߽�ƫ����    
////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
////	// �������ұ�Ե����
////	int rowroiLR = srcImg.rows;
////	int colroiLR = srcImg.cols;
////	int roweLR = rowroiLR - 2 * offset;
////	int coleLR = colroiLR - 2 * offset;
////	// ��ȡ���ұ�Եͼ
////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
////	imshow("���ҵ�һ��Եͼ", lrEdgeImg);
////
////	// �ҵ����ұ�Եλ��     
////	vector<int>     xypLRsrc(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
////
////
////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
////	// �������ұ�Ե����  
////	// ��ȡ���ұ�Եͼ
////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
////	imshow("���ҵڶ�����Եͼ", lrEdgeImg);
////
////	// �ҵ����ұ�Եλ��     
////	vector<int>     xypLRdetect(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
////
////	//------ ����ƫ�� ------
////	//int locCol = 0; 
////	locCol = 0;
////	for (int i = 0; i < roweLR; i++)
////	{
////		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
////	}
////	locCol = int(0.5 + float(locCol) / float(roweLR));
////
////	return locCol;
////}
////
////// ��λ����
////void ROIComLocation(Mat srcImg, Mat detectImg)
////{
////	//// ���ǰ��ʼ��λ      
////	int offsetx = 0;
////	int offsety = 0;
////	int grayTh = 50;
////
////	// �ƶ�X�ᣨ�У�  ����   
////	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
////	cout << offsetx << endl;
////
////	// �ƶ�Y�ᣨ�У�  �ϡ���   
////	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
////	cout << offsety << endl;
////}
////
////
//////��Ҫ����������ǣ�ƽ��֮��ͼ��϶���Ҫ��չ���ⲿ����ô���������Զ���չ��
////
////int main(){
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG", 0);
////	//imshow("ԭͼ", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
////	//imshow("�����ͼ", detectImg);
////
////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////
////	//�õ�ͼ���ȵ�ƽ����ȡƫ������ ��ƽ��
////	ROIComLocation(srcImg, detectImg);
////
////
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
////
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
////////��һ��ͼƬ���㷨�Ѿ����ˣ�ȫ��
//////////��λ����
//////#include <opencv2\opencv.hpp>
//////#include <opencv2\highgui\highgui.hpp>
//////#include <opencv2\imgproc\imgproc.hpp>
//////#include <iostream>
//////
//////using namespace std;
//////using namespace cv;
//////
//////Mat imgTranslate(Mat &matSrc, int xOffset, int yOffset, bool bScale) {
//////	// �ж��Ƿ�ı�ͼ���С,���趨������ROI 
//////	int nRows = matSrc.rows;
//////	int nCols = matSrc.cols;
//////	int nRowsRet = 0;
//////	int nColsRet = 0;
//////	Rect rectSrc;
//////	Rect rectRet;
//////	if (bScale) {
//////		nRowsRet = nRows + abs(yOffset);
//////		nColsRet = nCols + abs(xOffset);
//////		rectSrc.x = 0;
//////		rectSrc.y = 0;
//////		rectSrc.width = nCols;
//////		rectSrc.height = nRows;
//////	}
//////	else {
//////		nRowsRet = matSrc.rows;
//////		nColsRet = matSrc.cols;
//////		if (xOffset >= 0) {
//////			rectSrc.x = 0;
//////		}
//////		else {
//////			rectSrc.x = abs(xOffset);
//////		}
//////
//////		if (yOffset >= 0) {
//////			rectSrc.y = 0;
//////		}
//////		else {
//////			rectSrc.y = abs(yOffset);
//////		}
//////
//////		rectSrc.width = nCols - abs(xOffset);
//////		rectSrc.height = nRows - abs(yOffset);
//////	}
//////
//////	// ���������ROI 
//////	if (xOffset >= 0) {
//////		rectRet.x = xOffset;
//////	}
//////	else {
//////		rectRet.x = 0;
//////	}
//////
//////	if (yOffset >= 0) {
//////		rectRet.y = yOffset;
//////	}
//////	else {
//////		rectRet.y = 0;
//////	}
//////	rectRet.width = rectSrc.width;
//////	rectRet.height = rectSrc.height;
//////
//////	// ����ͼ�� 
//////	Mat matRet(nRowsRet, nColsRet, matSrc.type(), Scalar(0));
//////	matSrc(rectSrc).copyTo(matRet(rectRet));
//////	return matRet;
//////}
//////
//////
//////
//////void ROIComEdge(Mat srcImg, Mat edgeImg, int offset, int grayTh, int row, int col, int rowe, int cole)
//////{
//////	//int row = srcImg.rows;
//////	//int col = srcImg.cols;
//////	////int offset = 1;  // ��߽�ƫ����
//////	//int rowe = row - 2 * offset;
//////	//int cole = col - 2 * offset;
//////	////int grayTh = int(255 / 4);  
//////
//////	// ����� 1 ��ͼ��
//////	// ��ַ����Ե		
//////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
//////	for (int i = offset; i < row - offset; i++)
//////	{
//////		for (int j = offset; j < col - offset; j++)
//////		{
//////			edgeImg.at<uchar>(i - offset, j - offset) =
//////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
//////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
//////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
//////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
//////		}
//////	}
//////	// �ѱ�Եͼ������ֵӳ�䵽[0, 255]
//////	int  minEdgeImg = 255;
//////	int  maxEdgeImg = 0;
//////	for (int i = 0; i < rowe; i++)
//////	{
//////		for (int j = 0; j < cole; j++)
//////		{
//////			minEdgeImg = min(minEdgeImg, int(edgeImg.at<uchar>(i, j)));
//////			maxEdgeImg = max(maxEdgeImg, int(edgeImg.at<uchar>(i, j)));
//////		}
//////	}
//////	for (int i = 0; i < rowe; i++)
//////	{
//////		for (int j = 0; j < cole; j++)
//////		{
//////			edgeImg.at<uchar>(i, j) = 255 * (edgeImg.at<uchar>(i, j) - minEdgeImg) /
//////				(maxEdgeImg - edgeImg.at<uchar>(i, j) + 0.1);
//////		}
//////	}
//////
//////	// �ѱ�Եͼ��ȥ����С�ı�Ե  	
//////	//Mat edgeImgTh = Mat::zeros(rowe, cole, CV_8UC1);  
//////	for (int i = 0; i < rowe; i++)
//////	{
//////		for (int j = 0; j < cole; j++)
//////		{
//////			if (edgeImg.at<uchar>(i, j) < grayTh)
//////			{
//////				edgeImg.at<uchar>(i, j) = 0;
//////			}
//////		}
//////	}
//////
//////	//imshow("��Եͼ", edgeImg);
//////}
//////
//////// �ұ�Եͼ������λ��  
//////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
//////{
//////	int rowe = abEdgeImg.rows;
//////	int cole = abEdgeImg.cols;
//////
//////	// �ҵ����±�Եλ��
//////	//vector<int>     xypAB(cole);
//////	int maxval = 0;
//////	int pixval = 0;
//////	for (int j = 0; j < cole; j++)
//////	{
//////		maxval = 0;
//////		xypAB[j] = 0;
//////		for (int i = 0; i < rowe; i++)
//////		{
//////			pixval = abEdgeImg.at<uchar>(i, j);
//////			if (pixval > maxval)
//////			{
//////				maxval = pixval;
//////				xypAB[j] = i;
//////			}
//////		}
//////	}
//////}
//////
//////
//////// Y�ᣨ�У�ƫ��������  
//////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
//////{
//////	int locRow = 0;
//////	int  offset = 1;  // ��߽�ƫ����       ///offset�����ڼ���߽��ƫ���������ȸ����ҵı߽���ƫ���٣��� �����Ǽ��������locRow��ƫ�ƣ� �����߽�ͼ��ƫ�ƶ���
//////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//////	// �������±�Ե����
//////
//////	int rowroiAB = srcImg.rows;
//////	int colroiAB = srcImg.cols;
//////	int roweAB = rowroiAB - 2 * offset;
//////	int coleAB = colroiAB - 2 * offset;
//////	// ��ȡ���±�Եͼ
//////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//////	imshow("��һ����Եͼ", abEdgeImg);
//////
//////	// �ҵ����±�Եλ��     
//////	vector<int>     xypABsrc(coleAB);
//////	ROIComABPlace(abEdgeImg, xypABsrc);
//////
//////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//////	// �������±�Ե����
//////	// ��ȡ���±�Եͼ
//////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//////	imshow("�ڶ�����Եͼ", abEdgeImg);
//////
//////	// �ҵ����±�Եλ��     
//////	vector<int>     xypABdetect(coleAB);
//////	ROIComABPlace(abEdgeImg, xypABdetect);
//////
//////	//------ ����ƫ�� ------
//////	//int locRow = 0; 
//////	locRow = 0;
//////	for (int i = 0; i < coleAB; i++)
//////	{
//////		locRow = locRow + xypABsrc[i] - xypABdetect[i];
//////	}
//////	locRow = int(0.5 + float(locRow) / float(coleAB));
//////	return locRow;
//////}
//////
//////// �ұ�Եͼ������λ��  
//////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
//////{
//////	int rowe = lrEdgeImg.rows;
//////	int cole = lrEdgeImg.cols;
//////
//////	// �ҵ����ұ�Եλ��
//////	//vector<int>     xypLR(rowe);  
//////	int pixval = 0;
//////	int maxval = 0;
//////	for (int i = 0; i < rowe; i++)
//////	{
//////		maxval = 0;
//////		xypLR[i] = 0;
//////		for (int j = 0; j < cole; j++)
//////		{
//////			pixval = lrEdgeImg.at<uchar>(i, j);
//////			if (pixval > maxval)
//////			{
//////				maxval = pixval;
//////				xypLR[i] = j;
//////			}
//////		}
//////	}
//////}
//////
//////// X�ᣨ�У�ƫ��������  	// �ƶ�X�ᣨ�У�  
//////int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
//////	int locCol = 0;
//////	int  offset = 1;  // ��߽�ƫ����    
//////	// ------ ��ȡԭͼ�Ķ�λ��Ϣ ------      
//////	// �������ұ�Ե����
//////	int rowroiLR = srcImg.rows;
//////	int colroiLR = srcImg.cols;
//////	int roweLR = rowroiLR - 2 * offset;
//////	int coleLR = colroiLR - 2 * offset;
//////	// ��ȡ���ұ�Եͼ
//////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//////	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//////	imshow("���ҵ�һ��Եͼ", lrEdgeImg);
//////
//////	// �ҵ����ұ�Եλ��     
//////	vector<int>     xypLRsrc(roweLR);
//////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//////
//////
//////	// ------ ��ȡ�����ͼ��λ��Ϣ ------      
//////	// �������ұ�Ե����  
//////	// ��ȡ���ұ�Եͼ
//////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//////	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//////	imshow("���ҵڶ�����Եͼ", lrEdgeImg);
//////
//////	// �ҵ����ұ�Եλ��     
//////	vector<int>     xypLRdetect(roweLR);
//////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//////
//////	//------ ����ƫ�� ------
//////	//int locCol = 0; 
//////	locCol = 0;
//////	for (int i = 0; i < roweLR; i++)
//////	{
//////		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
//////	}
//////	locCol = int(0.5 + float(locCol) / float(roweLR));
//////
//////	return locCol;
//////}
//////
//////// ��λ����
//////Mat ROIComLocation(Mat srcImg, Mat detectImg)
//////{
//////	Mat detectImg_move;
//////	//// ���ǰ��ʼ��λ      
//////	int offsetx = 0;
//////	int offsety = 0;
//////	int grayTh = 50;
//////
//////	// �ƶ�X�ᣨ�У�  ����   
//////	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
//////	cout << offsetx << endl;
//////
//////	// �ƶ�Y�ᣨ�У�  �ϡ���   
//////	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
//////	cout << offsety << endl;
//////
//////	detectImg_move = imgTranslate(detectImg, offsetx, offsety, 1);
//////	imshow("ƽ�ƴ����ͼƬ", detectImg_move);
//////	imwrite("D:\\roiImgForTest\\move.jpg", detectImg_move);
//////	return detectImg_move;
//////}
//////
////////�����ػ��������ַ������������ƫ�������ԡ�
////////��Ҫ����������ǣ�ƽ��֮��ͼ��϶���Ҫ��չ���ⲿ����ô���������Զ���չ��
//////
//////int detectThr = 500;
//////
//////// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
//////bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
//////{
//////	bool  m_resultDetectCom = 0;
//////	//// �ȽϷ�ʶ��ȱ�ݴ���  
//////
//////	// ����Դͼ�񼰴����ͼ��ı�Եͼ��
//////	int  safePix = 9;      // ��ȫ���ظ���    
//////	int  numModel = 5;     // ɨ��ģ���С  
//////	int dataSafe = int(float(numModel*numModel) / 2);
//////	//int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
//////	int grayTh_1 = 50;
//////	int grayTh_2 = 30;
//////	int  numDetectTh = detectThr;   // ����ͬ���ظ���  
//////
//////	//// ��ͼ�����ͼ��  
//////	int row = detectImg.rows;
//////	int col = detectImg.cols;
//////
//////	///////////////////////////////////////////////
//////	int offset = 1;  // ��߽�ƫ����
//////	int rowe = row - 2 * offset;
//////	int cole = col - 2 * offset;
//////
//////	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//////	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//////
//////	ROIComEdge(detectImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//////	imshow("ok��Եͼ", edgeImgSrc);
//////
//////	////////////////////////////////////////////////
//////	// ����ͼ���Ե  
//////	ROIComEdge(srcImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
//////	imshow("ng��Եͼ", edgeImgDetect);
//////	////////////////////////////////////////////////
//////	// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
//////	// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
//////	// --- ��5*5ģ��ȥɨ�裬 
//////	// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
//////	// --- ���ظ���С��10��ȥ����������0     
//////	// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
//////	////////////////////////////////////////////////
//////	// 1 ��Դͼ���Ե�������ð�ȫ��Χ
//////	// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
//////	Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//////	Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
//////	for (int i = 1; i < rowe; i++)
//////	{
//////		for (int j = 1; j < cole; j++)
//////		{
//////			if (edgeImgSrc.at <uchar>(i, j) > 0)
//////			{
//////				edgeImgSrcTh.at <uchar>(i, j) = 255;
//////			}
//////			if (edgeImgDetect.at <uchar>(i, j) > 0)
//////			{
//////				edgeImgDetectTh.at <uchar>(i, j) = 255;
//////			}
//////		}
//////	}
//////	////////////////////////////////////////////////
//////	// �����ͷ�����չ��Ե������
//////	//��ȡ�Զ����
//////	//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//////	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//////	//���Ͳ���
//////	Mat edgeImgSafe;
//////	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//////	// ��ɫ���ҹ�һ����[0, 1]; 
//////	edgeImgSafe = (255 - edgeImgSafe) / 255;
//////
//////	////////////////////////////////////////////////
//////	// 2 ������Եͼ�����
//////	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//////	imshow("������", edgeImgSub);
//////
//////	////////////////////////////////////////////////
//////	// ��5*5ģ��ȥɨ�裬 
//////	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//////	int resultNum = 0;
//////	int dataTem = 0;
//////	int dataZong = 0;
//////	int dataNum = 0;
//////
//////	//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
//////	for (int i = numModel; i < rowe - numModel; i++)
//////	{
//////		for (int j = numModel; j < cole - numModel; j++)
//////		{
//////			dataTem = 0;
//////			dataZong = 0;
//////			dataNum = 0;
//////			for (int m = 0; m < numModel; m++)
//////			{
//////				for (int n = 0; n < numModel; n++)
//////				{
//////					dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//////					if (dataTem > 0)
//////					{
//////						dataZong = dataZong + 1;
//////					}
//////				}
//////			}
//////			if (dataZong > dataSafe)
//////			{
//////				//ֻҪ�в�ͬ�����������ģ����Ҳ�ֻ�����ǲ�ͬ�ĵط�������Ҫ�Ǳ߽磬�߽�û�غϣ��к�㣬�Ǿͱ�ʾ��Ƭ��
//////				//resultImg.at<uchar>(i, j) = 255;
//////				resultImg.at<Vec3b>(i, j)[0] = 0;
//////				resultImg.at<Vec3b>(i, j)[1] = 0;
//////				resultImg.at<Vec3b>(i, j)[2] = 255;
//////
//////				//showImg.at<Vec3b>(m, n)[2] = 255;
//////				resultNum++;
//////			}
//////		}
//////	}
//////	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
//////	imshow("�˲����", resultImg);
//////	////////////////////////////////////////////////
//////
//////	//��ͨ������ͨ��һ��Ҫ�ֿ�����Ȼ�����׳���
//////	// ��ͬ���������ĵ���Ϊ��ɫ  
//////	Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
//////	//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//////	for (int i = offset; i<row - offset; i++)
//////	{
//////		for (int j = offset; j < col - offset; j++)
//////		{
//////			resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
//////			if (resultImgTem.at<uchar>(i, j) == 255)
//////			{
//////				for (int m = 0; m < offset; m++)
//////				{
//////					for (int n = 0; n < offset; n++)
//////					{
//////						//cv::Point centerPoint, int rectWidth, int rectHeight,
//////						showImg.at<Vec3b>(m, n)[0] = 0;
//////						showImg.at<Vec3b>(m, n)[1] = 0;
//////						showImg.at<Vec3b>(m, n)[2] = 255;
//////					}
//////				}
//////			}
//////		}
//////	}
//////
//////	//imshow("���չʾ", showImg);
//////	////////////////////////////////////////////////
//////	// ����ֵ>0����NG�� ����ֵ=0, ��OK 
//////	if (resultNum <= numDetectTh)
//////	{
//////		m_resultDetectCom = 1;  // OK  
//////	}
//////	else
//////	{
//////		m_resultDetectCom = 0;  // NG    
//////	}
//////	return  m_resultDetectCom;
//////}
//////
//////int main(){
//////
//////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG", 0);
//////	//imshow("ԭͼ", srcImg);
//////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
//////	//imshow("�����ͼ", detectImg);
//////
//////	Mat detectMove;
//////
//////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
//////
//////	//�õ�ͼ���ȵ�ƽ����ȡƫ������ ��ƽ��
//////	detectMove = ROIComLocation(srcImg, detectImg);
//////
//////	bool flag = 0;
//////	flag = ROIComDetectMethod(srcImg, detectMove, showImg);
//////	if (flag == 0){
//////		cout << "ngͼƬ" << endl;
//////	}
//////	else{
//////		cout << "����okͼƬ" << endl;
//////	}
//////
//////	waitKey(0);
//////	system("pause");
//////	return 0;
//////}