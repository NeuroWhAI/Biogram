#pragma once
#include <d3dx9.h>

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �Ϲݱ���
// Desc : ��ġ�� ���������� ������ �����Ѵ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cRSLight
{
public:
	cRSLight(D3DLIGHTTYPE LightType, D3DXVECTOR3 Vec, D3DXCOLOR Color
		, D3DXVECTOR3 Pos = D3DXVECTOR3(0,0,0)/*�������� ����*/);
	cRSLight(D3DLIGHT9 Light);
	~cRSLight();


private:
	static int s_Number;
	int m_Number;


private:
	D3DXVECTOR3 m_Vec;
	D3DLIGHT9 m_Light;


public:
	int On();
	int Off();


public:
	static void ResetNum(); // s_Number �ʱ�ȭ
};

