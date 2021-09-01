#include "stdafx.h"
#include "Eight_neighborhood.h"
#include "max_min.h"
#include <vector>
#include<algorithm>
#include "Grid.h"
#include <set>
#include<stdio.h>
#include<math.h>
#include "ReadWrite.h"
using namespace std;
using namespace cv;

Eight_neighborhood::Eight_neighborhood()
{
}


Eight_neighborhood::~Eight_neighborhood()
{
}

double Eight_neighborhood::grid3d_Cluster_evaluation(vector<POINT3D>& OriginData, double Gridthreshold, POINT3D totalmin)
{
	max_min mm;
	POINT3D max1, min1;
	//unsigned int r, c, l;
	mm.max_min_calculation(OriginData, max1, min1);
	POINT3D point3d;
	int m_nx = (max1.x - min1.x) / Gridthreshold + 1;
	int m_ny = (max1.y - min1.y) / Gridthreshold + 1;
	int m_nz = (max1.z - min1.z) / Gridthreshold + 1;
	int nz = (max1.z - totalmin.z) / Gridthreshold + 1;
	int grid_z = nz - m_nz;
	vector<vector<Grid> > GridPoints(m_nx, vector<Grid>(m_ny));//定义二维格网
	int number2d = 0;//二维格网实体的个数
	//double number3d = number2d * nz;//三维格网完全分割理论上实体个数
	int number3d_s = 0;
	vector < vector<vector<Grid> >> GridPoints3d(m_nx, vector < vector<Grid>>(m_ny, vector<Grid>(m_nz)));
	for (int i = 0; i < OriginData.size(); i++)
	{
		int r = (OriginData[i].x - min1.x) / Gridthreshold;
		int c = (OriginData[i].y - min1.y) / Gridthreshold;
		GridPoints[r][c].m_index.push_back(i);
		int l = (OriginData[i].z - min1.z) / Gridthreshold;
		GridPoints3d[r][c][l].m_index.push_back(i);
	}
	for (int i = 0; i < m_nx; i++)
	{
		for (int j = 0; j < m_ny; j++)
		{
			for (int k = m_nz - 1; k >= 0; k--)
			{
				GridPoints3d[i][j][k].havepts = false;
			}
		}
	}
	for (int i = 0; i < m_nx; i++)
	{
		for (int j = 0; j < m_ny; j++)
		{
			if (GridPoints[i][j].m_index.size() > 0)
			{
				number2d++;

			}
			for (int k = m_nz - 1; k >= 0; k--)
			{
				if ((GridPoints3d[i][j][k].m_index.size() > 0) && (GridPoints3d[i][j][k].havepts == false))
				{
					for (int m = k; m >= 0; m--)
					{
						GridPoints3d[i][j][k].havepts = true;//赋值初始值了，不重新赋值，会不会越界，到时候再说
						number3d_s++;
					}
					//number3d_s++;//为0的那一次没有算上
					number3d_s = number3d_s + grid_z;
					break;
				}
			}
		}
	}
	double number3d = number2d * nz;//三维格网完全分割理论上实体个数
	GridPoints.clear();
	vector < vector<Grid >>().swap(GridPoints);
	GridPoints3d.clear();
	vector < vector<vector<Grid> >>().swap(GridPoints3d);
	double rato = number3d_s / number3d;
	return rato;
}

