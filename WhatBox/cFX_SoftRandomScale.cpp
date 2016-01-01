#include "cFX_SoftRandomScale.h"

#include "cCore.h"





































cFX_SoftRandomScale::cFX_SoftRandomScale(cTexture* pTx, float volatility, float speedFactor)
	: cFX(pTx)
	, m_volatility(volatility)
	, m_currTargetScale(1.f + CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * volatility)
	, m_currSpeed(0.f)
	, m_speedFactor(speedFactor)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_ScaleDown), 0);
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_ScaleUp), 1);


	m_sequencer.SetCurrFuncNum(rand()%2);
}


cFX_SoftRandomScale::~cFX_SoftRandomScale()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_SoftRandomScale::OnUpdate()
{
	


	return 0;
}


int cFX_SoftRandomScale::OnRender()
{
	cCore::Sprite.SetColor(0x4fffffff);
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_Pos, m_Angle, m_Scale);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_SoftRandomScale::Seq_ScaleDown()
{
	m_currSpeed = ((m_Scale.x - m_currTargetScale) / 32.f + 0.0001f) * m_speedFactor;

	m_Scale.x -= VFR(m_currSpeed);
	m_Scale.y -= VFR(m_currSpeed);


	if(m_Scale.x <= m_currTargetScale)
	{
		m_currTargetScale = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_volatility;

		if(Util::Probable(50U))
		{
			m_currTargetScale *= -1.f;
		}

		m_currTargetScale += 1.f;


		if(m_currTargetScale < m_Scale.x)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}


	return 0;
}


int cFX_SoftRandomScale::Seq_ScaleUp()
{
	m_currSpeed = ((m_currTargetScale - m_Scale.x) / 32.f + 0.0001f) * m_speedFactor;

	m_Scale.x += VFR(m_currSpeed);
	m_Scale.y += VFR(m_currSpeed);


	if(m_Scale.x >= m_currTargetScale)
	{
		m_currTargetScale = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_volatility;

		if(Util::Probable(50U))
		{
			m_currTargetScale *= -1.f;
		}

		m_currTargetScale += 1.f;


		if(m_currTargetScale < m_Scale.x)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}


	return 1;
}

