#include "cFX_Shake.h"

#include "cCore.h"





































cFX_Shake::cFX_Shake(float size, DWORD delay)
	: cFX()
	, m_shakePos(0.f, 0.f)
	, m_size(size)
	, m_delay(delay)
	, m_prevShakeTime(0UL)
{
	/*m_shakePos.x = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;
	m_shakePos.y = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;

	if(Util::Probable(50U)) m_shakePos.x *= -1.f;
	if(Util::Probable(50U)) m_shakePos.y *= -1.f;*/


	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Shake), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Shake::cFX_Shake(cTexture* pTx, float size, DWORD delay)
	: cFX(pTx)
	, m_shakePos(0.f, 0.f)
	, m_size(size)
	, m_delay(delay)
	, m_prevShakeTime(0UL)
{
	/*m_shakePos.x = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;
	m_shakePos.y = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;

	if(Util::Probable(50U)) m_shakePos.x *= -1.f;
	if(Util::Probable(50U)) m_shakePos.y *= -1.f;*/


	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Shake), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Shake::~cFX_Shake()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Shake::OnUpdate()
{
	


	return 0;
}


int cFX_Shake::OnRender()
{
	if(m_pTx != nullptr)
	{
		cCore::Sprite.RenderTextureCenter(m_pTx,
			m_Pos + m_shakePos, m_Angle, m_Scale);
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Shake::Seq_Shake()
{
	if(timeGetTime() - m_prevShakeTime > m_delay)
	{
		m_size -= 1.f;


		if(m_pTx == nullptr)
		{
			m_shakePos *= -1.f;
			cCore::Camera2D.AddPos(&m_shakePos);
		}


		m_shakePos.x = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;
		m_shakePos.y = CAST(rand()%RAND_MAX, float) / CAST(RAND_MAX, float) * m_size;

		if(Util::Probable(50U)) m_shakePos.x *= -1.f;
		if(Util::Probable(50U)) m_shakePos.y *= -1.f;


		if(m_pTx == nullptr)
		{
			cCore::Camera2D.AddPos(&m_shakePos);
		}


		m_prevShakeTime = timeGetTime();
	}


	if(m_size <= 0.f)
		return FUNCRESULT_End;


	return 0;
}

