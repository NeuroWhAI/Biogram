#pragma once
#include <d3dx9.h>

class cD3DIdxBuffer;
class cD3DVtxBuffer;
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���
// Desc : ���� ũ��, ĭ ���� ������ ���� �����. Draw�Լ� ��/�Ŀ� ���� ������ �����μ� �پ��ϰ� ����� �� �ִ�.
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
		, bool isUp/*�������ִ��� ������ �ִ���*/, bool isCenter/*�Ʒ��� �߽��� ���ʳ����� �������*/);
	int Release();

	virtual int Draw();
	int DrawWireFrame();


protected:
	virtual int OnRelease();
};

