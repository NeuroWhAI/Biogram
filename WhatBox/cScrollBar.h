#pragma once
#include "cUIControl.h"

class cFont;























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 스크롤바
// Desc : 인터페이스 스크롤바 출력
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cScrollBar : public cUIControl
{
public:
	cScrollBar(float minVal, float maxVal, float defaultVal, float barSize = 8.f);
	~cScrollBar();


private:
	float m_value;
	float m_minVal, m_maxVal;


private:
	D3DXVECTOR2 m_barPos;
	float m_barSize;
	bool m_bOnDrag;


private:
	DWORD m_backColor;
	DWORD m_lineColor;
	DWORD m_barColor;


public:
	virtual int OnUpdate();
	virtual int OnRender();


public:
	int SetValue(float value);
	float GetValue() const;
	int SetBarSize(float size);
	float GetBarSize() const;
	int SetColor(DWORD backColor, DWORD lineColor, DWORD barColor);


public:
	int UpdateBarPos();
	float GetValueFromPos(const D3DXVECTOR2& pos);
};

