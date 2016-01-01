#include "cTextbox.h"























cTextbox::cTextbox(bool bMulti)
	: m_bMulti(bMulti)
	, m_bActive(false)
{

}


cTextbox::~cTextbox()
{

}

/*------------------------------------------------------------------------------------*/

UINT cTextbox::AddChar(wchar_t Char)
{
	if(m_bActive)
	{
		if(Char == VK_TAB)
		{
			m_Text.push_back(' ');
		}
		else if(Char == VK_RETURN)
		{
			if(m_bMulti)
				m_Text.push_back('\n');
		}
		else if(Char == VK_BACK)
		{
			if(m_Text.size() > 0)
			{
				/*if(m_Text[m_Text.size()-1] & 0x80)
				{
					m_Text.pop_back();
				}*/

				m_Text.pop_back();
			}
		}
		else
		{
			m_Text.push_back(Char);
		}
	}


	return m_Text.size();
}


UINT cTextbox::Length() const
{
	return m_Text.size();
}


void cTextbox::Clear()
{
	m_Text.clear();
}


void cTextbox::SetActive(bool bActive)
{
	m_bActive = bActive;
}


std::wstring cTextbox::GetStr() const
{
	std::wstring Str(m_Text);
	Str.push_back('\0');

	return Str;
}


void cTextbox::GetStr(std::wstring* pOut)
{
	*pOut = m_Text;
	pOut->push_back('\0');
}


bool cTextbox::isActive() const
{
	return m_bActive;
}


bool cTextbox::isMulti() const
{
	return m_bMulti;
}

/*------------------------------------------------------------------------------------*/

wchar_t cTextbox::operator[] (UINT i) const
{
	return m_Text[i];
}


wchar_t& cTextbox::operator[] (UINT i)
{
	return m_Text[i];	
}

