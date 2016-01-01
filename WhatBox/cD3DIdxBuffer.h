#pragma once
#include <d3dx9.h>


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D인덱스버퍼
// Desc : D3D인덱스를 이용해 인덱스정보를 저장하고 변경하는 인터페이스 제공.
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
	int Create(UINT nPrimitive/*삼각형갯수*/);
	int IdxCpy(void *pWordIdx);
	int Release();

	int SetIndices() const;
	int DrawIndexedPrimitive() const;
	int Draw() const;


public:
	LPDIRECT3DINDEXBUFFER9 GetIdxBuffer();
	const LPDIRECT3DINDEXBUFFER9 GetIdxBuffer() const;
};

