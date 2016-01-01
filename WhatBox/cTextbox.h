#pragma once
#include <Windows.h>
#include <string>



















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 텍스트박스
// Desc : 키보드로부터 문자입력을 받는다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTextbox
{
public:
	cTextbox(bool bMulti);
	~cTextbox();


private:
	std::wstring m_Text;
	bool m_bMulti;
	bool m_bActive;


public:
	UINT AddChar(wchar_t Char);
	UINT Length() const;
	void Clear();
	void SetActive(bool bActive);
	std::wstring GetStr() const;
	void GetStr(std::wstring* pOut);
	bool isActive() const;
	bool isMulti() const;


public:
	wchar_t operator[] (UINT i) const;
	wchar_t& operator[] (UINT i);
};

