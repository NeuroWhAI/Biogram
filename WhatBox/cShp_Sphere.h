#pragma once
#include <d3dx9.h>





















class cShp_Sphere
{
public:
	cShp_Sphere();
	cShp_Sphere(float X, float Y, float Z, float Radius);
	cShp_Sphere(const D3DXVECTOR3& Pos, float Radius);
	~cShp_Sphere();


public:
	D3DXVECTOR3 Center;
	float Radius;
};

