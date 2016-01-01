#include "cShp_Polygon.h"

#include <fstream>

#include "cCore.h"
























cShp_Polygon::cShp_Polygon()
{

}


cShp_Polygon::cShp_Polygon(const char FileName[])
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
}



cShp_Polygon::~cShp_Polygon()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Polygon::Render(DWORD Color)
{
	UINT VtxCount = m_VtxList.size();


	D3DXVECTOR2* VtxList = new D3DXVECTOR2[VtxCount + 1];

	for(UINT i=0; i<=VtxCount; i++)
	{
		VtxList[i] = m_VtxList[i % VtxCount];
	}


	cCore::Resource.Line.Render(VtxList, VtxCount + 1, Color, 2.f);


	delete[] VtxList;


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Polygon::AddVtx(float x, float y)
{
	m_VtxList.push_back(D3DXVECTOR2(x, y));


	return 0;
}


int cShp_Polygon::SetVtx(UINT Idx, float x, float y)
{
	m_VtxList[Idx].x = x;
	m_VtxList[Idx].y = y;


	return 0;
}


UINT cShp_Polygon::VtxCount() const
{
	return m_VtxList.size();
}


std::vector<D3DXVECTOR2>* cShp_Polygon::GetVtxList()
{
	return &m_VtxList;
}


const std::vector<D3DXVECTOR2>* cShp_Polygon::GetVtxList() const
{
	return &m_VtxList;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cShp_Polygon::AddPos(float x, float y)
{
	for(UINT i=0; i<m_VtxList.size(); i++)
	{
		m_VtxList[i].x += x;
		m_VtxList[i].y += y;
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cShp_Polygon::isCollided(const cShp_Polygon* pOther, D3DXVECTOR2* IntersectPos)
{
	const std::vector<D3DXVECTOR2>& OtherVtxList = *pOther->GetVtxList();


	UINT VtxCount = m_VtxList.size();
	UINT OtherVtxCount = OtherVtxList.size();

	if(VtxCount == 0  ||  OtherVtxCount == 0) return false;


	for(UINT i=0; i<=VtxCount; i++)
	{
		UINT Idx1 = i % VtxCount;
		UINT Idx2 = (i + 1) % VtxCount;

		for(UINT j=0; j<=OtherVtxList.size(); j++)
		{
			if(cCore::ShapeMath.isCollided(&m_VtxList[Idx1], &m_VtxList[Idx2],
				&OtherVtxList[j % OtherVtxCount], &OtherVtxList[(j+1)%OtherVtxCount],
				IntersectPos))
			{
				return true;
			}
		}
	}


	return false;
}

