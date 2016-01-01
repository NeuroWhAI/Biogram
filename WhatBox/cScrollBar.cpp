#include "cScrollBar.h"

#include "cCore.h"
#include "cShp_Rectangle.h"































cScrollBar::cScrollBar(float minVal, float maxVal, float defaultVal, float barSize)
	: m_value(defaultVal)
	, m_minVal(minVal)
	, m_maxVal(maxVal)

	, m_barPos(m_Pos)
	, m_barSize(barSize)
	, m_bOnDrag(false)

	, m_backColor(0x88888888)
	, m_lineColor(0xff404040)
	, m_barColor(0xffffffff)
{
	
}


cScrollBar::~cScrollBar()
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cScrollBar::OnUpdate()
{
	m_Pos += m_Speed;
	m_barPos += m_Speed;


	const float width = m_Scale.x;
	const float height = m_Scale.y;


	if(cCore::Input.MouseDown(VK_LBUTTON))
	{
		if(cCore::ShapeMath.isCollided(&cCore::Input.fCursorPos(), &m_barPos, m_barSize))
		{
			m_value = GetValueFromPos(cCore::Input.fCursorPos());

			m_bOnDrag = true;
		}
		else
		{
			cShp_Rectangle rect(m_Pos.x, m_Pos.y-height/2.f, m_Pos.x+width, m_Pos.y+height/2.f);

			if(cCore::ShapeMath.isCollided(&cCore::Input.fCursorPos(), &rect))
			{
				if(cCore::Input.fCursorPos().x < m_barPos.x)
				{
					m_value = GetValueFromPos(m_barPos + D3DXVECTOR2(-1.f, 0.f));
				}
				else
				{
					m_value = GetValueFromPos(m_barPos + D3DXVECTOR2(+1.f, 0.f));
				}
			}
		}
	}
	else if(cCore::Input.MouseUp(VK_LBUTTON))
	{
		m_bOnDrag = false;
	}


	if(m_bOnDrag)
	{
		if(cCore::Input.fCursorPos().x < m_Pos.x)
		{
			m_value = m_minVal;
		}
		else if(cCore::Input.fCursorPos().x > m_Pos.x+width)
		{
			m_value = m_maxVal;
		}
		else
		{
			m_value = GetValueFromPos(cCore::Input.fCursorPos());
		}
	}


	UpdateBarPos();


	return 0;
}


int cScrollBar::OnRender()
{
	const float width = m_Scale.x;
	const float height = m_Scale.y;


	cCore::Sprite.SetColor(m_backColor);
	cCore::Sprite.RenderTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
		m_Pos+D3DXVECTOR2(0.f, -height/2.f), 0.f, m_Scale/16.f);

	
	cCore::Sprite.SetColor(m_lineColor);
	cCore::Sprite.RenderTextureCenter(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
		m_Pos+D3DXVECTOR2(width/2.f, 0.f), 0.f, (m_Scale+D3DXVECTOR2(-8.f, -4.f))/16.f);


	cCore::Sprite.SetColor(m_barColor);
	cCore::Sprite.RenderTextureCenter(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(5),
		m_barPos, 0.f, D3DXVECTOR2(m_barSize, m_barSize)/16.f);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cScrollBar::SetValue(float value)
{
	m_value = value;


	UpdateBarPos();


	return 0;
}


float cScrollBar::GetValue() const
{
	return m_value;
}


int cScrollBar::SetBarSize(float size)
{
	m_barSize = size;


	return 0;
}


float cScrollBar::GetBarSize() const
{
	return m_barSize;
}


int cScrollBar::SetColor(DWORD backColor, DWORD lineColor, DWORD barColor)
{
	m_backColor = backColor;
	m_lineColor = lineColor;
	m_barColor = barColor;


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cScrollBar::UpdateBarPos()
{
	const float width = m_Scale.x;

	m_barPos.x = m_Pos.x + (m_value-m_minVal)/(m_maxVal-m_minVal)*width;
	m_barPos.y = m_Pos.y;


	return 0;
}


float cScrollBar::GetValueFromPos(const D3DXVECTOR2& pos)
{
	return (m_minVal+(pos.x-m_Pos.x)/m_Scale.x*(m_maxVal - m_minVal));
}

