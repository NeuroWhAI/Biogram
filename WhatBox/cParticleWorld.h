#pragma once
#include <d3dx9.h>
#include <vector>

class cTexture;

class cParticle;
class cSpawner;
class cForce;








































class cParticleWorld
{
public:
	cParticleWorld();
	~cParticleWorld();


private:
	std::vector<cParticle*> m_pPartList;


private:
	std::vector<cSpawner*> m_pSpawnerList;


private:
	std::vector<cForce*> m_pForceList;


public:
	int Update();
	int Render();


public:
	int AddParticle(cParticle* pParticle);
	int AddBasicParticle(const D3DXVECTOR2* pPos, const D3DXVECTOR2* pSpeed,
		DWORD color = 0xffffffff, float mass = 1.f, cTexture* pTx = nullptr, float life = 128.f);


public:
	int AddSpawner(cSpawner* pSpawner);
	int AddBasicSpawner(const D3DXVECTOR2* pPos, const D3DXVECTOR2* pSpeed,
		DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count = -1, cTexture* pTx = nullptr);


public:
	int AddForce(cForce* pForce);
	int AddWindForce(float maxSpeed, const D3DXVECTOR2* dir,
		float life = -99999.f, DWORD delay = 0);
	int AddAirResistForce(float resist,
		float life = -99999.f, DWORD delay = 0);
	int AddGravityForce(float mass,
		const D3DXVECTOR2* pPos,
		cTexture* pTx = nullptr, float life = -99999.f, DWORD delay = 0);
};

