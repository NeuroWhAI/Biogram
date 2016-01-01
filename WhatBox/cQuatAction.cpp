#include "cQuatAction.h"

#include "cCore.h"

#include "cQuatAni.h"






































cQuatAction::cQuatAction()
	: m_currAniNum(-1)
	, m_bOnLock(false)
{

}


cQuatAction::~cQuatAction()
{
	for (UINT i = 0; i < m_pAniList.size(); ++i)
	{
		SAFE_DELETE(m_pAniList[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAction::Update()
{
	if (m_currAniNum >= 0)
	{
		m_pAniList[m_currAniNum]->SetPos(&m_Pos);
		m_pAniList[m_currAniNum]->SetSpeed(&m_Speed);
		m_pAniList[m_currAniNum]->SetAngle(m_Angle);
		m_pAniList[m_currAniNum]->SetAngleSpeed(m_AngleSpeed);
		m_pAniList[m_currAniNum]->SetZPos(m_zPos);
		m_pAniList[m_currAniNum]->SetZSpeed(m_zSpeed);


		m_pAniList[m_currAniNum]->Update();

		if (m_bOnLock  &&  m_pAniList[m_currAniNum]->IsEnd())
		{
			m_bOnLock = false;
		}
	}


	return 0;
}


int cQuatAction::Render()
{
	if (m_currAniNum >= 0)
	{
		m_pAniList[m_currAniNum]->Render();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAction::AddQuatAni(int aniNum, cTextureList* pTxList, int frameNum, int angleNum, DWORD delay)
{
	if (aniNum < 0) return -1;
	while (CAST(aniNum, UINT) >= m_pAniList.size()) m_pAniList.emplace_back(nullptr);


	SAFE_DELETE(m_pAniList[aniNum]);

	m_pAniList[aniNum] = new cQuatAni(pTxList, frameNum, angleNum, delay);


	return 0;
}


int cQuatAction::SetCurrAniNum(int currAniNum)
{
	if (m_bOnLock == false && m_currAniNum != currAniNum)
	{
		if (m_currAniNum >= 0)
		{
			m_pAniList[m_currAniNum]->Stop();
		}


		m_currAniNum = currAniNum;
	}


	return 0;
}


int cQuatAction::GetCurrAniNum() const
{
	return m_currAniNum;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAction::Play()
{
	for (UINT i = 0; i < m_pAniList.size(); ++i)
	{
		if (m_pAniList[i] == nullptr) continue;


		m_pAniList[i]->Play();
	}


	return 0;
}


int cQuatAction::Pause()
{
	for (UINT i = 0; i < m_pAniList.size(); ++i)
	{
		if (m_pAniList[i] == nullptr) continue;


		m_pAniList[i]->Pause();
	}


	return 0;
}


int cQuatAction::Stop()
{
	for (UINT i = 0; i < m_pAniList.size(); ++i)
	{
		if (m_pAniList[i] == nullptr) continue;


		m_pAniList[i]->Stop();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAction::Lock()
{
	m_bOnLock = true;


	return 0;
}


int cQuatAction::UnLock()
{
	m_bOnLock = false;


	return 0;
}

