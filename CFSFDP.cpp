#include "stdafx.h"
#include "CFSFDP.h"
#include "Eight_neighborhood.h"
#include<algorithm>
#include "max_min.h"
#include "myclass.h"
//#include <pcl/point_cloud.h>
//#include <pcl/kdtree/kdtree_flann.h>
#include <iostream>
#include <vector>
#include "time.h"
#include "ReadWrite.h"
#include "MBR.h"
CFSFDP::CFSFDP()
{
}


CFSFDP::~CFSFDP()
{
}


vector<vector<POINT3D>>  CFSFDP::superpoint_segmentation(vector<POINT3D>& points, double dc, double up)
{
	myclass mc;
	ReadWrite rw;
	vector<vector<POINT3D>> ccloud;
	for (int k = 0; k < points.size(); k++)
	{
		points[k].IsVisisted = false;
	}

	vector<int> idtotal;//整体记录每个点是否已经加入到类中
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	mc.SwitchDataAsciiToPCL(points, cloud);
	pcl::KdTreeFLANN<pcl::PointXYZ>kdtree;
	kdtree.setInputCloud(cloud);
	pcl::PointXYZ searchPoint;
	for (int k = 0; k < points.size(); k++)
	{
		if (points[k].IsVisisted == false)
		{
			vector<int> id;//记录每个点是否已经加入到类中
			vector<POINT3D> temp;
			POINT3D point3d;
			searchPoint.x = points[k].x; //centre.x;
			searchPoint.y = points[k].y;
			searchPoint.z = points[k].z;
			points[k].IsVisisted = true;
			point3d.x = points[k].x;
			point3d.y = points[k].y;
			point3d.z = points[k].z;
			temp.push_back(point3d);
			id.push_back(k);
			// 在半径r内搜索近邻
			std::vector<int> pointIdxRadiusSearch;
			std::vector<float> pointRadiusSquaredDistance;
			if (kdtree.radiusSearch(searchPoint, dc, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
			{
				for (int i = 0; i < pointIdxRadiusSearch.size(); ++i)
				{

					if (pointIdxRadiusSearch.size() > up)
					{
						if (points[pointIdxRadiusSearch[i]].IsVisisted == false)
						{
							point3d.x = points[pointIdxRadiusSearch[i]].x;
							point3d.y = points[pointIdxRadiusSearch[i]].y;
							point3d.z = points[pointIdxRadiusSearch[i]].z;
							points[pointIdxRadiusSearch[i]].IsVisisted = true;
							//point3d.IsVisisted = true;
							temp.push_back(point3d);
							id.push_back(pointIdxRadiusSearch[i]);
							//idtotal.push_back(pointIdxRadiusSearch[i]);
							//rho[pointIdxRadiusSearch[i]] = 0;
						}
					}
				}
			}
			pointIdxRadiusSearch.clear();
			pointRadiusSquaredDistance.clear();
			for (int i = 0; i < id.size(); i++)
			{
				int a = id[i];
				//if (points[id[i]].IsVisisted==false)
				//{
				searchPoint.x = points[a].x;
				searchPoint.y = points[a].y;
				searchPoint.z = points[a].z;
				// 在半径r内搜索近邻
				std::vector<int> pointIdxRadiusSearch1;
				std::vector<float> pointRadiusSquaredDistance1;
				if (kdtree.radiusSearch(searchPoint, dc, pointIdxRadiusSearch1, pointRadiusSquaredDistance1) > 0)
				{
					for (int j = 0; j < pointIdxRadiusSearch1.size(); j++)
					{
						if (pointIdxRadiusSearch1.size() > up)
						{
							if (points[pointIdxRadiusSearch1[j]].IsVisisted == false)
							{

								point3d.x = points[pointIdxRadiusSearch1[j]].x;
								point3d.y = points[pointIdxRadiusSearch1[j]].y;
								point3d.z = points[pointIdxRadiusSearch1[j]].z;
								points[pointIdxRadiusSearch1[j]].IsVisisted = true;
								temp.push_back(point3d);
								id.push_back(pointIdxRadiusSearch1[j]);
							}
						}
					}
				}
			}

			if (temp.size() > 0)
			{
				ccloud.push_back(temp);
				temp.clear();
			}
			else
				break;
		}

	}
	return ccloud;
}

