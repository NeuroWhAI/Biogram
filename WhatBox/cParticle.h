#pragma once
#include "c2DCoord.h"

class cTexture;






































class cParticle : public c2DCoord
{
public:
	cParticle(DWORD color = 0xffffffff, float mass = 1.f, cTexture* pTx = nullptr, float life = 128.f);
	virtual ~cParticle();


protected:
	cTexture* m_pTx;
	int m_maxAlpha;
	DWORD m_color;
	float m_mass;
	float m_maxLife;
	float m_fLife;


public:
	int Update();
	int Render();


protected:
	virtual int OnUpdate() = 0;
	virtual int OnRender() = 0;


public:
	int SetTexture(cTexture* pTx);
	int SetLife(float life);
	int SetMass(float mass);


public:
	float GetLife() const;
	float GetMass() const;
};

