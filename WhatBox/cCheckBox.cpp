#include "cCheckBox.h"

#include "cCore.h"







































cCheckBox::cCheckBox(bool bChecked, std::wstring text, DWORD color)
	: m_bChecked(bChecked)
	, m_text(text)

	, m_color(color)
{
	m_Scale.x = m_Scale.y = 16.f;
}


cCheckBox::~cCheckBox()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cCheckBox::OnUpdate()
{
	if (cCore::Input.MouseDown(VK_LBUTTON))
	{
		D3DXVECTOR2 cursor = cCore::Input.fCursorPos();

		if (cursor.x >= m_Pos.x  &&  cursor.x <= m_Pos.x + m_Scale.x
			&&
			cursor.y >= m_Pos.y  &&  cursor.y <= m_Pos.y + m_Scale.y)
		{
			m_bChecked = !m_bChecked;
		}
	}


	return 0;
}


int cCheckBox::OnRender()
{
	cCore::Sprite.BeginDraw();


	cCore::Sprite.SetColor(m_color);
	cCore::Sprite.DrawTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(6),
		m_Pos, m_Angle, m_Scale / 16.f);

	if (m_bChecked)
	{
		cCore::Sprite.SetColor(Util::GetReverseColor(m_color));
		cCore::Sprite.DrawTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(7),
			m_Pos, m_Angle, m_Scale / 16.f);
	}


	cCore::Sprite.EndDraw();


	if (m_Scale.y < 20.f)
	{
		cCore::Resource.Font0.ShowText(m_text, m_Pos.x + m_Scale.x + 2.f, m_Pos.y + 1.f, m_color);
	}
	else
	{
		cCore::Resource.Font1.ShowText(m_text, m_Pos.x + m_Scale.x + 2.f, m_Pos.y + 2.f, m_color);
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

