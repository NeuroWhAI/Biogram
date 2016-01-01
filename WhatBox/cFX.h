#pragma once
#include "cFuncSequence.h"
#include "c2DCoord.h"

class cTexture;

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 특수효과
// Desc : 텍스쳐를 기반으로 하는 특수효과 (※ delete가 필요없음)
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX : public c2DCoord
{
public:
	cFX();
	cFX(cTexture* pTx);
	cFX(cTexture* pTx, DWORD continueTime);
	virtual ~cFX();


private:
	bool m_bDeleteByMgr;


protected:
	cTexture* m_pTx;
	DWORD m_continueTime;


protected:
	cFuncSequence m_sequencer;
	DWORD m_prevFXStartTime;


public:
	int Update();
	int Render();


public:
	int SetFXTexture(cTexture* pTx);
	int SetContinueTime(DWORD continueTime);
	int Stop();


protected:
	virtual int OnUpdate() = 0;
	virtual int OnRender() = 0;


public:
	virtual bool isEnd();
	void SetDeleteByMgr();
};

