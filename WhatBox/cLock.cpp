#include "cLock.h"
























cLock::~cLock()
{
	DeleteAll();
}

//////////////////////////////////////////////////////////////////////////////////////

UINT cLock::Create(UINT Id)
{
	while(Id >= m_SecList.size()) m_SecList.push_back(CRITICAL_SECTION());
	while(Id >= m_IsReadyList.size()) m_IsReadyList.push_back(false);

	if(m_IsReadyList[Id])
	{// 이미 있음
		m_SecList.push_back(CRITICAL_SECTION());
		m_IsReadyList.push_back(false);

		InitializeCriticalSection(&m_SecList[Id + 1]);
		m_IsReadyList[Id + 1] = true;


		return Id + 1;
	}
	else
	{
		InitializeCriticalSection(&m_SecList[Id]);
		m_IsReadyList[Id] = true;
	}


	return Id;
}


void cLock::Delete(UINT Id)
{
	DeleteCriticalSection(&m_SecList[Id]);
	m_IsReadyList[Id] = false;
}


void cLock::DeleteAll()
{
	for(UINT i=0; i<m_SecList.size(); i++)
	{
		if(m_IsReadyList[i])
		{
			Delete(i);
		}
	}


	m_SecList.clear();
	m_IsReadyList.clear();
}

//////////////////////////////////////////////////////////////////////////////////////

void cLock::Begin(UINT Id)
{
	try
	{
		EnterCriticalSection(&m_SecList[Id]);
	}
	catch(...)
	{
		
	}
}


void cLock::End(UINT Id)
{
	try
	{
		LeaveCriticalSection(&m_SecList[Id]);
	}
	catch(...)
	{

	}
}

