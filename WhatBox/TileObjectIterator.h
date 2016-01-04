#pragma once

#include <memory>
#include <list>

template <typename T_OBJ>
class Tile;



























template <typename T_OBJ>
class TileObjectIterator
{
public:
	explicit TileObjectIterator(Tile<T_OBJ>& centerTile);
	virtual ~TileObjectIterator();


protected:
	Tile<T_OBJ>& m_centerTile;
	int m_currentNearIndex;
	typename std::list<std::shared_ptr<T_OBJ>>::
		iterator m_currentItr;
	typename std::list<std::shared_ptr<T_OBJ>>::
		iterator m_currentEnd;

	bool m_isEnd;


public:
	void setToEnd();
	bool isEnd() const;


public:
	std::shared_ptr<T_OBJ>& operator* ();
	std::shared_ptr<T_OBJ>* operator-> ();

	TileObjectIterator<T_OBJ>& operator++ ();
	TileObjectIterator<T_OBJ>& operator-- ();
	TileObjectIterator<T_OBJ> operator++ (int);
	TileObjectIterator<T_OBJ> operator-- (int);
};


#include "TileObjectIterator.inl"