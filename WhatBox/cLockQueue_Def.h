#include "cLockQueue.h"


































template <typename QueType>
cLockQueue<QueType>::cLockQueue()
{
	for(int i=LockNum_Queue; i<LockNum_EndOfList; i++)
	{
		m_Locker.Create(static_cast<unsigned int>(i));
	}
}


template <typename QueType>
cLockQueue<QueType>::~cLockQueue()
{
	m_Locker.DeleteAll();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename QueType>
int cLockQueue<QueType>::Send(const QueType& data)
{
	m_Locker.Begin(LockNum_Queue);

	m_Que.emplace(data);

	m_Locker.End(LockNum_Queue);


	return 0;
}


template <typename QueType>
int cLockQueue<QueType>::Receive(QueType* pOut)
{
	if(pOut == nullptr) return -2;


	m_Locker.Begin(LockNum_Queue);

	if(m_Que.size() <= 0)
	{
		m_Locker.End(LockNum_Queue);
		return -1;
	}

	m_Locker.End(LockNum_Queue);


	m_Locker.Begin(LockNum_Queue);

	*pOut = m_Que.front();

	m_Locker.End(LockNum_Queue);


	m_Locker.Begin(LockNum_Queue);

	m_Que.pop();

	m_Locker.End(LockNum_Queue);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename QueType>
UINT cLockQueue<QueType>::QueSize()
{
	m_Locker.Begin(LockNum_Queue);

	UINT temp = m_Que.size();

	m_Locker.End(LockNum_Queue);


	return temp;
}

