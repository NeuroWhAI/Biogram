#include "cLabel.h"

#include "cCore.h"

#include "cFont.h"






























cLabel::cLabel()
	: m_pStr(nullptr)
	, m_pFont(&cCore::Resource.Font1)
	, m_Color(0xffffffff)
	, m_Dt(0UL)
{
	
}


cLabel::cLabel(const char str[])
	: m_pStr(new char[strlen(str) + 1])
	, m_pFont(&cCore::Resource.Font1)
	, m_Color(0xffffffff)
	, m_Dt(0UL)
{
	strcpy_s(m_pStr, strlen(str) + 1, str);
}


cLabel::cLabel(const char str[], cFont* pFont)
	: m_pStr(new char[strlen(str) + 1])
	, m_pFont(pFont)
	, m_Color(0xffffffff)
	, m_Dt(0UL)
{
	strcpy_s(m_pStr, strlen(str) + 1, str);
}


cLabel::cLabel(const char str[], cFont* pFont, DWORD Color, DWORD Dt)
	: m_pStr(new char[strlen(str) + 1])
	, m_pFont(pFont)
	, m_Color(Color)
	, m_Dt(Dt)
{
	strcpy_s(m_pStr, strlen(str) + 1, str);
}


cLabel::~cLabel()
{
	if(m_pStr != nullptr)
	{
		delete[] m_pStr;
		m_pStr = nullptr;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLabel::OnUpdate()
{
	m_Pos += m_Speed;


	return 0;
}


int cLabel::OnRender()
{
	if(m_pFont != nullptr  &&  m_pStr != nullptr)
	{
		m_pFont->ShowText(m_pStr, CAST(m_Pos.x, int), CAST(m_Pos.y, int), m_Color, m_Dt);
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLabel::SetFont(cFont* pFont)
{
	m_pFont = pFont;


	return 0;
}


int cLabel::SetText(const char str[])
{
	if(m_pStr != nullptr)
	{
		delete[] m_pStr;
	}


	m_pStr = new char[strlen(str) + 1];
	strcpy_s(m_pStr, strlen(str) + 1, str);


	return 0;
}


int cLabel::SetColor(DWORD Color)
{
	m_Color = Color;


	return 0;
}


int cLabel::SetDt(DWORD Dt)
{
	m_Dt = Dt;


	return 0;
}

/*-----------------------------------------------------------------------------------------------------*/

cFont* cLabel::GetFont()
{
	return m_pFont;
}


void cLabel::GetText(char pOut[]) const
{
	strcpy_s(pOut, strlen(m_pStr) + 1, m_pStr);
}


DWORD cLabel::GetColor() const
{
	return m_Color;
}


DWORD cLabel::GetDt() const
{
	return m_Dt;
}

