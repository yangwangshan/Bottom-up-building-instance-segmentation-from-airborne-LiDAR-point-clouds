#include "stdafx.h"
//#include "common.h"
#include "PCA1.h"
#include "POINT3D.h"
#include "myclass.h"
//#include <pcl/visualization/pcl_visualizer.h>
#include <iostream>
#include <string>
#include <vector>
#include "max_min.h"


#include <iostream>
#include <string>
#include <stdio.h>
#include <Eigen/Core>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/correspondence.h>                 //��Ӧ��ʾ����ʵ��֮���ƥ�䣨���磬�㣬�������ȣ���
#include <pcl/features/normal_3d.h>             //����

#include <pcl/filters/uniform_sampling.h>    //���Ȳ���
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/pcl_visualizer.h>   //���ӻ�
#include <pcl/common/transforms.h>              //ת������
#include <pcl/console/parse.h>
#include <pcl/point_types.h>

#include <pcl/common/time.h>
#include <pcl/console/print.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>
#include <pcl/filters/filter.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/sample_consensus_prerejective.h>
#include <pcl/segmentation/sac_segmentation.h>
#include "POINT3D.h"
#include "ReadWrite.h"
#include <vector>
using namespace std;
typedef pcl::PointXYZRGB PointT;             //Point with color
typedef pcl::PointCloud<PointT> PointCloud; //PointCloud with color
#define PI 3.14159265
using namespace Eigen;
//using namespace std;
typedef pcl::PointXYZ PointType;
typedef pcl::PointXYZRGB PointT;             //Point with color
typedef pcl::PointCloud<PointT> PointCloud; //PointCloud with color
PCA1::PCA1()
{
}

PCA1::~PCA1()
{
}



vector<POINT3D>  PCA1::PCAalgorithm(vector<POINT3D> &incloud, double& length, double& width, double& angle)
{

	
	pcl::PointCloud<PointType>::Ptr original_cloud(new pcl::PointCloud<PointType>());
	//ͷ�ļ�����
	//original_cloud->width = incloud->size();  //���õ�����Ŀ
	original_cloud->width = incloud.size();  //���õ�����Ŀ
	original_cloud->height = 1;     //����Ϊ�������
	original_cloud->is_dense = false;
	original_cloud->points.resize(original_cloud->width  *original_cloud->height);
	//������������
	//vector<POINT3D>::iterator pit = incloud.begin();
	max_min mm;
	POINT3D max1, min1;
	vector<POINT3D> inputcloud;
	mm.max_min_calculation(incloud, max1, min1);
	POINT3D middle;
	middle.x = (max1.x + min1.x) / 2;
	middle.y = (max1.y + min1.y) / 2;

	for (int i = 0; i < incloud.size(); i++)
	{

		original_cloud->points[i].x = incloud[i].x - middle.x;
		original_cloud->points[i].y = incloud[i].y - middle.y;
		original_cloud->points[i].z = 0;
		//pit++;
	}


	
	Eigen::Vector4f centroid;							// ����
	pcl::compute3DCentroid(*original_cloud, centroid);	// ������꣬��c0,c1,c2,1��

	Eigen::Matrix3f covariance;
	computeCovarianceMatrixNormalized(*original_cloud, centroid, covariance);		// �����һ��Э�������

	// ������������������������ֵ
	Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigen_solver(covariance, Eigen::ComputeEigenvectors);
	Eigen::Matrix3f eigen_vectors = eigen_solver.eigenvectors();
	//Eigen::Vector3f eigen_values = eigen_solver.eigenvalues();
	eigen_vectors.col(2) = eigen_vectors.col(0).cross(eigen_vectors.col(1));	// У��������䴹ֱ�������������� (e0, e1, e0 �� e1) --- note: e0 �� e1 = +/- e2��

	// ת���ο�����ϵ����������������ο�����ϵ����������ж���
	Eigen::Matrix4f transformation(Eigen::Matrix4f::Identity());
	transformation.block<3, 3>(0, 0) = eigen_vectors.transpose();										// R^(-1) = R^T
	transformation.block<3, 1>(0, 3) = -1.f * (transformation.block<3, 3>(0, 0) * centroid.head<3>());	// t^(-1) = -R^T * t

	pcl::PointCloud<PointType> transformed_cloud;	// �任��ĵ���
	pcl::transformPointCloud(*original_cloud, transformed_cloud, transformation);

	PointType min_pt, max_pt;						// �زο�����ϵ������ı߽�ֵ
	pcl::getMinMax3D(transformed_cloud, min_pt, max_pt);
	const Eigen::Vector3f mean_diag = 0.5f*(max_pt.getVector3fMap() + min_pt.getVector3fMap());	// ����

	// �ο�����ϵ������������ϵ�ı任��ϵ
	const Eigen::Quaternionf qfinal(eigen_vectors);
	//�������������ĵĳ˻��������ĵ�����Ϳ��Եõ�������ϵ��ͨ�����ַ���������ɲο�����ϵ��������ϵ��ת��
	const Eigen::Vector3f tfinal = eigen_vectors * mean_diag + centroid.head<3>();

	POINT3D max, min;
	MatrixXf tmp_A(3, 4);
	max.x = max_pt.x - transformation(12); //+ centroid(0);
	max.y = max_pt.y - transformation(13);//+ centroid.y;
	max.z = max_pt.z - transformation(14);//+ centroid.z;
	min.x = min_pt.x - transformation(12); //+ centroid.x;
	min.y = min_pt.y - transformation(13); //+ centroid.y;
	min.z = min_pt.z - transformation(14);// + centroid.z;
	

	tmp_A(0, 0) = min.x;// +min1.x;// +centroid(0);
	tmp_A(1, 0) = min.y;// +min1.y;// +centroid(1);
	tmp_A(2, 0) = max.z;// +centroid(2);

	tmp_A(0, 1) = max.x;// +min1.x;// +centroid(0);
	tmp_A(1, 1) = min.y;// +min1.y;// +centroid(1);
	tmp_A(2, 1) = min.z;// +centroid(2);

	tmp_A(0, 2) = max.x;// +min1.x;// +centroid(0);
	tmp_A(1, 2) = max.y;// +min1.y;// +centroid(1);
	tmp_A(2, 2) = min.z;// +centroid(2);

	tmp_A(0, 3) = min.x;// +min1.x;// +centroid(0);
	tmp_A(1, 3) = max.y;// +min1.y;// +centroid(1);
	tmp_A(2, 3) = max.z;// +centroid(2);



	MatrixXf tmp_C(3, 4);
	tmp_C = eigen_vectors * tmp_A;
	
	vector<POINT3D> vertex;
	POINT3D vertex0; POINT3D vertex1;
	POINT3D vertex2; POINT3D vertex3;
	vertex0.x = tmp_C(0, 0) + middle.x;
	vertex0.y = tmp_C(1, 0) + middle.y;
	vertex1.x = tmp_C(0, 1) + middle.x;
	vertex1.y = tmp_C(1, 1) + middle.y;

	vertex2.x = tmp_C(0, 2) + middle.x;
	vertex2.y = tmp_C(1, 2) + middle.y;
	vertex3.x = tmp_C(0, 3) + middle.x;
	vertex3.y = tmp_C(1, 3) + middle.y;

	vertex.push_back(vertex1);
	vertex.push_back(vertex2);
	vertex.push_back(vertex3);
	vertex.push_back(vertex0);

	width = sqrt((vertex0.x - vertex1.x)*(vertex0.x - vertex1.x) + (vertex0.y - vertex1.y)*(vertex0.y - vertex1.y));
	length = sqrt((vertex0.x - vertex3.x)*(vertex0.x - vertex3.x) + (vertex0.y - vertex3.y)*(vertex0.y - vertex3.y));
	//double angle= x1x2 + y1y2 + z1z2
	POINT3D vec1;
	vec1.x = max1.x - min1.x;
	vec1.y = 0;// max.y - min.y;
	POINT3D vec2;
	vec2.x = vertex0.x - vertex3.x;
	vec2.y = vertex0.y - vertex3.y;
	if (vec2.x == 0 || vec2.y == 0)
	{
		angle = 0;
	}
	else
	{
		double ab = (vec1.x*vec2.x + vec1.y*vec2.y);
		double a = sqrt(vec1.x*vec1.x + vec1.y*vec1.y);
		double b = sqrt(vec2.x*vec2.x + vec2.y*vec2.y);
		double val = ab / (a * b);
		angle = acos(val) * 180.0 / PI;
		if (angle > 90)
		{
			angle = angle - 90;
		}
	}
	return vertex;

}

