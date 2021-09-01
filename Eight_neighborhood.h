#pragma once
#include "POINT3D.h"
#include "max_min.h"

using namespace std;
//using namespace cv;
typedef class Eight_neighborhood
{
//private:
//	fake_grid* _grids;
public:
	/*bool isVisisted;
	bool havepts;
	vector<POINT3D>meshpts;
	vector<int>m_index;*/
public:
	Eight_neighborhood();
	~Eight_neighborhood();
	
	double grid3d_Cluster_evaluation(vector<POINT3D>& OriginData, double Gridthreshold, POINT3D totalmin);




} Eight_neighborhood;

