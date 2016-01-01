#include "cForce_Gravity.h"

#include "cCore.h"

#include "cParticle.h"








































cForce_Gravity::cForce_Gravity(float mass,
						 std::vector<cParticle*>* pPartList, cTexture* pTx, float life, DWORD delay)
	: cForce(pPartList, pTx, life, delay)

	, m_mass(mass*mass)
{
	if(mass < 0.f) m_mass *= -1.f;
}


cForce_Gravity::~cForce_Gravity()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_Gravity::OnUpdate()
{



	return 0;
}


int cForce_Gravity::OnForce()
{
	for(UINT i=0; i<m_pPartList.size(); ++i)
	{
		cParticle* pPart = m_pPartList[i];


		float attraction = cCore::ShapeMath.GetAttractionPower(&m_Pos, m_mass, pPart->Pos(), pPart->GetMass());

		D3DXVECTOR2 vec;
		D3DXVec2Subtract(&vec, &m_Pos, pPart->Pos());
		D3DXVec2Normalize(&vec, &vec);
		vec *= VFR(attraction);

		pPart->AddSpeed(&vec);
	}


	return 0;
}


int cForce_Gravity::OnRender()
{
	


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cForce_Gravity::SetMass(float mass)
{
	m_mass = mass*mass;

	if(mass < 0.f) m_mass *= -1.f;


	return 0;
}


float cForce_Gravity::GetMass() const
{
	return sqrtf(fabsf(m_mass)) * ((m_mass < 0.f) ? -1.f : 1.f);
}

