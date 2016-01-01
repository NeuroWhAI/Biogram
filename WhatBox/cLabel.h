#pragma once
#include "cUIControl.h"

class cFont;























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 라벨
// Desc : 인터페이스 텍스트 출력
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cLabel : public cUIControl
{
public:
	cLabel();
	cLabel(const char str[]);
	cLabel(const char str[], cFont* pFont);
	cLabel(const char str[], cFont* pFont, DWORD Color, DWORD Dt);

	~cLabel();


private:
	cFont* m_pFont;
	char* m_pStr;
	DWORD m_Color;
	DWORD m_Dt;


public:
	virtual int OnUpdate();
	virtual int OnRender();


public:
	int SetFont(cFont* pFont);
	int SetText(const char str[]);
	int SetColor(DWORD Color);
	int SetDt(DWORD Dt);

	cFont* GetFont();
	void GetText(char pOut[]) const;
	DWORD GetColor() const;
	DWORD GetDt() const;
};

