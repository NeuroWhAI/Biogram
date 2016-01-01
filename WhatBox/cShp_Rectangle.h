#pragma once
#include <d3dx9.h>






















class cShp_Rectangle
{
public:
	cShp_Rectangle();
	cShp_Rectangle(float left, float top, float right, float bottom);
	~cShp_Rectangle();


public:
	float left, top, right, bottom;
};

