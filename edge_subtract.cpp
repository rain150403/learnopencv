//// Com--Detect Method   �Ƚ�ͼ���Ե�ۼ�   
//bool CVisionFun::ROIComDetectMethod(cv::Mat &srcImg, cv::Mat &showImg, int camIndex, cv::Point centerPoint,
//	int rectWidth, int rectHeight, int rectRotAngle, int distIndex, int detectThr)
//{
//	bool  m_resultDetectCom = 0;
//	//// �ȽϷ�ʶ��ȱ�ݴ���  
//	//if (1 == m_flagComDetect)  
//	{
//		// ����Դͼ�񼰴����ͼ��ı�Եͼ��
//		int  safePix = 9;      // ��ȫ���ظ���    
//		int  numModel = 5;     // ɨ��ģ���С  
//		int dataSafe = int(float(numModel*numModel) / 2);
//		int grayTh = int(255 / 3);  // ����ͼ���Ե��ֵ  
//		int  numDetectTh = detectThr;   // ����ͬ���ظ���  
//		//countROIImage++;
//		//// ���������ͼ��  
//		Mat  detectImgTotal = srcImg.clone();
//		//// ��ͼ�����ͼ��  
//		cv::Mat detectImg(rectHeight, rectWidth, CV_8UC1);
//		ROIRotateImage(AdjustImage[camIndex], centerPoint, rectWidth, rectHeight, rectRotAngle, detectImg);
//		int row = detectImg.rows;
//		int col = detectImg.cols;
//		////////////////////////////////////////////////
//		// ����Դͼ��    
//		String strImg = format("D:/roiImage/%02d.jpg", distIndex);
//		Mat  ImgOK = imread(strImg, 0);
//		//imwrite("D:/roiImage/0 ImgOK.jpg", ImgOK);   //////  
//		//imwrite("D:/roiImage/0 detectImg.jpg", detectImg);   //////  
//		//strImg = format("D:/roiImage/0 ImgOk/%05d.jpg", countROIImage);
//		//imwrite(strImg, ImgOK);
//		//strImg = format("D:/roiImage/0 detectImg/%05d.jpg", countROIImage);
//		//imwrite(strImg, detectImg);
//		///////////////////////////////////////////////
//		int offset = 1;  // ��߽�ƫ����
//		int rowe = row - 2 * offset;
//		int cole = col - 2 * offset;
//		Mat  edgeImgSrc = Mat::zeros(rowe, cole, CV_8UC1);
//		Mat  edgeImgDetect = Mat::zeros(rowe, cole, CV_8UC1);
//		ROIComEdge(ImgOK, edgeImgSrc, offset, grayTh);
//		//imwrite("D:/roiImage/1 edgeImgSrc.jpg", edgeImgSrc);   //////  
//		//strImg = format("D:/roiImage/1 edgeImgSrc/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgSrc);  
//		////////////////////////////////////////////////
//		// ����ͼ���Ե  
//		ROIComEdge(detectImg, edgeImgDetect, offset, grayTh);
//		//imwrite("D:/roiImage/2 edgeImgDetect.jpg", edgeImgDetect);   //////  
//		//strImg = format("D:/roiImage/2 edgeImgDetect/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgDetect);
//		////////////////////////////////////////////////
//		// ---------- ����һ ��ͼ�ı�Եͼ����� ----------
//		// --- �ڱ�Եλ�����ð�ȫ��Χ�����²�ͬ�����ص�  
//		// --- ��5*5ģ��ȥɨ�裬 
//		// --- ���ظ�������10��������������1����Ӧ�����ע��ɫ     
//		// --- ���ظ���С��10��ȥ����������0     
//		// --- ����ֵ>0����NG�� ����ֵ=0, ��OK     
//		////////////////////////////////////////////////
//		// 1 ��Դͼ���Ե�������ð�ȫ��Χ
//		// �ѱ�Եͼ���ɶ�ֵ��ͼ��   
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
//		// �����ͷ�����չ��Ե������
//		//��ȡ�Զ����
//		//��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
//		Mat elementSafe = getStructuringElement(MORPH_RECT, Size(safePix, safePix));
//		//���Ͳ���
//		Mat edgeImgSafe;
//		dilate(edgeImgSrc, edgeImgSafe, elementSafe);
//		// ��ɫ���ҹ�һ����[0, 1]; 
//		edgeImgSafe = (255 - edgeImgSafe) / 255;
//		//imwrite("D:/roiImage/4 edgeImgSafe.jpg", edgeImgSafe*255);   //////  
//		//strImg = format("D:/roiImage/4 edgeImgSafe/%05d.jpg", countROIImage);
//		//imwrite(strImg, edgeImgSafe);  
//		////////////////////////////////////////////////
//		// 2 ������Եͼ�����
//		Mat  edgeImgSub = abs(edgeImgSrc - edgeImgDetect);
//		//imwrite("D:/roiImage/5 edgeImgSub.jpg", edgeImgSub);   //////     
//		//strImg = format("D:/roiImage/5 edgeImgSub/%05d.jpg", countROIImage);   
//		//imwrite(strImg, edgeImgSub);      
//		////////////////////////////////////////////////
//		// ��5*5ģ��ȥɨ�裬 
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
//		// ��ͬ���������ĵ���Ϊ��ɫ  
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
//		// ����ֵ>0����NG�� ����ֵ=0, ��OK 
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
//		//countROIImage = countROIImage % 10000;   // ��ͼ����  
//	}
//	return  m_resultDetectCom;
//}