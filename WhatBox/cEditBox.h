#pragma once
#include "cUIControl.h"
#include <string>

class cTextbox;




























class cEditBox : public cUIControl
{
public:
	cEditBox(DWORD Color = 0xff000000, bool isPassword = false);
	~cEditBox();


private:
	DWORD m_Color;
	bool m_bPassword;
	cTextbox* m_pTextBox;


private:
	DWORD m_PrevTime;
	bool m_bShowCursor;
	

private:
	D3DXVECTOR2& m_Size;


public:
	int Init(float XPos, float YPos, float Width, float Height);
	virtual int OnUpdate();
	virtual int OnRender();


public:
	bool IsActivate() const;
	int GetStr(std::wstring* pOut);
	UINT Length() const;
	int Clear();
};

