#ifndef PCA_H
#define PCA_H
#include <vector>
#include "POINT3D.h"
using namespace std;
class PCA1
{
public:
	PCA1();
	~PCA1();
	vector<POINT3D>  PCAalgorithm(vector<POINT3D> &incloud, double& length, double& width, double& angle);

	
};

#endif 