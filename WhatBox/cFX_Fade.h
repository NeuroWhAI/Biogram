#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���̵���/�ƿ�
// Desc : ������ �������� �ؽ��� �Ǵ� ȭ����ü�� ���̵���
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Fade : public cFX
{
public:
	// speed : ������ ���̵��� ����� ���̵� �ƿ�
	cFX_Fade(DWORD color, float speed, float accelSpeed = 0.f);
	// speed : ������ ���̵��� ����� ���̵� �ƿ�
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

