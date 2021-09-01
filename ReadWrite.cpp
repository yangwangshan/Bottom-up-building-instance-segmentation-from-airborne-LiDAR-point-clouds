#include "stdafx.h"
#include "ReadWrite.h"
#include "POINT3D.h"
#include <iostream> //标准输入输出流
//#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
//#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件
//#include <pcl/io/ply_io.h> //PCL的ply格式文件的输入输出头文件
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