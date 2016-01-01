#pragma once
#include "cUIControl.h"


class cTextureList;






















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 버튼
// Desc : 버튼 인터페이스 구현
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cButton : public cUIControl
{
public:
	cButton(cTextureList* pTxList, const char Text[]);

	~cButton();


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
	cTextureList* m_pTxList;
	D3DXVECTOR2 m_Size;
	char m_Name[256];


public:
	virtual int OnUpdate();
	virtual int OnRender();


public:
	bool ButtonFocus();
	bool ButtonDown();
	bool ButtonPress();
	bool ButtonUp();
};

