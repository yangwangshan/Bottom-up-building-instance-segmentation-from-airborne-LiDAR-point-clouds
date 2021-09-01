#pragma once

#include "POINT3D.h"
#include <vector>
using namespace std;
class CFSFDP
{
public:
	CFSFDP();
	~CFSFDP();

	

	vector<vector<POINT3D>>superpoint_segmentation(vector<POINT3D>& points, double dc,double up);

	

};

