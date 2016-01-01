#include "c2DSoundList.h"

#include "c2DSound.h"




















c2DSoundList::c2DSoundList()
{

}


c2DSoundList::~c2DSoundList()
{
	Release();	
}

/*-----------------------------------------------------------------------------------*/

int c2DSoundList::AddSound(std::string SndFile)
{
	UINT Index = m_pSound.size();
	m_pSound.push_back(new c2DSound);

	m_pSound[Index]->LoadWave((LPSTR)SndFile.c_str());

	
	return Index;
}


int c2DSoundList::Release()
{
	for(UINT i=0; i<m_pSound.size(); i++)
	{
		m_pSound[i]->Release();
		delete m_pSound[i];
	}
	m_pSound.clear();


	return 0;
}

/*-----------------------------------------------------------------------------------*/

c2DSound* c2DSoundList::GetSound(UINT index)
{
	if(index >= m_pSound.size())
		return NULL;


	return m_pSound[index];
}


const c2DSound* c2DSoundList::GetSound(UINT index) const
{
	if(index >= m_pSound.size())
		return NULL;


	return m_pSound[index];
}

