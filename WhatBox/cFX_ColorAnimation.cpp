#include "cFX_ColorAnimation.h"

#include "cCore.h"





































cFX_ColorAnimation::cFX_ColorAnimation(cTexture* pTx, DWORD startColor, DWORD endColor, float speed)
	: cFX(pTx)
	, m_startColor(startColor)
	, m_endColor(endColor)
{
	m_speed.a = (m_endColor.a - m_startColor.a) / 255.f * speed;
	m_speed.r = (m_endColor.r - m_startColor.r) / 255.f * speed;
	m_speed.g = (m_endColor.g - m_startColor.g) / 255.f * speed;
	m_speed.b = (m_endColor.b - m_startColor.b) / 255.f * speed;


	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_ColorAni), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_ColorAnimation::~cFX_ColorAnimation()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ColorAnimation::OnUpdate()
{
	


	return 0;
}


int cFX_ColorAnimation::OnRender()
{
	cCore::Sprite.SetColor(m_startColor.GetColor());
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_Pos, m_Angle, m_Scale);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_ColorAnimation::Seq_ColorAni()
{
	m_startColor.a += VFR(m_speed.a);
	m_startColor.r += VFR(m_speed.r);
	m_startColor.g += VFR(m_speed.g);
	m_startColor.b += VFR(m_speed.b);


	if(isColorEnd(m_speed.a, &m_startColor.a, m_endColor.a)
		&&
		isColorEnd(m_speed.r, &m_startColor.r, m_endColor.r)
		&&
		isColorEnd(m_speed.g, &m_startColor.g, m_endColor.g)
		&&
		isColorEnd(m_speed.b, &m_startColor.b, m_endColor.b))
	{
		return FUNCRESULT_End;
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cFX_ColorAnimation::isColorEnd(float speed, float *curr, float end)
{
	if(speed < 0.f)
	{
		if(*curr <= end)
		{
			*curr = end;
			return true;
		}

		return false;
	}
	else if(speed > 0.f)
	{
		if(*curr >= end)
		{
			*curr = end;
			return true;
		}

		return false;
	}
	
	
	return true;
}

