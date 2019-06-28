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
//	// 判断是否改变图像大小,并设定被复制ROI 
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
//	// 修正输出的ROI 
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
//	// 复制图像 
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
//// 找边缘图像上下位置  
//void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
//{
//	int rowe = abEdgeImg.rows;
//	int cole = abEdgeImg.cols;
//
//	Mat resultImg = Mat::zeros(rowe, cole, CV_8UC3);
//
//	// 找到上下边缘位置
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
//	//imshow("上下边缘图", resultImg);
//}
//
//
//// Y轴（行）偏移量计算  
//int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
//{
//	int locRow = 0;
//	int  offset = 1;  // 求边界偏移量       ///offset是用于计算边界的偏移量（事先给定我的边界大概偏多少）， 而我们计算出来的locRow是偏移， 两个边界图像偏移多少
//	// ------ 获取原图的定位信息 ------      
//	// 剪切上下边缘区域
//
//	int rowroiAB = srcImg.rows;
//	int colroiAB = srcImg.cols;
//	int roweAB = rowroiAB - 2 * offset;
//	int coleAB = colroiAB - 2 * offset;
//	// 获取上下边缘图
//	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//	//imshow("第一个边缘图", abEdgeImg);
//
//	// 找到上下边缘位置     
//	vector<int>     xypABsrc(coleAB);
//	ROIComABPlace(abEdgeImg, xypABsrc);
//
//	// ------ 获取待检测图像定位信息 ------      
//	// 剪切上下边缘区域
//	// 获取上下边缘图
//	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//	//imshow("第二个边缘图", abEdgeImg);
//
//	// 找到上下边缘位置     
//	vector<int>     xypABdetect(coleAB);
//	ROIComABPlace(abEdgeImg, xypABdetect);
//
//	//------ 计算偏移 ------
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
////这种找上下左右边缘的方法，我觉得会有误差，因为找到的最大值不一定是同一个边缘上的，
////那么不同的图片找到的最大值在上下边缘的情况也不尽相同，很有可能是上边缘的点减去下边缘的点求出的偏移量，
////这样就有很大偏差， 即使相加求平均，影响还是会有的
////不知道对不对？？？
//
////还是说我的平移方法有问题？？？
//
//// 找边缘图像左右位置  
//void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
//{
//	int rowe = lrEdgeImg.rows;
//	int cole = lrEdgeImg.cols;
//
//	// 找到左右边缘位置
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
//				//问题是，这一列下来会有很多边界，但是找一个最大值，只是找到其中一个边界，万一不在同一条边界上怎么办？
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
//	//imshow("左右边缘图", resultImg);   //从图像来看基本上找的就是第一条线
//}
//
//// X轴（列）偏移量计算  	// 移动X轴（列）  
//int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
//	int locCol = 0;
//	int  offset = 1;  // 求边界偏移量    
//	// ------ 获取原图的定位信息 ------      
//	// 剪切左右边缘区域
//	int rowroiLR = srcImg.rows;
//	int colroiLR = srcImg.cols;
//	int roweLR = rowroiLR - 2 * offset;
//	int coleLR = colroiLR - 2 * offset;
//	// 获取左右边缘图
//	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//	//imshow("左右第一边缘图", lrEdgeImg);
//
//	// 找到左右边缘位置     
//	vector<int>     xypLRsrc(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//
//
//	// ------ 获取待检测图像定位信息 ------      
//	// 剪切左右边缘区域  
//	// 获取左右边缘图
//	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//	//imshow("左右第二个边缘图", lrEdgeImg);
//
//	// 找到左右边缘位置     
//	vector<int>     xypLRdetect(roweLR);
//	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//
//	//------ 计算偏移 ------
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
//// 定位函数
//Mat ROIComLocation(Mat srcImg, Mat detectImg)
//{
//	Mat detectImg_move;
//	//// 检测前开始定位      
//	int offsetx = 0;
//	int offsety = 0;
//	int grayTh = 50;
//	
//	// 移动X轴（列）  左、右   
//	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
//	cout << offsetx << endl;
//
//		// 移动Y轴（行）  上、下   
//	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
//	cout << offsety << endl;
//	////猜测是不是Y轴偏移量太大就会出错
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
//	imshow("平移待检测图片", detectImg_move);
//	//imwrite("D:\\roiImgForTest\\move.jpg", detectImg_move);
//	//waitKey(0);
//	return detectImg_move;
//}
//
////我严重怀疑用这种方法计算出来的偏移量不对。
////需要解决的问题是，平移之后图像肯定需要扩展，这部分怎么修正，会自动扩展吗？
//
//// Com--Detect Method   比较图像边缘痕迹   
//bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
//{
//	bool  m_resultDetectCom = 0;
//	//// 比较法识别缺陷代码  
//
//	// 计算源图像及待检测图像的边缘图像
//	int  safePix = 9;      // 安全像素个数   9 
//	int  numModel = 5;     // 扫描模板大小  
//	int dataSafe = int(float(numModel*numModel) / 2);
//	//int grayTh = int(255 / 3);  // 计算图像边缘阈值  
//	int grayTh_1 = 50;
//	int grayTh_2 = 30;
//	int  numDetectTh = detectThr;   // 允许不同像素个数  
//
//	//// 截图待检测图像  
//	int row = detectImg.rows;
//	int col = detectImg.cols;
//
//	//平移之后图像大小不同，但是这里处理的是变换后的图像，需要修改？？？
//
//
//	///////////////////////////////////////////////
//	int offset = 1;  // 求边界偏移量
//	int rowe = row - 2 * offset;
//	int cole = col - 2 * offset;
//
//	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//
//	ROIComEdge(srcImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//	//imshow("ok边缘图", edgeImgSrc);
//
//	////////////////////////////////////////////////
//	// 计算图像边缘  
//	ROIComEdge(detectImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
//	//imshow("ng边缘图", edgeImgDetect);
//	////////////////////////////////////////////////
//	// ---------- 方法一 两图的边缘图像相减 ----------
//	// --- 在边缘位置设置安全范围，留下不同的像素点  
//	// --- 用5*5模板去扫描， 
//	// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//	// --- 像素个数小于10，去除，计数加0     
//	// --- 计数值>0，则NG； 计数值=0, 则OK     
//	////////////////////////////////////////////////
//	// 1 沿源图像边缘区域设置安全范围
//	// 把边缘图像变成二值化图像   
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
//	// 用膨胀法，扩展边缘亮区域
//	//获取自定义核
//	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//	//膨胀操作
//	Mat edgeImgSafe;
//	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//	imshow("pengzhang", edgeImgSafe);
//	//waitKey(0);
//
//	imshow("fanseqian", edgeImgSafe);
//
//	// 反色，且归一化到[0, 1]; 
//	edgeImgSafe = (255 - edgeImgSafe) / 255;   //反色操作有什么效果，还没搞清楚
//	imshow("safe", edgeImgSafe);
//	//waitKey(0);
//
//	////////////////////////////////////////////////
//	// 2 两幅边缘图像相减
//	//Mat edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//	//imshow("相减结果", edgeImgSub);
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
//	////----------------->二值化<-------------------------------------------------------------
//	Mat thr_img;
//	threshold(diff_dst, thr_img, 10, 250, CV_THRESH_BINARY);  ///180, 255
//	//imshow("erzhihua", thr_img);
//	imwrite("D:\\roiImage_2\\sample3\\save\\erzhihua.jpg", thr_img);
//		
//	//cvtColor(thr_img, thr_img, CV_BGR2GRAY);  
//	
//	//图像反色
//	//thr_img = fanse(thr_img);
//	
//	////----------------->开运算<-----------------------
//	//morph(thr_img);
//	
//	////----------------->裁剪回原尺寸<---------------------------
//	/*Rect m_select = Rect(EXTD_EDGE, EXTD_EDGE, img_src_ok.cols, img_src_ok.rows);
//	Mat ROI = morph_out(m_select);*/
//	//imshow("剪裁图", ROI);
//	
//	////----------------->画轮廓，圈出缺陷，首先转换成彩色图像就能画颜色框了
//	//draw_contour(ROI);
//
//
//	////////////////////////////////////////////////
//	// 用5*5模板去扫描， 
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
//				//只要有不同，都会标出来的，而且不只是它们不同的地方，最主要是边界，边界没重合，有红点，那就表示坏片。
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
//	//cvtColor(resultImg, resultImg, CV_GRAY2BGR);
//	imshow("滤波结果", resultImg);   ///滤波结果其实保留的是原图， 然后与detect图重合的部分不显示
//	imwrite("D:\\roiImgForTest\\ngSave\\result.jpg", resultImg);
//	//waitKey(0);
//	////////////////////////////////////////////////
//
//	//单通道，多通道一定要分开，不然很容易出错。
//	// 不同的区域，中心点标记为红色  
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
//	//imshow("差别展示", showImg);
//	////////////////////////////////////////////////
//	// 计数值>0，则NG； 计数值=0, 则OK 
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
//	//imshow("原图", srcImg);
//	//imshow("待检测图", detectImg);
//
//	Mat showImg = imread("D:\\oldSample\\sample1\\ok\\1.jpg");
//
//	//拿到图像先调平，获取偏移量， 再平移
//	Mat detectMove = ROIComLocation(srcImg, detectImg);
//	
//	String strImg;
//
//	bool flag = 0;
//	flag = ROIComDetectMethod(srcImg, detectMove, showImg);
//	if (flag == 0){
//		cout << "ng图片" << endl;
//		strImg = format("D:\\roiImgForTest\\ngSave\\ng%02d.jpg", i);
//		imwrite(strImg, resultImg);
//		ng_num++;
//	}
//	else{
//		strImg = format("D:\\roiImgForTest\\okSave\\ok%02d.jpg", i);
//		cout << "这是ok图片" << endl;
//		imwrite(strImg, resultImg);
//	}
//
//	return ng_num;
//}
//
////目前记录的检测一张图片的时间
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
//	Mat element = getStructuringElement(MORPH_RECT, Size(18, 18)); //具体要选择哪种操作，就修改第三个参数就可以了。这里演示的是形态学开运算处理 
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
//	Mat drawing = Mat::zeros(canny_out.size(), CV_8UC3);
//	for (int i = 0; i < g_vContours.size(); i++) {
//		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
//		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
//	}
//	imshow("缺陷轮廓图", drawing);
//	imwrite("D:\\roiImage_2\\sample3\\save\\drawing.jpg", drawing);
//
//	//num_contours = g_vContours.size();
//}
//
//////////////////////////////////////////////////////以上为测试专用////////////////////////////
//
//
//
//
//
////// 找边缘图像上下位置  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////	imwrite("D:/roiImage/25 abEdgeImg.jpg", abEdgeImg);   //////   
////
////	// 找到上下边缘位置
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
////// 找边缘图像左右位置  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////	imwrite("D:/roiImage/15 lrEdgeImg.jpg", lrEdgeImg);   //////   
////
////	// 找到左右边缘位置
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
////// Y轴（行）偏移量计算  
////void ROIComLocationY(Mat &srcImg, Mat &detectImg, int &locRow)
//////, int grayTh, cv::Point centerPointAB, int rectWidthAB, int rectHeightAB, int rectRotAngleAB)
////{
////	int  offset = 1;  // 求边界偏移量    
////	// ------ 获取原图的定位信息 ------      
////	// 剪切上下边缘区域
////	cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);   
////	ROIRotateImage(srcImg, centerPointAB, rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);  
////	int rowroiAB = roiImgAB.rows;
////	int colroiAB = roiImgAB.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// 获取上下边缘图
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);   
////	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);        
////	imwrite("D:/roiImage/21 roiImgAB.jpg", roiImgAB);   //////  
////	imwrite("D:/roiImage/22 abEdgeImg.jpg", abEdgeImg);   //////  
////	String  strImg;
////	strImg = format("D:/roiImage/21 roiImgABSrc/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgAB);
////	
////	// 找到上下边缘位置     
////	vector<int>     xypABsrc(coleAB);      
////	ROIComABPlace(abEdgeImg, xypABsrc);    
////	
////	// ------ 获取待检测图像定位信息 ------      
////	// 剪切上下边缘区域
////	ROIRotateImage(detectImg, cv::Point(centerPointAB.x - locCol, centerPointAB.y), rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);
////	// 获取上下边缘图
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
////	imwrite("D:/roiImage/23 roiImgAB.jpg", roiImgAB);     //////  
////	imwrite("D:/roiImage/24 abEdgeImg.jpg", abEdgeImg);   //////  
////	strImg = format("D:/roiImage/23 roiImgABDetect/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgAB);
////	
////	// 找到上下边缘位置     
////	vector<int>     xypABdetect(coleAB);     
////	ROIComABPlace(abEdgeImg, xypABdetect);   
////	
////	//------ 计算偏移 ------
////	//int locRow = 0; 
////	locRow = 0;  
////	for (int i = 0; i < coleAB; i++)
////	{
////		locRow = locRow + xypABsrc[i] - xypABdetect[i];   
////	}
////	locRow = int(0.5 + float(locRow) / float(coleAB));     
////}
////
//////用直线检测方法就，就不需要确定上下边界， 那反过来呢
//////因为计算直线的方法一样，所以，好像用了确定边缘的方法，就不需要再添加检测直线的方法了
////
////// X轴（列）偏移量计算  	// 移动X轴（列）  
////void ROIComLocationX(Mat &srcImg, Mat &detectImg, int &locCol){
////	//DistRectDetectOne(srcImg, detectThreshold, detectDirection);    //因为从distrectdetectone可以计算出坐标点，所以这里直接获取坐标点，就能确定偏移量了
////	//DistRectDetectOne(detectImg, detectThreshold, detectDirection);    //沿同一方向分别检测原图与待检测图的同一条直线，计算两直线的距离，就是偏移量
////
////	int  offset = 1;  // 求边界偏移量    
////	// ------ 获取原图的定位信息 ------      
////	// 剪切左右边缘区域
////	cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
////	ROIRotateImage(srcImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	int rowroiLR = roiImgLR.rows;
////	int colroiLR = roiImgLR.cols;
////	int roweLR = rowroiLR - 2 * offset;  
////	int coleLR = colroiLR - 2 * offset;  
////	// 获取左右边缘图
////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);  
////	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);  
////	imwrite("D:/roiImage/11 roiImgLR.jpg", roiImgLR);   //////  
////	imwrite("D:/roiImage/12 lrEdgeImg.jpg", lrEdgeImg);   //////  
////	String  strImg;   
////	strImg = format("D:/roiImage/11 roiImgLRSrc/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgLR);
////	
////	// 找到左右边缘位置     
////	vector<int>     xypLRsrc(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
////	
////	// ------ 获取待检测图像定位信息 ------      
////	// 剪切左右边缘区域  
////	ROIRotateImage(detectImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	// 获取左右边缘图
////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
////	imwrite("D:/roiImage/13 roiImgLR.jpg", roiImgLR);   //////     
////	imwrite("D:/roiImage/14 lrEdgeImg.jpg", lrEdgeImg);   //////   
////	strImg = format("D:/roiImage/13 roiImgLRDetect/%05d.jpg", countROIImage);
////	imwrite(strImg, roiImgLR);
////	
////	// 找到左右边缘位置     
////	vector<int>     xypLRdetect(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
////	
////	//------ 计算偏移 ------
////	//int locCol = 0; 
////	locCol = 0;  
////	for (int i = 0; i < roweLR; i++)
////	{
////		locCol = locCol + xypLRsrc[i] - xypLRdetect[i];
////	}
////	locCol = int(0.5 + float(locCol) / float(roweLR));   
////}
////
////// 定位函数
////void ROIComLocation(Mat &srcImg, Mat &showImg)
////{
////	//// 检测前开始定位      
////	//if (1 == m_flagComDetect)
////	{
////
////		// 读入源整幅图像    
////		Mat  comOKsrcImgTotal = imread("D:/roiImage/comOKsrcImgTotal.jpg", 0);
////		// 现有的整幅图像    
////		Mat  detectImgTotal = srcImg;
////
////
////		// 移动检测框并计算待检测图像
////		locRow = 0;
////		locCol = 0;
////		locRotAngle = 0;
////
////
////		//只需要根据这两个函数找出偏移量， 再根据下面的几句代码来平移图像即可。
////		// 移动X轴（列）  左、右   
////		ROIComLocationX(comOKsrcImgTotal, detectImgTotal, locCol);
////
////		// 移动Y轴（行）  上、下   
////		ROIComLocationY(comOKsrcImgTotal, detectImgTotal, locRow);
////
////		//找到偏移量， 根据偏移量来移动工具框， 上下左右平移，但是现在不需要，只要移动图片
////
////		// 沿X轴（列）移动主框、左右框、上下框  
////		//这里是中心点减去locCol, 或者locRow就可以实现平移， 因为框的位置变了就相当于图像平移了
////		
////		// 沿Y轴（列）移动主框、左右框、上下框  
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
////////////////源代码/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////// 定位函数
////void ROIComLocation(Mat &srcImg, Mat &showImg);
////
////// X轴（列）偏移量计算  	// 移动X轴（列）  
////void ROIComLocationX(Mat &srcImg, Mat &detectImg, int &locCol);
////
////// Y轴（行）偏移量计算  
////void ROIComLocationY(Mat &srcImg, Mat &detectImg, int &locRow);
////
////// 找边缘图像上下位置  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB);
////
////// 找边缘图像左右位置  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR);
////
//////检测直线
////bool  DistRectDetectOne(Mat &srcImg, Point centerPoint, int rectWidth,
////	int rectHeight, int detectThreshold, int detectDirection,
////	float& x1CenterPoint, float& y1CenterPoint, int Red, int Green, int Blue);
////
//////检测直线方法
////bool  LineDetectMethod(Mat &srcImg, int detectThreshold,
////	int detectDirection, float &aLine, float &bLine, float &cLine);
////
////// Com--Detect Method   比较图像边缘痕迹   
////bool ROIComDetectMethod(Mat &srcImg, Mat &showImg, cv::Point centerPoint,
////	int rectWidth, int rectHeight, int rectRotAngle, int detectThr);
////
//////差分法求边缘
////void ROIComEdge(Mat &srcImg, Mat &edgeImg, int offset, int grayTh);
////
////
////int main(){
////
////	Mat src = imread("D:\\roiImage_2\\sample6\\4.JPG");
////	Mat ng_img = imread("D:\\roiImage_2\\sample6\\9.JPG");
////
////	//定位，就是为了让位置重合
////	ROIComLocation();
////
////	//开始检测，也就是比较方法
////	bool m_DetectResultFinal = ROIComDetectMethod();
////
////	// 显示结果
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
////// Com--Detect Method   比较图像边缘痕迹   
////bool ROIComDetectMethod(Mat &srcImg, Mat &showImg, Point centerPoint,
////	int rectWidth, int rectHeight, int detectThr)
////{
////	bool  m_resultDetectCom = 0;
////	//// 比较法识别缺陷代码  
////	//if (1 == m_flagComDetect)  
////	{
////		// 计算源图像及待检测图像的边缘图像
////		int  safePix = 9;      // 安全像素个数    
////		int  numModel = 5;     // 扫描模板大小  
////		int dataSafe = int(float(numModel*numModel) / 2);
////		int grayTh = int(255 / 3);  // 计算图像边缘阈值  
////		int  numDetectTh = detectThr;   // 允许不同像素个数  
////		//countROIImage++;
////		//// 待检测整张图像  
////		Mat  detectImgTotal = srcImg.clone();
////		//// 截图待检测图像  
////		cv::Mat detectImg(rectHeight, rectWidth, CV_8UC1);
////		ROIRotateImage(AdjustImage[camIndex], centerPoint, rectWidth, rectHeight, rectRotAngle, detectImg);
////		int row = detectImg.rows;
////		int col = detectImg.cols;
////		////////////////////////////////////////////////
////		// 读入源图像    
////		String strImg = format("D:/roiImage/%02d.jpg", distIndex);
////		Mat  ImgOK = imread(strImg, 0);
////		//imwrite("D:/roiImage/0 ImgOK.jpg", ImgOK);   //////  
////		//imwrite("D:/roiImage/0 detectImg.jpg", detectImg);   //////  
////		//strImg = format("D:/roiImage/0 ImgOk/%05d.jpg", countROIImage);
////		//imwrite(strImg, ImgOK);
////		//strImg = format("D:/roiImage/0 detectImg/%05d.jpg", countROIImage);
////		//imwrite(strImg, detectImg);
////		///////////////////////////////////////////////
////		int offset = 1;  // 求边界偏移量
////		int rowe = row - 2 * offset;
////		int cole = col - 2 * offset;
////		Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
////		Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
////		ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
////		//imwrite("D:/roiImage/1 edgeImgSrc.jpg", edgeImgSrc);   //////  
////		//strImg = format("D:/roiImage/1 edgeImgSrc/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgSrc);  
////		////////////////////////////////////////////////
////		// 计算图像边缘  
////		ROIComEdge(detectImg, edgeImgDetect, offset, grayTh);
////		//imwrite("D:/roiImage/2 edgeImgDetect.jpg", edgeImgDetect);   //////  
////		//strImg = format("D:/roiImage/2 edgeImgDetect/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgDetect);
////		////////////////////////////////////////////////
////		// ---------- 方法一 两图的边缘图像相减 ----------
////		// --- 在边缘位置设置安全范围，留下不同的像素点  
////		// --- 用5*5模板去扫描， 
////		// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
////		// --- 像素个数小于10，去除，计数加0     
////		// --- 计数值>0，则NG； 计数值=0, 则OK     
////		////////////////////////////////////////////////
////		// 1 沿源图像边缘区域设置安全范围
////		// 把边缘图像变成二值化图像   
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
////		// 用膨胀法，扩展边缘亮区域
////		//获取自定义核
////		//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////		Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
////		//膨胀操作
////		Mat edgeImgSafe;
////		dilate(edgeImgSrc, edgeImgSafe, elementSafe);
////		// 反色，且归一化到[0, 1]; 
////		edgeImgSafe = (255 - edgeImgSafe) / 255;
////		//imwrite("D:/roiImage/4 edgeImgSafe.jpg", edgeImgSafe*255);   //////  
////		//strImg = format("D:/roiImage/4 edgeImgSafe/%05d.jpg", countROIImage);
////		//imwrite(strImg, edgeImgSafe);  
////		////////////////////////////////////////////////
////		// 2 两幅边缘图像相减
////		Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
////		//imwrite("D:/roiImage/5 edgeImgSub.jpg", edgeImgSub);   //////     
////		//strImg = format("D:/roiImage/5 edgeImgSub/%05d.jpg", countROIImage);   
////		//imwrite(strImg, edgeImgSub);      
////		////////////////////////////////////////////////
////		// 用5*5模板去扫描， 
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
////		// 不同的区域，中心点标记为红色  
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
////		// 计数值>0，则NG； 计数值=0, 则OK 
////		if (resultNum <= numDetectTh)
////		{
////			m_resultDetectCom = 1;  // OK  
////		}
////		else
////		{
////			m_resultDetectCom = 0;  // NG    
////		}
////		////////////////////////////////////////////////
////		//countROIImage = countROIImage % 10000;   // 存图计数  
////	}
////	return  m_resultDetectCom;
////}
////
////void ROIComEdge(Mat &srcImg, Mat &edgeImg, int offset, int grayTh)
////{
////	int row = srcImg.rows;
////	int col = srcImg.cols;
////	//int offset = 1;  // 求边界偏移量
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////	//int grayTh = int(255 / 4);  
////
////	// 处理第 1 幅图像
////	// 差分法求边缘		
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
////	// 把边缘图像像素值映射到[0, 255]
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
////	// 把边缘图像，去掉过小的边缘  	
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
////// 定位函数
////void ROIComLocation(Mat &srcImg, Mat &showImg)
////{
////	//// 检测前开始定位      
////	//if (1 == m_flagComDetect)
////	{
////
////		// 读入源整幅图像    
////		Mat  comOKsrcImgTotal = imread("D:/roiImage/comOKsrcImgTotal.jpg", 0);
////		// 现有的整幅图像    
////		Mat  detectImgTotal = srcImg;
////
////
////		// 移动检测框并计算待检测图像
////		locRow = 0;
////		locCol = 0;
////		locRotAngle = 0;
////
////		// 移动X轴（列）  左、右   
////		ROIComLocationX(comOKsrcImgTotal, detectImgTotal, locCol);
////
////		// 移动Y轴（行）  上、下   
////		ROIComLocationY(comOKsrcImgTotal, detectImgTotal, locRow);
////
////		// 沿X轴（列）移动主框、左右框、上下框  
////		stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART].stLineDistance[1].nxCenter - locCol;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 1].stLineDistance[1].nxCenter - locCol;
////		stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[0].nxCenter =
////			stCamera[camIndex].stDistance[TOTALDETECTSTART + 2].stLineDistance[1].nxCenter - locCol;
////		// 沿Y轴（列）移动主框、左右框、上下框  
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
////// X轴（列）偏移量计算  	// 移动X轴（列）  
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
////	//int  offset = 1;  // 求边界偏移量    
////	//// ------ 获取原图的定位信息 ------      
////	//// 剪切左右边缘区域
////	//cv::Mat roiImgLR = Mat::zeros(rectHeightLR, rectWidthLR, CV_8UC1);
////	//ROIRotateImage(srcImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	//int rowroiLR = roiImgLR.rows;
////	//int colroiLR = roiImgLR.cols;
////	//int roweLR = rowroiLR - 2 * offset;  
////	//int coleLR = colroiLR - 2 * offset;  
////	//// 获取左右边缘图
////	//Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);  
////	//ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);  
////	//imwrite("D:/roiImage/11 roiImgLR.jpg", roiImgLR);   //////  
////	//imwrite("D:/roiImage/12 lrEdgeImg.jpg", lrEdgeImg);   //////  
////	//String  strImg;   
////	//strImg = format("D:/roiImage/11 roiImgLRSrc/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgLR);
////
////	//// 找到左右边缘位置     
////	//vector<int>     xypLRsrc(roweLR);
////	//ROIComLRPlace(lrEdgeImg, xypLRsrc);
////
////
////	//// ------ 获取待检测图像定位信息 ------      
////	//// 剪切左右边缘区域  
////	//ROIRotateImage(detectImg, centerPointLR, rectWidthLR, rectHeightLR, rectRotAngleLR, roiImgLR);
////	//// 获取左右边缘图
////	//lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	//ROIComEdge(roiImgLR, lrEdgeImg, offset, grayTh);
////	//imwrite("D:/roiImage/13 roiImgLR.jpg", roiImgLR);   //////     
////	//imwrite("D:/roiImage/14 lrEdgeImg.jpg", lrEdgeImg);   //////   
////	//strImg = format("D:/roiImage/13 roiImgLRDetect/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgLR);
////
////	//// 找到左右边缘位置     
////	//vector<int>     xypLRdetect(roweLR);
////	//ROIComLRPlace(lrEdgeImg, xypLRdetect);
////
////	////------ 计算偏移 ------
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
////// Y轴（行）偏移量计算  
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
////	//int  offset = 1;  // 求边界偏移量    
////	//// ------ 获取原图的定位信息 ------      
////	//// 剪切上下边缘区域
////	//cv::Mat roiImgAB(rectHeightAB, rectWidthAB, CV_8UC1);   
////	//ROIRotateImage(srcImg, centerPointAB, rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);  
////	//int rowroiAB = roiImgAB.rows;
////	//int colroiAB = roiImgAB.cols;
////	//int roweAB = rowroiAB - 2 * offset;
////	//int coleAB = colroiAB - 2 * offset;
////	//// 获取上下边缘图
////	//Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);   
////	//ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);        
////	//imwrite("D:/roiImage/21 roiImgAB.jpg", roiImgAB);   //////  
////	//imwrite("D:/roiImage/22 abEdgeImg.jpg", abEdgeImg);   //////  
////	//String  strImg;
////	//strImg = format("D:/roiImage/21 roiImgABSrc/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgAB);
////
////	//// 找到上下边缘位置     
////	//vector<int>     xypABsrc(coleAB);      
////	//ROIComABPlace(abEdgeImg, xypABsrc);    
////
////	//// ------ 获取待检测图像定位信息 ------      
////	//// 剪切上下边缘区域
////	//ROIRotateImage(detectImg, cv::Point(centerPointAB.x - locCol, centerPointAB.y), rectWidthAB, rectHeightAB, rectRotAngleAB, roiImgAB);
////	//// 获取上下边缘图
////	//abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	//ROIComEdge(roiImgAB, abEdgeImg, offset, grayTh);
////	//imwrite("D:/roiImage/23 roiImgAB.jpg", roiImgAB);     //////  
////	//imwrite("D:/roiImage/24 abEdgeImg.jpg", abEdgeImg);   //////  
////	//strImg = format("D:/roiImage/23 roiImgABDetect/%05d.jpg", countROIImage);
////	//imwrite(strImg, roiImgAB);
////
////	//// 找到上下边缘位置     
////	//vector<int>     xypABdetect(coleAB);     
////	//ROIComABPlace(abEdgeImg, xypABdetect);   
////
////	////------ 计算偏移 ------
////	////int locRow = 0; 
////	//locRow = 0;  
////	//for (int i = 0; i < coleAB; i++)
////	//{
////	//	locRow = locRow + xypABsrc[i] - xypABdetect[i];   
////	//}
////	//locRow = int(0.5 + float(locRow) / float(coleAB));   
////}
////
////// 找边缘图像上下位置  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////	imwrite("D:/roiImage/25 abEdgeImg.jpg", abEdgeImg);   //////   
////
////	// 找到上下边缘位置
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
////// 找边缘图像左右位置  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////	imwrite("D:/roiImage/15 lrEdgeImg.jpg", lrEdgeImg);   //////   
////
////	// 找到左右边缘位置
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
////	Point2f point4Ver[4];      //定义4个点的数组
////
////	Point  rectLTPoint;
////	rectLTPoint.x = int(point4Ver[1].x);
////	rectLTPoint.y = int(point4Ver[1].y); 
////	
////	// 测距为真，检测直线或圆并测距 
////
////	float atLine = 0.0, btLine = 0.0, ctLine = 0.0;
////
////	bool mLineTest = 1;
////
////	int rectRotAngle = 0;
////	float  rectAngle = rectRotAngle * 2 * 3.141592654 / 360;
////	
////	// 检测直线
////	mLineTest = LineDetectMethod(srcImg, detectThreshold, detectDirection, atLine, btLine, ctLine);
////
////	if (mLineTest == 0)
////	{
////		// 未检测到直线，画方框
////		return false;
////	}
////	else
////	{
////		// 绘制直线
////		Point2f  onePoint2f, twoPoint2f;
////		Point   onePoint, twoPoint;
////		float   edgePoint = 5.0;
////		switch (detectDirection)
////		{
////		case 0:  //从左到右
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
////				// 中心点
////				//x1CenterPoint = int((onePoint2f.y + twoPoint2f.y) / 2);
////				//y1CenterPoint = int((onePoint2f.x + twoPoint2f.x) / 2);
////				onePoint.x = int(onePoint2f.x);
////				onePoint.y = int(onePoint2f.y);
////				twoPoint.x = int(twoPoint2f.x);
////				twoPoint.y = int(twoPoint2f.y);
////				line(srcImg, cv::Point(onePoint), cv::Point(twoPoint), Scalar(0, 0, 255), 3);
////				break;
////			}
////		case 1:  //从右到左
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
////				// 中心点
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
////			//从上到下
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
////				// 中心点
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
////			//从下到上
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
////				// 中心点
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
//////检测直线只能返回true， 或者false， 并且有方向
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
////	// 左右
////	if (detectDirection == 0 || detectDirection == 1)
////	{
////		// 找每列像素值总的变化值  
////		vector<int>  grayVerdiff(col);
////		for (j = 0; j < col; j++)
////		{
////			grayVerdiff[j] = 0;   // 初始化为0
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
////		if (detectDirection == 0)  		// 从左到右  
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
////		else if (detectDirection == 1)  // 从右到左 
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
////		//// 找中心点  
////		//xCenterPoint = int(float(row) / 2);
////		//yCenterPoint = xypix;
////		return true;
////	}
////
////	// 上下边缘  
////	else if (detectDirection == 2 || detectDirection == 3)
////	{
////		// 找每列像素值总的变化值  
////		vector<int>  grayVerdiff(row);
////		for (i = 0; i < row; i++)
////		{
////			grayVerdiff[i] = 0;   // 初始化为0
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
////		if (detectDirection == 2)  //从上到下  
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
////		else if (detectDirection == 3)  // 从下到上  
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
////		//// 找中心点  
////		//yCenterPoint = int(float(col) / 2);
////		//xCenterPoint = xypix;
////		return true;
////	}
////}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
//////相减获取图像边缘的函数
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
////	////int offset = 1;  // 求边界偏移量
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// 处理第 1 幅图像
////	// 差分法求边缘		
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
////	// 把边缘图像像素值映射到[0, 255]
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
////	// 把边缘图像，去掉过小的边缘  	
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
////	imshow("边缘图", edgeImg);
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
////	//int offset = 1;  // 求边界偏移量
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////	//int grayTh = int(255 / 4);  
////
////	//Mat edgeImg = Mat::zeros(rowe, cole, CV_8UC1);
////
////	Mat src_edge = Mat::zeros(rowe, cole, CV_8UC1);
////	ROIComEdge(srcImg, src_edge, offset, grayTh, row, col, rowe, cole);
////	//imshow("原图边缘", src_edge);
////	imwrite("D:\\roiImageForTest\\src_edge.jpg", src_edge);
////
////	Mat ngImg = imread("D:\\roiImage_2\\sample6\\9.JPG");
////	Mat ng_edge;
////	//ROIComEdge(ngImg, ng_edge, offset, grayTh);
////	//imshow("ng边缘", ng_edge);
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
//////计算两个边缘图像的，y轴，偏移量， x轴类似
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
////	////int offset = 1;  // 求边界偏移量
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// 处理第 1 幅图像
////	// 差分法求边缘		
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
////	// 把边缘图像像素值映射到[0, 255]
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
////	// 把边缘图像，去掉过小的边缘  	
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
////	//imshow("边缘图", edgeImg);
////}
////
////// 找边缘图像上下位置  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////
////	// 找到上下边缘位置
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
////// Y轴（行）偏移量计算  
////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
////{
////	int locRow = 0;
////	int  offset = 1;  // 求边界偏移量       ///offset是用于计算边界的偏移量（事先给定我的边界大概偏多少）， 而我们计算出来的locRow是偏移， 两个边界图像偏移多少
////	// ------ 获取原图的定位信息 ------      
////	// 剪切上下边缘区域
////
////	int rowroiAB = srcImg.rows;
////	int colroiAB = srcImg.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// 获取上下边缘图
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("第一个边缘图", abEdgeImg);
////
////	// 找到上下边缘位置     
////	vector<int>     xypABsrc(coleAB);
////	ROIComABPlace(abEdgeImg, xypABsrc);
////
////	// ------ 获取待检测图像定位信息 ------      
////	// 剪切上下边缘区域
////	// 获取上下边缘图
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("第二个边缘图", abEdgeImg);
////
////	// 找到上下边缘位置     
////	vector<int>     xypABdetect(coleAB);
////	ROIComABPlace(abEdgeImg, xypABdetect);
////
////	//------ 计算偏移 ------
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
////	imshow("原图", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\9.JPG");
////	imshow("待检测图", detectImg);
////
////	offsety = ROIComLocationY(srcImg, detectImg, grayThreshold);
////	cout << "y轴偏移量：" << offsety << endl;
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///*/*////123456
////////比较两边缘图像的差异，区分OK，ng给出判断结果
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
////	////int offset = 1;  // 求边界偏移量
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// 处理第 1 幅图像
////	// 差分法求边缘		
////	//Mat edgeImg=Mat::zeros(rowe, cole, CV_8UC1);  
////	for (int i = offset; i < row - offset; i++)
////	{
////		for (int j = offset; j < col - offset; j++)
////		{
////			edgeImg.at<uchar>(i - offset, j - offset) =    //这里总是出错是因为输入的srcImg图像，是三通道的，但是这里需要的单通道，我理解的
////				(abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j - offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i - offset, j + offset)) +
////				abs(srcImg.at<uchar>(i, j) - srcImg.at<uchar>(i + offset, j - offset))) / 4;
////		}
////	}
////	// 把边缘图像像素值映射到[0, 255]
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
////	// 把边缘图像，去掉过小的边缘  	
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
////	//imshow("边缘图", edgeImg);
////}
////
////// Com--Detect Method   比较图像边缘痕迹   
////bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
////{
////	bool  m_resultDetectCom = 0;
////	//// 比较法识别缺陷代码  
////
////	// 计算源图像及待检测图像的边缘图像
////	int  safePix = 9;      // 安全像素个数    
////	int  numModel = 5;     // 扫描模板大小  
////	int dataSafe = int(float(numModel*numModel) / 2);
////	//int grayTh = int(255 / 3);  // 计算图像边缘阈值  
////	int grayTh_1 = 50;
////	int grayTh_2 = 30;
////	int  numDetectTh = detectThr;   // 允许不同像素个数  
////
////	//// 截图待检测图像  
////	int row = detectImg.rows;
////	int col = detectImg.cols;
////
////	///////////////////////////////////////////////
////	int offset = 1;  // 求边界偏移量
////	int rowe = row - 2 * offset;
////	int cole = col - 2 * offset;
////
////	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
////	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
////
////	ROIComEdge(detectImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
////	imshow("ok边缘图", edgeImgSrc);
////
////	////////////////////////////////////////////////
////	// 计算图像边缘  
////	ROIComEdge(srcImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
////	imshow("ng边缘图", edgeImgDetect);
////	////////////////////////////////////////////////
////	// ---------- 方法一 两图的边缘图像相减 ----------
////	// --- 在边缘位置设置安全范围，留下不同的像素点  
////	// --- 用5*5模板去扫描， 
////	// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
////	// --- 像素个数小于10，去除，计数加0     
////	// --- 计数值>0，则NG； 计数值=0, 则OK     
////	////////////////////////////////////////////////
////	// 1 沿源图像边缘区域设置安全范围
////	// 把边缘图像变成二值化图像   
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
////	// 用膨胀法，扩展边缘亮区域
////	//获取自定义核
////	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
////	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
////	//膨胀操作
////	Mat edgeImgSafe;
////	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
////	// 反色，且归一化到[0, 1]; 
////	edgeImgSafe = (255 - edgeImgSafe) / 255;
////
////	////////////////////////////////////////////////
////	// 2 两幅边缘图像相减
////	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
////	imshow("相减结果", edgeImgSub);
////
////	////////////////////////////////////////////////
////	// 用5*5模板去扫描， 
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
////				//只要有不同，都会标出来的，而且不只是它们不同的地方，最主要是边界，边界没重合，有红点，那就表示坏片。
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
////	imshow("滤波结果", resultImg);
////	////////////////////////////////////////////////
////
////	//单通道，多通道一定要分开，不然很容易出错。
////	// 不同的区域，中心点标记为红色  
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
////	//imshow("差别展示", showImg);
////	////////////////////////////////////////////////
////	// 计数值>0，则NG； 计数值=0, 则OK 
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
//////需要解决的问题是，平移之后图像肯定需要扩展，这部分怎么修正，会自动扩展吗？
////
////int main(){
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG", 0);
////	//imshow("原图", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
////	//imshow("待检测图", detectImg);
////
////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////
////	bool flag = 0;
////	flag = ROIComDetectMethod(srcImg, detectImg, showImg);
////	if (flag == 0){
////		cout << "ng图片" << endl;
////	}
////	else{
////		cout << "这是ok图片" << endl;
////	}
////
////	waitKey(0);
////	system("pause");
////	return 0;
////}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////*/*////123456
//////////定位方法,也就是得到x， y轴的偏移量
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
////	////int offset = 1;  // 求边界偏移量
////	//int rowe = row - 2 * offset;
////	//int cole = col - 2 * offset;
////	////int grayTh = int(255 / 4);  
////
////	// 处理第 1 幅图像
////	// 差分法求边缘		
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
////	// 把边缘图像像素值映射到[0, 255]
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
////	// 把边缘图像，去掉过小的边缘  	
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
////	//imshow("边缘图", edgeImg);
////}
////
////// 找边缘图像上下位置  
////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
////{
////	int rowe = abEdgeImg.rows;
////	int cole = abEdgeImg.cols;
////
////	// 找到上下边缘位置
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
////// Y轴（行）偏移量计算  
////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
////{
////	int locRow = 0;
////	int  offset = 1;  // 求边界偏移量       ///offset是用于计算边界的偏移量（事先给定我的边界大概偏多少）， 而我们计算出来的locRow是偏移， 两个边界图像偏移多少
////	// ------ 获取原图的定位信息 ------      
////	// 剪切上下边缘区域
////
////	int rowroiAB = srcImg.rows;
////	int colroiAB = srcImg.cols;
////	int roweAB = rowroiAB - 2 * offset;
////	int coleAB = colroiAB - 2 * offset;
////	// 获取上下边缘图
////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("第一个边缘图", abEdgeImg);
////
////	// 找到上下边缘位置     
////	vector<int>     xypABsrc(coleAB);
////	ROIComABPlace(abEdgeImg, xypABsrc);
////
////	// ------ 获取待检测图像定位信息 ------      
////	// 剪切上下边缘区域
////	// 获取上下边缘图
////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
////	imshow("第二个边缘图", abEdgeImg);
////
////	// 找到上下边缘位置     
////	vector<int>     xypABdetect(coleAB);
////	ROIComABPlace(abEdgeImg, xypABdetect);
////
////	//------ 计算偏移 ------
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
////// 找边缘图像左右位置  
////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
////{
////	int rowe = lrEdgeImg.rows;
////	int cole = lrEdgeImg.cols;
////
////	// 找到左右边缘位置
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
////// X轴（列）偏移量计算  	// 移动X轴（列）  
////int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
////	int locCol = 0;
////	int  offset = 1;  // 求边界偏移量    
////	// ------ 获取原图的定位信息 ------      
////	// 剪切左右边缘区域
////	int rowroiLR = srcImg.rows;
////	int colroiLR = srcImg.cols;
////	int roweLR = rowroiLR - 2 * offset;
////	int coleLR = colroiLR - 2 * offset;
////	// 获取左右边缘图
////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
////	imshow("左右第一边缘图", lrEdgeImg);
////
////	// 找到左右边缘位置     
////	vector<int>     xypLRsrc(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
////
////
////	// ------ 获取待检测图像定位信息 ------      
////	// 剪切左右边缘区域  
////	// 获取左右边缘图
////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
////	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
////	imshow("左右第二个边缘图", lrEdgeImg);
////
////	// 找到左右边缘位置     
////	vector<int>     xypLRdetect(roweLR);
////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
////
////	//------ 计算偏移 ------
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
////// 定位函数
////void ROIComLocation(Mat srcImg, Mat detectImg)
////{
////	//// 检测前开始定位      
////	int offsetx = 0;
////	int offsety = 0;
////	int grayTh = 50;
////
////	// 移动X轴（列）  左、右   
////	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
////	cout << offsetx << endl;
////
////	// 移动Y轴（行）  上、下   
////	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
////	cout << offsety << endl;
////}
////
////
//////需要解决的问题是，平移之后图像肯定需要扩展，这部分怎么修正，会自动扩展吗？
////
////int main(){
////
////	Mat srcImg = imread("D:\\roiImage_2\\sample6\\4.JPG", 0);
////	//imshow("原图", srcImg);
////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
////	//imshow("待检测图", detectImg);
////
////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
////
////	//拿到图像先调平，获取偏移量， 再平移
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
////////测一张图片的算法已经有了，全了
//////////定位方法
//////#include <opencv2\opencv.hpp>
//////#include <opencv2\highgui\highgui.hpp>
//////#include <opencv2\imgproc\imgproc.hpp>
//////#include <iostream>
//////
//////using namespace std;
//////using namespace cv;
//////
//////Mat imgTranslate(Mat &matSrc, int xOffset, int yOffset, bool bScale) {
//////	// 判断是否改变图像大小,并设定被复制ROI 
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
//////	// 修正输出的ROI 
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
//////	// 复制图像 
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
//////	////int offset = 1;  // 求边界偏移量
//////	//int rowe = row - 2 * offset;
//////	//int cole = col - 2 * offset;
//////	////int grayTh = int(255 / 4);  
//////
//////	// 处理第 1 幅图像
//////	// 差分法求边缘		
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
//////	// 把边缘图像像素值映射到[0, 255]
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
//////	// 把边缘图像，去掉过小的边缘  	
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
//////	//imshow("边缘图", edgeImg);
//////}
//////
//////// 找边缘图像上下位置  
//////void ROIComABPlace(Mat &abEdgeImg, vector<int> &xypAB)
//////{
//////	int rowe = abEdgeImg.rows;
//////	int cole = abEdgeImg.cols;
//////
//////	// 找到上下边缘位置
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
//////// Y轴（行）偏移量计算  
//////int ROIComLocationY(Mat srcImg, Mat detectImg, int grayTh)
//////{
//////	int locRow = 0;
//////	int  offset = 1;  // 求边界偏移量       ///offset是用于计算边界的偏移量（事先给定我的边界大概偏多少）， 而我们计算出来的locRow是偏移， 两个边界图像偏移多少
//////	// ------ 获取原图的定位信息 ------      
//////	// 剪切上下边缘区域
//////
//////	int rowroiAB = srcImg.rows;
//////	int colroiAB = srcImg.cols;
//////	int roweAB = rowroiAB - 2 * offset;
//////	int coleAB = colroiAB - 2 * offset;
//////	// 获取上下边缘图
//////	Mat abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//////	ROIComEdge(srcImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//////	imshow("第一个边缘图", abEdgeImg);
//////
//////	// 找到上下边缘位置     
//////	vector<int>     xypABsrc(coleAB);
//////	ROIComABPlace(abEdgeImg, xypABsrc);
//////
//////	// ------ 获取待检测图像定位信息 ------      
//////	// 剪切上下边缘区域
//////	// 获取上下边缘图
//////	abEdgeImg = Mat::zeros(roweAB, coleAB, CV_8UC1);
//////	ROIComEdge(detectImg, abEdgeImg, offset, grayTh, rowroiAB, colroiAB, roweAB, coleAB);
//////	imshow("第二个边缘图", abEdgeImg);
//////
//////	// 找到上下边缘位置     
//////	vector<int>     xypABdetect(coleAB);
//////	ROIComABPlace(abEdgeImg, xypABdetect);
//////
//////	//------ 计算偏移 ------
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
//////// 找边缘图像左右位置  
//////void ROIComLRPlace(Mat &lrEdgeImg, vector<int> &xypLR)
//////{
//////	int rowe = lrEdgeImg.rows;
//////	int cole = lrEdgeImg.cols;
//////
//////	// 找到左右边缘位置
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
//////// X轴（列）偏移量计算  	// 移动X轴（列）  
//////int ROIComLocationX(Mat srcImg, Mat detectImg, int grayTh){
//////	int locCol = 0;
//////	int  offset = 1;  // 求边界偏移量    
//////	// ------ 获取原图的定位信息 ------      
//////	// 剪切左右边缘区域
//////	int rowroiLR = srcImg.rows;
//////	int colroiLR = srcImg.cols;
//////	int roweLR = rowroiLR - 2 * offset;
//////	int coleLR = colroiLR - 2 * offset;
//////	// 获取左右边缘图
//////	Mat lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//////	ROIComEdge(srcImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//////	imshow("左右第一边缘图", lrEdgeImg);
//////
//////	// 找到左右边缘位置     
//////	vector<int>     xypLRsrc(roweLR);
//////	ROIComLRPlace(lrEdgeImg, xypLRsrc);
//////
//////
//////	// ------ 获取待检测图像定位信息 ------      
//////	// 剪切左右边缘区域  
//////	// 获取左右边缘图
//////	lrEdgeImg = Mat::zeros(roweLR, coleLR, CV_8UC1);
//////	ROIComEdge(detectImg, lrEdgeImg, offset, grayTh, rowroiLR, colroiLR, roweLR, coleLR);
//////	imshow("左右第二个边缘图", lrEdgeImg);
//////
//////	// 找到左右边缘位置     
//////	vector<int>     xypLRdetect(roweLR);
//////	ROIComLRPlace(lrEdgeImg, xypLRdetect);
//////
//////	//------ 计算偏移 ------
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
//////// 定位函数
//////Mat ROIComLocation(Mat srcImg, Mat detectImg)
//////{
//////	Mat detectImg_move;
//////	//// 检测前开始定位      
//////	int offsetx = 0;
//////	int offsety = 0;
//////	int grayTh = 50;
//////
//////	// 移动X轴（列）  左、右   
//////	offsetx = ROIComLocationX(srcImg, detectImg, grayTh);
//////	cout << offsetx << endl;
//////
//////	// 移动Y轴（行）  上、下   
//////	offsety = ROIComLocationY(srcImg, detectImg, grayTh);
//////	cout << offsety << endl;
//////
//////	detectImg_move = imgTranslate(detectImg, offsetx, offsety, 1);
//////	imshow("平移待检测图片", detectImg_move);
//////	imwrite("D:\\roiImgForTest\\move.jpg", detectImg_move);
//////	return detectImg_move;
//////}
//////
////////我严重怀疑用这种方法计算出来的偏移量不对。
////////需要解决的问题是，平移之后图像肯定需要扩展，这部分怎么修正，会自动扩展吗？
//////
//////int detectThr = 500;
//////
//////// Com--Detect Method   比较图像边缘痕迹   
//////bool ROIComDetectMethod(Mat srcImg, Mat detectImg, Mat showImg)
//////{
//////	bool  m_resultDetectCom = 0;
//////	//// 比较法识别缺陷代码  
//////
//////	// 计算源图像及待检测图像的边缘图像
//////	int  safePix = 9;      // 安全像素个数    
//////	int  numModel = 5;     // 扫描模板大小  
//////	int dataSafe = int(float(numModel*numModel) / 2);
//////	//int grayTh = int(255 / 3);  // 计算图像边缘阈值  
//////	int grayTh_1 = 50;
//////	int grayTh_2 = 30;
//////	int  numDetectTh = detectThr;   // 允许不同像素个数  
//////
//////	//// 截图待检测图像  
//////	int row = detectImg.rows;
//////	int col = detectImg.cols;
//////
//////	///////////////////////////////////////////////
//////	int offset = 1;  // 求边界偏移量
//////	int rowe = row - 2 * offset;
//////	int cole = col - 2 * offset;
//////
//////	Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//////	Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//////
//////	ROIComEdge(detectImg, edgeImgSrc, offset, grayTh_1, row, col, rowe, cole);
//////	imshow("ok边缘图", edgeImgSrc);
//////
//////	////////////////////////////////////////////////
//////	// 计算图像边缘  
//////	ROIComEdge(srcImg, edgeImgDetect, offset, grayTh_2, row, col, rowe, cole);
//////	imshow("ng边缘图", edgeImgDetect);
//////	////////////////////////////////////////////////
//////	// ---------- 方法一 两图的边缘图像相减 ----------
//////	// --- 在边缘位置设置安全范围，留下不同的像素点  
//////	// --- 用5*5模板去扫描， 
//////	// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//////	// --- 像素个数小于10，去除，计数加0     
//////	// --- 计数值>0，则NG； 计数值=0, 则OK     
//////	////////////////////////////////////////////////
//////	// 1 沿源图像边缘区域设置安全范围
//////	// 把边缘图像变成二值化图像   
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
//////	// 用膨胀法，扩展边缘亮区域
//////	//获取自定义核
//////	//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//////	Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//////	//膨胀操作
//////	Mat edgeImgSafe;
//////	dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//////	// 反色，且归一化到[0, 1]; 
//////	edgeImgSafe = (255 - edgeImgSafe) / 255;
//////
//////	////////////////////////////////////////////////
//////	// 2 两幅边缘图像相减
//////	Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//////	imshow("相减结果", edgeImgSub);
//////
//////	////////////////////////////////////////////////
//////	// 用5*5模板去扫描， 
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
//////				//只要有不同，都会标出来的，而且不只是它们不同的地方，最主要是边界，边界没重合，有红点，那就表示坏片。
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
//////	imshow("滤波结果", resultImg);
//////	////////////////////////////////////////////////
//////
//////	//单通道，多通道一定要分开，不然很容易出错。
//////	// 不同的区域，中心点标记为红色  
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
//////	//imshow("差别展示", showImg);
//////	////////////////////////////////////////////////
//////	// 计数值>0，则NG； 计数值=0, 则OK 
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
//////	//imshow("原图", srcImg);
//////	Mat detectImg = imread("D:\\roiImage_2\\sample6\\5.JPG", 0);
//////	//imshow("待检测图", detectImg);
//////
//////	Mat detectMove;
//////
//////	Mat showImg = imread("D:\\roiImage_2\\sample6\\4.JPG");
//////
//////	//拿到图像先调平，获取偏移量， 再平移
//////	detectMove = ROIComLocation(srcImg, detectImg);
//////
//////	bool flag = 0;
//////	flag = ROIComDetectMethod(srcImg, detectMove, showImg);
//////	if (flag == 0){
//////		cout << "ng图片" << endl;
//////	}
//////	else{
//////		cout << "这是ok图片" << endl;
//////	}
//////
//////	waitKey(0);
//////	system("pause");
//////	return 0;
//////}