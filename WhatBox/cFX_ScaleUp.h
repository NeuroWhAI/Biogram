#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 점점커지게
// Desc : 이미지가 점점 커지다가 사라짐
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_ScaleUp : public cFX
{
public:
	cFX_ScaleUp(cTexture* pTx, float targetScale, float speed, float accelSpeed = 0.f);
	~cFX_ScaleUp();


private:
	float m_targetScale;
	float m_speed, m_accelSpeed;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_ScaleUp();
};

