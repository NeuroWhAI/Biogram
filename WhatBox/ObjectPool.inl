#include "ObjectPool.h"



























template <typename T>
size_t ObjectPool<T>::s_defaultChunkSize;

//#################################################################

template <typename T>
ObjectPool<T>::ObjectPool(size_t chunkSize)
	: m_chunkSize(chunkSize)
{
	allocateChunk();
}


template <typename T>
ObjectPool<T>::~ObjectPool()
{

}

//#################################################################

template <typename T>
ObjectPool<T>::ObjectPool(const ObjectPool<T>& src)
{

}


template <typename T>
ObjectPool<T>& ObjectPool<T>::operator= (const ObjectPool<T>& rhs)
{
	return *this;
}

//#################################################################

template <typename T>
void ObjectPool<T>::allocateChunk()
{
	for (size_t i = 0; i < m_chunkSize; ++i)
	{
		m_freeList.push(std::make_shared<T>());
	}
}

//#################################################################

template <typename T>
std::shared_ptr<T> ObjectPool<T>::acquireObject()
{
	if (m_freeList.empty())
	{
		allocateChunk();
	}


	auto obj = m_freeList.front();
	m_freeList.pop();


	return obj;
}


template <typename T>
void ObjectPool<T>::releaseObject(std::shared_ptr<T> obj)
{
	m_freeList.push(obj);
}

