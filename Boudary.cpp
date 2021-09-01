#include "stdafx.h"
#include "Boudary.h"
#include <vector>
#include "POINT3D.h"
#include "myclass.h"
#include "PLANE.h"
#include "max_min.h"
#include "common.h"
#include "PCA1.h"
#include "Grid.h"

using namespace std;




Boudary::Boudary()
{
}


Boudary::~Boudary()
{
}



void Boudary::cylinder_neighbor_radius_Label(vector < vector<POINT3D>>incloud, double radius, double t_lable, vector <int>& is_no_merging)
{
	myclass mc;
	POINT3D point3d;
	vector < POINT3D>incloud_label;
	//vector < vector<POINT3D>>roof_instance;
	for (int i = 0; i < incloud.size(); i++)
	{
		for (int j = 0; j < incloud[i].size(); j++)
		{
			point3d.x = incloud[i][j].x;
			point3d.y = incloud[i][j].y;
			point3d.z = 0;
			point3d.label = i;
			incloud_label.push_back(point3d);
		}
	}
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	mc.SwitchDataAsciiToPCL(incloud_label, cloud);
	pcl::KdTreeFLANN<pcl::PointXYZ>kdtree;
	kdtree.setInputCloud(cloud);

	for (int i = 0; i < incloud.size(); i++)
	{
		vector<int>t_label;
		vector < int>num;
		vector < vector < int>>m_num;
		for (int j = 0; j < incloud[i].size(); j++)
		{
			pcl::PointXYZ searchPoint;
			searchPoint.x = incloud[i][j].x;
			searchPoint.y = incloud[i][j].y;
			searchPoint.z = 0;
			// 在半径r内搜索近邻
			std::vector<int> pointIdxRadiusSearch;
			std::vector<float> pointRadiusSquaredDistance;
			////float radius = 2;
			//std::cout << "Neighbors within radius search at (" << searchPoint.x
			//	<< " " << searchPoint.y
			//	<< " " << searchPoint.z
			//	<< ") with radius=" << radius << std::endl;
			//pcl::PointCloud<pcl::PointXYZRGB>::Ptr icloud(new pcl::PointCloud<pcl::PointXYZRGB>);

			if (kdtree.radiusSearch(searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
			{
				for (int k = 0; k < pointIdxRadiusSearch.size(); k++)
				{
					int a = pointIdxRadiusSearch[k];
					int label = incloud_label[a].label;
					t_label.push_back(label);
				}
			}
		}
		vector<int>t_label_sort;
		t_label_sort = t_label;
		sort(t_label_sort.begin(), t_label_sort.end());
		int jj = 0;
		for (int j = 0; j < t_label_sort.size() - 1; j++)
		{
			if (jj == 0)
			{
				if (t_label_sort[j] == t_label_sort[j + 1])
				{
					num.push_back(t_label_sort[j]);
				}
				else
				{
					num.push_back(t_label_sort[j]);
					m_num.push_back(num);
					jj = 1;
					j--;
				}
			}
			else
			{
				num.clear();
				vector<int>().swap(num);
				jj = 0;
				//j--;
				//num.push_back(t_label_sort[j]);
			}
		}
		num.push_back(t_label_sort[t_label_sort.size() - 1]);
		m_num.push_back(num);
		double  current_num = 0;
		vector<int>element_max;
		for (int j = 0; j < m_num.size(); j++)
		{
			if (i == m_num[j][0])
			{
				current_num = m_num[j].size();
			}
			else
			{
				element_max.push_back(m_num[j].size());
			}
		}
		if (element_max.size() > 0)
		{
			int sum_element = 0;
			for (int j = 0; j < element_max.size(); j++)
			{
				sum_element += element_max[j];
			}
			double element_rata = sum_element / current_num;
			if (element_rata > t_lable)
			{
				is_no_merging.push_back(1);
			}
			else
			{
				is_no_merging.push_back(0);
			}
		}
		else
		{
			is_no_merging.push_back(0);
		}
	}
	
}

void Boudary::PCA_linear_planar_volumetric(vector<POINT3D>&incloud, vector<POINT3D>&line, vector<POINT3D>&plane, vector<POINT3D>&volume)
{

	myclass mc;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	mc.SwitchDataAsciiToPCL(incloud, cloud);
	int cld_sz = cloud->size();
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	normals->resize(cld_sz);
	//计算中心点坐标
	double center_x = 0, center_y = 0, center_z = 0;
	for (int i = 0; i < cld_sz; i++)
	{
		center_x += cloud->points[i].x;
		center_y += cloud->points[i].y;
		center_z += cloud->points[i].z;
	}
	center_x /= cld_sz;
	center_y /= cld_sz;
	center_z /= cld_sz;
	//计算协方差矩阵
	double xx = 0, xy = 0, xz = 0, yy = 0, yz = 0, zz = 0;
	for (int i = 0; i < cld_sz; i++)
	{
		xx += (cloud->points[i].x - center_x) * (cloud->points[i].x - center_x);
		xy += (cloud->points[i].x - center_x) * (cloud->points[i].y - center_y);
		xz += (cloud->points[i].x - center_x) * (cloud->points[i].z - center_z);
		yy += (cloud->points[i].y - center_y) * (cloud->points[i].y - center_y);
		yz += (cloud->points[i].y - center_y) * (cloud->points[i].z - center_z);
		zz += (cloud->points[i].z - center_z) * (cloud->points[i].z - center_z);
	}
	//大小为3*3的协方差矩阵
	Eigen::Matrix3f covMat(3, 3);
	covMat(0, 0) = xx / cld_sz;
	covMat(0, 1) = covMat(1, 0) = xy / cld_sz;
	covMat(0, 2) = covMat(2, 0) = xz / cld_sz;
	covMat(1, 1) = yy / cld_sz;
	covMat(1, 2) = covMat(2, 1) = yz / cld_sz;
	covMat(2, 2) = zz / cld_sz;

	//求特征值与特征向量
	Eigen::EigenSolver<Eigen::Matrix3f> es(covMat);
	Eigen::Matrix3f val = es.pseudoEigenvalueMatrix();
	Eigen::Matrix3f vec = es.pseudoEigenvectors();

	//找到最小特征值t1
	//自己对特征值进行排序
	vector<double>t_value;
	t_value.push_back(val(0, 0));
	t_value.push_back(val(1, 1));
	t_value.push_back(val(2, 2));
	sort(t_value.begin(), t_value.end());
	double tz1 = t_value[2];
	double tz2 = t_value[1];
	double tz3 = t_value[0];
	double a1d = (sqrt(tz1) - sqrt(tz2)) / sqrt(tz1);
	double a2d = (sqrt(tz2) - sqrt(tz3)) / sqrt(tz1);
	double a3d = sqrt(tz3) / sqrt(tz1);
	if ((a1d > a2d) && (a1d > a3d))
	{
		line = incloud;
	}
	else if ((a2d > a1d) && (a2d > a3d))
	{
		plane = incloud;
	}
	else
	{
		volume = incloud;
	}

}


void Boudary::PCA_plane_normal(vector<POINT3D>&incloud, PLANE &NormalA)
{
	myclass mc;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	mc.SwitchDataAsciiToPCL(incloud, cloud);
	int cld_sz = cloud->size();
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	normals->resize(cld_sz);
	//计算中心点坐标
	double center_x = 0, center_y = 0, center_z = 0;
	for (int i = 0; i < cld_sz; i++)
	{
		center_x += cloud->points[i].x;
		center_y += cloud->points[i].y;
		center_z += cloud->points[i].z;
	}
	center_x /= cld_sz;
	center_y /= cld_sz;
	center_z /= cld_sz;
	//计算协方差矩阵
	double xx = 0, xy = 0, xz = 0, yy = 0, yz = 0, zz = 0;
	for (int i = 0; i < cld_sz; i++)
	{
		xx += (cloud->points[i].x - center_x) * (cloud->points[i].x - center_x);
		xy += (cloud->points[i].x - center_x) * (cloud->points[i].y - center_y);
		xz += (cloud->points[i].x - center_x) * (cloud->points[i].z - center_z);
		yy += (cloud->points[i].y - center_y) * (cloud->points[i].y - center_y);
		yz += (cloud->points[i].y - center_y) * (cloud->points[i].z - center_z);
		zz += (cloud->points[i].z - center_z) * (cloud->points[i].z - center_z);
	}
	//大小为3*3的协方差矩阵
	Eigen::Matrix3f covMat(3, 3);
	covMat(0, 0) = xx / cld_sz;
	covMat(0, 1) = covMat(1, 0) = xy / cld_sz;
	covMat(0, 2) = covMat(2, 0) = xz / cld_sz;
	covMat(1, 1) = yy / cld_sz;
	covMat(1, 2) = covMat(2, 1) = yz / cld_sz;
	covMat(2, 2) = zz / cld_sz;

	//求特征值与特征向量
	Eigen::EigenSolver<Eigen::Matrix3f> es(covMat);
	Eigen::Matrix3f val = es.pseudoEigenvalueMatrix();
	Eigen::Matrix3f vec = es.pseudoEigenvectors();

	//找到最小特征值t1
	//自己对特征值进行排序
	vector<double>t_value;
	t_value.push_back(val(0, 0));
	t_value.push_back(val(1, 1));
	t_value.push_back(val(2, 2));
	sort(t_value.begin(), t_value.end());
	double tz1 = t_value[2];
	double tz2 = t_value[1];
	double tz3 = t_value[0];
	int min_i = 0; int mid_i = 0; int max_i = 0;
	for (int i = 0; i < 3; i++)
	{
		if (t_value[0] == val(i, i))
		{
			min_i = i;
		}
		if (t_value[1] == val(i, i))
		{
			mid_i = i;
		}
		if (t_value[2] == val(i, i))
		{
			max_i = i;
		}
	}

	
	Eigen::Vector3f v1(vec(0, max_i), vec(1, max_i), vec(2, max_i));
	Eigen::Vector3f v2(vec(0, mid_i), vec(1, mid_i), vec(2, mid_i));
	NormalA.A = v1(1)*v2(2) - v2(1)*v1(2);
	NormalA.B = -(v1(0)*v2(2) - v2(0)*v1(2));
	NormalA.C = v1(0)*v2(1) - v2(0)*v1(1);


	
}

