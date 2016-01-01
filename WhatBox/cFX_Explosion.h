#pragma once
#include "cFX.h"


































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : Æø¹ß
// Desc : Æø¹ßÈ¿°ú
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Explosion : public cFX
{
public:
	cFX_Explosion(cTexture* pTxBoom, cTexture* pTxShockWave, float startSize, float endSize, float boomSpeed);
	~cFX_Explosion();


private:
	cTexture* m_pTxShockWave;
	float m_startSize, m_endSize;
	float m_boomSpeed;


private:
	float m_currBoomSize;
	float m_currWaveSize;
	float m_currBoomSpeed;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_Boom();
};

