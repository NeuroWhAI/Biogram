#pragma once

#include <memory>
#include <vector>

#include "Utility.h"

template <typename T_OBJ>
class Tile;



























template <typename T_OBJ>
class TileMap
{
public:
	TileMap();
	virtual ~TileMap();


protected:
	float m_tileSize;
	std::vector < std::vector < // 2Â÷¿ø
		std::shared_ptr<Tile<T_OBJ>> >> m_pTileMap;


public:
	template <typename T_TILE>
	int init(int widthTileCount, int heightTileCount,
		float tileSize);
	int update(double timePitch);


public:
	Utility::Point getTileIndexHave(std::shared_ptr<T_OBJ> pObj);
	std::shared_ptr<Tile<T_OBJ>> getTileHave(std::shared_ptr<T_OBJ> pObj);


public:
	bool addObject(std::shared_ptr<T_OBJ> pObj);
	bool removeObject(std::shared_ptr<T_OBJ> pObj);
};


#include "TileMap.inl"