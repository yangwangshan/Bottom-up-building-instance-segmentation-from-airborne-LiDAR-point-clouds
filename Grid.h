#ifndef _GRID_H_
#define _GRID_H_
#include <vector>
#include "POINT3D.h"
using namespace std;
//����typedef�ǲ��Ǿ������ݽṹ��
typedef class Grid
{
public:
	Grid();
	~Grid();
public:
	unsigned short grid_r;//��������ɫ
	unsigned short grid_g;//��������ɫ
	unsigned short grid_b;//��������ɫ
	long int grid_intens;//�����ķ�����
	double grid_density;//�����ڵ��Ƶ��ܶ�
	double grid_Ave_height;//�����ڵ��Ƶ�ƽ���߳�
	double grid_Max_height;//�����ڵ��Ƶ����߳�
	double grid_Max_min_z;//�����ڵ��Ƶĸ߲�
	unsigned short grid_hsv;//�����ڵ��Ƶ�HSV��ɫ�ռ�
	double grid_rgb_SD;//Ӧ���ò��ˣ�����rgb��׼��
	double grid_intens_SD;//Ӧ���ò��ˣ����������ʱ�׼��
	double grid_xy_SD;//����xy�����׼��
	double grid_density_SD;//�����ܶȱ�׼��
	//float f;//��������ֵ
	//float g;//��������ֵ������õĻҶ�ֵ
	//float z_max, z_min;//�����ڵ�߳����ֵ����Сֵ
	//float GWxy;//�������Ȩֵ
	//float GWh;//����߳�Ȩֵ
	//int m_point_n;//ÿ������������
	//int a;//���ò���a
	//int b;//���ò���b
	//float c;//���ò���c
	bool isVisisted;//�Ƿ���ʹ�
	bool havepts;//�Ƿ��е�
	int coi;
	int coj;
	int cok;
	vector <int>m_index;
	vector <POINT3D>Meshpts;
	int gird_z;//Ӧ���ھ��������У�����ά������ʵ�ı�ǣ����Ϊ1λʵ�����Ϊ0λ��
public:



}Grid;

#endif 