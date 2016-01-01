#include "cAction.h"

#include "cCore.h"

#include "c2DImgListRender.h"
#include "cTextureList.h"































cAction::cAction()
	: m_pRender(new c2DImgListRender())
	, m_BasicActionNum(0)
	, m_CurrActionNum(0)
	, m_bWasEnd(false)
{

}


cAction::~cAction()
{
	if(m_pRender != NULL)
	{
		delete m_pRender;
		m_pRender = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cAction::Init(int BasicActionNum)
{
	m_BasicActionNum = BasicActionNum;
	m_CurrActionNum = BasicActionNum;


	return 0;
}


int cAction::AddAction(cTextureList* pTxList, DWORD Delay, bool bOnce, int NextActionNum)
{
	UINT Idx = m_pActionList.size();


	m_pActionList.push_back(pTxList);
	m_DelayList.push_back(Delay);
	m_bOnceList.push_back(bOnce);
	m_NextActionNumList.push_back(NextActionNum);


	if(Idx == CAST(m_BasicActionNum, UINT))
	{
		m_CurrActionNum = m_BasicActionNum;
		m_pRender->Init(pTxList, Delay, bOnce);
	}


	return 0;
}


int cAction::AddAction(UINT Idx, cTextureList* pTxList, DWORD Delay, bool bOnce, int NextActionNum)
{
	while(Idx >= m_pActionList.size()) m_pActionList.push_back(NULL);
	while(Idx >= m_DelayList.size()) m_DelayList.push_back(1UL);
	while(Idx >= m_bOnceList.size()) m_bOnceList.push_back(false);
	while(Idx >= m_NextActionNumList.size()) m_NextActionNumList.push_back(-1);


	m_pActionList[Idx] = pTxList;
	m_DelayList[Idx] = Delay;
	m_bOnceList[Idx] = bOnce;
	m_NextActionNumList[Idx] = NextActionNum;


	if(Idx == CAST(m_BasicActionNum, UINT))
	{
		m_CurrActionNum = m_BasicActionNum;
		m_pRender->Init(pTxList, Delay, bOnce);
	}


	return 0;
}


int cAction::RemoveAction(UINT Idx)
{
	if(Idx < m_pActionList.size())
	{
		m_pActionList.erase(m_pActionList.begin() + Idx);
		m_DelayList.erase(m_DelayList.begin() + Idx);
		m_bOnceList.erase(m_bOnceList.begin() + Idx);
		m_NextActionNumList.erase(m_NextActionNumList.begin() + Idx);
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cAction::Update()
{
	m_bWasEnd = false;


	m_pRender->Update();

	if(m_pRender->isEnd())
	{
		m_bWasEnd = true;


		if(m_NextActionNumList[m_CurrActionNum] < 0)
		{// 기본 동작으로 감
			m_CurrActionNum = m_BasicActionNum;
		}
		else
		{// 다음 동작으로 감
			m_CurrActionNum = m_NextActionNumList[m_CurrActionNum];
		}

		m_pRender->Init(m_pActionList[m_CurrActionNum],
			m_DelayList[m_CurrActionNum],
			m_bOnceList[m_CurrActionNum]);
	}


	return 0;
}


int cAction::Render()
{
	if(cCore::Sprite.CameraOnCheck())
		SetMatrixWithCameraToSprite();
	else
		SetMatrixToSprite();


	m_pRender->Render();


	return 0;
}


int cAction::RenderCenter()
{
	if(cCore::Sprite.CameraOnCheck())
		SetMatrixWithCameraToSprite();
	else
		SetMatrixToSprite();


	m_pRender->RenderCenter();


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cAction::SetAction(int Idx)
{
	if(Idx < 0)
		return SetActionToBasic();


	m_CurrActionNum = Idx;
	m_pRender->Init(m_pActionList[Idx],
		m_DelayList[Idx],
		m_bOnceList[Idx]);


	return 0;
}


int cAction::SetActionNoReset(int Idx)
{
	if(Idx < 0)
		return SetActionToBasic();


	if(m_CurrActionNum != Idx)
	{
		m_CurrActionNum = Idx;

		m_pRender->Init(m_pActionList[Idx],
			m_DelayList[Idx],
			m_bOnceList[Idx]);
	}


	return 0;
}


int cAction::SetActionToBasic()
{
	m_CurrActionNum = m_BasicActionNum;
	m_pRender->Init(m_pActionList[m_BasicActionNum],
		m_DelayList[m_BasicActionNum],
		m_bOnceList[m_BasicActionNum]);


	return 0;
}


int cAction::CurrActionNum() const
{
	return m_CurrActionNum;
}


bool cAction::isEnd() const
{
	return m_bWasEnd;
}

