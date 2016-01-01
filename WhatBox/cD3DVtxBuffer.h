#pragma once
#include <d3dx9.h>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D정점버퍼
// Desc : D3D정점버퍼를 이용해 정점정보들을 저장하고 변경하는 인터페이스 제공.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DVtxBuffer
{
public:
	cD3DVtxBuffer();
	virtual ~cD3DVtxBuffer();


protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;		// 정점버퍼

	UINT m_nVtx;						// 정점 갯수
	UINT m_VtxSize;						// 정점 크기
	UINT m_SizeofBuffer;				// 정점버퍼 크기
	DWORD m_FVF;


public:
	int Create(UINT VtxSize, UINT VtxNum, DWORD FVF); // 정점크기, 정점갯수, FVF값
	int VtxCpy(void* pVtx);
	int Release();

	int SetStreamSource() const; // 그리기는 하지않고 파이프라인에 정점을 연결하기만 한다
	int SetFVF() const; // 그리기는 하지않고 FVF만 설정한다
	int SetVtxToDevice() const;		// 위의 두 작업만 한다.
	int Draw(D3DPRIMITIVETYPE PrimitiveType) const;


public:
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer();
	const LPDIRECT3DVERTEXBUFFER9 GetVtxBuffer() const;
};

