#ifndef _IMAGE_H_
#define _IMAGE_H_
typedef unsigned char  BYTE;
#include "POINT3D.h"
using namespace std;
using namespace cv;
struct pixelnode {
	int regionID;
	float z;
	float dir;
	float ndvi;
	BYTE idr;
	int prior;
	bool isEdge;
	BYTE ired;
	BYTE label;
};

class image
{
	public :
		int _size_x, _size_y;



public:
	image();
	~image();

	//

};
#endif 
