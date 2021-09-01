#include "stdafx.h"
#include "isodata.h"
#include "myclass.h"
#include<vector>
#include<algorithm>
#include<set>
#include<time.h>
#include<cstdlib>
#include<iostream>
#include <iterator>
#pragma warning(disable:4996)
//#include <pcl/ModelCoefficients.h>
//#include <pcl/point_types.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/filters/extract_indices.h>
//#include <pcl/filters/voxel_grid.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/kdtree/kdtree.h>
//#include <pcl/sample_consensus/method_types.h>
//#include <pcl/sample_consensus/model_types.h>
//#include <pcl/segmentation/sac_segmentation.h>
//#include <pcl/segmentation/extract_clusters.h>
#include "stdafx.h"


using namespace std;

isodata::isodata() :meandis(0), alpha(0), current_iter(0)
{
	time_t t;
	srand(time(&t));
}


isodata::~isodata()
{
}

