#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ������
// Desc : �� ȿ��
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Laser : public cFX
{
public:
	cFX_Laser(DWORD color,
		const D3DXVECTOR2* dir,
		int count,
		float targetLength, float beginLength, float lengthSpeed,
		float targetSize, float beginSize, float sizeSpeed,
		float sizeAccelSpeed = 0.f, float lengthAccelSpeed = 0.f);
	cFX_Laser(cTexture* pTx, DWORD color,
		const D3DXVECTOR2* dir,
		int count,
		float targetLength, float beginLength, float lengthSpeed,
		float targetSize, float beginSize, float sizeSpeed,
		float sizeAccelSpeed = 0.f, float lengthAccelSpeed = 0.f);
	~cFX_Laser();


private:
	DWORD m_color;
	D3DXVECTOR2 m_dir;
	int m_count;
	float m_targetLength;
	float m_lengthSpeed;
	float m_targetSize;
	float m_sizeSpeed;
	float m_sizeAccelSpeed;
	float m_lengthAccelSpeed;


private:
	// m_Pos���� ����� ��ġ
	D3DXVECTOR2 m_currPos;

	// ���� ����
	float m_currSize;


private:
	virtual int OnUpdate();
	virtual int OnRender();


private:
	int Seq_IsEnd();
};

