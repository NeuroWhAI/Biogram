#include "cForce.h"

#include "cCore.h"

#include "cTexture.h"
#include "cParticle.h"






































cForce::cForce(std::vector<cParticle*>* pPartList, cTexture* pTx, float life, DWORD delay)
	: m_pPartList(*pPartList)
	, m_life(life)
	, m_delay(delay)
	, m_pTx(pTx)

	, m_prevTime(timeGetTime())
{

}


cForce::~cForce()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce::Update()
{
	m_Pos += VFR(m_Speed);
	m_Angle += VFR(m_AngleSpeed);

	while(m_Angle >= 360.f) m_Angle -= 360.f;
	while(m_Angle < 0.f) m_Angle += 360.f;


	if(m_life > -99.f)
	{
		m_life -= cCore::FrameRate;

		if(m_life < -99.f) m_life = -99.f;
	}


	OnUpdate();


	if(timeGetTime() - m_prevTime >= m_delay)
	{
		m_prevTime = timeGetTime();


		OnForce();
	}


	return 0;
}


int cForce::Render()
{
	if(m_pTx != nullptr)
	{
		cCore::Sprite.RenderTextureCenter(m_pTx, m_Pos, m_Angle, m_Scale);
	}


	return OnRender();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cForce::IsEnd() const
{
	return (m_life > -9999.f  &&  m_life <= 0.f);
}

