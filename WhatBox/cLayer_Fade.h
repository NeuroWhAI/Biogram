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
	// Speed : 0에서 255까지 가는데 16ms마다 몇씩 증가하나
	int FadeOut(float Speed, DWORD color);

	// Speed : 255에서 0까지 가는데 16ms마다 몇씩 감소하나
	int FadeIn(float Speed, DWORD color);

	bool IsEnd() const;
};

