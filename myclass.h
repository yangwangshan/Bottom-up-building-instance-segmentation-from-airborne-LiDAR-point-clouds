#ifndef MYCLASS_H
#define MYCLASS_H
//#include "Point3D.h"
#include <vector>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
//#include "Point3D.h"
#include "POINT3D.h"
#include "Plane.h"

using namespace std;

class myclass
{
public:
	myclass();
	~myclass();


	
	
	void SwitchDataAsciiToPCLXYZL(vector<POINT3D> &icloud, pcl::PointCloud<pcl::PointXYZL>::Ptr &cloud);
	void SwitchDataAsciiToPCL(vector<POINT3D> &icloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);




};

#endif 