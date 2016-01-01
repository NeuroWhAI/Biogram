#include "cMessageMgr.h"

#include "cCore.h"

#include "cFuncSequence.h"



































cMessageMgr::cMessageMgr()
{

}


cMessageMgr::~cMessageMgr()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cMessageMgr::Update()
{
	for(UINT i=0; i<m_msgList.size(); i++)
	{
		m_msgList[i].Update();

		if(m_msgList[i].GetLife() < 1.f)
		{
			m_msgList.erase(m_msgList.begin() + i);
			i--;
		}
	}


	return 0;
}


int cMessageMgr::Render()
{
	for(UINT i=0; i<m_msgList.size(); i++)
	{
		m_msgList[i].Render();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cMessageMgr::PushMessage(std::wstring msg, DWORD color)
{
	UINT oldSize = m_msgList.size();


	m_msgList.emplace_back(msg, color);


	float height = m_msgList[oldSize].GetHeight();

	for(UINT i=0; i<oldSize; i++)
	{
		m_msgList[i].AddYPos(-height - 16.f);
	}


	return 0;
}

