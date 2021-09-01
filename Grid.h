#ifndef _GRID_H_
#define _GRID_H_
#include <vector>
#include "POINT3D.h"
using namespace std;
//加上typedef是不是就是数据结构了
typedef class Grid
{
public:
	Grid();
	~Grid();
public:
	unsigned short grid_r;//格网的颜色
	unsigned short grid_g;//格网的颜色
	unsigned short grid_b;//格网的颜色
	long int grid_intens;//格网的反射率
	double grid_density;//格网内点云的密度
	double grid_Ave_height;//格网内点云的平均高程
	double grid_Max_height;//格网内点云的最大高程
	double grid_Max_min_z;//格网内点云的高差
	unsigned short grid_hsv;//格网内点云的HSV颜色空间
	double grid_rgb_SD;//应该用不了，格网rgb标准差
	double grid_intens_SD;//应该用不了，格网反射率标准差
	double grid_xy_SD;//格网xy坐标标准差
	double grid_density_SD;//格网密度标准差
	//float f;//格网特征值
	//float g;//网格特征值计算而得的灰度值
	//float z_max, z_min;//格网内点高程最大值和最小值
	//float GWxy;//单点距离权值
	//float GWh;//单点高程权值
	//int m_point_n;//每个格网点云数
	//int a;//备用参数a
	//int b;//备用参数b
	//float c;//备用参数c
	bool isVisisted;//是否访问过
	bool havepts;//是否有点
	int coi;
	int coj;
	int cok;
	vector <int>m_index;
	vector <POINT3D>Meshpts;
	int gird_z;//应该在聚类评估中，对三维格网虚实的标记，标记为1位实，标记为0位虚
public:



}Grid;

#endif 