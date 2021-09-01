#ifndef ISODATA_H
#define ISODATA_H
#include <vector>
#include "POINT3D.h"
using namespace std;
class isodata
{
	//public:
	//isodata();

private:
	// �����õ��ľ�����
	unsigned int K;
	//ÿһ����������ٵ��������������ڴ�����ȥ�������
	unsigned int thetaN;
	// ����������ļ����С���룬��С�ڴ������������������кϲ�
	double theta_c;
	// һ������У���������������׼����������ֵ������ܷ���
	double theta_s;
	// ��һ�κϲ������У����Ժϲ�������������
	unsigned int maxcombine;
	// ��������Ĵ���
	unsigned int maxiteration;
	// ��������ʱ�Ǽ�ά����
	unsigned int dim;
	//��������Sj��ģʽ��������������ļ��ƽ������
	double meandis;
	// �ϲ��Ĳ�����Ӧ���Ƿ���ϵ����
	double alpha;
	unsigned int current_iter;
public:
	//���ݼ�
	/*vector<vector<int>>dataset;*/
	vector<vector<double>>dataset;
private:
	typedef vector<double> Centroid;
	struct Cluster
	{
		vector<int>clusterID;
		Centroid center;
		double inner_meandis;
		vector<double>sigma;
	};
	vector<Cluster>clus;

public:
	isodata();

	~isodata();






};

#endif 