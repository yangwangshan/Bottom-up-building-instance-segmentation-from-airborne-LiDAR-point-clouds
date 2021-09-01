// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__39D6F63D_46FB_424C_8C22_E583CC632A9F__INCLUDED_)
#define AFX_STDAFX_H__39D6F63D_46FB_424C_8C22_E583CC632A9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef STDAFX_H
#define STDAFX_H
//#include <vtkAutoInit.h>         
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);

//PCL
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/io/ply_io.h> //PCL的ply格式文件的输入输出头文件
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/common/impl/io.hpp>
#include <pcl/console/parse.h>
#include <pcl/sample_consensus/ransac.h>
#include <pcl/sample_consensus/sac_model_plane.h>
#include <pcl/sample_consensus/sac_model_sphere.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/common/transforms.h>
#include <pcl/common/common.h>
#include <pcl/common/time.h>
#include <pcl/common/angles.h>
#include <pcl/registration/transformation_estimation_svd.h>
#include <pcl/visualization/point_cloud_color_handlers.h>  
#include <pcl/filters/passthrough.h>  
#include <pcl/segmentation/supervoxel_clustering.h>  
#include <pcl/segmentation/lccp_segmentation.h>  
#include <pcl\sample_consensus\sac_model_line.h>
#include <pcl\point_types.h>
#include <pcl/filters/project_inliers.h>
#include<pcl/kdtree/io.h>
#include <pcl/surface/gp3.h>
#include <pcl/octree/octree.h>
#include <Eigen/Core>
#include <pcl/features/feature.h>
#include <pcl/features/eigen.h>
#include <pcl/impl/point_types.hpp>
#include <pcl/features/boundary.h>
#include <Eigen/Core>



//OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/highgui/highgui_c.h>




#endif //PCH_H



// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__39D6F63D_46FB_424C_8C22_E583CC632A9F__INCLUDED_)
