#include "cShp_Sphere.h"























cShp_Sphere::cShp_Sphere()
	: Center(0.f, 0.f, 0.f)
	, Radius(0.f)
{

}


cShp_Sphere::cShp_Sphere(float X, float Y, float Z, float Radius)
	: Center(X, Y, Z)
	, Radius(Radius)
{

}


cShp_Sphere::cShp_Sphere(const D3DXVECTOR3& Pos, float Radius)
	: Center(Pos)
	, Radius(Radius)
{

}


cShp_Sphere::~cShp_Sphere()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

