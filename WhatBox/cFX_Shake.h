#pragma once
#include "cFX.h"


































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��鸲
// Desc : �����̳� ī�޶� ��鸲
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Shake : public cFX
{
public:
	cFX_Shake(float size, DWORD delay);
	cFX_Shake(cTexture* pTx, float size, DWORD delay);
	~cFX_Shake();


private:
	D3DXVECTOR2 m_shakePos;
	float m_size;
	DWORD m_delay;
	DWORD m_prevShakeTime;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_Shake();
};

