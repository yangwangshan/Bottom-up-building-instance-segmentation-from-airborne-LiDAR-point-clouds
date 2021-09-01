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
	// 期望得到的聚类数
	unsigned int K;
	//每一个类别中最少的样本数，若少于此数则去掉该类别
	unsigned int thetaN;
	// 两个类别中心间的最小距离，若小于此数，把两个类别需进行合并
	double theta_c;
	// 一个类别中，样本特征中最大标准差。若大于这个值，则可能分裂
	double theta_s;
	// 在一次合并操作中，可以合并的类别的最多对数
	unsigned int maxcombine;
	// 迭代运算的次数
	unsigned int maxiteration;
	// 生成数据时是几维数组
	unsigned int dim;
	//各聚类域Sj中模式样本与各聚类中心间的平均距离
	double meandis;
	// 合并的参数（应该是分裂系数）
	double alpha;
	unsigned int current_iter;
public:
	//数据集
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