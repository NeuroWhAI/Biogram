#include "Tile.h"

#include "TileObjectIterator.h"



























template <typename T_OBJ>
Tile<T_OBJ>::Tile()
	: m_tileSize(1.0f)
{
	for (auto& pNearTile : m_pNearTiles)
		pNearTile = nullptr;
}


template <typename T_OBJ>
Tile<T_OBJ>::~Tile()
{

}

//###############################################################

template <typename T_OBJ>
int Tile<T_OBJ>::update(double timePitch)
{



	return afterUpdate(timePitch);
}


template <typename T_OBJ>
int Tile<T_OBJ>::checkObjectOut()
{
	auto it = m_pObjList.begin();
	while(it != m_pObjList.end())
	{
		if (checkObjectOut(*it))
			it = m_pObjList.erase(it);
		else
			++it;
	}


	return 0;
}


template <typename T_OBJ>
bool Tile<T_OBJ>::checkObjectOut(std::shared_ptr<T_OBJ> pObj)
{
	Utility::PointF location = pObj->getLocation();
	Utility::PointF speed = pObj->getSpeed();
	bool isOut = true;
	int nearIndex = -1;


	if (location.x < m_leftTop.x)
	{
		if (location.y < m_leftTop.y)
		{
			nearIndex = 0;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocation(m_leftTop);
				pObj->setSpeed(-speed);
			}
		}
		else if (location.y >= m_rightBottom.y)
		{
			nearIndex = 6;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocation(m_leftTop + Utility::PointF(0.0f, m_tileSize - 0.001f));
				pObj->setSpeed(-speed);
			}
		}
		else
		{
			nearIndex = 7;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocationX(m_leftTop.x);
				pObj->setSpeedX(-speed.x);
			}
		}
	}
	else if (location.x >= m_rightBottom.x)
	{
		if (location.y < m_leftTop.y)
		{
			nearIndex = 2;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocation(m_leftTop + Utility::PointF(m_tileSize - 0.001f, 0.0f));
				pObj->setSpeed(-speed);
			}
		}
		else if (location.y >= m_rightBottom.y)
		{
			nearIndex = 4;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocation(m_rightBottom + Utility::PointF(-0.001f, -0.001f));
				pObj->setSpeed(-speed);
			}
		}
		else
		{
			nearIndex = 3;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocationX(m_rightBottom.x - 0.001f);
				pObj->setSpeedX(-speed.x);
			}
		}
	}
	else
	{
		if (location.y < m_leftTop.y)
		{
			nearIndex = 1;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocationY(m_leftTop.y);
				pObj->setSpeedY(-speed.y);
			}
		}
		else if (location.y >= m_rightBottom.y)
		{
			nearIndex = 5;
			if (m_pNearTiles[nearIndex] != nullptr)
				m_pNearTiles[nearIndex]->addObject(pObj);
			else
			{
				pObj->setLocationY(m_rightBottom.y - 0.001f);
				pObj->setSpeedY(-speed.y);
			}
		}
		else
		{
			isOut = false;
		}
	}


	return (isOut && m_pNearTiles[nearIndex] != nullptr);
}

//###############################################################

template <typename T_OBJ>
int Tile<T_OBJ>::setRect(float leftX, float topY, float tileSize)
{
	m_leftTop.x = leftX;
	m_leftTop.y = topY;

	m_rightBottom.x = leftX + tileSize;
	m_rightBottom.y = topY + tileSize;

	m_tileSize = tileSize;


	return 0;
}


template <typename T_OBJ>
int Tile<T_OBJ>::setRect(Utility::PointF leftTop, float tileSize)
{
	return setRect(leftTop.x, leftTop.y, tileSize);
}


template <typename T_OBJ>
int Tile<T_OBJ>::setNearTile(std::shared_ptr<Tile<T_OBJ>> pTile, int index)
{
	m_pNearTiles[index] = pTile;


	return 0;
}

//###############################################################

template <typename T_OBJ>
bool Tile<T_OBJ>::addObject(std::shared_ptr<T_OBJ> pObj)
{
	m_pObjList.push_back(pObj);


	return afterAddUnit(pObj);
}


template <typename T_OBJ>
bool Tile<T_OBJ>::removeObject(std::shared_ptr<T_OBJ> pObj)
{
	bool bResult = beforeRemoveUnit(pObj);


	m_pObjList.remove(pObj);


	return bResult;
}

//###############################################################

template <typename T_OBJ>
TileObjectIterator<T_OBJ> Tile<T_OBJ>::getObjectIterator()
{
	TileObjectIterator<T_OBJ> beginItr(*this);

	return beginItr;
}

