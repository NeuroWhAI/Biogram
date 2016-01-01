#pragma once
#include <queue>

#include "cLock.h"






























template <typename QueType>
class cLockQueue
{
public:
	cLockQueue();
	~cLockQueue();


private:
	cLock m_Locker;
	enum LockNum_
	{
		LockNum_Queue,



		//--------------
		LockNum_EndOfList
	};


private:
	std::queue<QueType> m_Que;


public:
	int Send(const QueType& data);
	int Receive(QueType* pOut);


public:
	UINT QueSize();
};


#include "cLockQueue_Def.h"