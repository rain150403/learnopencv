#pragma once
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>  

using namespace std;

class kmeansMethon
{
public:
	kmeansMethon();
	~kmeansMethon();

private:
	float getDistance(cv::Point3f t1, cv::Point3f t2);
	int class_inputdata(cv::Point3f means[], cv::Point3f tuple);
	cv::Point3f getMeans(vector<cv::Point3f> cluster);
	float getVar(vector<cv::Point3f> clusters[], cv::Point3f means[]);
	bool check_repeat(cv::Point3f means[], int tmp);

public:
	void run(cv::Mat inputdata, cv::Mat &outlabel, int iterCnt, float eps);

};
