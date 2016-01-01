#include "cShp_Triangle.h"

#include "cCore.h"































cShp_Triangle::cShp_Triangle()
	: m_P1(0.f, 0.f)
	, m_P2(0.f, 0.f)
	, m_P3(0.f, 0.f)
{

}


cShp_Triangle::cShp_Triangle(const D3DXVECTOR2* P1, const D3DXVECTOR2* P2, const D3DXVECTOR2* P3)
	: m_P1(*P1)
	, m_P2(*P2)
	, m_P3(*P3)
{
	this->Rasterize();
}


cShp_Triangle::~cShp_Triangle()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DXVECTOR2* cShp_Triangle::GetP1() const
{
	return &m_P1;
}


const D3DXVECTOR2* cShp_Triangle::GetP2() const
{
	return &m_P2;
}


const D3DXVECTOR2* cShp_Triangle::GetP3() const
{
	return &m_P3;
}

/*------------------------------------------------------------------------------------------------*/

void cShp_Triangle::GetP1(D3DXVECTOR2* pOut) const
{
	*pOut = m_P1;
}


void cShp_Triangle::GetP2(D3DXVECTOR2* pOut) const
{
	*pOut = m_P2;
}


void cShp_Triangle::GetP3(D3DXVECTOR2* pOut) const
{
	*pOut = m_P3;
}

/*------------------------------------------------------------------------------------------------*/

void cShp_Triangle::SetP1(float x, float y)
{
	m_P1.x = x;
	m_P1.y = y;
}


void cShp_Triangle::SetP2(float x, float y)
{
	m_P2.x = x;
	m_P2.y = y;
}


void cShp_Triangle::SetP3(float x, float y)
{
	m_P3.x = x;
	m_P3.y = y;
}

/*------------------------------------------------------------------------------------------------*/

void cShp_Triangle::SetP1(const D3DXVECTOR2* vtx)
{
	m_P1 = *vtx;
}


void cShp_Triangle::SetP2(const D3DXVECTOR2* vtx)
{
	m_P2 = *vtx;
}


void cShp_Triangle::SetP3(const D3DXVECTOR2* vtx)
{
	m_P3 = *vtx;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Triangle::Rasterize()
{
	m_points.clear();
	m_li.clear();


	POINT A, B, C;

	A.x = static_cast<long>(m_P1.x);
	A.y = static_cast<long>(m_P1.y);

	B.x = static_cast<long>(m_P2.x);
	B.y = static_cast<long>(m_P2.y);

	C.x = static_cast<long>(m_P3.x);
	C.y = static_cast<long>(m_P3.y);


	POINT D;
	Classify(A, B, C);
	CuttingY(A, B, C, D);
	RasterizerType1(A, B, C);
	RasterizerType2(B, D, C);


	return 0;
}


int cShp_Triangle::GetPixelList(std::vector<D3DXVECTOR2>* pOut)
{
	*pOut = m_points;


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Triangle::Render(DWORD color, float width)
{
	if (m_points.size() > 0)
		cCore::Resource.Line.Render(&m_points[0], m_points.size(), color, width);


	return 0;
}


int cShp_Triangle::Draw(DWORD color)
{
	if (m_points.size() > 0)
		cCore::Resource.Line.Draw(&m_points[0], m_points.size(), color);


	return 0;
}

