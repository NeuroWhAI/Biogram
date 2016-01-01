#pragma once
#include "cFX.h"

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ������ũ�⺯ȯ
// Desc : �̹����� ũ�Ⱑ �ε巴�� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_SoftRandomScale : public cFX
{
public:
	/*
	# ������ũ�⺯ȯ ȿ��
	* pTx : �ؽ��ĸ� �����մϴ�.
	* volatility : ũ���� ��ȭ���� �����մϴ�.
	* speedFactor : ũ�Ⱑ ���ϴ� �ӵ������� �����մϴ�.
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

