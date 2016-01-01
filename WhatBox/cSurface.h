#pragma once
#include <d3dx9.h>

class cD3DIdxBuffer;
class cD3DVtxBuffer;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 평면
// Desc : x, y평면을 만든다. Draw함수 전/후에 여러 설정을 함으로서 다양하게 사용할 수 있다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSurface
{
public:
	cSurface();
	~cSurface();


private:
	typedef struct
	{
		D3DXVECTOR3 p;
		DWORD d;
		FLOAT u,v;

		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1};
	} sVertex;


private:
	cD3DIdxBuffer* m_pIdxBuffer;
	cD3DVtxBuffer* m_pVtxBuffer;


public:
	int Create(float Width, float Height);
	int Draw();
};

