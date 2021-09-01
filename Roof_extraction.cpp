#include "stdafx.h"
#include "Roof_extraction.h"
//#include <pcl/point_types.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/surface/gp3.h>
//#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
//#include <pcl/common/common.h>
#include <iostream>
#include<vector>
#include "myclass.h"
#include "PLANE.h"
#include "MBR.h"
#include "ReadWrite.h"
#include<math.h>
#include "CFSFDP.h"
//#include <pcl/filters/voxel_grid.h>

using namespace std;


Roof_extraction::Roof_extraction()
{
}


Roof_extraction::~Roof_extraction()
{
}