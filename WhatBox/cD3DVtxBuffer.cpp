#include "cD3DVtxBuffer.h"

#include "cCore.h"




















cD3DVtxBuffer::cD3DVtxBuffer()
	: m_pVB(NULL)
	, m_nVtx(0U)
	, m_VtxSize(0U)
	, m_SizeofBuffer(0U)
{

}


cD3DVtxBuffer::~cD3DVtxBuffer()
{
	Release();
}

/*--------------------------------------------------------------------------------------*/

int cD3DVtxBuffer::Create(UINT VtxSize, UINT VtxNum, DWORD FVF)
{
	m_nVtx = VtxNum;
	m_VtxSize = VtxSize;
	m_FVF = FVF;

	// ������ ���� ũ��
	m_SizeofBuffer = VtxSize*VtxNum;

	// �������� ����
	if(FAILED(cCore::pd3dDevice->CreateVertexBuffer(m_SizeofBuffer, 0, FVF
		, D3DPOOL_MANAGED, &m_pVB, 0)))
		return Util::ErrorMessage("CreateVertexBuffer()"); // ���н�


	return 0;
}


int cD3DVtxBuffer::VtxCpy(void* pVtx)
{
	void* pVtxBuffer = NULL; // ���� ���� �ּ�

	// ���� �ּ� ���
	if(FAILED(m_pVB->Lock(0, m_SizeofBuffer, &pVtxBuffer, 0)))
		return Util::ErrorMessage("Lock()");

	// ���ۿ� �� �����
	memcpy(pVtxBuffer, pVtx, m_SizeofBuffer);

	m_pVB->Unlock();


	return 0;
}


int cD3DVtxBuffer::Release()
{
	SAFE_RELEASE(m_pVB);


	return 0;
}


int cD3DVtxBuffer::SetStreamSource() const
{
	cCore::pd3dDevice->SetStreamSource( 0, m_pVB, 0, m_VtxSize ); 


	return 0;
}


int cD3DVtxBuffer::SetFVF() const
{
	cCore::pd3dDevice->SetFVF( m_FVF ); 


	return 0;
}


int cD3DVtxBuffer::SetVtxToDevice() const
{
	// ����̽��� ��Ʈ�� ����
	cCore::pd3dDevice->SetStreamSource( 0, m_pVB, 0, m_VtxSize ); 

	// FVF �˸�
	cCore::pd3dDevice->SetFVF( m_FVF ); 


	return 0;
}


int cD3DVtxBuffer::Draw(D3DPRIMITIVETYPE PrimitiveType) const
{
	// ����̽��� ��Ʈ�� ����
	cCore::pd3dDevice->SetStreamSource( 0, m_pVB, 0, m_VtxSize ); 

	// FVF �˸�
	cCore::pd3dDevice->SetFVF( m_FVF ); 

	// ������Ƽ�� ���� ���ް� ������ ���
	cCore::pd3dDevice->DrawPrimitive( PrimitiveType, 0, m_nVtx ); 


	return 0;
}

/*--------------------------------------------------------------------------------------*/

LPDIRECT3DVERTEXBUFFER9 cD3DVtxBuffer::GetVtxBuffer()
{
	return m_pVB;
}


const LPDIRECT3DVERTEXBUFFER9 cD3DVtxBuffer::GetVtxBuffer() const
{
	return m_pVB;
}

