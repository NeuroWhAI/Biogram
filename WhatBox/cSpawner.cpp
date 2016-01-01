#include "cSpawner.h"

#include "cTexture.h"
#include "cParticle.h"

#include "cCore.h"







































cSpawner::cSpawner(DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count, cTexture* pTx)
	: m_color(color)
	, m_mass(mass)
	, m_pPartTx(pPartTx)
	, m_partLife(partLife)
	, m_delay(delay)
	, m_prevTime(timeGetTime())
	, m_count(count)
	, m_pTx(pTx)
{

}


cSpawner::~cSpawner()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cParticle* cSpawner::Update()
{
	//m_Pos += VFR(m_Speed);
	//m_Angle += VFR(m_AngleSpeed);

	//while(m_Angle >= 360.f) m_Angle -= 360.f;
	//while(m_Angle < 0.f) m_Angle += 360.f;


	OnUpdate();


	if(timeGetTime() - m_prevTime >= m_delay)
	{
		m_prevTime = timeGetTime();


		cParticle* pPart = OnCreate();


		if(pPart != nullptr)
		{
			pPart->SetPos(&m_Pos);
			pPart->SetSpeed(&m_Speed);
			pPart->SetAngle(m_Angle);
			pPart->SetAngleSpeed(m_AngleSpeed);


			if(m_count > 0) --m_count;
		}


		return pPart;
	}


	return nullptr;
}


int cSpawner::Render()
{
	if(m_pTx != nullptr)
	{
		cCore::Sprite.RenderTextureCenter(m_pTx, m_Pos, m_Angle, m_Scale);
	}


	return OnRender();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cSpawner::IsEnd() const
{
	return (m_count == 0  ||  m_count < -1);
}

