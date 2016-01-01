#include "cD3DIdxBuffer.h"

#include "cCore.h"





















cD3DIdxBuffer::cD3DIdxBuffer()
	: m_pIB(NULL)
	, m_BufferSize(0U)
	, m_nPrimitive(0U)
{

}


cD3DIdxBuffer::~cD3DIdxBuffer()
{
	Release();
}

/*--------------------------------------------------------------------------------------*/

int cD3DIdxBuffer::Create(UINT nPrimitive)
{
	m_nPrimitive = nPrimitive;
	m_BufferSize = (3*sizeof(WORD))*nPrimitive;

	if(FAILED(cCore::pd3dDevice->CreateIndexBuffer(m_BufferSize, 0 , D3DFMT_INDEX16 
		, D3DPOOL_MANAGED, &m_pIB, 0)))
		return Util::ErrorMessage("CreateIndexBuffer()");


	return 0;
}


int cD3DIdxBuffer::IdxCpy(void *pWordIdx)
{
	WORD* pIndices; 

	if( FAILED( m_pIB->Lock( 0, 0, (void**)&pIndices, 0 ) ) ) 
		return Util::ErrorMessage("Lock()");

	memcpy( pIndices, pWordIdx, m_BufferSize ); // 복사

	m_pIB->Unlock(); 

	return 0;
}


int cD3DIdxBuffer::Release()
{
	SAFE_RELEASE(m_pIB);


	return 0;
}


int cD3DIdxBuffer::SetIndices() const
{
	cCore::pd3dDevice->SetIndices(m_pIB);


	return 0;
}


int cD3DIdxBuffer::DrawIndexedPrimitive() const
{
	cCore::pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST 
		, 0 // Base Vertex Index 
		, 0 // Minimum vertex Index 
		, 2+m_nPrimitive // number of vertices 
		, 0 // Start Index 
		, m_nPrimitive // number of primitives 
		); 


	return 0;
}


int cD3DIdxBuffer::Draw() const
{
	// 인덱스 버퍼를 파이프라인에 연결
	cCore::pd3dDevice->SetIndices(m_pIB);

	// 렌더
	cCore::pd3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST 
		, 0 // Base Vertex Index 
		, 0 // Minimum vertex Index 
		, 2+m_nPrimitive // number of vertices 
		, 0 // Start Index 
		, m_nPrimitive // number of primitives 
		); 


	return 0;
}

/*--------------------------------------------------------------------------------------*/

LPDIRECT3DINDEXBUFFER9 cD3DIdxBuffer::GetIdxBuffer()
{
	return m_pIB;
}


const LPDIRECT3DINDEXBUFFER9 cD3DIdxBuffer::GetIdxBuffer() const
{
	return m_pIB;
}

