//// Com--Detect Method   比较图像边缘痕迹   
//bool CVisionFun::ROIComDetectMethod(cv::Mat &srcImg, cv::Mat &showImg, int camIndex, cv::Point centerPoint,
//	int rectWidth, int rectHeight, int rectRotAngle, int distIndex, int detectThr)
//{
//	bool  m_resultDetectCom = 0;
//	//// 比较法识别缺陷代码  
//	//if (1 == m_flagComDetect)  
//	{
//		// 计算源图像及待检测图像的边缘图像
//		int  safePix = 9;      // 安全像素个数    
//		int  numModel = 5;     // 扫描模板大小  
//		int dataSafe = int(float(numModel*numModel) / 2);
//		int grayTh = int(255 / 3);  // 计算图像边缘阈值  
//		int  numDetectTh = detectThr;   // 允许不同像素个数  
//		//countROIImage++;
//		//// 待检测整张图像  
//		Mat  detectImgTotal = srcImg.clone();
//		//// 截图待检测图像  
//		cv::Mat detectImg(rectHeight, rectWidth, CV_8UC1);
//		ROIRotateImage(AdjustImage[camIndex], centerPoint, rectWidth, rectHeight, rectRotAngle, detectImg);
//		int row = detectImg.rows;
//		int col = detectImg.cols;
//		////////////////////////////////////////////////
//		// 读入源图像    
//		String strImg = format("D:/roiImage/%02d.jpg", distIndex);
//		Mat  ImgOK = imread(strImg, 0);
//		//imwrite("D:/roiImage/0 ImgOK.jpg", ImgOK);   //////  
//		//imwrite("D:/roiImage/0 detectImg.jpg", detectImg);   //////  
//		//strImg = format("D:/roiImage/0 ImgOk/%05d.jpg", countROIImage);
//		//imwrite(strImg, ImgOK);
//		//strImg = format("D:/roiImage/0 detectImg/%05d.jpg", countROIImage);
//		//imwrite(strImg, detectImg);
//		///////////////////////////////////////////////
//		int offset = 1;  // 求边界偏移量
//		int rowe = row - 2 * offset;
//		int cole = col - 2 * offset;
//		Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//		Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//		ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
//		//imwrite("D:/roiImage/1 edgeImgSrc.jpg", edgeImgSrc);   //////  
//		//strImg = format("D:/roiImage/1 edgeImgSrc/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgSrc);  
//		////////////////////////////////////////////////
//		// 计算图像边缘  
//		ROIComEdge(detectImg, edgeImgDetect, offset, grayTh);
//		//imwrite("D:/roiImage/2 edgeImgDetect.jpg", edgeImgDetect);   //////  
//		//strImg = format("D:/roiImage/2 edgeImgDetect/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgDetect);
//		////////////////////////////////////////////////
//		// ---------- 方法一 两图的边缘图像相减 ----------
//		// --- 在边缘位置设置安全范围，留下不同的像素点  
//		// --- 用5*5模板去扫描， 
//		// --- 像素个数大于10，保留，计数加1，相应区域标注红色     
//		// --- 像素个数小于10，去除，计数加0     
//		// --- 计数值>0，则NG； 计数值=0, 则OK     
//		////////////////////////////////////////////////
//		// 1 沿源图像边缘区域设置安全范围
//		// 把边缘图像变成二值化图像   
//		Mat  edgeImgSrcTh = Mat::zeros(rowe, cole, CV_8UC1);
//		Mat  edgeImgDetectTh = Mat::zeros(rowe, cole, CV_8UC1);
//		for (int i = 1; i < rowe; i++)
//		{
//			for (int j = 1; j < cole; j++)
//			{
//				if (edgeImgSrc.at <uchar>(i, j) > 0)
//				{
//					edgeImgSrcTh.at <uchar>(i, j) = 255;
//				}
//				if (edgeImgDetect.at <uchar>(i, j) > 0)
//				{
//					edgeImgDetectTh.at <uchar>(i, j) = 255;
//				}
//			}
//		}
//		//imwrite("D:/roiImage/3 edgeImgSrcTh.jpg", edgeImgSrcTh);   ////// 
//		//imwrite("D:/roiImage/3 edgeImgDetectTh.jpg", edgeImgDetectTh);   ////// 
//		//strImg = format("D:/roiImage/3 edgeImgSrcTh/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgSrcTh);
//		//strImg = format("D:/roiImage/3 edgeImgDetectTh/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgDetectTh);
//		////////////////////////////////////////////////
//		// 用膨胀法，扩展边缘亮区域
//		//获取自定义核
//		//第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
//		Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//		//膨胀操作
//		Mat edgeImgSafe;
//		dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//		// 反色，且归一化到[0, 1]; 
//		edgeImgSafe = (255 - edgeImgSafe) / 255;
//		//imwrite("D:/roiImage/4 edgeImgSafe.jpg", edgeImgSafe*255);   //////  
//		//strImg = format("D:/roiImage/4 edgeImgSafe/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgSafe);  
//		////////////////////////////////////////////////
//		// 2 两幅边缘图像相减
//		Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//		//imwrite("D:/roiImage/5 edgeImgSub.jpg", edgeImgSub);   //////     
//		//strImg = format("D:/roiImage/5 edgeImgSub/%05d.jpg", countROIImage);   
//		//imwrite(strImg, edgeImgSub);      
//		////////////////////////////////////////////////
//		// 用5*5模板去扫描， 
//		Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//		int resultNum = 0;
//		int dataTem = 0;
//		int dataZong = 0;
//		int dataNum = 0;
//		//int dataSafe = int(float(numModel*numModel) / float(3) + 0.5);
//		for (int i = numModel; i < rowe - numModel; i++)
//		{
//			for (int j = numModel; j < cole - numModel; j++)
//			{
//				dataTem = 0;
//				dataZong = 0;
//				dataNum = 0;
//				for (int m = 0; m < numModel; m++)
//				{
//					for (int n = 0; n < numModel; n++)
//					{
//						dataTem = edgeImgSub.at<uchar>(i, j) *edgeImgSafe.at<uchar>(i, j);
//						if (dataTem > 0)
//						{
//							dataZong = dataZong + 1;
//						}
//					}
//				}
//				if (dataZong > dataSafe)
//				{
//					resultImg.at<uchar>(i, j) = 255;
//					resultNum++;
//				}
//			}
//		}
//		//imwrite("D:/roiImage/6 resultImg.jpg", resultImg);   //////  
//		//strImg = format("D:/roiImage/6 resultImg/%05d.jpg", countROIImage);
//		//imwrite(strImg, resultImg);
//		////////////////////////////////////////////////
//		// 不同的区域，中心点标记为红色  
//		Mat resultImgTem = Mat::zeros(row, col, CV_8UC1);
//		//Mat resultImg = Mat::zeros(rowe, cole, CV_8UC1);
//		for (int i = offset; i<row - offset; i++)
//		{
//			for (int j = offset; j < col - offset; j++)
//			{
//				resultImgTem.at<uchar>(i, j) = resultImg.at<uchar>(i - offset, j - offset);
//				if (resultImgTem.at<uchar>(i, j) == 255)
//				{
//					for (int m = 0; m < offset; m++)
//					{
//						for (int n = 0; n < offset; n++)
//						{
//							//cv::Point centerPoint, int rectWidth, int rectHeight,
//							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
//								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[0] = 0;
//							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
//								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[1] = 0;
//							showImg.at<Vec3b>(centerPoint.y + i - int(float(rectHeight) / 2.0) + m,
//								centerPoint.x + j - int(float(rectWidth) / 2.0) + n)[2] = 255;
//						}
//					}
//				}
//			}
//		}
//		////////////////////////////////////////////////
//		// 计数值>0，则NG； 计数值=0, 则OK 
//		if (resultNum <= numDetectTh)
//		{
//			m_resultDetectCom = 1;  // OK  
//			//putText(showImg, "OK", cv::Point(TOTAL_IMAG_WIDTH - 300, 100), CV_FONT_HERSHEY_COMPLEX,
//			//	stCamera[camIndex].nFontSize, cv::Scalar(0, 255, 0), 3);
//		}
//		else
//		{
//			m_resultDetectCom = 0;  // NG      
//			//putText(showImg, "NG", cv::Point(TOTAL_IMAG_WIDTH - 300, 100), CV_FONT_HERSHEY_COMPLEX,
//			//	stCamera[camIndex].nFontSize, cv::Scalar(0, 0, 255), 3);
//		}
//		////////////////////////////////////////////////
//		//countROIImage = countROIImage % 10000;   // 存图计数  
//	}
//	return  m_resultDetectCom;
//}