#ifndef _COMMON_H_
#define _COMMON_H_


#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>//法向量
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/segmentation/extract_clusters.h>
#include <Eigen/Core>
#include <pcl/common/transforms.h>//  //转换矩阵
#include <pcl/common/common.h>
#include <pcl/common/time.h>
#include <pcl/common/angles.h>
#include <pcl/registration/transformation_estimation_svd.h>
#include <pcl/segmentation/region_growing.h>		//分割

#include<fstream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>



//点特征直方图

#include <string>
#include <stdio.h>
#include <pcl/io/ply_io.h>
#include <pcl/correspondence.h>                 //对应表示两个实体之间的匹配（例如，点，描述符等）。
#include <pcl/filters/uniform_sampling.h>    //均匀采样
#include <pcl/visualization/pcl_visualizer.h>   //可视化         
#include <pcl/console/parse.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/sample_consensus_prerejective.h>


//CGAL
//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Alpha_shape_2.h>
//#include <CGAL/Alpha_shape_vertex_base_2.h>
//#include <CGAL/Alpha_shape_face_base_2.h>
//#include <CGAL/Delaunay_triangulation_2.h>
//#include <CGAL/algorithm.h>
//#include <CGAL/assertions.h>
//#include <fstream>
//#include <iostream>
//#include <list>
//#include <vector>


//typedef pcl::PointXYZRGB PointT;             //Point with color
//typedef pcl::PointCloud<PointT> PointCloud; //PointCloud with color

using namespace pcl;

//template <class OutputIterator>




#endif    // _COMMON_H_