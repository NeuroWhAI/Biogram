#pragma once

#include <memory>
#include <list>
#include <array>
#include <type_traits>

#include "Utility.h"

#include "Object.h"

template <typename T_OBJ>
class TileObjectIterator;



























template <typename T_OBJ>
class Tile
{
	static_assert(std::is_base_of<Object, T_OBJ>::value,
		"T_OBJ is not derived from Object.");


protected:
	friend TileObjectIterator<T_OBJ>;


public:
	Tile();
	virtual ~Tile();


protected:
	std::array<std::shared_ptr<Tile<T_OBJ>>, 8> m_pNearTiles;
	Utility::PointF m_leftTop, m_rightBottom;
	float m_tileSize;


protected:
	std::list<std::shared_ptr<T_OBJ>> m_pObjList;


public:
	int update(double timePitch);
	int checkObjectOut();
	bool checkObjectOut(std::shared_ptr<T_OBJ> pObj);


public:
	int setRect(float leftX, float topY, float tileSize);
	int setRect(Utility::PointF leftTop, float tileSize);
	int setNearTile(std::shared_ptr<Tile<T_OBJ>> pTile, int index);


public:
	// * 타일에 pObj을 등록합니다.
	// * @Return: 등록성공여부
	bool addObject(std::shared_ptr<T_OBJ> pObj);
	// * 타일에서 pObj을 제거합니다.
	// * @Return: 제거성공여부
	bool removeObject(std::shared_ptr<T_OBJ> pObj);


protected:
	typedef TileObjectIterator<T_OBJ> ObjectIterator;
	ObjectIterator getObjectIterator();


protected:
	virtual int afterUpdate(double timePitch) = 0;
	virtual bool afterAddUnit(std::shared_ptr<T_OBJ> pObj) = 0;
	virtual bool beforeRemoveUnit(std::shared_ptr<T_OBJ> pObj) = 0;
};


#include "Tile.inl"