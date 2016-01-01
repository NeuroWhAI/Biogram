#pragma once
#include <d3dx9.h>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D��ġ
// Desc : D3D����̽��� �ʱ�ȭ�� �ı��� ����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DDevice
{
public:
	cD3DDevice();
	~cD3DDevice();


private:
	D3DPRESENT_PARAMETERS m_d3dpp;

	LPDIRECT3D9         m_pD3D;
	LPDIRECT3DDEVICE9   m_pd3dDevice;


public:
	int Create(bool bWindowed, bool bTransparent);
	int CleanUp();


private:
	int InitCore();


public:
	D3DPRESENT_PARAMETERS* pD3DPP();
	const D3DPRESENT_PARAMETERS* pD3DPP() const;
};

