#include "cForce_Wind.h"

#include "cCore.h"

#include "cParticle.h"








































cForce_Wind::cForce_Wind(float maxSpeed, const D3DXVECTOR2* dir,
						 std::vector<cParticle*>* pPartList, float life, DWORD delay)
	: cForce(pPartList, nullptr, life, delay)

	, m_maxSpeedSq(maxSpeed*maxSpeed)
	, m_force(*dir)
{

}


cForce_Wind::~cForce_Wind()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_Wind::OnUpdate()
{



	return 0;
}


int cForce_Wind::OnForce()
{
	D3DXVECTOR2 wind = VFR(m_force);


	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		cParticle* pPart = m_pPartList[i];


		float speedSq = D3DXVec2LengthSq(pPart->Speed());

		if(speedSq < m_maxSpeedSq)
		{
			pPart->AddSpeed(&wind);	
		}
	}


	return 0;
}


int cForce_Wind::OnRender()
{
	


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_Wind::SetMaxSpeed(float speed)
{
	m_maxSpeedSq = speed*speed;


	return 0;
}


float cForce_Wind::GetMaxSpeed() const
{
	return sqrtf(m_maxSpeedSq);
}

/*------------------------------------------------------------------------------------------------------------*/

int cForce_Wind::SetForce(const D3DXVECTOR2* force)
{
	m_force = *force;


	return 0;
}


const D3DXVECTOR2* cForce_Wind::GetForce() const
{
	return &m_force;
}

