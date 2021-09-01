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
	//原始点云数据
	vector<POINT3D> m_raw_points;
	//0-地面点,1-非地面点,2-粗差点
	std::vector<unsigned char> m_raw_points_mode;
	//原始点云数据
	vector<POINT3D> m_building_points;

	//二维转为单体化的数据
	vector<POINT3D> m_IndividualRGBpointcloud;
	//tsk文件读取存放路径
	vector <string >m_whole_tsk_file_path;
	float a[50];
public:
	//数据范围
	extent_3d _extent;
	//点云间距(没有用到，感觉没啥用)
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