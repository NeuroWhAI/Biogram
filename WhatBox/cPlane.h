#pragma once
#include <d3dx9.h>

class cD3DIdxBuffer;
class cD3DVtxBuffer;
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 평면
// Desc : 정한 크기, 칸 수로 평평한 면을 만든다. Draw함수 전/후에 여러 설정을 함으로서 다양하게 사용할 수 있다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cPlane
{
public:
	cPlane();
	virtual ~cPlane();


private:
	typedef struct
	{
		D3DXVECTOR3 p;
		DWORD d;
		FLOAT u,v;

		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1};
	} sVertex;


protected:
	cD3DIdxBuffer* m_pIdxBuffer;
	cD3DVtxBuffer* m_pVtxBuffer;


public:
	virtual int Create(float X, float Z, float Width, float Height, int nWidth, int nHeight
		, bool isUp/*세워져있는지 누워져 있는지*/, bool isCenter/*아랫면 중심이 왼쪽끝인지 가운데인지*/);
	int Release();

	virtual int Draw();
	int DrawWireFrame();


protected:
	virtual int OnRelease();
};

