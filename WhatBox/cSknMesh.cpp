#include "cSknMesh.h"

#include "cSkinnedMesh.h"
#include "LcXSkin/ILcMdl.h"

#include "cCore.h"
#include "Util.h"





















cSknMesh::cSknMesh()
	: m_pMeshIns(NULL)
{

}


cSknMesh::cSknMesh(cSkinnedMesh* pMeshOrg)
	: m_pMeshIns(NULL)
{
	Create(pMeshOrg);
}


cSknMesh::~cSknMesh()
{
	CleanUp();
}

/*---------------------------------------------------------------------------------------------------*/

int cSknMesh::Create(cSkinnedMesh* pMeshOrg)
{
	SAFE_DELETE(m_pMeshIns);
	return pMeshOrg->CreateInstance(&m_pMeshIns);
}


int cSknMesh::Render(INT AniNum)
{
	D3DXMATRIX matWorld = *Matrix();
#ifdef USE_VFR
	float fElapsedTime = cCore::ElapsedTime;
#else
	float fElapsedTime = 0.016f;
#endif
	
	m_pMeshIns->SetAttrib(SknMeshNameSpace::ATTRIB_Ani, &AniNum);	

	m_pMeshIns->SetAttrib(SknMeshNameSpace::ATTRIB_Matrix, &matWorld);
	m_pMeshIns->SetAttrib(SknMeshNameSpace::ATTRIB_ElapsedTime, &fElapsedTime);
	m_pMeshIns->Render();


	//DOUBLE Time = 0.;
	//m_pMeshIns->GetAttrib(SknMeshNameSpace::ATTRIB_CurrentTime, &Time);
	//Util::Log("%lf", Time);


	Util::SetIdentityMatrix();
	return 0;
}



/*int cSknMesh::Release()
{



	return 0;
}


int cSknMesh::Restore()
{
	


	return 0;
}*/



int cSknMesh::CleanUp()
{
	SAFE_DELETE(m_pMeshIns);


	return 0;
}

