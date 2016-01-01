#pragma once
#include "cUIControl.h"


class cTexture;






















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 버튼
// Desc : 버튼 인터페이스 구현
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTransformButton : public cUIControl
{
public:
	cTransformButton();
	cTransformButton(cTexture* pTx, const char text[]="");
	cTransformButton(cTexture* pTx, const wchar_t text[]);

	~cTransformButton();


private:
	enum STATE
	{
		STATE_Not,
		STATE_Focus,
		STATE_Down,
		STATE_Press,
		STATE_Up,
	};

	STATE m_currState;


private:
	cTexture* m_pTx;
	char* m_text;
	wchar_t* m_wText;
	D3DXVECTOR2 m_Size;

	D3DXVECTOR2 m_RealPos;


public:
	int SetTexture(cTexture* pTx);
	int SetText(const char text[]);
	int SetText(const wchar_t text[]);

	virtual int OnUpdate();
	virtual int OnRender();
	int RenderSmall();


public:
	bool ButtonFocus();
	bool ButtonDown();
	bool ButtonPress();
	bool ButtonUp();


public:
	int Reset();
};

