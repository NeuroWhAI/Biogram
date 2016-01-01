#include "cFX.h"

#include "cCore.h"




































cFX::cFX()
	: m_pTx(nullptr)
	, m_bDeleteByMgr(false)
	, m_continueTime(0UL)
	, m_prevFXStartTime(timeGetTime())
{
	cCore::FxMgr.AddFX(this);
}


cFX::cFX(cTexture* pTx)
	: m_pTx(pTx)
	, m_bDeleteByMgr(false)
	, m_continueTime(0UL)
	, m_prevFXStartTime(timeGetTime())
{
	cCore::FxMgr.AddFX(this);
}


cFX::cFX(cTexture* pTx, DWORD continueTime)
	: m_pTx(pTx)
	, m_bDeleteByMgr(false)
	, m_continueTime(continueTime)
	, m_prevFXStartTime(timeGetTime())
{
	cCore::FxMgr.AddFX(this);
}


cFX::~cFX()
{
	if(!m_bDeleteByMgr)
		cCore::FxMgr.RemoveFX(this);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX::Update()
{
	m_sequencer.Update();


	if(m_continueTime != 0UL)
	{
		if(timeGetTime() - m_prevFXStartTime > m_continueTime)
		{
			m_sequencer.SetCurrFuncNum(FUNCRESULT_End);
		}
	}


	m_Pos += VFR(m_Speed);
	m_Angle += VFR(m_AngleSpeed);


	return OnUpdate();
}


int cFX::Render()
{



	return OnRender();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX::SetFXTexture(cTexture* pTx)
{
	m_pTx = pTx;


	return 0;
}


int cFX::SetContinueTime(DWORD continueTime)
{
	m_continueTime = continueTime;
	m_prevFXStartTime = timeGetTime();


	return 0;
}


int cFX::Stop()
{
	m_sequencer.SetCurrFuncNum(FUNCRESULT_End);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cFX::isEnd()
{
	return m_sequencer.IsEnd();
}


void cFX::SetDeleteByMgr()
{
	m_bDeleteByMgr = true;
}

