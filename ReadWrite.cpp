#include "stdafx.h"
#include "ReadWrite.h"
#include "POINT3D.h"
#include <iostream> //��׼���������
//#include <pcl/io/pcd_io.h> //PCL��PCD��ʽ�ļ����������ͷ�ļ�
//#include <pcl/point_types.h> //PCL�Ը��ָ�ʽ�ĵ��֧��ͷ�ļ�
//#include <pcl/io/ply_io.h> //PCL��ply��ʽ�ļ����������ͷ�ļ�
#include <vector>
////#include <pcl/filters/statistical_outlier_removal.h>
////#include <pcl/filters/voxel_grid.h>
//#include "lasreader.h"
#include "fstream"


#include<opencv2/opencv.hpp>
#include<iostream>
#include<time.h>
#include<fstream>


using namespace cv;



SYSTEMTIME _T;
using namespace std;
#define Random(x) (rand() % x)
ReadWrite::ReadWrite()
{
}


ReadWrite::~ReadWrite()
{
}



int  ReadWrite::read_tsk(const char*filename)
{
	
	ifstream in(filename);
	if (!in) {
		cerr << "Can't open the task file." << endl;
		return -1;
	}

	string line;
	/*vector<string> words;*/
	while (getline(in, line))
		m_whole_tsk_file_path.push_back(line);

	in.close();

	
	return 0;

}


#pragma endregion