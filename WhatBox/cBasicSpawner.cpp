#include "cBasicSpawner.h"

#include "cTexture.h"
#include "cParticle.h"
#include "cParticle_Basic.h"

#include "cCore.h"







































cBasicSpawner::cBasicSpawner(DWORD color, float mass, cTexture* pPartTx, float partLife, DWORD delay, int count, cTexture* pTx)
	: cSpawner(color, mass, pPartTx, partLife, delay, count, pTx)
{

}


cBasicSpawner::~cBasicSpawner()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBasicSpawner::OnUpdate()
{



	return 0;
}


cParticle* cBasicSpawner::OnCreate()
{
	cParticle* pPart = new cParticle_Basic(m_color, m_mass, m_pPartTx, m_partLife);


	return pPart;
}


int cBasicSpawner::OnRender()
{
	


	return 0;
}

