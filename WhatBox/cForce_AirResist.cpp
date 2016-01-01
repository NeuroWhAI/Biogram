#include "cForce_AirResist.h"

#include "cCore.h"

#include "cParticle.h"








































cForce_AirResist::cForce_AirResist(float resist,
						 std::vector<cParticle*>* pPartList, float life, DWORD delay)
	: cForce(pPartList, nullptr, life, delay)

	, m_resist(resist)
{

}


cForce_AirResist::~cForce_AirResist()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_AirResist::OnUpdate()
{



	return 0;
}


int cForce_AirResist::OnForce()
{
	float resist = VFR(m_resist);


	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		cParticle* pPart = m_pPartList[i];


		if(D3DXVec2LengthSq(pPart->Speed()) < resist*resist)
		{
			pPart->SetSpeed(0.f, 0.f);
		}
		else
		{
			D3DXVECTOR2 breakVec;
			D3DXVec2Normalize(&breakVec, pPart->Speed());

			breakVec *= -resist;

			pPart->AddSpeed(&breakVec);
		}
	}


	return 0;
}


int cForce_AirResist::OnRender()
{
	


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_AirResist::SetResist(float resist)
{
	m_resist = resist;


	return 0;
}


float cForce_AirResist::GetResist() const
{
	return m_resist;
}

