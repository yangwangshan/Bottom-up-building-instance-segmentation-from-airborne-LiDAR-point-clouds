#include "stdafx.h"
#include "myclass.h"
#include <iostream> //标准输入输出流
//#include <pcl/io/pcd_io.h> //PCL的PCD格式文件的输入输出头文件
//#include <pcl/point_types.h> //PCL对各种格式的点的支持头文件
//#include <pcl/io/ply_io.h> //PCL的ply格式文件的输入输出头文件
////#include "Point3D.h"
#include <vector>
//#include <pcl/filters/statistical_outlier_removal.h>
//#include <pcl/filters/voxel_grid.h>
////#include "lasreader.h"
//
//#include <pcl/ModelCoefficients.h>
//#include <pcl/filters/extract_indices.h>
//#include <pcl/filters/voxel_grid.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/kdtree/kdtree.h>
//#include <pcl/sample_consensus/method_types.h>
//#include <pcl/sample_consensus/model_types.h>
//#include <pcl/segmentation/sac_segmentation.h>
//#include <pcl/segmentation/extract_clusters.h>
#include <Eigen/Core>
//#include <pcl/common/impl/io.hpp>
//#include <pcl/point_cloud.h>
//#include <pcl/segmentation/sac_segmentation.h>
//#include <pcl/ModelCoefficients.h>
#include "iterator" //求交并补使用到的迭代器
//#include "algorithm" //sort函数、交并补函数
#include <algorithm>
//#include <pcl/console/parse.h>
//#include <pcl/sample_consensus/ransac.h>
//#include <pcl/sample_consensus/sac_model_plane.h>
//#include <pcl/sample_consensus/sac_model_sphere.h>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <pcl/filters/radius_outlier_removal.h>
//#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/common/transforms.h>
//#include <pcl/common/common.h>
//#include <pcl/common/time.h>
//#include <pcl/common/angles.h>
//#include <pcl/registration/transformation_estimation_svd.h>
////超体聚类+LCCP
#include <pcl/surface/mls.h>
#include "ReadWrite.h"
#include <stdlib.h>    //malloc  free
#include <cmath>  
#include <limits.h>  
#include <boost/format.hpp>  
#include <fstream> 
#include "MBR.h"
//#include <pcl/console/parse.h>  
//#include <pcl/io/pcd_io.h>  
//#include <pcl/visualization/pcl_visualizer.h>  
//#include <pcl/visualization/point_cloud_color_handlers.h>  
//#include <pcl/visualization/cloud_viewer.h>
//
//#include <pcl/filters/passthrough.h>  
//#include <pcl/segmentation/supervoxel_clustering.h>  
//
//#include <pcl/segmentation/lccp_segmentation.h>  
#include "max_min.h"
#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "WuLasFile.h"
#include "time.h"
//#include <pcl\sample_consensus\sac_model_line.h>
////#include <pcl\sample_consensus\sac_model_circle2d.h>
//#include <pcl\point_types.h>
//
//#include <pcl/filters/project_inliers.h>
#include "Eight_neighborhood.h"
#include <iomanip>
#include "max_min.h"
//
using namespace std;
typedef pcl::PointXYZ PointType;
#define Random(x) (rand() % x)
typedef pcl::PointXYZRGBA PointT;
typedef pcl::LCCPSegmentation<PointT>::SupervoxelAdjacencyList SuperVoxelAdjacencyList;


myclass::myclass()
{
}


myclass::~myclass()
{
}


void myclass::SwitchDataAsciiToPCL(vector<POINT3D> &icloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
	//头文件定义
	cloud->width = (int)icloud.size();  //设置点云数目
	cloud->height = 1;     //设置为无序点云
	cloud->is_dense = false;
	cloud->points.resize(cloud->width*cloud->height);
	//拷贝点云数据
	vector<POINT3D>::iterator pit = icloud.begin();
	for (unsigned i = 0; i < cloud->points.size(); ++i)
	{
		cloud->points[i].x = pit->x;
		cloud->points[i].y = pit->y;
		cloud->points[i].z = pit->z;
		//cloud->points[i].label = pit->label;
		pit++;
	}
}

void myclass::SwitchDataAsciiToPCLXYZL(vector<POINT3D> &icloud, pcl::PointCloud<pcl::PointXYZL>::Ptr &cloud)
{
	//头文件定义
	cloud->width = (int)icloud.size();  //设置点云数目
	cloud->height = 1;     //设置为无序点云
	cloud->is_dense = false;
	cloud->points.resize(cloud->width*cloud->height);
	//拷贝点云数据
	vector<POINT3D>::iterator pit = icloud.begin();
	for (unsigned i = 0; i < cloud->points.size(); ++i)
	{
		cloud->points[i].x = pit->x;
		cloud->points[i].y = pit->y;
		cloud->points[i].z = pit->z;
		cloud->points[i].label = pit->label;
		pit++;
	}
}
