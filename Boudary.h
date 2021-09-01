#ifndef _BOUDARY_H_
#define _BOUDARY_H_
#include <vector>
#include "POINT3D.h"
//#include "triangle.h"
#include "Plane.h"
using namespace std;

typedef vector<POINT3D>	PointArray;//点云组

typedef vector<int>	PointArrayIndex;//点云组索引

class Boudary
{


	


public:
	Boudary();
	~Boudary();
	

	void PCA_plane_normal(vector<POINT3D>&incloud, PLANE &NormalA);

	void PCA_linear_planar_volumetric(vector<POINT3D>&incloud, vector<POINT3D>&line, vector<POINT3D>&plane, vector<POINT3D>&volume);


	

	void cylinder_neighbor_radius_Label(vector < vector<POINT3D>>incloud, double radius, double t_lable, vector <int> &is_no_merging);




	
};
#endif 

////////////////////////////////////////////////////////////////////////////
////STL  C++ template class  类模板
////#include <math.h>
//#include <vector>
////#include <list>
////#include <cstring>
////#include <algorithm>
//using namespace std;
//
//
//class Outline
//{
//public:
//	Outline();
//	~Outline();
//
//public:
//	int dpID;    //数据点ID,用于建立数据点索引，便于后期查找
//	//POINT3D point;        //数据点三维坐标
//	//	long clusterID;       //聚类ID，用于将轮廓线与建筑物编号对应
//	bool visited;         //是否已访问标记
//	int NnPtID;  //最紧邻数据点id或最小旋转角对应点id
//	int LastPtID;//上一点对应的ID
//	//	float slope;//定义该点对应的斜率
//	//	bool iskeyPt;  //是否是轮廓线关键点
//	vector<int >arrivalPoints;    //邻域数据点id列表
//};
//
////typedef class CExtrOutline : public CWnd
//typedef class CExtrOutline 
//{
//public:
//	CExtrOutline(void);
//	~CExtrOutline(void);
//public:
//	void CalcConvexHull(vector<POINT3D> &vecSrc, vector<POINT3D> &vecSrcIndex);
//	void OnLocalConvexHull(vector<POINT3D> &in_Cloud, vector<int> &outlinIndex, vector<POINT3D> &m_OutlinePoints,
//		float MinRotateAngle, float m_pointInterval, float m_lchRadius, float m_ratio,
//		float m_lchRadiusSteps, int m_nSteps);
//	void ShrinkageIterativeConvexHull(vector<POINT3D> &in_Cloud, vector<int> &vecSrcIndex, vector<POINT3D> &m_Outline, float MinSidelength);
//
//protected:
//	bool segmentInsection(Outline &p1, Outline &p2, Outline &p3, Outline &p4);
//	bool onSegment(Outline &pi, Outline &pj, Outline &pk);
//	int direction(Outline &pi, Outline &pj, Outline &pk);
//	double GetK(POINT3D &p1, POINT3D &p2);
//	double GetCos(POINT3D &p1, POINT3D &p2);
//	double GetEpDistance(Outline &lp1, Outline &lp2, float Ratio, float theta);
//
//	void DoLCH_DeepReecursive(vector<Outline> &m_Outline, vector<Outline> &m_tempOutline,
//		vector<Outline>::iterator &lit, unsigned int &Interruptions, float &m_cosMinRotateAngle,
//		float &m_templchR, float &m_lchRadiusMax, float &m_lchRadiusSteps, float &m_lchRadius
//		, float &m_ratio, vector<vector<vector<unsigned long> > > &grid, int &m_LeftDownID);
//
//	void setArriPoints(vector<Outline> &m_Outline, vector<Outline>::iterator lit, float &m_lchRadius
//		, float &m_ratio, vector<vector<vector<unsigned long> > > &grid);
//
//	void ReSetArrivalPoints(vector<Outline> &m_Outline, Outline &lit, float &SearchRadius, float &m_ratio);
//
//}CExtrOutline;
//
//
//
//
////};