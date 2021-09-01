#ifndef _BOUDARY_H_
#define _BOUDARY_H_
#include <vector>
#include "POINT3D.h"
//#include "triangle.h"
#include "Plane.h"
using namespace std;

typedef vector<POINT3D>	PointArray;//������

typedef vector<int>	PointArrayIndex;//����������

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
////STL  C++ template class  ��ģ��
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
//	int dpID;    //���ݵ�ID,���ڽ������ݵ����������ں��ڲ���
//	//POINT3D point;        //���ݵ���ά����
//	//	long clusterID;       //����ID�����ڽ��������뽨�����Ŷ�Ӧ
//	bool visited;         //�Ƿ��ѷ��ʱ��
//	int NnPtID;  //��������ݵ�id����С��ת�Ƕ�Ӧ��id
//	int LastPtID;//��һ���Ӧ��ID
//	//	float slope;//����õ��Ӧ��б��
//	//	bool iskeyPt;  //�Ƿ��������߹ؼ���
//	vector<int >arrivalPoints;    //�������ݵ�id�б�
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