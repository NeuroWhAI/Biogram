#include "cParticleWorld.h"

#include "cCore.h"

#include "cTexture.h"

#include "cParticle.h" //---- 파티클 ----*
#include "cParticle_Basic.h"
/*-----------------------------------------*/

#include "cSpawner.h" //---- 생성기 ----*
#include "cBasicSpawner.h"
/*-----------------------------------------*/

#include "cForce.h" //------ 힘 ------*
#include "cForce_Wind.h"
#include "cForce_AirResist.h"
#include "cForce_Gravity.h"
/*-----------------------------------------*/








































cParticleWorld::cParticleWorld()
{

}


cParticleWorld::~cParticleWorld()
{
	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		SAFE_DELETE(m_pPartList[i]);
	}

	for(UINT i=0; i<m_pSpawnerList.size(); ++i)
	{
		SAFE_DELETE(m_pSpawnerList[i]);
	}

	for(UINT i=0; i<m_pForceList.size(); ++i)
	{
		SAFE_DELETE(m_pForceList[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticleWorld::Update()
{
	for(UINT i=0; i<m_pSpawnerList.size(); ++i)
	{
		cParticle* pPart = m_pSpawnerList[i]->Update();

		if(pPart != nullptr)
		{
			m_pPartList.emplace_back(pPart);
		}

		if(m_pSpawnerList[i]->IsEnd())
		{
			delete m_pSpawnerList[i];
			m_pSpawnerList.erase(m_pSpawnerList.begin() + i);
			--i;

			continue;
		}
	}


	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		m_pPartList[i]->Update();

		if(m_pPartList[i]->GetLife() <= 0.f)
		{
			delete m_pPartList[i];
			m_pPartList.erase(m_pPartList.begin() + i);
			--i;

			continue;
		}
	}


	for(UINT i=0; i<m_pForceList.size(); ++i)
	{
		m_pForceList[i]->Update();

		if(m_pForceList[i]->IsEnd())
		{
			delete m_pForceList[i];
			m_pForceList.erase(m_pForceList.begin() + i);
			--i;

			continue;
		}
	}


	return 0;
}


int cParticleWorld::Render()
{
	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		m_pPartList[i]->Render();
	}


	for(UINT i=0; i<m_pSpawnerList.size(); ++i)
	{
		m_pSpawnerList[i]->Render();
	}


	for(UINT i=0; i<m_pForceList.size(); ++i)
	{
		m_pForceList[i]->Render();
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticleWorld::AddParticle(cParticle* pParticle)
{
	if(pParticle == nullptr) return -1;


	m_pPartList.emplace_back(pParticle);


	return 0;
}


int cParticleWorld::AddBasicParticle(const D3DXVECTOR2* pPos, const D3DXVECTOR2* pSpeed,
									 DWORD color, float mass, cTexture* pTx, float life)
{
	cParticle_Basic* pPart = new cParticle_Basic(color, mass, pTx, life);
	pPart->SetPos(pPos);
	pPart->SetSpeed(pSpeed);


	m_pPartList.emplace_back(pPart);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticleWorld::AddSpawner(cSpawner* pSpawner)
{
	if(pSpawner == nullptr) return -1;


	m_pSpawnerList.emplace_back(pSpawner);


	return 0;
}


int cParticleWorld::AddBasicSpawner(const D3DXVECTOR2* pPos, const D3DXVECTOR2* pSpeed,
									DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count, cTexture* pTx)
{
	cBasicSpawner* pSpawner = new cBasicSpawner(color, mass, pPartTx,  partLife, delay, count, pTx);
	pSpawner->SetPos(pPos);
	pSpawner->SetSpeed(pSpeed);


	m_pSpawnerList.emplace_back(pSpawner);


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticleWorld::AddForce(cForce* pForce)
{
	if(pForce == nullptr) return -1;


	m_pForceList.emplace_back(pForce);


	return 0;
}


int cParticleWorld::AddWindForce(float maxSpeed, const D3DXVECTOR2* dir,
								 float life, DWORD delay)
{
	cForce_Wind* pForce = new cForce_Wind(maxSpeed, dir,
		&m_pPartList, life, delay);


	m_pForceList.emplace_back(pForce);


	return 0;
}


int cParticleWorld::AddAirResistForce(float resist,
									  float life, DWORD delay)
{
	cForce_AirResist* pForce = new cForce_AirResist(resist,
		&m_pPartList, life, delay);


	m_pForceList.emplace_back(pForce);


	return 0;
}


int cParticleWorld::AddGravityForce(float mass,
									const D3DXVECTOR2* pPos,
									cTexture* pTx, float life, DWORD delay)
{
	cForce_Gravity* pForce = new cForce_Gravity(mass,
		&m_pPartList, pTx, life, delay);
	pForce->SetPos(pPos);


	m_pForceList.emplace_back(pForce);


	return 0;
}

