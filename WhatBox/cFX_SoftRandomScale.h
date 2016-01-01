#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 은은한크기변환
// Desc : 이미지의 크기가 부드럽게 변함
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_SoftRandomScale : public cFX
{
public:
	/*
	# 은은한크기변환 효과
	* pTx : 텍스쳐를 설정합니다.
	* volatility : 크기의 변화율을 설정합니다.
	* speedFactor : 크기가 변하는 속도비율을 설정합니다.
	*/
	cFX_SoftRandomScale(cTexture* pTx, float volatility, float speedFactor);
	~cFX_SoftRandomScale();


private:
	float m_volatility;
	float m_speedFactor;


private:
	float m_currTargetScale;
	float m_currSpeed;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_ScaleDown();
	int Seq_ScaleUp();
};

