#ifndef _PLANE_H_
#define _PLANE_H_

#include <vector>
#include "POINT3D.h"
#include "myclass.h"
using namespace std;

typedef class PLANE //typedef--用于将Point3D定义为数据类型
{

public:
	PLANE();
	~PLANE();


public:
	//平面方程的系数A
	double A;
	//平面方程的系数B
	double B;
	//平面方程的系数C
	double C;
	//平面方程的系数D
	double D;
	//平面的曲率
	double curvature;
	/*vector<PLANE> normal;*/


public:
	
	double PlaneNormalsAngle3D(PLANE NormalA, PLANE NormalB);
	
	void instance_MBR(vector<vector<POINT3D>>incloud, double radius, double m_buffer, double min_height,
		double max_height, double mbr_max_threshold, vector<int>&is_or_merge);

	vector<vector<POINT3D>>optimal_Building_Facade_Emagemax2(vector<vector<POINT3D>>roof_superpoint, vector<vector<POINT3D>>facade_superpoint, double radius, double radius_min);


	vector<vector<POINT3D>> energy_optimization_superpoint_merging_new2(vector<vector<POINT3D>>&individual_building,
		double radius, double evaluation_min, double evaluation_difference,  double length_width, double length_width_threshold, double Energy_minimum);


	
	
	vector < vector<POINT3D>> kdtree_mergesingle_building_knn_cluster2d(vector < vector<POINT3D>>otherpoints2, vector < vector<POINT3D>>individual_building);



	double Minimum_2D_distance_between_clusters(vector<POINT3D>small_cluster, vector<POINT3D>big_cluster);

	
	
	void roofpoint_facadepoint_m_volume_knn(vector < POINT3D > &incloud,
		int k, double angle_threshold, vector < POINT3D >& roofpoint, vector <  POINT3D >& facadepoint);




	vector<vector<POINT3D>>Superpoint_graph_building_instance_segmentation(vector<POINT3D>&incloud);


	



}plane;//Point3D--指向空间点Point3D类型的指针
#endif 
