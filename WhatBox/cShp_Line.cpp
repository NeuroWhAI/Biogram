#include "cShp_Line.h"

#include "cCore.h"

























cShp_Line::cShp_Line()
	: P1(0.f, 0.f)
	, P2(0.f, 0.f)
{

}


cShp_Line::cShp_Line(float X1, float Y1, float X2, float Y2)
	: P1(X1, Y1)
	, P2(X2, Y2)
{

}


cShp_Line::cShp_Line(const D3DXVECTOR2& P1, const D3DXVECTOR2& P2)
	: P1(P1)
	, P2(P2)
{

}


cShp_Line::~cShp_Line()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cShp_Line::GetLength() const
{
	D3DXVECTOR2 SubVec(P1 - P2);
	return D3DXVec2Length(&SubVec);
}


float cShp_Line::GetLengthSq() const
{
	D3DXVECTOR2 SubVec(P1 - P2);
	return D3DXVec2LengthSq(&SubVec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Line::Render(DWORD Color, float Width)
{
	cCore::Resource.Line.Render(&P1, &P2, Color, Width);


	return 0;
}

