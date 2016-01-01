#pragma once
#include <d3dx9.h>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D��������
// Desc : D3D�������۸� �̿��� ������������ �����ϰ� �����ϴ� �������̽� ����.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DVtxBuffer
{
public:
	cD3DVtxBuffer();
	virtual ~cD3DVtxBuffer();


protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;		// ��������

	UINT m_nVtx;						// ���� ����
	UINT m_VtxSize;						// ���� ũ��
	UINT m_SizeofBuffer;				// �������� ũ��
	DWORD m_FVF;


public:
	int Create(UINT VtxSize, UINT VtxNum, DWORD FVF); // ����ũ��, ��������, FVF��
	int VtxCpy(void* pVtx);
	int Release();

	int SetStreamSource() const; // �׸���� �����ʰ� ���������ο� ������ �����ϱ⸸ �Ѵ�
	int SetFVF() const; // �׸���� �����ʰ� FVF�� �����Ѵ�
	int SetVtxToDevice() const;		// ���� �� �۾��� �Ѵ�.
	int Draw(D3DPRIMITIVETYPE PrimitiveType) const;


public:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer();
	const LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer() const;
};

