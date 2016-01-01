#pragma once
#include "cLayer.h"

class cFade;


























class cLayer_Fade : public cLayer
{
public:
	cLayer_Fade();
	~cLayer_Fade();


private:
	cFade* m_pFade;
	DWORD m_color;
	bool m_bWaitOnce;


private:
	virtual int OnInit();
	virtual int OnDestory();

	virtual int OnUpdate();
	virtual int OnRender();


public:
	// Speed : 0���� 255���� ���µ� 16ms���� � �����ϳ�
	int FadeOut(float Speed, DWORD color);

	// Speed : 255���� 0���� ���µ� 16ms���� � �����ϳ�
	int FadeIn(float Speed, DWORD color);

	bool IsEnd() const;
};

