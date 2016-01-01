#include "cButton.h"

#include "cCore.h"

#include "cTextureList.h"



























cButton::cButton(cTextureList* pTxList, const char Text[])
	: m_currState(STATE_Not)

	, m_pTxList(pTxList)
{// 0:일반, 1:포커스, 2:클릭, 3:눌림, 4:땜
	if(m_pTxList->GetSize() < 5)
		MessageBox(NULL, TEXT("버튼의 텍스쳐는 5개 이상이여야 합니다."), TEXT("ERROR!"), MB_OK);

	m_Size = D3DXVECTOR2(CAST(m_pTxList->GetTexture(0)->Width(), float),
		CAST(m_pTxList->GetTexture(0)->Height(), float));


	m_Name[0] = '\0';
	strcpy_s(m_Name, 256, Text);
}


cButton::~cButton()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cButton::OnUpdate()
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
		}
		else if(cCore::Input.MouseUp(VK_LBUTTON))
		{
			m_currState = STATE_Up;
		}
		else
		{
			m_currState = STATE_Focus;
		}
	}
	else
	{
		m_currState = STATE_Not;
	}
	

	return 0;
}


int cButton::OnRender()
{
	bool PrevCameraState = cCore::Sprite.CameraOnCheck();
	cCore::Sprite.OffCamera();


	cCore::Sprite.RenderTexture(m_pTxList->GetTexture((UINT)m_currState),
		m_Pos, m_Angle, m_Scale);

	cCore::Resource.Font1.ShowText(m_Name, CAST(m_Pos.x, int) + (CAST(m_Size.x, int)>>1),
		CAST(m_Pos.y, int) + (CAST(m_Size.y, int)>>1) - 8, 0xff000000, DT_CENTER);


	if(PrevCameraState)
		cCore::Sprite.OnCamera();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cButton::ButtonFocus()
{
	return (m_currState == STATE_Focus);
}


bool cButton::ButtonDown()
{
	return (m_currState == STATE_Down);
}


bool cButton::ButtonPress()
{
	return (m_currState == STATE_Press);
}


bool cButton::ButtonUp()
{
	return (m_currState == STATE_Up);
}

