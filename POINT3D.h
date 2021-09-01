#ifndef _POINT3D_H_
#define _POINT3D_H_
typedef class POINT3D //typedef--���ڽ�Point3D����Ϊ��������
{
//public:
//	POINT3D();
//	~POINT3D();
public:
	POINT3D();
	POINT3D(const float& X, const float& Y, const float& Z);
	~POINT3D();
	POINT3D operator + (const POINT3D &point3d);//C++��չ���������
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
	unsigned char Classification;//������Ϣ
	unsigned short intens;//������
	unsigned short HSV;//HSV��ɫģ��
	double density;//�õ���ܶ�
	//unsigned short i;//�ظ��ˣ�һ�㲻��
	//bool isVisisted;
	//int f;
	int label;//���label���������
	int grid2d_index;
	int grid3d_index;
	bool IsVisisted;//�Ƿ����
	//�������ֱ��ͼ
	
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
	//unsigned int PlaneID;//����ID
	//int feature;
	

}Point3D;//Point3D--ָ��ռ��Point3D���͵�ָ��



typedef class POINT2D //typedef--���ڽ�Point3D����Ϊ��������
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
	


}Point2D;//Point3D--ָ��ռ��Point3D���͵�ָ��


struct fake_grid
{
	
	std::vector<int> index;
};



typedef class extent_3d //typedef--���ڽ�Point3D����Ϊ��������
{
public:
	//X����Сֵ
	double m_xmin;
	//X�����ֵ
	double m_xmax;
	//Y����Сֵ
	double m_ymin;
	//Y�����ֵ
	double m_ymax;
	//Z����Сֵ
	double m_zmin;
	//Z�����ֵ
	double m_zmax;

public:
	extent_3d();
	~extent_3d();

}extent;


//�Ժ��ٶ���ƽ��
typedef class  planar_3d
{
public:
	//ƽ�淽�̵�ϵ��A
	double A;
	//ƽ�淽�̵�ϵ��B
	double B;
	//ƽ�淽�̵�ϵ��C
	double C;
	//ƽ�淽�̵�ϵ��D
	double D;
public:
	planar_3d();
	~planar_3d();

} planar;     //12.3�ռ�



typedef class POINTND //typedef--���ڽ�Point3D����Ϊ��������
{
	//public:
	//	POINT3D();
	//	~POINT3D();
public:
	POINTND();

	~POINTND();
	//POINT3D(const float& X, const float& Y, const float& Z);
	//POINT3D operator + (const POINT3D &point3d);//C++��չ���������
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


}PointnD;//Point3D--ָ��ռ��Point3D���͵�ָ��








#endif 