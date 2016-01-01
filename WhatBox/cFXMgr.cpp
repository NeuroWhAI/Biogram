#include "cFXMgr.h"

#include "cFX.h"



































cFXMgr::cFXMgr()
{

}


cFXMgr::~cFXMgr()
{
	for(unsigned int i=0; i<m_pFXList.size(); i++)
	{
		m_pFXList[i]->SetDeleteByMgr(); // cFX가 자신의 RemoveFX를 호출하지 않도록 함
		delete m_pFXList[i];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFXMgr::Update()
{
	for(unsigned int i=0; i<m_pFXList.size(); i++)
	{
		if(m_pFXList[i]->isEnd())
		{
			m_pFXList[i]->SetDeleteByMgr(); // cFX가 자신의 RemoveFX를 호출하지 않도록 함
			delete m_pFXList[i];
			m_pFXList.erase(m_pFXList.begin() + i);


			i--;
			continue;
		}


		m_pFXList[i]->Update();
	}


	return 0;
}


int cFXMgr::Render()
{
	for(unsigned int i=0; i<m_pFXList.size(); i++)
	{
		m_pFXList[i]->Render();
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFXMgr::AddFX(cFX* pFX)
{
	m_pFXList.emplace_back(pFX);


	return 0;
}


int cFXMgr::RemoveFX(const cFX* pFX)
{
	for(unsigned int i=0; i<m_pFXList.size(); i++)
	{
		if(m_pFXList[i] == pFX)
		{
			m_pFXList[i]->SetDeleteByMgr(); // cFX가 자신의 RemoveFX를 호출하지 않도록 함
			delete m_pFXList[i];
			m_pFXList.erase(m_pFXList.begin() + i);


			return 0;
		}
	}


	return -1;
}


int cFXMgr::RemoveAll()
{
	for(unsigned int i=0; i<m_pFXList.size(); i++)
	{
		m_pFXList[i]->SetDeleteByMgr(); // cFX가 자신의 RemoveFX를 호출하지 않도록 함
		delete m_pFXList[i];
	}

	m_pFXList.clear();


	return 0;
}

