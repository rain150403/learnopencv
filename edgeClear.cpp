//////基于边缘强度的图像清晰度检测
//
//
//
//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#define mydebug
//#define test
//
//using namespace std;
//using namespace cv;
//
//
//	float getImageQuality(cv::Mat& m)
//	{
//		int nr = m.rows;
//		int nc = m.cols;
//		Mat g_x(nr, nc, CV_32FC1);//垂直边缘图
//		Mat g_y(nr, nc, CV_32FC1);//水平边缘图
//		float thresh_x = 0.0f;
//		float thresh_y = 0.0f;
//#ifdef test
//		float metric = 0.0;
//#endif
//		for (int i = 1; i != nr - 1; i++)
//		{
//			const uchar* up_line = m.ptr<uchar>(i - 1);
//			const uchar* mid_line = m.ptr<uchar>(i);
//			const uchar* down_line = m.ptr<uchar>(i + 1);
//			float* cur_x_line = g_x.ptr<float>(i);
//			float* cur_y_line = g_y.ptr<float>(i);
//			for (int j = 1; j != nc - 1; j++)
//			{
//				cur_x_line[j] = (up_line[j - 1] - up_line[j + 1]) +
//					(mid_line[j - 1] - mid_line[j + 1]) * 2 +
//					(down_line[j - 1] - down_line[j + 1]);
//				cur_y_line[j] = (up_line[j - 1] - down_line[j - 1]) +
//					(up_line[j] - down_line[j]) * 2 +
//					(up_line[j + 1] - down_line[j + 1]);
//				thresh_x += cur_x_line[j] * cur_x_line[j];
//				thresh_y += cur_y_line[j] * cur_y_line[j];
//#ifdef test
//				metric += std::abs(cur_x_line[j] * cur_x_line[j]) + std::abs(cur_y_line[j] * cur_y_line[j]);
//#endif
//			}
//		}
//
//		g_x.row(0).setTo(cv::Scalar(0.0f));
//		g_x.row(nr - 1).setTo(cv::Scalar(0.0f));
//		g_x.col(0).setTo(cv::Scalar(0.0f));
//		g_x.col(nc - 1).setTo(cv::Scalar(0.0f));
//		g_y.row(0).setTo(cv::Scalar(0.0f));
//		g_y.row(nr - 1).setTo(cv::Scalar(0.0f));
//		g_y.col(0).setTo(cv::Scalar(0.0f));
//		g_y.col(nc - 1).setTo(cv::Scalar(0.0f));
//
//		thresh_x = 4 * thresh_x / nr / nc;
//		thresh_y = 4 * thresh_y / nr / nc;
//#ifdef mydebug
//		//std::cout<<"g_x:"<<std::endl<<g_x<<std::endl;
//		//std::cout<<"g_y:"<<std::endl<<g_y<<std::endl;
//		Mat temp_x, temp_y;
//		g_x.convertTo(temp_x, CV_8UC1);
//		g_y.convertTo(temp_y, CV_8UC1);
//		cv::imshow("水平梯度图", temp_x);
//		cv::imshow("垂直直方图", temp_y);
//		imwrite("D:\\roiImage_2\\sample3\\save\\x.jpg", temp_x);
//		imwrite("D:\\roiImage_2\\sample3\\save\\y.jpg", temp_y);
//		
//		Mat b_x = Mat::zeros(nr, nc, CV_8UC1);
//		Mat b_y = Mat::zeros(nr, nc, CV_8UC1);
//
//#endif
//#ifdef test
//		std::cout << "test metricd:" << metric / nr / nc << std::endl;
//		return metric / nr / nc;
//#endif
//		//int e_hist_x[nr];//水平边缘宽度直方图
//		//int e_hist_y[nc];//垂直边缘宽度直方图
//
//		int e_hist_x[1604];
//		int e_hist_y[140];
//
//		for (int i = 0; i<nr; i++)   e_hist_x[i] = 0.0f;
//		for (int i = 0; i<nc; i++)   e_hist_y[i] = 0.0f;
//		int nw_x = 0;
//		int nw_y = 0;
//		for (int i = 1; i != nr - 1; i++){
//			float* cur_x_line = g_x.ptr<float>(i);
//			float* cur_y_line = g_y.ptr<float>(i);
//			for (int j = 1; j != nc - 1; j++){
//				if (cur_x_line[j] * cur_x_line[j]>thresh_x){//计算垂直方向边缘宽度
//#ifdef mydebug
//					b_x.ptr<uchar>(i)[j] = 255;
//#endif
//					float up = g_x.ptr<float>(i - 1)[j];
//					float down = g_x.ptr<float>(i + 1)[j];
//					float cur = g_x.ptr<float>(i)[j];
//					int w_x_u = 1;
//					int w_x_d = 1;
//					if (up >= cur && cur >= down){//如果是递减边缘
//						float t_up = up;
//						float t_cur_up = cur;
//						while (t_up>t_cur_up && i>w_x_u)
//						{
//							w_x_u++;
//							t_cur_up = t_up;
//							t_up = g_x.ptr<float>(i - w_x_u)[j];
//						}
//						w_x_u--;
//						float t_down = down;
//						float t_cur_down = cur;
//						while (t_down<t_cur_down && i<nr - w_x_d){
//							w_x_d++;
//							t_cur_down = t_down;
//							t_down = g_x.ptr<float>(i + w_x_d)[j];
//						}
//						w_x_d--;
//
//					}
//					else if (up <= cur && cur <= down){//如果是递增边缘
//						float t_up = up;
//						float t_cur_up = cur;
//						while (t_up<t_cur_up && i>w_x_u){
//							w_x_u++;
//							t_cur_up = t_up;
//							t_up = g_x.ptr<float>(i - w_x_u)[j];
//						}
//						w_x_u--;
//						float t_down = down;
//						float t_cur_down = cur;
//						while (t_down>t_cur_down && i<nr - w_x_d){
//							w_x_d++;
//							t_cur_down = t_down;
//							t_down = g_x.ptr<float>(i + w_x_d)[j];
//						}
//						w_x_d--;
//					}
//					e_hist_x[w_x_d + w_x_u]++;
//					nw_x++;
//				}
//				if (cur_y_line[j] * cur_y_line[j]>thresh_y){//计算水平方向边缘宽度
//#ifdef mydebug
//					b_y.ptr<uchar>(i)[j] = 255;
//#endif
//					float left = cur_y_line[j - 1];
//					float right = cur_y_line[j + 1];
//					float cur = cur_y_line[j];
//					int w_y_l = 1;
//					int w_y_r = 1;
//					if (left >= cur && cur >= right){//如果是递减边缘
//						float t_left = left;
//						float t_cur_left = cur;
//						while (t_left>t_cur_left && j>w_y_l)
//						{
//							w_y_l++;
//							t_cur_left = t_left;
//							t_left = cur_y_line[j - w_y_l];
//						}
//						w_y_l--;
//						float t_right = right;
//						float t_cur_right = cur;
//						while (t_right<t_cur_right && j<nc - w_y_r){
//							w_y_r++;
//							t_cur_right = t_right;
//							t_right = cur_y_line[j + w_y_r];
//						}
//						w_y_r--;
//
//					}
//					else if (left <= cur && cur <= right){//如果是递增边缘
//						float t_left = left;
//						float t_cur_left = cur;
//						while (t_left<t_cur_left && j>w_y_l){
//							w_y_l++;
//							t_cur_left = t_left;
//							t_left = cur_y_line[j - w_y_l];
//						}
//						w_y_l--;
//						float t_right = right;
//						float t_cur_right = cur;
//						while (t_right>t_cur_right && j<nc - w_y_r){
//							w_y_r++;
//							t_cur_right = t_right;
//							t_right = cur_y_line[j + w_y_r];
//						}
//						w_y_r--;
//					}
//					e_hist_y[w_y_l + w_y_r]++;
//					nw_y++;
//				}
//			}
//		}
//
//#ifdef mydebug
//		//std::cout<<"b_x"<<std::endl<<b_x<<std::endl;
//		//std::cout<<"b_y"<<std::endl<<b_y<<std::endl;
//		imshow("b_x", b_x);
//		imshow("b_y", b_y);
//		std::cout << "e_hist_x:";
//		for (int i = 0; i<nr; i++)
//		{
//			std::cout << e_hist_x[i] << ",";
//		}
//		std::cout << std::endl;
//		std::cout << "e_hist_y:";
//		for (int i = 0; i<nc; i++){
//			std::cout << e_hist_y[i] << ",";
//		}
//		std::cout << std::endl;
//#endif
//		//计算x方向清晰度评价值
//		int wm_x = 0, we_x = 0;
//		float maxEdge_x = 0.0f;
//		for (int i = 0; i<nr; i++){
//			if (e_hist_x[i]>maxEdge_x){
//				maxEdge_x = e_hist_x[i];
//				wm_x = i;
//			}
//			if (e_hist_x[i] != 0)  we_x = i;
//		}
//		float metric_x = 0.0f;
//		for (int i = 0; i != we_x; i++){
//			float d = 1.0f;
//			if (i<wm_x) d = (i*i*1.0f) / (wm_x*wm_x);
//			else if (i == wm_x)    d = 1;
//			else d = ((we_x - i)*(we_x - i)*1.0f) / ((we_x - wm_x)*(we_x - wm_x));
//			float p = e_hist_x[i] * 1.0f / nw_x;
//			metric_x += d*p*(i);
//		}
//#ifdef mydebug
//
//#endif
//		//计算y方向清晰度评价值
//		int wm_y = 0, we_y = 0;
//		float mayEdge_y = 0.0f;
//		for (int i = 0; i<nc; i++){
//			if (e_hist_y[i]>mayEdge_y){
//				mayEdge_y = e_hist_y[i];
//				wm_y = i;
//			}
//			if (e_hist_y[i] != 0)  we_y = i;
//		}
//		float metric_y = 0.0f;
//		for (int i = 0; i != we_y; i++){
//			float d = 1.0f;
//			if (i<wm_y) d = (i*i*1.0f) / (wm_y*wm_y);
//			else if (i == wm_y)    d = 1;
//			else d = ((we_y - i)*(we_y - i)*1.0f) / ((we_y - wm_y)*(we_y - wm_y));
//			float p = e_hist_y[i] * 1.0f / nw_y;
//			metric_y += d*p*(i);
//		}
//#ifdef mydebug
//		std::cout << "metric_x:" << metric_x << std::endl;
//		std::cout << "metric_y:" << metric_y << std::endl;
//		std::cout << "metric:" << (metric_x + metric_y) / 2 << std::endl;
//#endif
//		return (metric_x + metric_y) / 2;
//	}
//
//
//	int main(){
//		Mat src;
//		src = imread("D:\\roiImgForTest\\okSave\\ok41.jpg");
//
//		getImageQuality(src);
//
//		waitKey(0);
//		system("pause");
//		return 0;
//	}
//
