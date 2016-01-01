#include "cFX_ScaleDown.h"

#include "cCore.h"





































cFX_ScaleDown::cFX_ScaleDown(cTexture* pTx, float targetScale, float speed, float accelSpeed)
	: cFX(pTx)
	, m_targetScale(targetScale)
	, m_speed(speed)
	, m_accelSpeed(accelSpeed)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_ScaleDown), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_ScaleDown::~cFX_ScaleDown()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ScaleDown::OnUpdate()
{
	


	return 0;
}


int cFX_ScaleDown::OnRender()
{
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_Pos, m_Angle, m_Scale);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ScaleDown::Seq_ScaleDown()
{
	m_Scale.x -= VFR(m_speed);
	m_Scale.y -= VFR(m_speed);

	m_speed += VFR(m_accelSpeed);


	if(m_Scale.x <= m_targetScale)
		return FUNCRESULT_End;


	return 0;
}

