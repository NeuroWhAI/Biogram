#include "cTransformButton.h"

#include "cCore.h"

#include "cTexture.h"



























cTransformButton::cTransformButton()
	: m_currState(STATE_Not)

	, m_pTx(nullptr)
	, m_text(nullptr)
	, m_wText(nullptr)

	, m_RealPos(0.f, 0.f)
{

}


cTransformButton::cTransformButton(cTexture* pTx, const char text[])
	: m_currState(STATE_Not)

	, m_pTx(pTx)
	, m_text(new char[strlen(text)+1])
	, m_wText(nullptr)

	, m_RealPos(0.f, 0.f)
{
	m_Size = D3DXVECTOR2(CAST(m_pTx->Width(), float),
		CAST(m_pTx->Height(), float));

	strcpy_s(m_text, strlen(text)+1, text);
}


cTransformButton::cTransformButton(cTexture* pTx, const wchar_t text[])
	: m_currState(STATE_Not)

	, m_pTx(pTx)
	, m_text(nullptr)
	, m_wText(new wchar_t[lstrlenW(text)+1])

	, m_RealPos(0.f, 0.f)
{
	m_Size = D3DXVECTOR2(CAST(m_pTx->Width(), float),
		CAST(m_pTx->Height(), float));

	lstrcpyW(m_wText, text);
}


cTransformButton::~cTransformButton()
{
	SAFE_DELETE_ARR(m_text);
	SAFE_DELETE_ARR(m_wText);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTransformButton::SetTexture(cTexture* pTx)
{
	m_pTx = pTx;


	return 0;
}


int cTransformButton::SetText(const char text[])
{
	SAFE_DELETE_ARR(m_text);

	m_text = new char[strlen(text)+1];
	strcpy_s(m_text, strlen(text)+1, text);


	return 0;
}


int cTransformButton::SetText(const wchar_t text[])
{
	SAFE_DELETE_ARR(m_wText);

	m_wText = new wchar_t[lstrlenW(text)+1];
	lstrcpyW(m_wText, text);


	return 0;
}


int cTransformButton::OnUpdate()
{
	D3DXVECTOR2 Cursor = cCore::Input.fCursorPos();
	
	
	if(Cursor.x >= m_Pos.x  &&  Cursor.x <= m_Pos.x + m_Size.x
		&&
		Cursor.y >= m_Pos.y  &&  Cursor.y <= m_Pos.y + m_Size.y)
	{
		if(cCore::Input.MouseDown(VK_LBUTTON))
		{ 
			m_currState = STATE_Down;
		}
		else if(cCore::Input.MousePress(VK_LBUTTON))
		{
			m_currState = STATE_Press;

			m_Scale.x = m_Scale.y = 0.9f;
		}
		else if(cCore::Input.MouseUp(VK_LBUTTON))
		{
			m_currState = STATE_Up;
		}
		else
		{
			m_currState = STATE_Focus;

			m_Scale.x = m_Scale.y = 1.1f;
		}
	}
	else
	{
		m_currState = STATE_Not;

		m_Scale.x = m_Scale.y = 1.f;
	}


	m_RealPos = m_Pos + m_Size/2.f;
	

	return 0;
}


int cTransformButton::OnRender()
{
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_RealPos, m_Angle, m_Scale);

	if(m_wText != nullptr)
	{
		cCore::Resource.Font1.ShowText(m_wText,
			CAST(m_RealPos.x, int), CAST(m_RealPos.y, int) - 8,
			0xff000000, DT_CENTER);
	}
	else if(m_text != nullptr)
	{
		cCore::Resource.Font1.ShowText(m_text,
			CAST(m_RealPos.x, int), CAST(m_RealPos.y, int) - 8,
			0xff000000, DT_CENTER);
	}


	return 0;
}


int cTransformButton::RenderSmall()
{
	cCore::Sprite.RenderTextureCenter(m_pTx,
		m_RealPos, m_Angle, m_Scale);

	cCore::Resource.Font0.ShowText(m_text,
		CAST(m_RealPos.x, int), CAST(m_RealPos.y, int) - 8,
		0xff000000, DT_CENTER);


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cTransformButton::ButtonFocus()
{
	return (m_currState == STATE_Focus);
}


bool cTransformButton::ButtonDown()
{
	return (m_currState == STATE_Down);
}


bool cTransformButton::ButtonPress()
{
	return (m_currState == STATE_Press);
}


bool cTransformButton::ButtonUp()
{
	return (m_currState == STATE_Up);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cTransformButton::Reset()
{
	m_currState = STATE_Not;


	return 0;
}

