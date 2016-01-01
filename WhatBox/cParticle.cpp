#include "cParticle.h"

#include "cCore.h"

#include "cTexture.h"








































cParticle::cParticle(DWORD color, float mass, cTexture* pTx, float life)
	: m_pTx(pTx)
	, m_maxAlpha((color & 0xff000000) >> 24)
	, m_color(color)
	, m_mass(mass)
	, m_maxLife(life)
	, m_fLife(life)
{

}


cParticle::~cParticle()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticle::Update()
{
	m_Pos += VFR(m_Speed);
	m_Angle += VFR(m_AngleSpeed);

	while(m_Angle >= 360.f) m_Angle -= 360.f;
	while(m_Angle < 0.f) m_Angle += 360.f;


	m_fLife -= cCore::FrameRate;


	DWORD a = (static_cast<DWORD>(m_fLife/m_maxLife*m_maxAlpha) << 24) & 0xff000000;
	m_color = m_color&0x00ffffff|a;


	return OnUpdate();
}


int cParticle::Render()
{
	


	return OnRender();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticle::SetTexture(cTexture* pTx)
{
	m_pTx = pTx;


	return 0;
}


int cParticle::SetLife(float life)
{
	m_fLife = life;
	m_maxLife = life;


	return 0;
}


int cParticle::SetMass(float mass)
{
	m_mass = mass;


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cParticle::GetLife() const
{
	return m_fLife;
}


float cParticle::GetMass() const
{
	return m_mass;
}

