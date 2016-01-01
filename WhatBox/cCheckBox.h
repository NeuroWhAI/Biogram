#pragma once
#include "cUIControl.h"
#include <string>



























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 선택상자
// Desc : 논리선택 인터페이스
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cCheckBox : public cUIControl
{
public:
	cCheckBox(bool bChecked = false, std::wstring text = L"", DWORD color = 0xffffffff);
	~cCheckBox();


private:
	bool m_bChecked;
	std::wstring m_text;

	
private:
	DWORD m_color;


public:
	virtual int OnUpdate();
	virtual int OnRender();


public:
	bool IsChecked() const;
	void SetChecked(bool bChecked);

	std::wstring GetText() const;
	void SetText(std::wstring text);

	DWORD GetColor() const;
	void SetColor(DWORD color);
};

