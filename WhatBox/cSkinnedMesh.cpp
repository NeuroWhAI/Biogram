#include "cSkinnedMesh.h"

#include "cCore.h"

#include "LcXSkin/ILcMdl.h"





















cSkinnedMesh::cSkinnedMesh()
	: m_pMesh(NULL)
{
	
}


cSkinnedMesh::~cSkinnedMesh()
{
	CleanUp();
}

/*---------------------------------------------------------------------------------------------------*/

int cSkinnedMesh::LoadXFile(std::string XFile)
{
	char* XFileName = new char[XFile.size()+1];
	strcpy_s(XFileName, XFile.size()+1, XFile.c_str());


	if(FAILED(LcMdl_Create(NULL, &m_pMesh, cCore::pd3dDevice, XFileName)))
	{
		delete[] XFileName;
		return Util::ErrorMessage("LcMdl_Create()");
	}

	
	return 0;
}



int cSkinnedMesh::FrameMove()
{
	// Setup world matrix
	D3DXVECTOR3		vObjectCenter(0,0,0);
	FLOAT			fObjectRadius = 0;

	m_pMesh->GetAttrib(SknMeshNameSpace::ATTRIB_Center, &vObjectCenter);
	m_pMesh->GetAttrib(SknMeshNameSpace::ATTRIB_Radius, &fObjectRadius);


	return 0;
}


int cSkinnedMesh::Render()
{
	FLOAT fObjectRadius = 0;
	m_pMesh->GetAttrib(SknMeshNameSpace::ATTRIB_Radius, &fObjectRadius);


	return 0;
}



int cSkinnedMesh::Release()
{



	return 0;
}


int cSkinnedMesh::Restore()
{
	FLOAT fObjectRadius = 0.f;
	m_pMesh->GetAttrib(SknMeshNameSpace::ATTRIB_Radius, &fObjectRadius);


	return 0;
}



int cSkinnedMesh::CleanUp()
{
	SAFE_DELETE(m_pMesh);


	return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int cSkinnedMesh::CreateInstance(ILcMdl** pMeshIns)
{
	if(FAILED(LcMdl_Create(NULL, pMeshIns, cCore::pd3dDevice, NULL, m_pMesh)))
		return Util::ErrorMessage("LcMdl_Create()");


	return 0;
}

