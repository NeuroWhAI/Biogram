#pragma once
#include "cTileMap.h"

#include <assert.h>

#include "cTile.h"
#include "c2DCoord.h"

































template <typename TileType>
cTileMap<TileType>::cTileMap()
	: m_tileSize(0.f)
	, m_startX(0), m_endX(0)
	, m_startY(0), m_endY(0)
{
	TileType test(0.f, 0.f, 0.f);
	cTile* pTest = dynamic_cast<cTile*>(&test);

	assert(pTest != nullptr);
}


template <typename TileType>
cTileMap<TileType>::cTileMap(int width, int height, float tileSize)
	: m_startX(0), m_endX(0)
	, m_startY(0), m_endY(0)
{
	TileType test(0.f, 0.f, 0.f);
	cTile* pTest = dynamic_cast<cTile*>(&test);

	assert(pTest != nullptr);


	Init(width, height, tileSize);
}


template <typename TileType>
cTileMap<TileType>::~cTileMap()
{
	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			delete m_tileMap[y][x];
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TileType>
int cTileMap<TileType>::Init(int width, int height, float tileSize)
{
	m_tileSize = tileSize;


	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			delete m_tileMap[y][x];
		}
	}
	m_tileMap.clear();


	/* 鸥老 积己 */
	for(int y=0; y<height; y++)
	{
		m_tileMap.emplace_back();

		for(int x=0; x<width; x++)
		{
			m_tileMap[y].push_back(new TileType(static_cast<float>(x) * tileSize, static_cast<float>(y) * tileSize,
				tileSize));
		}
	}


	/* 鸥老 楷搬 */
	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			int Y[8] = {y-1, y-1, y-1, y, y+1, y+1, y+1, y};
			int X[8] = {x-1, x, x+1, x+1, x+1, x, x-1, x-1};

			for(int i=0; i<8; i++)
			{
				if(Y[i] < 0  ||  Y[i] >= height
					||
					X[i] < 0  ||  X[i] >= width)
				{
					continue;
				}

				m_tileMap[y][x]->SetNode(m_tileMap[Y[i]][X[i]], i);
			}
		}
	}


	return 0;
}

/*----------------------------------------------------------------------------------------------------*/

template <typename TileType>
int cTileMap<TileType>::Update()
{
	D3DXVECTOR2 camPos = *cCore::Camera2D.Pos();
	
	D3DXVECTOR2 startVec = camPos/m_tileSize;
	D3DXVECTOR2 endVec = (camPos+D3DXVECTOR2(CAST(cCore::WinSize.x, float), CAST(cCore::WinSize.y, float)))/m_tileSize;

	m_startX = (startVec.x < 0.f) ? 0 : CAST(startVec.x, UINT);
	m_startY = (startVec.y < 0.f) ? 0 : CAST(startVec.y, UINT);
	
	m_endX = (endVec.x+1.f > m_tileMap[0].size()) ? m_tileMap[0].size() : CAST(endVec.x, UINT)+1;
	m_endY = (endVec.y+1.f > m_tileMap.size()) ? m_tileMap.size() : CAST(endVec.y, UINT)+1;

	if(m_startX > m_tileMap[0].size()) m_startX = m_tileMap[0].size();
	if(m_startY > m_tileMap.size()) m_startY = m_tileMap.size();

	if(m_endX > m_tileMap[0].size()) m_endX = m_tileMap[0].size();
	if(m_endY > m_tileMap.size()) m_endY = m_tileMap.size();


	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			m_tileMap[y][x]->UpdateOutCheck();
		}
	}


	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			m_tileMap[y][x]->Update();
		}
	}


	return 0;
}


template <typename TileType>
int cTileMap<TileType>::Render()
{
	cCore::Resource.Line.SetWidth(2.f);
	cCore::Resource.Line.Begin();

	cCore::Resource.Line.Draw(0.f, 0.f, m_tileSize*m_tileMap[0].size(), 0.f,
		0xffffffff);
	cCore::Resource.Line.Draw(m_tileSize*m_tileMap[0].size(), 0.f, m_tileSize*m_tileMap[0].size(), m_tileSize*m_tileMap.size(),
		0xffffffff);
	cCore::Resource.Line.Draw(m_tileSize*m_tileMap[0].size(), m_tileSize*m_tileMap.size(), 0.f, m_tileSize*m_tileMap.size(),
		0xffffffff);
	cCore::Resource.Line.Draw(0.f, m_tileSize*m_tileMap.size(), 0.f, 0.f,
		0xffffffff);

	cCore::Resource.Line.End();


	for(UINT y=m_startY; y<m_endY; ++y)
	{
		for(UINT x=m_startX; x<m_endX; ++x)
		{
			m_tileMap[y][x]->Render();
		}
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TileType>
int cTileMap<TileType>::AddObject(c2DCoord* pObj)
{
	m_pObjList.push_back(pObj);


	AddObjToTileMap(pObj);


	return 0;
}


template <typename TileType>
int cTileMap<TileType>::RemoveObject(const c2DCoord* pObj)
{
	for(UINT i=0; i<m_pObjList.size(); i++)
	{
		if(pObj == m_pObjList[i])
		{
			RemoveObjFromTileMap(pObj);


			m_pObjList.erase(m_pObjList.begin() + i);


			return static_cast<int>(i);
		}
	}


	return -1;
}


template <typename TileType>
int cTileMap<TileType>::RemoveAt(int Idx)
{
	if(Idx < 0  ||  static_cast<UINT>(Idx) >= m_pObjList.size()) return -1;


	RemoveObjFromTileMap(m_pObjList[Idx]);


	m_pObjList.erase(m_pObjList.begin() + Idx);


	return 0;
}


template <typename TileType>
int cTileMap<TileType>::IndexOf(const c2DCoord* pObj)
{
	for(UINT i=0; i<m_pObjList.size(); i++)
	{
		if(pObj == m_pObjList[i])
		{
			return static_cast<int>(i);
		}
	}


	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TileType>
int cTileMap<TileType>::AddObjToTileMap(c2DCoord* pObj)
{
	D3DXVECTOR2 Pos(*pObj->Pos());

	Pos /= m_tileSize;

	int yPos = static_cast<int>(Pos.y);
	int xPos = static_cast<int>(Pos.x);


	if(yPos < 0) yPos = 0;
	else if(static_cast<UINT>(yPos) >= m_tileMap.size()) yPos = static_cast<int>(m_tileMap.size()-1);

	if(xPos < 0) xPos = 0;
	else if(static_cast<UINT>(xPos) >= m_tileMap[0].size()) xPos = static_cast<int>(m_tileMap.size()-1);


	if(yPos >= 0  &&  static_cast<UINT>(yPos) < m_tileMap.size()
		&&
		xPos >= 0  &&  static_cast<UINT>(xPos) < m_tileMap[yPos].size())
	{
		m_tileMap[yPos][xPos]->AddObj(pObj);
		m_tileMap[yPos][xPos]->UpdateOutCheck();
		return 0;
	}


	return -1;


	return -1;
}


template <typename TileType>
int cTileMap<TileType>::RemoveObjFromTileMap(const c2DCoord* pObj)
{
	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			m_tileMap[y][x]->RemoveObj(pObj);
		}
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TileType>
int cTileMap<TileType>::ForeachAboutTile(std::function<int(cTile*)> Func)
{
	for(UINT y=0; y<m_tileMap.size(); y++)
	{
		for(UINT x=0; x<m_tileMap[y].size(); x++)
		{
			Func(m_tileMap[y][x]);
		}
	}


	return 0;
}


template <typename TileType>
cTile* cTileMap<TileType>::GetTileIn(float x, float y)
{
	D3DXVECTOR2 Pos(x, y);

	Pos /= m_tileSize;

	int yPos = static_cast<int>(Pos.y);
	int xPos = static_cast<int>(Pos.x);


	if(yPos < 0) yPos = 0;
	else if(static_cast<UINT>(yPos) >= m_tileMap.size()) yPos = static_cast<int>(m_tileMap.size()-1);

	if(xPos < 0) xPos = 0;
	else if(static_cast<UINT>(xPos) >= m_tileMap[0].size()) xPos = static_cast<int>(m_tileMap.size()-1);


	if(yPos >= 0  &&  static_cast<UINT>(yPos) < m_tileMap.size()
		&&
		xPos >= 0  &&  static_cast<UINT>(xPos) < m_tileMap[yPos].size())
	{
		return m_tileMap[yPos][xPos];
	}


	return nullptr;
}


template <typename TileType>
cTile* cTileMap<TileType>::GetTileInCanNull(float x, float y)
{
	D3DXVECTOR2 Pos(x, y);

	Pos /= m_tileSize;

	int yPos = static_cast<int>(Pos.y);
	int xPos = static_cast<int>(Pos.x);


	if(yPos >= 0  &&  static_cast<UINT>(yPos) < m_tileMap.size()
		&&
		xPos >= 0  &&  static_cast<UINT>(xPos) < m_tileMap[yPos].size())
	{
		return m_tileMap[yPos][xPos];
	}


	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TileType>
D3DXVECTOR2 cTileMap<TileType>::GetRect() const
{
	return D3DXVECTOR2(m_tileSize*m_tileMap[0].size(), m_tileSize*m_tileMap.size());
}


template <typename TileType>
float cTileMap<TileType>::GetTileSize() const
{
	return m_tileSize;
}

