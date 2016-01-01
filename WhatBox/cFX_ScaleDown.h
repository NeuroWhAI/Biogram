#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �����۾�����
// Desc : �̹����� ���� �۾����ٰ� �����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_ScaleDown : public cFX
{
public:
	cFX_ScaleDown(cTexture* pTx, float targetScale, float speed, float accelSpeed = 0.f);
	~cFX_ScaleDown();


private:
	float m_targetScale;
	float m_speed, m_accelSpeed;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_ScaleDown();
};

