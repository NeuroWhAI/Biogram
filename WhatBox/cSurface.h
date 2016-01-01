#pragma once
#include <d3dx9.h>

class cD3DIdxBuffer;
class cD3DVtxBuffer;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���
// Desc : x, y����� �����. Draw�Լ� ��/�Ŀ� ���� ������ �����μ� �پ��ϰ� ����� �� �ִ�.
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

