#pragma once

#include <queue>
#include <memory>



























template <typename T>
class ObjectPool
{
protected:
	static const size_t s_defaultChunkSize = 10;


public:
	ObjectPool(size_t chunkSize = s_defaultChunkSize);
	virtual ~ObjectPool();


private:
	ObjectPool(const ObjectPool<T>& src);
	ObjectPool<T>& operator= (const ObjectPool<T>& rhs);


protected:
	std::queue<std::shared_ptr<T>> m_freeList;
	size_t m_chunkSize;


protected:
	void allocateChunk();


public:
	std::shared_ptr<T> acquireObject();
	void releaseObject(std::shared_ptr<T> obj);
};


#include "ObjectPool.inl"