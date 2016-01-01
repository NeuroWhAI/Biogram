#pragma once
#include "cParticle.h"







































class cParticle_Basic : public cParticle
{
public:
	cParticle_Basic(DWORD color = 0xffffffff, float mass = 1.f, cTexture* pTx = nullptr, float life = 128.f);
	~cParticle_Basic();


private:
	virtual int OnUpdate() override;
	virtual int OnRender() override;
};

