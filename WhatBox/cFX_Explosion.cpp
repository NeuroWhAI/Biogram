#include "cFX_Explosion.h"

#include "cCore.h"





































cFX_Explosion::cFX_Explosion(cTexture* pTxBoom, cTexture* pTxShockWave, float startSize, float endSize, float boomSpeed)
	: cFX(pTxBoom)
	, m_pTxShockWave(pTxShockWave)
	, m_startSize(startSize)
	, m_endSize(endSize)
	, m_boomSpeed(boomSpeed)

	, m_currBoomSize(startSize)
	, m_currWaveSize(0.f)
	, m_currBoomSpeed(0.f)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Boom), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Explosion::~cFX_Explosion()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Explosion::OnUpdate()
{
	


	return 0;
}


int cFX_Explosion::OnRender()
{
	float alpha = 255.f * (m_endSize - m_currBoomSize) / (m_endSize - m_startSize);
	if(alpha < 0.f) alpha = 0.f;
	else if(alpha > 255.f) alpha = 255.f;


	cCore::Sprite.SetColor(D3DCOLOR_ARGB(CAST(alpha, int), 255, 255, 255));
	cCore::Sprite.RenderTextureCenter(m_pTxShockWave,
		m_Pos, m_Angle, D3DXVECTOR2(m_currWaveSize, m_currWaveSize));
	
	cCore::Sprite.SetColor(D3DCOLOR_ARGB(CAST(alpha, int), 255, 255, 255));
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_Pos, m_Angle, D3DXVECTOR2(m_currBoomSize, m_currBoomSize));


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Explosion::Seq_Boom()
{
	m_currBoomSize += VFR(m_currBoomSpeed);
	m_currWaveSize += VFR(m_currBoomSpeed * 4.f);

	m_currBoomSpeed = 0.001f + m_boomSpeed * (m_endSize - m_currBoomSize) / (m_endSize - m_startSize);


	if(m_currBoomSize >= m_endSize)
		return FUNCRESULT_End;


	return 0;
}

