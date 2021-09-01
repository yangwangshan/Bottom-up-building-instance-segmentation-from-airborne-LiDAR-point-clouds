#include "stdafx.h"
#include "Grid.h"
#include "POINT3D.h"
#include "max_min.h"
#include "myclass.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<vector>
#include"ReadWrite.h"
#include<math.h>
#include"Eight_neighborhood.h"
#include"CFSFDP.h"

using namespace std;
using namespace cv;
//using Point = Eigen::Vector3f;
Grid::Grid() :isVisisted(false), havepts(false), coi(0), coj(0), cok(0), grid_r(0), grid_g(0), grid_b(0), grid_intens(0), gird_z(0),
grid_density(0), grid_Ave_height(0), grid_Max_height(0), grid_Max_min_z(0), grid_hsv(0), grid_rgb_SD(0), grid_intens_SD(0), grid_xy_SD(0), grid_density_SD(0)

//,feature(0), IsVisisted(false)//, f(0), z_max(0), z_min(0), g(0), GWxy(0), GWh(0), a(0), b(0), c(0) m_point_n(0), 
{

}


Grid::~Grid()
{
}
