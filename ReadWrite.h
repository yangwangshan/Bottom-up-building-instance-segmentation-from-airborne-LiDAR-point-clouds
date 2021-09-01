#ifndef _READWRITE_H_
#define _READWRITE_H_
#include <vector>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include "POINT3D.h"
using namespace std;



class ReadWrite
{
public:
	ReadWrite();
	~ReadWrite();


public:
	int read_pcd();
	int read_ply();
	//int read_las(std::string points_file);
	int read_tsk(const char*filename);
	

public:
	/*vector<POINT3D> RawData;*/
	//ԭʼ��������
	vector<POINT3D> m_raw_points;
	//0-�����,1-�ǵ����,2-�ֲ��
	std::vector<unsigned char> m_raw_points_mode;
	//ԭʼ��������
	vector<POINT3D> m_building_points;

	//��άתΪ���廯������
	vector<POINT3D> m_IndividualRGBpointcloud;
	//tsk�ļ���ȡ���·��
	vector <string >m_whole_tsk_file_path;
	float a[50];
public:
	//���ݷ�Χ
	extent_3d _extent;
	//���Ƽ��(û���õ����о�ûɶ��)
	float _span;


};
typedef struct txtPoint_3D {
	double x;
	double y;
	double z;
	int r;
	int g;
	int b;
	int i;
	double Classification;


}txtPoint_3D;
#endif 