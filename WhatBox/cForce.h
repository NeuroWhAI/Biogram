#pragma once
#include "c2DCoord.h"
#include <vector>

class cParticle;
class cTexture;







































class cForce : public c2DCoord
{
public:
	cForce(std::vector<cParticle*>* pPartList, cTexture* pTx = nullptr, float life = -99999.f, DWORD delay = 0);
	virtual ~cForce();


protected:
	std::vector<cParticle*>& m_pPartList;
	float m_life;
	DWORD m_delay;
	cTexture* m_pTx;


private:
	DWORD m_prevTime;
	

public:
	int Update();
	int Render();


protected:
	virtual int OnUpdate() = 0;
	virtual int OnForce() = 0;
	virtual int OnRender() = 0;


public:
	bool IsEnd() const;
};

