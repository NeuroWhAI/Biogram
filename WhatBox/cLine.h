#pragma once
#include <d3dx9.h>

class cD3DVtxBuffer;
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D��
// Desc : 3���� ������ �����ش�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cLine
{
public:
	cLine();
	~cLine();


private:
	typedef struct
	{
		D3DXVECTOR3 p;
		DWORD d;

		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
	} sVertex;


private:
	cD3DVtxBuffer* m_pVB;


public:
	int Create(D3DXVECTOR3 P1, D3DXVECTOR3 P2, DWORD Color);
	int Release();

	int Draw();
};

