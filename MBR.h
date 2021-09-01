#ifndef MBR_H
#define MBR_H

#include "POINT3D.h"
#include <vector>
using namespace std;
class MBR
{
public:
	MBR();
	~MBR();

public:
	vector<vector<POINT3D>>perfectindividualbuildings;
	//double m_angle;

	
	vector<vector<POINT3D>>m_MBRdataClusteringestimate;
public:
//	

};

#endif 