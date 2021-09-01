#include "stdafx.h"
#include "POINT3D.h"

POINT3D::POINT3D() : x(0), y(0), z(0), r(255), g(255), b(255),  Classification(0), intens(0), HSV(0), density(0), label(0), grid2d_index(0),grid3d_index(0), IsVisisted(false)
//f(0), retnum(0), PlaneID(0), feature(0), i(0),
//h1(0), h2(0), h3(0), h4(0), h5(0), h6(0), h7(0), h8(0), h9(0), h10(0), h11(0), h12(0), h13(0), h14(0), h15(0),
//h16(0), h17(0), h18(0), h19(0), h20(0), h21(0), h22(0), h23(0), h24(0), h25(0), h26(0), h27(0), h28(0), h29(0), h30(0), h31(0), h32(0), h33(0)

{

}

POINT3D::POINT3D(const float& X, const float& Y, const float& Z)
{
	x = X; y = Y; z = Z;
}

POINT3D::~POINT3D()
{

}

POINT3D POINT3D::operator + (const POINT3D &point3d)
{
	POINT3D p;
	p.x = x + point3d.x;
	p.y = y + point3d.y;
	p.z = z + point3d.z;
	return p;
}

POINT3D POINT3D::operator - (const POINT3D &point3d)
{
	POINT3D p;
	p.x = x - point3d.x;
	p.y = y - point3d.y;
	p.z = z - point3d.z;
	return p;
}

POINT3D POINT3D::operator / (const int &sum)
{
	if (sum <= 0)
		return (*this);
	POINT3D p;
	p.x = x / sum;
	p.y = y / sum;
	p.z = z / sum;
	return p;
}

POINT3D POINT3D::operator * (const int &sum)
{
	POINT3D p;
	p.x = x * sum;
	p.y = y * sum;
	p.z = z * sum;
	return p;
}

POINT3D POINT3D::operator += (const POINT3D &point3d)
{
	x = x + point3d.x;
	y = y + point3d.y;
	z = z + point3d.z;
	return (*this);
}

POINT3D POINT3D::operator -= (const POINT3D &point3d)
{
	x = x - point3d.x;
	y = y - point3d.y;
	z = z - point3d.z;
	return (*this);
}

POINT3D POINT3D::operator /= (const int &sum)
{
	if (sum <= 0)
		return (*this);
	x = x / sum;
	y = y / sum;
	z = z / sum;
	return (*this);
}

POINT3D POINT3D::operator *= (const int &sum)
{
	x = x * sum;
	y = y * sum;
	z = z * sum;
	return (*this);
}

//×îÖµ
extent_3d::extent_3d() :m_xmin(0), m_xmax(0), m_ymin(0), m_ymax(0), m_zmin(0), m_zmax(0)
{

}

extent_3d::~extent_3d()
{

}

planar_3d::planar_3d() :A(0), B(0), C(0), D(0)
{

}

planar_3d::~planar_3d()
{

}


POINT2D::POINT2D() :x(0), y(0)
{

}

POINT2D::~POINT2D()
{
}

POINTND::POINTND() : h1(0), h2(0), h3(0), h4(0), h5(0), h6(0), h7(0), h8(0), h9(0), h10(0), h11(0), h12(0), h13(0), h14(0), h15(0),
h16(0), h17(0), h18(0), h19(0), h20(0), h21(0), h22(0), h23(0), h24(0), h25(0), h26(0), h27(0), h28(0), h29(0), h30(0), h31(0), h32(0), h33(0)

{

}

POINTND::~POINTND()
{

}
