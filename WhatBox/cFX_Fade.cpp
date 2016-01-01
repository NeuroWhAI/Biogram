#include "cFX_Fade.h"

#include "cCore.h"





































cFX_Fade::cFX_Fade(DWORD color, float speed, float accelSpeed)
	: cFX()

	, m_color(color)
	, m_speed(speed)
	, m_accelSpeed(accelSpeed)

	, m_currAlpha((speed < 0.f) ? 255.f : 0.f)
{
	if(speed < 0.f)
		m_sequencer.AddFunction(LAMBDA_FUNC(Seq_FadeIn), 0);
	else
		m_sequencer.AddFunction(LAMBDA_FUNC(Seq_FadeOut), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Fade::cFX_Fade(cTexture* pTx, DWORD color, float speed, float accelSpeed)
	: cFX(pTx)

	, m_color(color)
	, m_speed(speed)
	, m_accelSpeed(accelSpeed)

	, m_currAlpha((speed < 0.f) ? 255.f : 0.f)
{
	if(speed < 0.f)
		m_sequencer.AddFunction(LAMBDA_FUNC(Seq_FadeIn), 0);
	else
		m_sequencer.AddFunction(LAMBDA_FUNC(Seq_FadeOut), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Fade::~cFX_Fade()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Fade::OnUpdate()
{
	m_currAlpha += VFR(m_speed);
	m_speed += VFR(m_accelSpeed);

	if(m_currAlpha < 0.f) m_currAlpha = 0.f;
	else if(m_currAlpha > 255.f) m_currAlpha = 255.f;

	m_color = m_color & 0x00ffffff | (CAST(m_currAlpha, DWORD) << 24);


	return 0;
}


int cFX_Fade::OnRender()
{
	cCore::Sprite.SetColor(m_color);

	if(m_pTx == nullptr)
	{
		Util::TempOffCamera tempOffCam;


		cCore::Sprite.RenderTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
			D3DXVECTOR2(0.f, 0.f), 0.f,
			cCore::fWinSize/16.f);
	}
	else
	{
		cCore::Sprite.RenderTextureCenter(m_pTx,
			m_Pos, m_Angle, m_Scale);
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Fade::Seq_FadeOut()
{
	if(m_currAlpha >= 255.f  ||  m_currAlpha < 0.f)
	{
		m_currAlpha = 255.f;

		return FUNCRESULT_End;
	}


	return 0;
}


int cFX_Fade::Seq_FadeIn()
{
	if(m_currAlpha <= 0.f  ||  m_currAlpha > 255.f)
	{
		m_currAlpha = 0.f;

		return FUNCRESULT_End;
	}


	return 0;
}

