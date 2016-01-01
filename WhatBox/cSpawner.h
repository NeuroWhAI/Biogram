#pragma once
#include "c2DCoord.h"

class cTexture;
class cParticle;






































class cSpawner : public c2DCoord
{
public:
	cSpawner(DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count = -1, cTexture* pTx = nullptr);
	virtual ~cSpawner();


protected:
	DWORD m_color;

	float m_mass;

	cTexture* m_pPartTx;
	float m_partLife;

	DWORD m_delay;
	DWORD m_prevTime;

	int m_count;

	cTexture* m_pTx;


public:
	cParticle* Update();
	int Render();


protected:
	virtual int OnUpdate() = 0;
	virtual cParticle* OnCreate() = 0;
	virtual int OnRender() = 0;


public:
	bool IsEnd() const;
};

