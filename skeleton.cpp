//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//void zhangSkeleton(Mat &srcimage);
//
//int main(){
//	Mat src = imread("D:\\newSample\\0513\\b\\20.JPG");
//	cvtColor(src, src, CV_BGR2GRAY);
//	imshow("src", src);
//	zhangSkeleton(src);
//	imshow("result", src);
//
//	waitKey(0);
//	system("pause");
//	return 0;
//}
//
//
//void zhangSkeleton(Mat &srcimage) {
//	int kernel[9]; 
//	int nl = srcimage.rows; 
//	int nc = srcimage.cols; 
//	vector<Point> delete_list; 
//	int A, B; 
//	
//	while (true) {
//		for (int j = 1; j < nl - 1; j++) {
//			uchar* data_pre = srcimage.ptr<uchar>(j - 1); 
//			uchar* data = srcimage.ptr<uchar>(j); 
//			uchar* data_next = srcimage.ptr<uchar>(j + 1); 
//			
//			for (int i = 1; i < (nc - 1); i++) {
//				if (data[i] == 255) {
//					kernel[0] = 1; 
//					if (data_pre[i] == 255) 
//						kernel[1] = 1; 
//					else 
//						kernel[1] = 0; 
//					if (data_pre[i + 1] == 255) 
//						kernel[2] = 1; 
//					else 
//						kernel[2] = 0; 
//					if (data[i + 1] == 255) 
//						kernel[3] = 1; 
//					else 
//						kernel[3] = 0; 
//					if (data_next[i + 1] == 255) 
//						kernel[4] = 1; 
//					else 
//						kernel[4] = 0; 
//					if (data_next[i] == 255) 
//						kernel[5] = 1; 
//					else 
//						kernel[5] = 0; 
//					if (data_next[i - 1] == 255) 
//						kernel[6] = 1; 
//					else 
//						kernel[6] = 0; 
//					if (data[i - 1] == 255) 
//						kernel[7] = 1; 
//					else 
//						kernel[7] = 0; 
//					if (data_pre[i - 1] == 255) 
//						kernel[8] = 1; 
//					else 
//						kernel[8] = 0;
//
//					B = 0; 
//					for (int k = 1; k < 9; k++) { 
//						B = B + kernel[k]; 
//					} 
//					if ((B >= 2) && (B <= 6)) {
//						A = 0; 
//						if (!kernel[1] && kernel[2]) 
//							A++; 
//						if (!kernel[2] && kernel[3]) 
//							A++; 
//						if (!kernel[3] && kernel[4]) 
//							A++; 
//						if (!kernel[4] && kernel[5]) 
//							A++; 
//						if (!kernel[5] && kernel[6]) 
//							A++; 
//						if (!kernel[6] && kernel[7]) 
//							A++; 
//						if (!kernel[7] && kernel[8]) 
//							A++; 
//						if (!kernel[8] && kernel[1]) 
//							A++; 
//						// 
//						if (A == 1) { 
//							if ((kernel[1] * kernel[3] * kernel[5] == 0) 
//								&& (kernel[3] * kernel[5] * kernel[7] == 0)) { 
//								delete_list.push_back(Point(i, j)); 
//							} 
//						} 
//					} 
//				} 
//			} 
//		} 
//		int size = delete_list.size(); 
//		if (size == 0) { 
//			break; 
//		} 
//		for (int n = 0; n < size; n++) { 
//			Point tem; 
//			tem = delete_list[n]; 
//			uchar* data = srcimage.ptr<uchar>(tem.y); 
//			data[tem.x] = 0; 
//		} 
//		delete_list.clear(); 
//		for (int j = 1; j < nl - 1; j++) { 
//			uchar* data_pre = srcimage.ptr<uchar>(j - 1); 
//			uchar* data = srcimage.ptr<uchar>(j); 
//			uchar* data_next = srcimage.ptr<uchar>(j + 1); 
//			for (int i = 1; i < (nc - 1); i++) { 
//				if (data[i] == 255) { 
//					kernel[0] = 1; 
//					if (data_pre[i] == 255) 
//						kernel[1] = 1; 
//					else 
//						kernel[1] = 0; 
//					if (data_pre[i + 1] == 255) 
//						kernel[2] = 1; 
//					else 
//						kernel[2] = 0; 
//					if (data[i + 1] == 255) 
//						kernel[3] = 1; 
//					else 
//						kernel[3] = 0; 
//					if (data_next[i + 1] == 255) 
//						kernel[4] = 1; 
//					else 
//						kernel[4] = 0; 
//					if (data_next[i] == 255) 
//						kernel[5] = 1; 
//					else 
//						kernel[5] = 0; 
//					if (data_next[i - 1] == 255) 
//						kernel[6] = 1; 
//					else 
//						kernel[6] = 0; 
//					if (data[i - 1] == 255) 
//						kernel[7] = 1; 
//					else 
//						kernel[7] = 0; 
//					if (data_pre[i - 1] == 255) 
//						kernel[8] = 1; 
//					else 
//						kernel[8] = 0; 
//
//					B = 0; 
//					for (int k = 1; k < 9; k++) { 
//						B = B + kernel[k]; 
//					} 
//					if ((B >= 2) && (B <= 6)) { 
//						A = 0; 
//						if (!kernel[1] && kernel[2]) 
//							A++; 
//						if (!kernel[2] && kernel[3]) 
//							A++; 
//						if (!kernel[3] && kernel[4]) 
//							A++; 
//						if (!kernel[4] && kernel[5]) 
//							A++; 
//						if (!kernel[5] && kernel[6]) 
//							A++; 
//						if (!kernel[6] && kernel[7]) 
//							A++; 
//						if (!kernel[7] && kernel[8]) 
//							A++; 
//						if (!kernel[8] && kernel[1]) 
//							A++; 
//						// 
//						if (A == 1) { 
//							if ((kernel[1] * kernel[3] * kernel[7] == 0) 
//								&& (kernel[1] * kernel[5] * kernel[7] == 0)) { 
//								delete_list.push_back(Point(i, j)); 
//							} 
//						} 
//					} 
//				} 
//			} 
//		} 
//		if (size == 0) { 
//			break; 
//		} 
//		for (int n = 0; n < size; n++) { 
//			Point tem; 
//			tem = delete_list[n]; 
//			uchar* data = srcimage.ptr<uchar>(tem.y); 
//			data[tem.x] = 0; 
//		} 
//		delete_list.clear(); 
//	} 
//}