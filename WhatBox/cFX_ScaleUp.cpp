#include "cFX_ScaleUp.h"

#include "cCore.h"





































cFX_ScaleUp::cFX_ScaleUp(cTexture* pTx, float targetScale, float speed, float accelSpeed)
	: cFX(pTx)
	, m_targetScale(targetScale)
	, m_speed(speed)
	, m_accelSpeed(accelSpeed)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_ScaleUp), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_ScaleUp::~cFX_ScaleUp()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ScaleUp::OnUpdate()
{
	


	return 0;
}


int cFX_ScaleUp::OnRender()
{
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_Pos, m_Angle, m_Scale);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ScaleUp::Seq_ScaleUp()
{
	m_Scale.x += VFR(m_speed);
	m_Scale.y += VFR(m_speed);

	m_speed += VFR(m_accelSpeed);


	if(m_Scale.x >= m_targetScale)
		return FUNCRESULT_End;


	return 0;
}

