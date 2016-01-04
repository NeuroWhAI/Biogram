#include "TileObjectIterator.h"

#include "Tile.h"



























template <typename T_OBJ>
TileObjectIterator<T_OBJ>::TileObjectIterator(Tile<T_OBJ>& centerTile)
	: m_centerTile(centerTile)
	, m_currentNearIndex(-1)
	, m_currentItr(centerTile.m_pObjList.begin())
	, m_currentEnd(centerTile.m_pObjList.end())

	, m_isEnd(centerTile.m_pObjList.size() <= 0)
{

}


template <typename T_OBJ>
TileObjectIterator<T_OBJ>::~TileObjectIterator()
{

}

//###############################################################

template <typename T_OBJ>
void TileObjectIterator<T_OBJ>::setToEnd()
{
	m_isEnd = true;
}


template <typename T_OBJ>
bool TileObjectIterator<T_OBJ>::isEnd() const
{
	return m_isEnd;
}

//###############################################################

template <typename T_OBJ>
std::shared_ptr<T_OBJ>& TileObjectIterator<T_OBJ>::operator* ()
{
	return *m_currentItr;
}


template <typename T_OBJ>
std::shared_ptr<T_OBJ>* TileObjectIterator<T_OBJ>::operator-> ()
{
	return &*m_currentItr;
}

//---------------------------------------------------------------

template <typename T_OBJ>
TileObjectIterator<T_OBJ>& TileObjectIterator<T_OBJ>::operator++ ()
{
	++m_currentItr;

	if (m_currentItr == m_currentEnd)
	{
		std::shared_ptr<Tile<T_OBJ>> pNextTile = nullptr;


		for (++m_currentNearIndex; m_currentNearIndex < 8; ++m_currentNearIndex)
		{
			pNextTile = m_centerTile.m_pNearTiles[m_currentNearIndex];

			if (pNextTile)
			{
				m_currentItr = pNextTile->m_pObjList.begin();
				m_currentEnd = pNextTile->m_pObjList.end();

				if (m_currentItr == m_currentEnd) continue;

				break;
			}
		}

		if (m_currentNearIndex >= 8
			||
			pNextTile == nullptr)
		{
			m_isEnd = true;
		}
	}


	return *this;
}


template <typename T_OBJ>
TileObjectIterator<T_OBJ>& TileObjectIterator<T_OBJ>::operator-- ()
{
	// TODO: 


	return *this;
}


template <typename T_OBJ>
TileObjectIterator<T_OBJ> TileObjectIterator<T_OBJ>::operator++ (int)
{
	auto temp = *this;

	this->operator++();

	return temp;
}


template <typename T_OBJ>
TileObjectIterator<T_OBJ> TileObjectIterator<T_OBJ>::operator-- (int)
{
	auto temp = *this;

	this->operator--();

	return temp;
}

