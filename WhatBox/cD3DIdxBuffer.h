#pragma once
#include <d3dx9.h>


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D�ε�������
// Desc : D3D�ε����� �̿��� �ε��������� �����ϰ� �����ϴ� �������̽� ����.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DIdxBuffer
{
public:
	cD3DIdxBuffer();
	virtual ~cD3DIdxBuffer();


protected:
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	UINT m_BufferSize;
	UINT m_nPrimitive;


public:
	int Create(UINT nPrimitive/*�ﰢ������*/);
	int IdxCpy(void *pWordIdx);
	int Release();

	int SetIndices() const;
	int DrawIndexedPrimitive() const;
	int Draw() const;


public:
	LPDIRECT3DINDEXBUFFER9 GetIdxBuffer();
	const LPDIRECT3DINDEXBUFFER9 GetIdxBuffer() const;
};

