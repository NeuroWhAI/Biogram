#pragma once
#include <d3dx9.h>
#include <vector>
#include <functional>

class cTile;
class c2DCoord;
































template <typename TileType>
class cTileMap
{
public:
	cTileMap();
	cTileMap(int width, int height, float tileSize);
	~cTileMap();


private:
	float m_tileSize;
	std::vector<std::vector<cTile*>> m_tileMap;


private:
	std::vector<c2DCoord*> m_pObjList;


private:
	UINT m_startX, m_startY;
	UINT m_endX, m_endY;


public:
	int Init(int width, int height, float tileSize);

	int Update();
	int Render();


public:
	int AddObject(c2DCoord* pObj);
	int RemoveObject(const c2DCoord* pObj);
	int RemoveAt(int Idx);
	int IndexOf(const c2DCoord* pObj);


private:
	int AddObjToTileMap(c2DCoord* pObj);
	int RemoveObjFromTileMap(const c2DCoord* pObj);


public:
	int ForeachAboutTile(std::function<int(cTile*)> Func);
	cTile* GetTileIn(float x, float y);
	cTile* GetTileInCanNull(float x, float y);


public:
	D3DXVECTOR2 GetRect() const;
	float GetTileSize() const;
};


#include "cTileMap_Def.h"

