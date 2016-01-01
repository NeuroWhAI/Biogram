#include "cMeshList.h"

#include "cMesh.h"




















cMeshList::cMeshList()
{

}


cMeshList::~cMeshList()
{
	CleanUp();	
}

/*-----------------------------------------------------------------------------------*/

UINT cMeshList::AddMesh(std::string XFile)
{
	UINT Index = m_pMsh.size();
	m_pMsh.push_back(new cMesh);

	m_pMsh[Index]->LoadXFile(XFile);


	return Index;
}


UINT cMeshList::AddMesh(cMesh* pMsh)
{
	UINT Index = m_pMsh.size();
	m_pMsh.push_back(pMsh);


	return Index;
}



int cMeshList::Release()
{// 화면복구용이므로 delete, clear는 하지않음
	for(UINT i=0; i<m_pMsh.size(); i++)
	{
		m_pMsh[i]->Release();
	}


	return 0;
}


int cMeshList::Restore()
{
	for(UINT i=0; i<m_pMsh.size(); i++)
	{
		m_pMsh[i]->Restore();
	}


	return 0;
}



int cMeshList::CleanUp()
{
	for(UINT i=0; i<m_pMsh.size(); i++)
	{
		m_pMsh[i]->Release();
		delete m_pMsh[i];
	}
	m_pMsh.clear();


	return 0;
}

/*-----------------------------------------------------------------------------------*/

cMesh* cMeshList::GetMesh(UINT index)
{
	if(index >= m_pMsh.size())
		return NULL;


	return m_pMsh[index];
}


const cMesh* cMeshList::GetMesh(UINT index) const
{
	if(index >= m_pMsh.size())
		return NULL;


	return m_pMsh[index];
}

