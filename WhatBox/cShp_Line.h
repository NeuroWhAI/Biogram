#pragma once
#include <d3dx9.h>





















class cShp_Line
{
public:
	cShp_Line();
	cShp_Line(float X1, float Y1, float X2, float Y2);
	cShp_Line(const D3DXVECTOR2& P1, const D3DXVECTOR2& P2);
	~cShp_Line();


public:
	D3DXVECTOR2 P1, P2;


public:
	float GetLength() const;
	float GetLengthSq() const;


public:
	int Render(DWORD Color, float Width);
};

