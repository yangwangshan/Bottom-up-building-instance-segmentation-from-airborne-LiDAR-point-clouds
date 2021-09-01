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
#include <pcl/features/normal_3d.h>//������
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/segmentation/extract_clusters.h>
#include <Eigen/Core>
#include <pcl/common/transforms.h>//  //ת������
#include <pcl/common/common.h>
#include <pcl/common/time.h>
#include <pcl/common/angles.h>
#include <pcl/registration/transformation_estimation_svd.h>
#include <pcl/segmentation/region_growing.h>		//�ָ�

#include<fstream>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>



//������ֱ��ͼ

#include <string>
#include <stdio.h>
#include <pcl/io/ply_io.h>
#include <pcl/correspondence.h>                 //��Ӧ��ʾ����ʵ��֮���ƥ�䣨���磬�㣬�������ȣ���
#include <pcl/filters/uniform_sampling.h>    //���Ȳ���
#include <pcl/visualization/pcl_visualizer.h>   //���ӻ�         
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