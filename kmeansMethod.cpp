#include "kmeansMethon.h"

#define CLUSTERCNT 2

kmeansMethon::kmeansMethon()
{
}

kmeansMethon::~kmeansMethon()
{
}

//��������Ԫ����ŷ�������     //����������ά�ռ��еĵ��ŷʽ����
float kmeansMethon::getDistance(cv::Point3f t1, cv::Point3f t2)
{
	double dx = powf((t1.x - t2.x), 2);
	double dy = powf((t1.y - t2.y), 2);
	double dz = powf((t1.z - t2.z), 2);
	return sqrt(dx + dy + dz);
}

//�������ģ�������ǰԪ�������ĸ���  
int kmeansMethon::class_inputdata(cv::Point3f means[], cv::Point3f tuple)
{
	float dist = getDistance(means[0], tuple);
	float tmp;
	int label = 0;//��ʾ������һ����  
	for (int i = 1; i < CLUSTERCNT; i++)
	{
		tmp = getDistance(means[i], tuple);
		if (tmp < dist)
		{
			dist = tmp;
			label = i;
		}
	}
	return label;
}

//��õ�ǰ�صľ�ֵ�����ģ�       ///û��⣿
cv::Point3f kmeansMethon::getMeans(vector<cv::Point3f> cluster)
{

	double num = cluster.size();
	cv::Point3f t;
	for (double i = 0; i < num; i++)
	{
		t.x += cluster[i].x;
		t.y += cluster[i].y;
		t.z += cluster[i].z;
	}
	t.x /= num;
	t.y /= num;
	t.z /= num;
	return t;
}

//��ø����ؼ���ƽ�����      //����ÿһ������������㵽���ĵľ����ƽ��ֵ
float kmeansMethon::getVar(vector<cv::Point3f> clusters[], cv::Point3f means[])
{
	float var = 0;
	float count = 0;
	for (int i = 0; i < CLUSTERCNT; i++)
	{
		vector<cv::Point3f> t = clusters[i];
		for (int j = 0; j< t.size(); j++)
		{
			count++;
			var += getDistance(t[j], means[i]);
		}
	}
	return var / count;

}

//��鵱ǰ��ʼ���Ƿ������е��ظ�
//�ظ� ����true
//���ظ� ����false
bool kmeansMethon::check_repeat(cv::Point3f means[], int tmp)
{
	for (int i = tmp; i >= 1; i--)
	{
		if (means[tmp] == means[i - 1])
			return true;
	}
	return false;
}

void kmeansMethon::run(cv::Mat inputdata, cv::Mat &outlabel, int iterCnt, float eps)
{
	assert(inputdata.type() == CV_32FC3 || inputdata.type() == CV_64FC3);
	cv::Point3f centers[CLUSTERCNT];

	float *pInput = (float*)inputdata.data;
	int *plabel = (int*)outlabel.data;

	vector<cv::Point3f> clusters[CLUSTERCNT];

	//Ĭ��һ��ʼ��ǰK��Ԫ���ֵ��Ϊk���ص����ģ���ֵ��     //��νԪ����ǵ�
	for (int i = 0; i < CLUSTERCNT; i++)
	{
		centers[i].x = pInput[i * 3 + 0];
		centers[i].y = pInput[i * 3 + 1];
		centers[i].z = pInput[i * 3 + 2];
		if (i > 0)
		{
			int t = 1;
			while (check_repeat(centers, i))
			{
				int id = i + t;
				centers[i].x = pInput[id * 3 + 0];
				centers[i].y = pInput[id * 3 + 1];
				centers[i].z = pInput[id * 3 + 2];
				t++;
			}
		}
	}

	int lable = 0;
	//����Ĭ�ϵ����ĸ��ظ�ֵ  
	int data_num = inputdata.rows;

	for (int i = 0; i < data_num; ++i)
	{
		cv::Point3f tmp;
		tmp.x = pInput[i * 3 + 0];
		tmp.y = pInput[i * 3 + 1];
		tmp.z = pInput[i * 3 + 2];
		lable = class_inputdata(centers, tmp);
		clusters[lable].push_back(tmp);
	}
	float oldVar = -1;
	float newVar = getVar(clusters, centers);
	int count_ = 0;
	while (abs(newVar - oldVar) >= eps || count_ >= iterCnt) //���¾ɺ���ֵ����1��׼����ֵ���������Ա仯ʱ���㷨��ֹ       //��һ���������̣�ѭ������
	{
		for (int i = 0; i < CLUSTERCNT; i++) //����ÿ���ص����ĵ�  
		{
			centers[i] = getMeans(clusters[i]);
		}
		oldVar = newVar;
		newVar = getVar(clusters, centers); //�����µ�׼����ֵ  

		for (int i = 0; i < CLUSTERCNT; i++) //���ÿ����  
		{
			clusters[i].clear();
		}

		//�����µ����Ļ���µĴ�  
		for (int i = 0; i < data_num; ++i)
		{
			cv::Point3f tmp;
			tmp.x = pInput[i * 3 + 0];
			tmp.y = pInput[i * 3 + 1];
			tmp.z = pInput[i * 3 + 2];
			lable = class_inputdata(centers, tmp);
			clusters[lable].push_back(tmp);

			plabel[i] = lable;
		}
		count_++;
	}
}
