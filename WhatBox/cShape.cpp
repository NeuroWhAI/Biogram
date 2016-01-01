#include "cShape.h"

#include <fstream>

#include "cCore.h"



























cShape::cShape()
	: m_Center(0.f, 0.f)
	, m_Angle(0.f)
{

}


cShape::cShape(const D3DXVECTOR2& Center)
	: m_Center(Center)
	, m_Angle(0.f)
{

}


cShape::cShape(const char FileName[], const D3DXVECTOR2* Center)
	: m_Center((Center == nullptr) ? D3DXVECTOR2(0.f, 0.f) : *Center)
	, m_Angle(0.f)
{
	std::ifstream File(FileName);

	if(File.is_open())
	{
		int VtxNum = 0;

		File>>VtxNum;


		float X=0, Y=0;

		for(int i=0; i<VtxNum; i++)
		{
			File>>X>>Y;

			AddVtx(X, Y);
		}


		File.close();
	}


	UpdatePos();
}


cShape::~cShape()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShape::UpdatePos()
{
	for(UINT i=0; i<m_VtxList.size(); i++)
	{
		cCore::ShapeMath.GetPosition(&m_VtxList[i], m_DisList[i], m_Angle + m_AngleList[i]);

		m_VtxList[i] += m_Center;
	}


	return 0;
}


int cShape::AddVtx(float x, float y)
{
	cShp_Polygon::AddVtx(x, y);


	float Angle = 0.f, Dis = 0.f;

	cCore::ShapeMath.GetAnglePos(&Angle, &Dis, &m_Center, &D3DXVECTOR2(x, y));
	

	m_AngleList.push_back(Angle);
	m_DisList.push_back(Dis);


	return 0;
}


UINT cShape::VtxCount() const
{
	return m_VtxList.size();
}


const std::vector<D3DXVECTOR2>* cShape::GetVtxList() const
{
	return &m_VtxList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShape::SetCenter(float x, float y)
{
	m_Center.x = x;
	m_Center.y = y;


	UpdatePos();


	return 0;
}


const D3DXVECTOR2* cShape::Center() const
{
	return &m_Center;
}


int cShape::AddPos(float x, float y)
{
	cShp_Polygon::AddPos(x, y);

	m_Center.x += x;
	m_Center.y += y;


	return 0;
}


int cShape::SetPos(float x, float y)
{
	m_Center.x = x;
	m_Center.y = y;


	UpdatePos();


	return 0;
}


int cShape::SetAngle(float Degree)
{
	m_Angle = Degree;


	UpdatePos();


	return 0;
}


int cShape::AddAngle(float Degree)
{
	m_Angle += Degree;


	UpdatePos();


	return 0;
}

