#pragma once
#include "cSpawner.h"

class cTexture;
class cParticle;






































class cBasicSpawner : public cSpawner
{
public:
	cBasicSpawner(DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count = -1, cTexture* pTx = nullptr);
	~cBasicSpawner();


private:
	virtual int OnUpdate() override;
	virtual cParticle* OnCreate() override;
	virtual int OnRender() override;
};

