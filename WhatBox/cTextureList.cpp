#include "cTextureList.h"

#include "cTexture.h"




















cTextureList::cTextureList()
{

}


cTextureList::~cTextureList()
{
	Release();	
}

/*-----------------------------------------------------------------------------------*/

UINT cTextureList::AddTexture(std::string TxFile)
{
	UINT Index = m_pTx.size();
	m_pTx.push_back(new cTexture);

	m_pTx[Index]->LoadTexture(TxFile);


	return Index;
}


UINT cTextureList::AddTexture(cTexture* pTx)
{
	UINT Index = m_pTx.size();
	m_pTx.push_back(pTx);


	return Index;
}


UINT cTextureList::AddTexture(LPDIRECT3DTEXTURE9 pTx)
{
	UINT Index = m_pTx.size();
	m_pTx.push_back(new cTexture);

	m_pTx[Index]->SetTexture(pTx);


	return Index;
}


int cTextureList::Release()
{
	for(UINT i=0; i<m_pTx.size(); i++)
	{
		m_pTx[i]->Release();
		delete m_pTx[i];
	}
	m_pTx.clear();


	return 0;
}

/*-----------------------------------------------------------------------------------*/

cTexture* cTextureList::GetTexture(UINT index)
{
	if(index >= m_pTx.size())
		return NULL;


	return m_pTx[index];
}


const cTexture* cTextureList::GetTexture(UINT index) const
{
	if(index >= m_pTx.size())
		return NULL;


	return m_pTx[index];
}


UINT cTextureList::GetSize() const
{
	return m_pTx.size();
}

/*-----------------------------------------------------------------------------------*/

cTexture* cTextureList::operator[] (int idx)
{
	if(static_cast<unsigned int>(idx) < m_pTx.size())
		return m_pTx[idx];


	return nullptr;
}


cTexture* cTextureList::operator[] (unsigned int idx)
{
	if(idx < m_pTx.size())
		return m_pTx[idx];


	return nullptr;
}


const cTexture* cTextureList::operator[] (int idx) const
{
	if(static_cast<unsigned int>(idx) < m_pTx.size())
		return m_pTx[idx];


	return nullptr;
}


const cTexture* cTextureList::operator[] (unsigned int idx) const
{
	if(idx < m_pTx.size())
		return m_pTx[idx];


	return nullptr;
}

