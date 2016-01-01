#include "cSknMeshList.h"

#include "cSkinnedMesh.h"




















cSknMeshList::cSknMeshList()
{

}


cSknMeshList::~cSknMeshList()
{
	Release();	
}

/*-----------------------------------------------------------------------------------*/

UINT cSknMeshList::AddSknMesh(std::string XFile)
{
	UINT Index = m_pSknMesh.size();
	m_pSknMesh.push_back(new cSkinnedMesh);

	m_pSknMesh[Index]->LoadXFile(XFile);


	return Index;
}


UINT cSknMeshList::AddSknMesh(cSkinnedMesh* pSknMesh)
{
	UINT Index = m_pSknMesh.size();
	m_pSknMesh.push_back(pSknMesh);


	return Index;
}


int cSknMeshList::Release()
{



	return 0;
}


int cSknMeshList::Restore()
{
	


	return 0;
}



int cSknMeshList::CleanUp()
{
	for(UINT i=0; i<m_pSknMesh.size(); i++)
	{
		m_pSknMesh[i]->Release();
		delete m_pSknMesh[i];
	}
	m_pSknMesh.clear();


	return 0;
}



int cSknMeshList::FrameMove()
{
	for(UINT i=0; i<m_pSknMesh.size(); i++)
	{
		m_pSknMesh[i]->FrameMove();
	}


	return 0;
}

/*-----------------------------------------------------------------------------------*/

cSkinnedMesh* cSknMeshList::GetSknMesh(UINT index)
{
	if(index >= m_pSknMesh.size())
		return NULL;


	return m_pSknMesh[index];
}


const cSkinnedMesh* cSknMeshList::GetSknMesh(UINT index) const
{
	if(index >= m_pSknMesh.size())
		return NULL;


	return m_pSknMesh[index];
}

