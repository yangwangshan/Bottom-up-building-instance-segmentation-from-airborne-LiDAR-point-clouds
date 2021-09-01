#include "stdafx.h"
#include "PLANE.h"
#include "POINT3D.h"
#include "max_min.h"
#include "MBR.h"
#include "myclass.h"
#include "ReadWrite.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include "ReadWrite.h"
#include "Roof_extraction.h"
#include "projection.h"
#include "Grid.h"
#include "Eight_neighborhood.h"
#include "Boudary.h"
#include "Grid.h"
#include"common.h"
#include"CFSFDP.h"
#include"PCA1.h"
#include <set>
#define DEBUG
#define RELEASE
using namespace std;
typedef pcl::PointXYZ PointT;
typedef std::vector< pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ> > AlignedPointTVector;   ///分配内存对齐Eigen::MatrixXf;
#define PI 3.141592653
PLANE::PLANE() :A(0), B(0), C(0), D(0), curvature(0)
{
}


PLANE::~PLANE()
{
}

void PLANE::roofpoint_facadepoint_m_volume_knn(vector < POINT3D > &incloud,
	int k, double angle_threshold, vector < POINT3D >& roofpoint, vector <  POINT3D >& facadepoint)
{
	PLANE plane;
	POINT3D point3d;
	Boudary bd;
	CFSFDP cf;
	ReadWrite rw;
	myclass mc;
	PLANE NormalB;
	NormalB.A = 0;
	NormalB.B = 0;
	NormalB.C = 1;
	PLANE NormalA;
	//noplanepoint = incloud;
	pcl::PointCloud<pcl::PointXYZ>::Ptr pointcloud(new pcl::PointCloud<pcl::PointXYZ>);
	mc.SwitchDataAsciiToPCL(incloud, pointcloud);
	pcl::KdTreeFLANN<pcl::PointXYZ>kdtree;
	kdtree.setInputCloud(pointcloud);

	vector<POINT3D>t_line; vector<POINT3D>t_plane; vector<POINT3D>t_volume;
	for (int i = 0; i < incloud.size(); ++i)
	{
		pcl::PointXYZ searchPoint;
		//int K = 10;
		int K = k;
		std::vector<int> pointIdxNKNSearch(K);      //存储查询点近邻索引
		std::vector<float> pointNKNSquaredDistance(K); //存储近邻点对应距离平方
		
		searchPoint.x = incloud[i].x; //centre.x;
		searchPoint.y = incloud[i].y;
		searchPoint.z = incloud[i].z;
		// 在半径r内搜索近邻
		//std::vector<int> pointIdxRadiusSearch;
		//std::vector<float> pointRadiusSquaredDistance;
		kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance);
		//int a = pointIdxNKNSearch[0];
		//inindices.push_back(a);//可以获得索引，通过索引获得反索引，可以更好的获得那些点
		vector < POINT3D > temp_point;
		for (int j = 0; j < K; j++)
		{
			int a = pointIdxNKNSearch[j];
			point3d.x = incloud[a].x;
			point3d.y = incloud[a].y;
			point3d.z = incloud[a].z;
			temp_point.push_back(point3d);
		}
		vector<POINT3D>line; vector<POINT3D>plane; vector<POINT3D>volume;
		bd.PCA_linear_planar_volumetric(temp_point, line, plane, volume);//线、面和球的判断
		if (plane.size() > 0)
		{
			bd.PCA_plane_normal(temp_point, NormalA);//计算法向量判断是立面还是屋顶
		//double angle = plane.PlaneNormalsAngle3D(NormalA, NormalB);
			double angle = PlaneNormalsAngle3D(NormalA, NormalB);//明天往下继续
			//m_angle.push_back(angle);
			//vector < POINT3D > temp_facadepoint;
			if (angle > 90)
			{
				if ((angle - 90) > angle_threshold)
				{
					point3d.x = incloud[i].x;
					point3d.y = incloud[i].y;
					point3d.z = incloud[i].z;
					roofpoint.push_back(point3d);

				}
				else
				{
					point3d.x = incloud[i].x;
					point3d.y = incloud[i].y;
					point3d.z = incloud[i].z;
					facadepoint.push_back(point3d);

				}
			}
			else
			{
				if ((90 - angle) > angle_threshold)
				{
					point3d.x = incloud[i].x;
					point3d.y = incloud[i].y;
					point3d.z = incloud[i].z;
					roofpoint.push_back(point3d);

				}
				else
				{
					point3d.x = incloud[i].x;
					point3d.y = incloud[i].y;
					point3d.z = incloud[i].z;
					facadepoint.push_back(point3d);
				}
			}
			point3d.x = incloud[i].x;
			point3d.y = incloud[i].y;
			point3d.z = incloud[i].z;
			t_plane.push_back(point3d);
		}

		if (line.size() > 0)
		{
			point3d.x = incloud[i].x;
			point3d.y = incloud[i].y;
			point3d.z = incloud[i].z;
			roofpoint.push_back(point3d);
			t_line.push_back(point3d);
		}

		if (volume.size() > 0)
		{
			point3d.x = incloud[i].x;
			point3d.y = incloud[i].y;
			point3d.z = incloud[i].z;
			roofpoint.push_back(point3d);
			t_volume.push_back(point3d);
		}
	}
	//string t_outtxt_txtline = "E:\\t_line.txt";
	//rw.write_txt(t_outtxt_txtline, t_line);

	//string t_outtxt_txtplane = "E:\\t_plane.txt";
	//rw.write_txt(t_outtxt_txtplane, t_plane);

	//string t_outtxt_txtvolume = "E:\\t_volume.txt";
	//rw.write_txt(t_outtxt_txtvolume, t_volume);



	//vector<vector<POINT3D>>t_line_Superpoint = cf.superpoint_segmentation(t_line, 0.8, 3);////ANH3	
	//string outtxt_t_line_Superpoint01 = "E:\\t_line_Superpoint01.txt";
	//vector<POINT3D>m_t_line_Superpoint = rw.IndividualRGBpointcloud(t_line_Superpoint);
	//rw.write_txt(outtxt_t_line_Superpoint01, m_t_line_Superpoint);

	//vector<vector<POINT3D>>t_plane_Superpoint = cf.superpoint_segmentation(t_plane, 0.8, 3);////ANH3	
	//string outtxt_t_plane_Superpoint01 = "E:\\t_plane_Superpoint01.txt";
	//vector<POINT3D>m_t_plane_Superpoint = rw.IndividualRGBpointcloud(t_plane_Superpoint);
	//rw.write_txt(outtxt_t_plane_Superpoint01, m_t_plane_Superpoint);

	//vector<vector<POINT3D>>t_volume_Superpoint = cf.superpoint_segmentation(t_volume, 0.8, 3);////ANH3	
	//string outtxt_t_volume_Superpoint01 = "E:\\t_volume_Superpoint01.txt";
	//vector<POINT3D>m_t_volume_Superpoint = rw.IndividualRGBpointcloud(t_volume_Superpoint);
	//rw.write_txt(outtxt_t_volume_Superpoint01, m_t_volume_Superpoint);

}



vector<vector<POINT3D>> PLANE::energy_optimization_superpoint_merging_new2(vector<vector<POINT3D>>&individual_building,
	double radius, double evaluation_min, double evaluation_difference, double length_width, double length_width_threshold, double Energy_minimum)
{
	POINT3D point3d;
	ReadWrite rw;
	myclass mc;
	vector<POINT3D>building;
	vector<POINT3D>building2d;
	max_min mm;
	Eight_neighborhood en;
	Boudary bd;
	PCA1 pca;
	//double T_label_value = 1;
	//能量函数前的系数
	double aa = -1;
	double bb = 1;
	double cc = 1;
	double t_length_width = 0;
	//double dd = 15;
	//double ee = 1;
	double min_min = 0.000001; //(1.0) / (1000.0);
	//double min_min = 1;
	//Boudary bd;
	//Grid grid;
	//int num= individual_building.size()
	vector<vector<POINT3D>>Isolated_point;//在二维邻域搜索范围内没有其他建筑物。
	//vector<vector<POINT3D>>Isolated_point2;
	vector<POINT3D>small_building_emage;
	vector<double>min_energy_value;
	//vector<vector<POINT3D>>total_indivudal_building;
	vector<vector<POINT3D>>emage_indivudal_building;

	//int i_temp = 0;//将建筑物单体的label设置大于1、
	//对超点中所包含的点从小到大进行排序
	vector<int >pointnum;
	for (int i = 0; i < individual_building.size(); i++)
	{
		pointnum.push_back(individual_building[i].size());

	}
	////应该把他从
	vector<int >pointnum_sort;
	pointnum_sort = pointnum;
	sort(pointnum_sort.begin(), pointnum_sort.end());
	vector<vector<POINT3D>>total_indivudal_building_sort;
	for (int i = 0; i < individual_building.size(); i++)
	{
		for (int j = 0; j < individual_building.size(); j++)
		{
			if (pointnum_sort[i] == individual_building[j].size())
			{
				total_indivudal_building_sort.push_back(individual_building[j]);
				individual_building[j].clear();
				break;
			}
		}
	}
	int iii = 0;
	//排序后的超点（从小到大排序）
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		for (int j = 0; j < total_indivudal_building_sort[i].size(); j++)
		{
			point3d.x = total_indivudal_building_sort[i][j].x;
			point3d.y = total_indivudal_building_sort[i][j].y;
			point3d.z = total_indivudal_building_sort[i][j].z;
			//i_temp = i + 1;
			point3d.label = i;
			building.push_back(point3d);
			//tempbuilding.push_back(point3d);
			point3d.x = total_indivudal_building_sort[i][j].x;
			point3d.y = total_indivudal_building_sort[i][j].y;
			point3d.z = 0;
			building2d.push_back(point3d);
			iii = i;
		}
	}


	//std::cout << "0000000000000000000" << std::endl;
	//屋顶细节结构
	vector<vector<POINT3D>>is_merge_roof_Superpoint;
	vector<vector<POINT3D>>no_merge_roof_Superpoint;
	vector<int>is_no_merge2;
	//instance_MBR(total_indivudal_building_sort, 1.2, 0.5, 3, 4, 20, is_no_merge2);
	instance_MBR(total_indivudal_building_sort, 1.2, 0.5, 3, 4, 10000, is_no_merge2);//这样不会限制最小外接矩形大小
	//std::cout << "11111111111111111111" << std::endl;
	//重叠度合并好像还有问题
	vector <int> is_no_merging;
	bd.cylinder_neighbor_radius_Label(total_indivudal_building_sort, radius, 1, is_no_merging);
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		if ((is_no_merge2[i] == 1) && (is_no_merging[i] == 0))
		{
			is_merge_roof_Superpoint.push_back(total_indivudal_building_sort[i]);
		}
		else
		{
			no_merge_roof_Superpoint.push_back(total_indivudal_building_sort[i]);
		}
	}

	//string outtxt_txtis_merge_roof_Superpoint = "E:\\is_merge_roof_Superpoint_detail.txt";
	//vector<POINT3D>m_is_merge_roof_Superpoint = rw.IndividualRGBpointcloud(is_merge_roof_Superpoint);
	//rw.write_txt(outtxt_txtis_merge_roof_Superpoint, m_is_merge_roof_Superpoint);
	//string outtxt_txtno_merge_roof_Superpoint = "E:\\no_merge_roof_Superpoint_detail.txt";
	//vector<POINT3D>m_no_merge_roof_Superpoint = rw.IndividualRGBpointcloud(no_merge_roof_Superpoint);
	//rw.write_txt(outtxt_txtno_merge_roof_Superpoint, m_no_merge_roof_Superpoint);



	////cout << "2、屋顶细节结构  :" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
	//std::cout << "002、屋顶细节结构" << std::endl;


	vector<vector<POINT3D>>is_merge_Superpoint;
	vector<vector<POINT3D>>no_merge_Superpoint;
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		if ((is_no_merging[i] == 1) && (is_no_merge2[i] == 0))
			//if ((is_no_merging[i] == 1)|| (is_no_merge2[i] == 1))
		{
			is_merge_Superpoint.push_back(total_indivudal_building_sort[i]);
		}
		else
		{
			no_merge_Superpoint.push_back(total_indivudal_building_sort[i]);
		}
	}
	//string outtxt_txtis_merge_Superpoint = "E:\\is_merge_Superpoint_facade.txt";
	//vector<POINT3D>m_is_merge_Superpoint = rw.IndividualRGBpointcloud(is_merge_Superpoint);
	//rw.write_txt(outtxt_txtis_merge_Superpoint, m_is_merge_Superpoint);

	//string outtxt_txtno_merge_Superpoint = "E:\\no_merge_Superpoint_facade.txt";
	//vector<POINT3D>m_no_merge_Superpoint = rw.IndividualRGBpointcloud(no_merge_Superpoint);
	//rw.write_txt(outtxt_txtno_merge_Superpoint, m_no_merge_Superpoint);
	//std::cout << "002、重叠度即立面点云" << std::endl;


	vector<vector<POINT3D>>roof_Superpoint2;
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		if ((is_no_merging[i] == 0) && (is_no_merge2[i] == 0))
			//if ((is_no_merging[i] == 1)|| (is_no_merge2[i] == 1))
		{
			roof_Superpoint2.push_back(total_indivudal_building_sort[i]);
		}
	}
	/*string outtxt_txtroof_Superpoint2 = "E:\\roof_Superpoint2.txt";
	vector<POINT3D>m_roof_Superpoint2 = rw.IndividualRGBpointcloud(roof_Superpoint2);
	rw.write_txt(outtxt_txtroof_Superpoint2, m_roof_Superpoint2);
	std::cout << "002、屋顶超点" << std::endl;*/


	vector<vector<POINT3D>>is_merge_Superpoint2;
	vector<vector<POINT3D>>no_merge_Superpoint2;
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		//if (is_no_merging[i] == 1)
		if ((is_no_merging[i] == 1) || (is_no_merge2[i] == 1))
		{
			is_merge_Superpoint2.push_back(total_indivudal_building_sort[i]);
			is_no_merging[i] = 1;
		}
		else
		{
			no_merge_Superpoint2.push_back(total_indivudal_building_sort[i]);
		}
	}
	/*string outtxt_txtis_merge_Superpoint2 = "E:\\is_merge_Superpoint2.txt";
	vector<POINT3D>m_is_merge_Superpoint2 = rw.IndividualRGBpointcloud(is_merge_Superpoint2);
	rw.write_txt(outtxt_txtis_merge_Superpoint2, m_is_merge_Superpoint2);

	string outtxt_txtno_merge_Superpoint2 = "E:\\no_merge_Superpoint2.txt";
	vector<POINT3D>m_no_merge_Superpoint2 = rw.IndividualRGBpointcloud(no_merge_Superpoint2);
	rw.write_txt(outtxt_txtno_merge_Superpoint2, m_no_merge_Superpoint2);
	std::cout << "222、是否合并" << std::endl;*/


	//vector<vector<POINT3D>>total_indivudal_building_sort;
	//total_indivudal_building_sort = individual_building;
	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input_building2d(new pcl::PointCloud<pcl::PointXYZL>);
	mc.SwitchDataAsciiToPCLXYZL(building2d, cloud_input_building2d);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree2d;
	kdtree2d.setInputCloud(cloud_input_building2d);//kdtree2仅单体建筑物点云
	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input_building(new pcl::PointCloud<pcl::PointXYZL>);
	mc.SwitchDataAsciiToPCLXYZL(building, cloud_input_building);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree;
	kdtree.setInputCloud(cloud_input_building);//kdtree2仅单体建筑物点云
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		float mindis = 0;
		int label = 0;
		vector<int>t_label;

		for (int j = 0; j < total_indivudal_building_sort[i].size(); j++)
		{
			//int KK1 = 1;
			pcl::PointXYZL searchPoint;

			searchPoint.x = total_indivudal_building_sort[i][j].x;
			searchPoint.y = total_indivudal_building_sort[i][j].y;
			searchPoint.z = 0;// total_indivudal_building[i][j].z;//往下好多都是错误的
			std::vector<int>pointIdxNKNSearch;
			std::vector<float>pointNKNSquaredDistance;
			if (kdtree2d.radiusSearch(searchPoint, radius, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)//kdtree2仅单体建筑物点云
			{
				for (int k = 0; k < pointIdxNKNSearch.size(); k++)
					//for (int k = 0; k < 1; k++)
				{
					if (t_label.size() == 0)
					{
						int bb = t_label.size();
						int a = pointIdxNKNSearch[k];
						label = building[a].label;
						t_label.push_back(label);
					}
					if (t_label.size() > 0)
					{
						int bb = t_label.size();
						int a = pointIdxNKNSearch[k];
						label = building[a].label;
						if (t_label[bb - 1] != label)
						{
							t_label.push_back(label);
							//break;
						}
					}
				}
			}
		}
		//周围超点的个数
		if (t_label.size() > 0)
		{
			if (t_label.size() > 1)
			{
				vector<int>label1_sort;
				label1_sort = t_label;
				sort(label1_sort.begin(), label1_sort.end());
				//int k = 1;
				vector<int> number_label;
				number_label.push_back(label1_sort[0]);
				for (int j = 0; j < label1_sort.size() - 1; j++)
				{
					if (label1_sort[j] != label1_sort[j + 1])
					{
						//k++;//这样计算整好等于label个数
						number_label.push_back(label1_sort[j + 1]);//这样计算整好等于label个数
					}
				}
				if (number_label.size() > 1)
				{
					vector<double>energy_value;//能量值
					//vector<double>length_width_value;该参数弃用
					vector<double> evaluation_difference_value;//模型一致性差异值
					vector<double> evaluation_value;//模型一致性值
					vector<double> cluster_distance2d_value;//两个簇之间的二维距离
					vector<double> cluster_distance3d_value;//两个簇之间的三维距离
					vector<int> is_noise_point;//是否是
					vector<POINT3D>temp_individual;
					double grid3dd1 = 0;
					int ii = -1;

					for (int j = 1; j < number_label.size(); j++)
					{
						//在立面没有合并的时候是这样，合并后不是这样

						//ifdayu
						if ((number_label[j]) > i)
						{
							int a = number_label[j];
							vector<POINT3D>Multiple_Building;
							Multiple_Building = total_indivudal_building_sort[a];//要合并到的建筑物上，两个簇中点云较多的那个簇
							POINT3D max, min, mean0;
							//mm.max_min_meanZ_calculation(Multiple_Building, max, min, mean0);
							mm.max_min_calculation(Multiple_Building, max, min);
							double grid3dd = en.grid3d_Cluster_evaluation(Multiple_Building, radius, min);
							for (int k = 0; k < total_indivudal_building_sort[i].size(); k++)
							{
								point3d.x = total_indivudal_building_sort[i][k].x;
								point3d.y = total_indivudal_building_sort[i][k].y;
								point3d.z = total_indivudal_building_sort[i][k].z;//往下好多都是错误的
								Multiple_Building.push_back(point3d);
							}

							//模型一致性差异性
							POINT3D max1, min1, mean1;
							//mm.max_min_meanZ_calculation(Multiple_Building, max1, min1, mean1);
							mm.max_min_calculation(Multiple_Building, max1, min1);
							grid3dd1 = en.grid3d_Cluster_evaluation(Multiple_Building, radius, min1);
							double m_evaluation_difference = grid3dd - grid3dd1;

							//建筑物之间的二维距离
							double dis2d = Minimum_2D_distance_between_clusters(total_indivudal_building_sort[i], total_indivudal_building_sort[a]);
							//double dis3d = Minimum_3D_distance_between_clusters(total_indivudal_building_sort[i], total_indivudal_building_sort[a]);
							cluster_distance2d_value.push_back(dis2d);//两个簇之间的最小二维距离
							if (is_no_merging[i] == 1)
							{
								is_noise_point.push_back(1);//是小于阈值的建筑物,
								//length_width_value.push_back(1);
								evaluation_difference_value.push_back(m_evaluation_difference);//能量优化计算是否合并
								evaluation_value.push_back(grid3dd1);//能量优化计算是否合并
							}
							else
							{
								if (total_indivudal_building_sort[i].size() < 3)//为了加速计算临时设置的，一个屋顶的点不会少于10个点，每个根据长和宽进行换算
								{
									is_noise_point.push_back(1);//是小于阈值的建筑物,
									//length_width_value.push_back(1);
									evaluation_difference_value.push_back(m_evaluation_difference);//能量优化计算是否合并
									evaluation_value.push_back(grid3dd1);//能量优化计算是否合并
								}
								else
								{
									is_noise_point.push_back(0);//不是小于阈值的建筑物
										//evaluation_value.push_back(grid3dd1);//模型一致性
									if (m_evaluation_difference > evaluation_difference)//模型一致性差异大于阈值，不合并，否则合并
									{
										evaluation_difference_value.push_back(100);//不合并//模型一致性差异太大
									}
									else
									{
										evaluation_difference_value.push_back(m_evaluation_difference);//能量优化计算是否合并
									}
									if (grid3dd1 < evaluation_min)//模型一致性小于阈值不合并，否则合并
									{
										evaluation_value.push_back(-100);//不合并//模型一致性不强
										//length_width_value.push_back(1);
									}
									else
									{
										evaluation_value.push_back(grid3dd1);//能量优化计算是否合并
										//length_width_value.push_back(1);
									}

								}

							}

						}
						else
						{
							//length_width_value.push_back(1);
							//表示该实例不合并到比自己小的实例上
							evaluation_value.push_back(-1);
							evaluation_difference_value.push_back(-1);
							cluster_distance2d_value.push_back(-1);//两个簇之间的最小二维距离
							cluster_distance3d_value.push_back(-1);//两个簇之间的最小三维距离
							is_noise_point.push_back(-1);
						}
					}
					int iii = 0;
					for (int j = 0; j < evaluation_value.size(); j++)
					{
						if (is_noise_point[j] == (-1))//表示该实例不合并到比自己小的实例上
						{
							energy_value.push_back(100);
						}
						/*if (point_distance[i] == 0)
						{
							energy_value.push_back(-100);
						}*/
						else if (is_noise_point[j] == 0)//不是小于阈值的建筑物
						{
							if ((evaluation_value[j] == -100) || (evaluation_difference_value[j] == 100))
							{
								energy_value.push_back(100);
							}
							else
							{
								double energy = aa * exp(evaluation_value[j]) + bb * exp(cluster_distance2d_value[j])
									+ cc * exp(evaluation_difference_value[j]);

								energy_value.push_back(energy);
							}
						}
						else////是小于阈值的建筑物
						{
							
							double energy = min_min * (aa * exp(evaluation_value[j]) + bb * exp(cluster_distance2d_value[j])
								+ cc * exp(evaluation_difference_value[j])) - 10000;//-1000的目的是让他必须合并
							energy_value.push_back(energy);

						}

					}

					vector<double>energy_value_sort;
					energy_value_sort = energy_value;
					sort(energy_value_sort.begin(), energy_value_sort.end());

					/*if (energy_value_sort[0] == 1000.1)
					{
						Isolated_point2.push_back(total_indivudal_building_sort[i]);
					}*/
					for (int j = 0; j < energy_value.size(); j++)
					{
						double eva = energy_value[j] - energy_value_sort[0];
						if (eva < 0.000001)
						{
							ii = j;
							if (j > i)
							{
								break;
							}

						}
					}
					//n_energy_value.push_back(energy_value[ii]);

					if (energy_value[ii] <= Energy_minimum)//这一点不可能一样，有问题。
						//if ((evaluation_value[ii] <= evaluation_difference) && (grid3dd1 >= evaluation_max))
					{

						int b = number_label[ii + 1];//加1是因为上面是从1开始的，这是从0开始的，要加回去
						for (int k = 0; k < total_indivudal_building_sort[i].size(); k++)
						{
							point3d.x = total_indivudal_building_sort[i][k].x;
							point3d.y = total_indivudal_building_sort[i][k].y;
							point3d.z = total_indivudal_building_sort[i][k].z;
							total_indivudal_building_sort[b].push_back(point3d);
						}
						total_indivudal_building_sort[i].clear();
					}
					energy_value.clear();
					vector<double>().swap(energy_value);
					evaluation_difference_value.clear();
					vector<double>().swap(evaluation_difference_value);
					evaluation_value.clear();
					vector<double>().swap(evaluation_value);
					cluster_distance2d_value.clear();
					vector<double>().swap(cluster_distance2d_value);
					cluster_distance3d_value.clear();
					vector<double>().swap(cluster_distance3d_value);
					is_noise_point.clear();
					vector<int>().swap(is_noise_point);
					temp_individual.clear();
					vector<POINT3D>().swap(temp_individual);

				}


				else
				{
					int ccc = 0;//就一个，说明就自己，不需要合并
				   //这种好像不存在，不需要考虑
				}
			}
			else if (t_label[0] > i)
			{
				//点数都换为pca的最小外接矩形，这样一下子就OK，上面的也都换
				double angle = 0;
				double width = 0;
				double length = 0;
				vector<POINT3D> vertex = pca.PCAalgorithm(total_indivudal_building_sort[i], length, width, angle);

				if ((width < length_width) || (length < length_width))
				{
					//根据模型差异最小合并
					int b = t_label[0];//加1是因为上面是从1开始的，这是从0开始的，要加回去
					for (int k = 0; k < total_indivudal_building_sort[i].size(); k++)
					{
						point3d.x = total_indivudal_building_sort[i][k].x;
						point3d.y = total_indivudal_building_sort[i][k].y;
						point3d.z = total_indivudal_building_sort[i][k].z;
						total_indivudal_building_sort[b].push_back(point3d);
					}
					total_indivudal_building_sort[i].clear();

					//small_building.push_back(incloud[i]);
				}
				else
				{
					int ccc = 0;
					//这是贵
					//big_building.push_back(incloud[i]);
				}

			}

			else if (t_label[0] == i)
			{
				//就单独几个点，并且点数小于
				double angle = 0;
				double width = 0;
				double length = 0;
				vector<POINT3D> vertex = pca.PCAalgorithm(total_indivudal_building_sort[i], length, width, angle);
				if ((width < length_width) || (length < length_width))
				{
					//开始找该簇最近的簇。，是二维不是三维
					Isolated_point.push_back(total_indivudal_building_sort[i]);
					total_indivudal_building_sort[i].clear();
					//small_building.push_back(incloud[i]);
				}
			}
		}
	}



	vector<int>num;
	
	vector < vector<POINT3D>>T_indivudal_building;
	for (int i = 0; i < total_indivudal_building_sort.size(); i++)
	{
		if (total_indivudal_building_sort[i].size() > 0)
		{
			double angle = 0;
			double width = 0;
			double length = 0;
			vector<POINT3D> vertex = pca.PCAalgorithm(total_indivudal_building_sort[i], length, width, angle);
			if ((width < length_width) || (length < length_width))
			{
				Isolated_point.push_back(total_indivudal_building_sort[i]);
			}
			else
			{
				T_indivudal_building.push_back(total_indivudal_building_sort[i]);
				num.push_back(i);
			}
		}
	}
	total_indivudal_building_sort.clear();
	vector < vector<POINT3D>>().swap(total_indivudal_building_sort);
	vector < vector<POINT3D>> improve_induvidual_building;
	if (Isolated_point.size() > 0)//在场景中，一些独立的点在邻域范围内没有其他建筑物，将该孤立的点合并到二维邻域内最近的建筑物
	{
		improve_induvidual_building = kdtree_mergesingle_building_knn_cluster2d(Isolated_point, T_indivudal_building);
	}
	else
	{
		improve_induvidual_building = T_indivudal_building;
		T_indivudal_building.clear();
		vector < vector<POINT3D>>().swap(T_indivudal_building);
	}

	
	return improve_induvidual_building;
}


double PLANE::Minimum_2D_distance_between_clusters(vector<POINT3D>small_cluster, vector<POINT3D>big_cluster)
{
	myclass mc;
	POINT3D point3d;
	vector<POINT3D>m_big_cluster2d;
	for (int i = 0; i < big_cluster.size(); i++)
	{
		point3d.x = big_cluster[i].x;
		point3d.y = big_cluster[i].y;
		point3d.z = 0;
		m_big_cluster2d.push_back(point3d);
	}
	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input(new pcl::PointCloud<pcl::PointXYZL>);
	mc.SwitchDataAsciiToPCLXYZL(m_big_cluster2d, cloud_input);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree;
	kdtree.setInputCloud(cloud_input);
	vector<double>distance;
	for (int i = 0; i < small_cluster.size(); i++)
	{
		pcl::PointXYZL searchPoint;
		searchPoint.x = small_cluster[i].x;
		searchPoint.y = small_cluster[i].y;
		searchPoint.z = 0;
		int K = 1;
		std::vector<int>pointIdxNKNSearch(K);
		std::vector<float>pointNKNSquaredDistance(K);
		if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
		{
			int a = pointIdxNKNSearch[0];
			double dis = sqrt(pointNKNSquaredDistance[0]);
			distance.push_back(dis);
		}
	}
	vector<double>distance_sort;
	distance_sort = distance;
	sort(distance_sort.begin(), distance_sort.end());
	double mindis = distance_sort[0];
	return mindis;
}


void PLANE::instance_MBR(vector<vector<POINT3D>>incloud, double radius, double m_buffer, double min_height,
	double max_height, double mbr_max_threshold, vector<int>&is_or_merge)
	
{
	myclass mc;
	max_min mm;
	MBR mbr;
	PCA1 pca;
	POINT3D point3d;
	vector<POINT3D>incloud_label2d;
	vector<vector<POINT3D>> merging_building;
	vector<POINT3D>m_max;
	vector<POINT3D>m_min;
	for (int i = 0; i < incloud.size(); i++)
	{
		POINT3D max, min;
		mm.max_min_calculation(incloud[i], max, min);
		m_max.push_back(max);
		m_min.push_back(min);
		for (int j = 0; j < incloud[i].size(); j++)
		{
			point3d.x = incloud[i][j].x;
			point3d.y = incloud[i][j].y;
			point3d.z = 0;
			point3d.label = i;
			incloud_label2d.push_back(point3d);
		}
	}


	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input_building2d(new pcl::PointCloud<pcl::PointXYZL>);
	mc.SwitchDataAsciiToPCLXYZL(incloud_label2d, cloud_input_building2d);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree2d;
	kdtree2d.setInputCloud(cloud_input_building2d);//kdtree2仅单体建筑物点云
	for (int i = 0; i < incloud.size(); i++)
	{
		float mindis = 0;
		int label = 0;
		vector<int>t_label;

		for (int j = 0; j < incloud[i].size(); j++)
		{
			//int KK1 = 1;
			pcl::PointXYZL searchPoint;

			searchPoint.x = incloud[i][j].x;
			searchPoint.y = incloud[i][j].y;
			searchPoint.z = 0;// total_indivudal_building[i][j].z;//往下好多都是错误的
			std::vector<int>pointIdxNKNSearch;
			std::vector<float>pointNKNSquaredDistance;
			if (kdtree2d.radiusSearch(searchPoint, radius, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)//kdtree2仅单体建筑物点云
			{
				for (int k = 0; k < pointIdxNKNSearch.size(); k++)
					//for (int k = 0; k < 1; k++)
				{
					if (t_label.size() == 0)
					{
						int bb = t_label.size();
						int a = pointIdxNKNSearch[k];
						label = incloud_label2d[a].label;
						t_label.push_back(label);
					}
					if (t_label.size() > 0)
					{
						int bb = t_label.size();
						int a = pointIdxNKNSearch[k];
						label = incloud_label2d[a].label;
						if (t_label[bb - 1] != label)
						{
							t_label.push_back(label);
							//break;
						}
					}
				}
			}
		}
		int befor_num = is_or_merge.size();//标记是否为屋顶细节结构前
		//周围超点的个数
		if (t_label.size() > 0)
		{
			//z周围邻域范围内就一个，肯定不是屋顶细节结构
			if (t_label.size() > 1)
			{
				vector<int>label1_sort;
				label1_sort = t_label;
				sort(label1_sort.begin(), label1_sort.end());
				//int k = 1;
				vector<int> number_label;
				number_label.push_back(label1_sort[0]);
				for (int j = 0; j < label1_sort.size() - 1; j++)
				{
					if (label1_sort[j] != label1_sort[j + 1])
					{
						//k++;//这样计算整好等于label个数
						number_label.push_back(label1_sort[j + 1]);//这样计算整好等于label个数
					}
				}
				if (number_label.size() > 1)
				{
					for (int j = 0; j < number_label.size(); j++)
					{
						int a = number_label[j];
						//if ((number_label[j]) > 0)
						if (i != a)
						{
							//a对应的label为邻域超点
							if (((m_max[a].x + m_buffer) > m_max[i].x) && ((m_min[a].x - m_buffer) < m_min[i].x))
							{
								if (((m_max[a].y + m_buffer) > m_max[i].y) && ((m_min[a].y - m_buffer) < m_min[i].y))
								{
									
									if (((m_max[a].z - m_min[i].z) < min_height) && (m_max[i].z - m_max[a].z) < max_height)
									{
										double angle = 0;
										double width = 0;
										double length = 0;
										vector<POINT3D> tempvertex = pca.PCAalgorithm(incloud[i], length, width, angle);
										if ((width < mbr_max_threshold) && (length < mbr_max_threshold))//对于面积超级大的屋顶细节结构不合并，这个结果不知道可以去掉不。
										{
											is_or_merge.push_back(1);
											break;
										}

									}
								}
							}


						}
					}
				}
			}
		}
		int after_num = is_or_merge.size();//标记是否为屋顶细节结构前
		if (befor_num == after_num)
		{
			is_or_merge.push_back(0);
		}
	}
}



vector < vector<POINT3D>> PLANE::kdtree_mergesingle_building_knn_cluster2d(vector < vector<POINT3D>>otherpoints2, vector < vector<POINT3D>>individual_building)
{
	myclass mc;
	POINT3D point3d;
	max_min mm;
	vector<POINT3D>noise;
	vector<POINT3D>noise3d;
	for (int i = 0; i < otherpoints2.size(); i++)
	{
		for (int j = 0; j < otherpoints2[i].size(); j++)
		{
			point3d.x = otherpoints2[i][j].x;
			point3d.y = otherpoints2[i][j].y;
			point3d.z = 0;
			noise.push_back(point3d);
			point3d.x = otherpoints2[i][j].x;
			point3d.y = otherpoints2[i][j].y;
			point3d.z = otherpoints2[i][j].z;
			noise3d.push_back(point3d);
		}
	}
	vector<POINT3D>building;
	vector<POINT3D>building3d;
	for (int i = 0; i < individual_building.size(); i++)
	{
		for (int j = 0; j < individual_building[i].size(); j++)
		{
			point3d.x = individual_building[i][j].x;
			point3d.y = individual_building[i][j].y;
			point3d.z = 0;
			point3d.label = i;
			building.push_back(point3d);
			point3d.x = individual_building[i][j].x;
			point3d.y = individual_building[i][j].y;
			point3d.z = individual_building[i][j].z;
			point3d.label = i;
			building3d.push_back(point3d);
		}
	}
	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input(new pcl::PointCloud<pcl::PointXYZL>);

	mc.SwitchDataAsciiToPCLXYZL(building, cloud_input);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree;
	kdtree.setInputCloud(cloud_input);
	vector<POINT3D>temppoint;

	for (int i = 0; i < otherpoints2.size(); i++)
	{
		vector<double>distance;
		vector<int>label1;
		for (int j = 0; j < otherpoints2[i].size(); j++)
		{
			/*POINT3D max, min;
			mm.max_min_calculation(otherpoints2[i], max, min);*/
			pcl::PointXYZL searchPoint;
			searchPoint.x = otherpoints2[i][j].x;
			searchPoint.y = otherpoints2[i][j].y;
			searchPoint.z = 0;

			int K = 1;
			std::vector<int>pointIdxNKNSearch(K);
			std::vector<float>pointNKNSquaredDistance(K);
			if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
			{
				int a = pointIdxNKNSearch[0];
				double dis = sqrt(pointNKNSquaredDistance[0]);
				distance.push_back(dis);
				//label1.push_back(building[a].label);
				label1.push_back(building[a].label);
			}

		}
		vector<double>distance_sort;
		distance_sort = distance;
		sort(distance_sort.begin(), distance_sort.end());
		int ii = 0;
		for (int j = 0; j < distance.size(); j++)
		{
			double dis = distance[j] - distance_sort[0];
			if (dis <= 0.000001)
			{
				ii = label1[j];
			}

		}
		int label = ii;
		for (int j = 0; j < otherpoints2[i].size(); j++)
		{
			/*point3d.x = otherpoints2[i][j].x;
			point3d.y = otherpoints2[i][j].y;
			point3d.z = otherpoints2[i][j].z;*/
			otherpoints2[i][j].label = label;

		}
	}

	int cluser_number = individual_building.size();
	vector < vector<POINT3D>>totalindividual_building(cluser_number);
	for (int i = 0; i < building3d.size(); i++)
	{
		int a = building[i].label;
		point3d.x = building3d[i].x;
		point3d.y = building3d[i].y;
		point3d.z = building3d[i].z;
		totalindividual_building[a].push_back(point3d);
	}
	for (int i = 0; i < otherpoints2.size(); i++)
	{
		for (int j = 0; j < otherpoints2[i].size(); j++)
		{
			int a = otherpoints2[i][j].label;
			point3d.x = otherpoints2[i][j].x;
			point3d.y = otherpoints2[i][j].y;
			point3d.z = otherpoints2[i][j].z;
			totalindividual_building[a].push_back(point3d);
		}
	}
	individual_building.clear();
	vector < vector<POINT3D>>().swap(individual_building);
	otherpoints2.clear();
	vector < vector<POINT3D>>().swap(otherpoints2);

	building.clear();
	vector<POINT3D>().swap(building);
	cloud_input->clear();
	pcl::PointCloud<pcl::PointXYZL>().swap(*cloud_input);
	return totalindividual_building;
}


vector<vector<POINT3D>> PLANE::optimal_Building_Facade_Emagemax2(vector<vector<POINT3D>>roof_superpoint,
	vector<vector<POINT3D>>facade_superpoint, double radius_max, double radius_min)
{
	POINT3D point3d;
	ReadWrite rw;
	myclass mc;
	vector<POINT3D>building;
	vector<POINT3D>building2d;
	max_min mm;
	Eight_neighborhood en;
	//Boudary bd;
	//Grid grid;
	//int num= individual_building.size()
	vector<POINT3D>small_building_emage;
	//vector<vector<POINT3D>>total_indivudal_building;
	vector<vector<POINT3D>>emage_indivudal_building;
	double T_label_value = 1;
	//呢能力函数前的系数
	double aa = 1;
	double bb = -1;
	double cc = 1;

	for (int i = 0; i < roof_superpoint.size(); i++)
	{
		for (int j = 0; j < roof_superpoint[i].size(); j++)
		{
			point3d.x = roof_superpoint[i][j].x;
			point3d.y = roof_superpoint[i][j].y;
			point3d.z = roof_superpoint[i][j].z;
			//i_temp = i + 1;
			point3d.label = i;
			building.push_back(point3d);
			//tempbuilding.push_back(point3d);
			point3d.x = roof_superpoint[i][j].x;
			point3d.y = roof_superpoint[i][j].y;
			point3d.z = 0;
			building2d.push_back(point3d);

		}
	}

	
	pcl::PointCloud<pcl::PointXYZL>::Ptr cloud_input_building2d(new pcl::PointCloud<pcl::PointXYZL>);
	mc.SwitchDataAsciiToPCLXYZL(building2d, cloud_input_building2d);//使用的格式转为pcl格式的点云
	pcl::KdTreeFLANN<pcl::PointXYZL>kdtree2d;
	kdtree2d.setInputCloud(cloud_input_building2d);//kdtree2仅单体建筑物点云
	
	vector < vector<POINT3D>>mean_cluster;
	for (int i = 0; i < facade_superpoint.size(); i++)
	{
		float mindis = 0;
		int label = 0;
		vector<int>t_label;
		POINT3D max_value; POINT3D min_value; POINT3D mean_value;
		mm.max_min_mean_calculation(facade_superpoint[i], max_value, min_value, mean_value);
		//for (int j = 0; j < facade_superpoint[i].size(); j++)
		//{
			//int KK1 = 1;

		pcl::PointXYZL searchPoint;
		searchPoint.x = mean_value.x;
		searchPoint.y = mean_value.y;
		//searchPoint.x = facade_superpoint[i][j].x;
		//searchPoint.y = facade_superpoint[i][j].y;
		searchPoint.z = 0;// total_indivudal_building[i][j].z;//往下好多都是错误的
		std::vector<int>pointIdxNKNSearch;
		std::vector<float>pointNKNSquaredDistance;
		if (kdtree2d.radiusSearch(searchPoint, radius_min, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)//kdtree2仅单体建筑物点云
		{
			for (int k = 0; k < pointIdxNKNSearch.size(); k++)
				//for (int k = 0; k < 1; k++)
			{
				if (t_label.size() == 0)
				{
					int bb = t_label.size();
					int a = pointIdxNKNSearch[k];
					label = building[a].label;
					t_label.push_back(label);
				}
				if (t_label.size() > 0)
				{
					int bb = t_label.size();
					int a = pointIdxNKNSearch[k];
					label = building[a].label;
					if (t_label[bb - 1] != label)
					{
						t_label.push_back(label);
					}
				}
			}
		}
		//}

		if (t_label.size() > 0)
		{
			vector<int> number_label;
			if (t_label.size() == 1)
			{
				int b = t_label[0];

				for (int k = 0; k < facade_superpoint[i].size(); k++)
				{
					point3d.x = facade_superpoint[i][k].x;
					point3d.y = facade_superpoint[i][k].y;
					point3d.z = facade_superpoint[i][k].z;
					roof_superpoint[b].push_back(point3d);
				}
				facade_superpoint[i].clear();
			}

			else if (t_label.size() > 1)
			{
				vector<int>label1_sort;
				label1_sort = t_label;
				sort(label1_sort.begin(), label1_sort.end());
				//int k = 1;

				number_label.push_back(label1_sort[0]);
				for (int j = 0; j < label1_sort.size() - 1; j++)
				{
					if (label1_sort[j] != label1_sort[j + 1])
					{
						//k++;//这样计算整好等于label个数
						number_label.push_back(label1_sort[j + 1]);//这样计算整好等于label个数
					}
				}

				if (number_label.size() > 1)
				{
					vector<double>energy_value;//能量值
					vector<double> evaluation_difference_value;//模型一致性差异值
					vector<double> evaluation_value;//模型一致性值
					vector<double> cluster_distance2d_value;//两个簇之间的二维距离
					//vector<double> evaluation_value;
					vector<POINT3D>temp_individual;
					int ii = -1;
					for (int j = 0; j < number_label.size(); j++)
					{
						//if (number_label[j] > i)
						//{
						int a = number_label[j];
						vector<POINT3D>Multiple_Building;
						Multiple_Building = roof_superpoint[a];
						POINT3D max, min, mean0;
						//mm.max_min_meanZ_calculation(Multiple_Building, max, min, mean0);
						mm.max_min_calculation(Multiple_Building, max, min);
						double grid3dd = en.grid3d_Cluster_evaluation(Multiple_Building, radius_max, min);
						for (int k = 0; k < facade_superpoint[i].size(); k++)
						{
							point3d.x = facade_superpoint[i][k].x;
							point3d.y = facade_superpoint[i][k].y;
							point3d.z = facade_superpoint[i][k].z;//往下好多都是错误的
							Multiple_Building.push_back(point3d);
						}
						POINT3D max1, min1, mean1;
						//mm.max_min_meanZ_calculation(Multiple_Building, max1, min1, mean1);
						mm.max_min_calculation(Multiple_Building, max1, min1);
						double grid3dd1 = en.grid3d_Cluster_evaluation(Multiple_Building, radius_max, min1);
						evaluation_value.push_back(grid3dd1);
						double m_evaluation_difference = grid3dd - grid3dd1;
						evaluation_difference_value.push_back(m_evaluation_difference);
						double dis2d = Minimum_2D_distance_between_clusters(facade_superpoint[i], roof_superpoint[a]);
						//double dis3d = Minimum_3D_distance_between_clusters(total_indivudal_building_sort[i], total_indivudal_building_sort[a]);
						cluster_distance2d_value.push_back(dis2d);
					}
					for (int j = 0; j < evaluation_value.size(); j++)
					{
						double energy = aa * exp(cluster_distance2d_value[j]) +
							bb * exp(evaluation_value[j]) + cc * exp(evaluation_difference_value[j]);
						energy_value.push_back(energy);
					}
					vector<double>energy_value_sort;
					energy_value_sort = energy_value;
					sort(energy_value_sort.begin(), energy_value_sort.end());
					for (int j = 0; j < energy_value.size(); j++)
					{
						double eva = energy_value[j] - energy_value_sort[0];
						if (eva < 0.000001)
						{
							ii = j;
							break;
						}
					}
					int b = number_label[ii];

					for (int k = 0; k < facade_superpoint[i].size(); k++)
					{
						point3d.x = facade_superpoint[i][k].x;
						point3d.y = facade_superpoint[i][k].y;
						point3d.z = facade_superpoint[i][k].z;
						roof_superpoint[b].push_back(point3d);
					}
					facade_superpoint[i].clear();
				}
			}
		}
		//根据重心距离最近的建筑物，合并上去就OK啦
		else
		{
			mean_cluster.push_back(facade_superpoint[i]);
			/* point3d.x = mean_value.x;
			 point3d.y = mean_value.y;
			 point3d.z = 0;
			 mean_cluster.push_back(point3d);*/
		}

	}
	vector < vector<POINT3D>>indivudal_building;
	for (int i = 0; i < roof_superpoint.size(); i++)
	{
		if (roof_superpoint[i].size() > 0)
		{
			indivudal_building.push_back(roof_superpoint[i]);
		}
	}
	roof_superpoint.clear();
	vector < vector<POINT3D>>().swap(roof_superpoint);
	vector < vector<POINT3D>>T_indivudal_building;
	
	if (mean_cluster.size() > 0)
	{
		T_indivudal_building = kdtree_mergesingle_building_knn_cluster2d(mean_cluster, indivudal_building);
	}
	else
	{
		T_indivudal_building = indivudal_building;
		indivudal_building.clear();
		vector < vector<POINT3D>>().swap(indivudal_building);
	}

	return T_indivudal_building;
}

//【函数说明】空间向量之间的夹角
//【输入参数】NormalA——某个平面的法向量
//【输入参数】NormalB——Z轴正方向
//【返回值】两个向量之间的夹角
double PLANE::PlaneNormalsAngle3D(PLANE NormalA, PLANE NormalB)
{
	double angle;
	double AA = NormalA.A*NormalA.A + NormalA.B*NormalA.B + NormalA.C*NormalA.C;
	double BB = NormalB.A*NormalB.A + NormalB.B*NormalB.B + NormalB.C*NormalB.C;
	double AABB = sqrt(AA*BB);
	double AB = NormalA.A*NormalB.A + NormalA.B*NormalB.B + NormalA.C*NormalB.C;
	if (AABB == 0)
	{
		angle = 0;
	}
	else if ((AB / AABB) >= 0)
	{
		double sum = AB / AABB;
		angle = (acos(sum)) * 180 / PI;
	}
	else
	{
		double sum = AB / AABB;
		angle = (acos(sum)) * 180 / PI;
	}

	
	return angle;
}



//根据建筑物实例模型一致性合并超点，实现建筑物实例分割。
vector<vector<POINT3D>> PLANE::Superpoint_graph_building_instance_segmentation(vector<POINT3D>&incloud)
{
	myclass mc;
	ReadWrite rw;
	Grid grid;
	CFSFDP cf;
	PCA1 pca;
	int start = clock();
	Eight_neighborhood en;
	vector < vector<POINT3D>>instance_building;
	
	POINT3D point3d;
	Boudary bd;
	int  max_cluster_size = 10000000;
	vector<POINT3D > Facadepoint;
	vector<POINT3D > normalvectorRoof;
	double angle_threshold = 15;
	roofpoint_facadepoint_m_volume_knn(incloud, 20, angle_threshold, normalvectorRoof, Facadepoint);

	//string outtxt_txtplanepoint = "E:\\Roofpoint.txt";
	////vector<POINT3D>m_planepoint = rw.IndividualRGBpointcloud(planepoint);
	//rw.write_txt(outtxt_txtplanepoint, normalvectorRoof);
	////string outtxt_txthorizontal_plane = "E:\\horizontal_plane.txt";
	//////vector<POINT3D>m_planepoint = rw.IndividualRGBpointcloud(planepoint);
	////rw.write_txt(outtxt_txthorizontal_plane, horizontal_plane);
	//string outtxt_txtFacadepoint = "E:\\Facadepoint.txt";
	//rw.write_txt(outtxt_txtFacadepoint, Facadepoint);
	cout << "0、屋顶提取   :" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;

	
	vector<vector<POINT3D>>Roof_Superpoint = cf.superpoint_segmentation(normalvectorRoof, 0.8, 3);//ANH3
	
	vector<vector<POINT3D>>Facade_Superpoint = cf.superpoint_segmentation(Facadepoint, 0.8, 3);////ANH3
	

	/*string outtxt_Roof_Superpoint01 = "E:\\Roof_Superpoint01.txt";
	vector<POINT3D>m_Roof_Superpoint = rw.IndividualRGBpointcloud(Roof_Superpoint);
	rw.write_txt(outtxt_Roof_Superpoint01, m_Roof_Superpoint);
	string outtxt_Facade_Superpoint01 = "E:\\Facade_Superpoint01.txt";
	vector<POINT3D>m_Facade_Superpoint = rw.IndividualRGBpointcloud(Facade_Superpoint);
	rw.write_txt(outtxt_Facade_Superpoint01, m_Facade_Superpoint);*/

	
	cout << "1、超点分割  :" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
	std::cout << "1、超点分割" << std::endl;

	vector<vector<POINT3D>>optimal_Emage = energy_optimization_superpoint_merging_new2(Roof_Superpoint, 1.2, 0.8, 0.00, 0, 0, 0.5);//ANH3

	/*string outtxt_txtoptimal_Emage03 = "E:\\optimal_Emage02.txt";
	vector<POINT3D>m_optimal_Emage = rw.IndividualRGBpointcloud(optimal_Emage);
	rw.write_txt(outtxt_txtoptimal_Emage03, m_optimal_Emage);*/
	cout << "2、超点图合并  :" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
	std::cout << "2、超点图合并" << std::endl;

	
	vector<vector<POINT3D>>optimal_building_Emage = optimal_Building_Facade_Emagemax2(optimal_Emage, Facade_Superpoint, 1.2, 1.0);// ANH3

	
	/*string outtxt_txtoptimal_Emage034 = "E:\\optimal_Emage04.txt";
	vector<POINT3D>m_optimal_builing_Emage = rw.IndividualRGBpointcloud(optimal_building_Emage);
	rw.write_txt(outtxt_txtoptimal_Emage034, m_optimal_builing_Emage);*/
	cout << "4、立面合并运行时间  :" << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
	std::cout << "4、立面合并" << std::endl;
	

	return optimal_building_Emage;
}

