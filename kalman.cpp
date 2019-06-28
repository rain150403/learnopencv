//////https://www.cnblogs.com/kuangxionghui/p/10382124.html
////
////��ϴ�����������ʽ
////https ://www.cnblogs.com/yueyangtze/p/9503835.html
////
////��ϸ��ԭ����
////https ://blog.csdn.net/u010720661/article/details/63253509
////
////GitHub�ϵĴ���
////https ://github.com/TKJElectronics/KalmanFilter/blob/master/Kalman.cpp
//
////https://www.cnblogs.com/TIANHUAHUA/p/8473029.html
//
//
//
////#include <ros/ros.h>
//#include <string>
//#include <stdlib.h>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <Eigen/Dense>
//#include <cmath>
//#include <limits>
//
//using namespace std;
//using Eigen::MatrixXd;
//
////
//double generateGaussianNoise(double mu, double sigma)
//{
//	const double epsilon = std::numeric_limits<double>::min();
//	const double two_pi = 2.0*3.14159265358979323846;
//
//	static double z0, z1;
//	static bool generate;
//	generate = !generate;
//
//	if (!generate)
//		return z1 * sigma + mu;
//
//	double u1, u2;
//	do
//	{
//		u1 = rand() * (1.0 / RAND_MAX);
//		u2 = rand() * (1.0 / RAND_MAX);
//	} while (u1 <= epsilon);
//
//	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
//	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
//	return z0 * sigma + mu;
//}
//
//int main(int argc, char **argv)
//{
//	std::cout << "test qusetion2 start !" << std::endl;
//	/*ros::init(argc, argv, "question2_node");
//	ros::NodeHandle node;*/
//
//	ofstream fout("result.txt");
//
//	double generateGaussianNoise(double mu, double sigma);//�����˹�ֲ���������������
//
//	const double delta_t = 0.1;//�������ڣ�100ms
//	const int num = 100;//��������
//	const double acc = 10;//���ٶȣ�ft/m
//
//	MatrixXd A(2, 2);
//	A(0, 0) = 1;
//	A(1, 0) = 0;
//	A(0, 1) = delta_t;
//	A(1, 1) = 1;
//
//	MatrixXd B(2, 1);
//	B(0, 0) = pow(delta_t, 2) / 2;
//	B(1, 0) = delta_t;
//
//	MatrixXd H(1, 2);//��������С����λ�ƣ��ٶ�Ϊ0
//	H(0, 0) = 1;
//	H(0, 1) = 0;
//
//	MatrixXd Q(2, 2);//���̼�������Э�������ϵͳ����������ֻ�����ٶȷ����ϣ����ٶ������ķ�����һ������0.01��λ�Ʒ����ϵ�ϵͳ����Ϊ0
//	Q(0, 0) = 0;
//	Q(1, 0) = 0;
//	Q(0, 1) = 0;
//	Q(1, 1) = 0.01;
//
//	MatrixXd R(1, 1);//�۲�����Э�������ֵֻ��λ�ƣ�����Э��������С��1*1�����ǲ��������ķ����
//	R(0, 0) = 10;
//
//	//time��ʼ��������ʱ������
//	vector<double> time(100, 0);
//	for (decltype(time.size()) i = 0; i != num; ++i) {
//		time[i] = i * delta_t;
//		//cout<<time[i]<<endl;
//	}
//
//	MatrixXd X_real(2, 1);
//	vector<MatrixXd> x_real, rand;
//	//���ɸ�˹�ֲ��������
//	for (int i = 0; i<100; ++i) {
//		MatrixXd a(1, 1);
//		a(0, 0) = generateGaussianNoise(0, sqrt(10));
//		rand.push_back(a);
//	}
//	//������ʵ��λ��ֵ
//	for (int i = 0; i < num; ++i) {
//		X_real(0, 0) = 0.5 * acc * pow(time[i], 2);
//		X_real(1, 0) = 0;
//		x_real.push_back(X_real);
//	}
//
//	//�������壬����״̬Ԥ��ֵ��״̬����ֵ������ֵ��Ԥ��״̬����ʵ״̬��Э������󣬹���״̬����ʵ״̬��Э������󣬳�ʼֵ��Ϊ��
//	MatrixXd X_evlt = MatrixXd::Constant(2, 1, 0), X_pdct = MatrixXd::Constant(2, 1, 0), Z_meas = MatrixXd::Constant(1, 1, 0),
//		Pk = MatrixXd::Constant(2, 2, 0), Pk_p = MatrixXd::Constant(2, 2, 0), K = MatrixXd::Constant(2, 1, 0);
//	vector<MatrixXd> x_evlt, x_pdct, z_meas, pk, pk_p, k;
//	x_evlt.push_back(X_evlt);
//	x_pdct.push_back(X_pdct);
//	z_meas.push_back(Z_meas);
//	pk.push_back(Pk);
//	pk_p.push_back(Pk_p);
//	k.push_back(K);
//
//	//��ʼ����
//	for (int i = 1; i < num; ++i) {
//		//Ԥ��ֵ
//		X_pdct = A * x_evlt[i - 1] + B * acc;
//		x_pdct.push_back(X_pdct);
//		//Ԥ��״̬����ʵ״̬��Э�������Pk'
//		Pk_p = A * pk[i - 1] * A.transpose() + Q;
//		pk_p.push_back(Pk_p);
//		//K:2x1
//		MatrixXd tmp(1, 1);
//		tmp = H * pk_p[i] * H.transpose() + R;
//		K = pk_p[i] * H.transpose() * tmp.inverse();
//		k.push_back(K);
//		//����ֵz
//		Z_meas = H * x_real[i] + rand[i];
//		z_meas.push_back(Z_meas);
//		//����ֵ
//		X_evlt = x_pdct[i] + k[i] * (z_meas[i] - H * x_pdct[i]);
//		x_evlt.push_back(X_evlt);
//		//����״̬����ʵ״̬��Э�������Pk
//		Pk = (MatrixXd::Identity(2, 2) - k[i] * H) * pk_p[i];
//		pk.push_back(Pk);
//	}
//
//	cout << "����������" << "  " << "�������" << "  " << "��ֵ" << "  " << endl;
//	for (int i = 0; i < num; ++i) {
//		cout << z_meas[i] << "  " << x_evlt[i](0, 0) << "  " << x_real[i](0, 0) << endl;
//		fout << z_meas[i] << "  " << x_evlt[i](0, 0) << "  " << x_real[i](0, 0) << endl;
//	}
//
//	fout.close();
//	getchar();
//	return 0;
//}
//
//
