#ifndef _POINT3D_H_
#define _POINT3D_H_
typedef class POINT3D //typedef--用于将Point3D定义为数据类型
{
//public:
//	POINT3D();
//	~POINT3D();
public:
	POINT3D();
	POINT3D(const float& X, const float& Y, const float& Z);
	~POINT3D();
	POINT3D operator + (const POINT3D &point3d);//C++扩展运算符功能
	POINT3D operator - (const POINT3D &point3d);
	POINT3D operator / (const int &sum);
	POINT3D operator * (const int &sum);
	POINT3D operator += (const POINT3D &point3d);
	POINT3D operator -= (const POINT3D &point3d);
	POINT3D operator /= (const int &sum);
	POINT3D operator *= (const int &sum);
public:
	double x;
	double y;
	double z;
	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned char Classification;//分类信息
	unsigned short intens;//反射率
	unsigned short HSV;//HSV颜色模型
	double density;//该点的密度
	//unsigned short i;//重复了，一般不用
	//bool isVisisted;
	//int f;
	int label;//点的label，即是类别
	int grid2d_index;
	int grid3d_index;
	bool IsVisisted;//是否访问
	//点的特征直方图
	
	/*double h1;
	double h2;
	double h3;
	double h4;
	double h5;
	double h6;
	double h7;
	double h8;
	double h9;
	double h10;
	double h11;
	double h12;
	double h13;
	double h14;
	double h15;
	double h16;
	double h17;
	double h18;
	double h19;
	double h20;
	double h21;
	double h22;
	double h23;
	double h24;
	double h25;
	double h26;
	double h27;
	double h28;
	double h29;
	double h30;
	double h31;
	double h32;
	double h33;*/



	//unsigned char retnum;
	//unsigned int PlaneID;//立面ID
	//int feature;
	

}Point3D;//Point3D--指向空间点Point3D类型的指针



typedef class POINT2D //typedef--用于将Point3D定义为数据类型
{
	//public:
	//	POINT3D();
	//	~POINT3D();
public:
	POINT2D();

	~POINT2D();

public:
	double x;
	double y;
	


}Point2D;//Point3D--指向空间点Point3D类型的指针


struct fake_grid
{
	
	std::vector<int> index;
};



typedef class extent_3d //typedef--用于将Point3D定义为数据类型
{
public:
	//X的最小值
	double m_xmin;
	//X的最大值
	double m_xmax;
	//Y的最小值
	double m_ymin;
	//Y的最大值
	double m_ymax;
	//Z的最小值
	double m_zmin;
	//Z的最大值
	double m_zmax;

public:
	extent_3d();
	~extent_3d();

}extent;


//以后再定义平面
typedef class  planar_3d
{
public:
	//平面方程的系数A
	double A;
	//平面方程的系数B
	double B;
	//平面方程的系数C
	double C;
	//平面方程的系数D
	double D;
public:
	planar_3d();
	~planar_3d();

} planar;     //12.3日加



typedef class POINTND //typedef--用于将Point3D定义为数据类型
{
	//public:
	//	POINT3D();
	//	~POINT3D();
public:
	POINTND();

	~POINTND();
	//POINT3D(const float& X, const float& Y, const float& Z);
	//POINT3D operator + (const POINT3D &point3d);//C++扩展运算符功能
	//POINT3D operator - (const POINT3D &point3d);
	//POINT3D operator / (const int &sum);
	//POINT3D operator * (const int &sum);
	//POINT3D operator += (const POINT3D &point3d);
	//POINT3D operator -= (const POINT3D &point3d);
	//POINT3D operator /= (const int &sum);
	//POINT3D operator *= (const int &sum);
public:
	/*double x1;
	double x2;
	double x3;
	double x4;
	double x5;
	double x6;
	double x7;
	double x8;
	double x9;
	double x10;
	double x11;
	double x12;
	double x13;
	double x14;
	double x15;
	double x16;
	double x17;
	double x18;
	double x19;
	double x20;
	double x21;
	double x22;
	double x23;
	double x24;
	double x25;
	double x26;
	double x27;
	double x28;
	double x29;
	double x30;
	double x31;
	double x32;
	double x33;*/
	double h1;
	double h2;
	double h3;
	double h4;
	double h5;
	double h6;
	double h7;
	double h8;
	double h9;
	double h10;
	double h11;
	double h12;
	double h13;
	double h14;
	double h15;
	double h16;
	double h17;
	double h18;
	double h19;
	double h20;
	double h21;
	double h22;
	double h23;
	double h24;
	double h25;
	double h26;
	double h27;
	double h28;
	double h29;
	double h30;
	double h31;
	double h32;
	double h33;


}PointnD;//Point3D--指向空间点Point3D类型的指针








#endif 