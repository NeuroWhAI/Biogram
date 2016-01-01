#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 페이드인/아웃
// Desc : 지정한 색상으로 텍스쳐 또는 화면전체를 페이드함
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Fade : public cFX
{
public:
	// speed : 음수면 페이드인 양수면 페이드 아웃
	cFX_Fade(DWORD color, float speed, float accelSpeed = 0.f);
	// speed : 음수면 페이드인 양수면 페이드 아웃
	cFX_Fade(cTexture* pTx, DWORD color, float speed, float accelSpeed = 0.f);
	~cFX_Fade();


private:
	DWORD m_color;
	float m_speed;
	float m_accelSpeed;


private:
	float m_currAlpha;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_FadeOut();
	int Seq_FadeIn();
};

