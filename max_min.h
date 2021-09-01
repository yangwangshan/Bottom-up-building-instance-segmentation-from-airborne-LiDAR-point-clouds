#ifndef MAX_MIN_H
#define MAX_MIN_H

#include <vector>
#include "POINT3D.h"
using namespace std;

class max_min
{

public:
	POINT3D m_buildingsmax;
	POINT3D m_buildingsmin;


public:
	max_min();
	~max_min();

	
	void max_min_calculation(vector<POINT3D > &incloud, POINT3D &max, POINT3D &min);

	void max_min_mean_calculation(vector<POINT3D > &incloud, POINT3D &max, POINT3D &min, POINT3D&mean);
	


};
#endif 
