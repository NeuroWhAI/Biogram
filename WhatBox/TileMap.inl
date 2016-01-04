#include "TileMap.h"

#include <type_traits>

#include "Tile.h"



























template <typename T_OBJ>
TileMap<T_OBJ>::TileMap()
	: m_tileSize(1.0f)
{

}


template <typename T_OBJ>
TileMap<T_OBJ>::~TileMap()
{

}

//###############################################################

template <typename T_OBJ>
template <typename T_TILE>
int TileMap<T_OBJ>::init(int widthTileCount, int heightTileCount,
	float tileSize)
{
	static_assert(std::is_base_of<Tile<T_OBJ>, T_TILE>::value,
		"T_TILE is not derived from Tile<T_OBJ>.");


	m_tileSize = tileSize;


	// 타일 생성
	m_pTileMap.clear();

	for (int x = 0; x < widthTileCount; ++x)
	{
		m_pTileMap.emplace_back();

		for (int y = 0; y < heightTileCount; ++y)
		{
			std::shared_ptr<Tile<T_OBJ>> pNewTile = std::make_shared<T_TILE>();
			pNewTile->setRect(tileSize * x, tileSize * y,
				tileSize);

			m_pTileMap[x].emplace_back(pNewTile);
		}
	}


	// 인접타일 연결
	for (int x = 0; x < widthTileCount; ++x)
	{
		for (int y = 0; y < heightTileCount; ++y)
		{
			std::shared_ptr<Tile<T_OBJ>> centerTile = m_pTileMap[x][y];

			int nearX[8] = {
				x - 1, x, x + 1, x + 1, x + 1, x, x - 1, x - 1
			};
			int nearY[8] = {
				y - 1, y - 1, y - 1, y, y + 1, y + 1, y + 1, y
			};

			for (int n = 0; n < 8; ++n)
			{
				int nX = nearX[n];
				int nY = nearY[n];

				if (nX < 0
					||
					static_cast<size_t>(nX) >= m_pTileMap.size()
					||
					nY < 0
					||
					static_cast<size_t>(nY) >= m_pTileMap[nX].size())
				{
					centerTile->setNearTile(nullptr, n);
				}
				else
				{
					centerTile->setNearTile(m_pTileMap[nX][nY], n);
				}
			}
		}
	}


	return 0;
}


template <typename T_OBJ>
int TileMap<T_OBJ>::update(double timePitch)
{
	// 타일 내부작업 수행
	for (auto& verticalList : m_pTileMap)
	{
		for (auto& pTile : verticalList)
		{
			pTile->update(timePitch);
		}
	}


	// 타일을 벗어난 물체 확인 후 처리
	for (auto& verticalList : m_pTileMap)
	{
		for (auto& pTile : verticalList)
		{
			pTile->checkObjectOut();
		}
	}


	return 0;
}

//###############################################################

template <typename T_OBJ>
Utility::Point TileMap<T_OBJ>::getTileIndexHave(std::shared_ptr<T_OBJ> pObj)
{
	Utility::PointF location = pObj->getLocation();
	location /= m_tileSize;
	Utility::Point index = location;

	if (index.x < 0)
		index.x = 0;
	else if (static_cast<size_t>(index.x) >= m_pTileMap.size())
		index.x = static_cast<int>(m_pTileMap.size() - 1);

	if (index.y < 0)
		index.y = 0;
	else if (static_cast<size_t>(index.y) >= m_pTileMap[index.x].size())
		index.y = static_cast<int>(m_pTileMap[index.x].size() - 1);


	return index;
}


template <typename T_OBJ>
std::shared_ptr<Tile<T_OBJ>> TileMap<T_OBJ>::getTileHave(std::shared_ptr<T_OBJ> pObj)
{
	Utility::Point index = getTileIndexHave(pObj);


	return m_pTileMap[index.x][index.y];
}

//###############################################################

template <typename T_OBJ>
bool TileMap<T_OBJ>::addObject(std::shared_ptr<T_OBJ> pObj)
{
	std::shared_ptr<Tile<T_OBJ>> tile = getTileHave(pObj);

	if (tile)
	{
		tile->checkObjectOut(pObj);
		return tile->addObject(pObj);
	}


	return false;
}


template <typename T_OBJ>
bool TileMap<T_OBJ>::removeObject(std::shared_ptr<T_OBJ> pObj)
{
	std::shared_ptr<Tile<T_OBJ>> tile = getTileHave(pObj);

	if(tile)
		return tile->removeObject(pObj);


	return false;
}

