#include "cEditBox.h"

#include "cCore.h"

#include "cTextbox.h"
































cEditBox::cEditBox(DWORD Color, bool isPassword)
	: m_Color(Color)
	, m_bPassword(isPassword)
	, m_pTextBox(cCore::Resource.CreateTextbox(false))

	, m_PrevTime(timeGetTime())
	, m_bShowCursor(false)

	, m_Size(m_Speed)
{
	
}


cEditBox::~cEditBox()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int cEditBox::Init(float XPos, float YPos, float Width, float Height)
{
	m_Pos.x = XPos;
	m_Pos.y = YPos;

	m_Size.x = Width;
	m_Size.y = Height;

	m_Scale.x = Width / 16.f;
	m_Scale.y = Height / 16.f;


	return 0;
}


int cEditBox::OnUpdate()
{
	/* 텍스트박스 클릭 */
	if(cCore::Input.MouseDown(VK_LBUTTON)  ||  cCore::Input.MouseDown(VK_RBUTTON))
	{
		bool bCameraOn = cCore::Sprite.CameraOnCheck();
		cCore::Sprite.OffCamera();


		D3DXVECTOR2 Cursor = cCore::Input.fCursorPos();


		if(Cursor.x > m_Pos.x  &&  Cursor.x < m_Pos.x + m_Size.x
			&&
			Cursor.y > m_Pos.y  &&  Cursor.y < m_Pos.y + m_Size.y)
		{// 커서가 안에 있음
			m_pTextBox->SetActive(true);
		}
		else
		{
			m_pTextBox->SetActive(false);
			m_bShowCursor = false;
		}


		if(bCameraOn)
			cCore::Sprite.OnCamera();
	}


	/* 커서 깜빡임 */
	if(m_pTextBox->isActive())
	{
		if(timeGetTime() - m_PrevTime > 500UL)
		{
			m_bShowCursor = !m_bShowCursor;

			m_PrevTime = timeGetTime();
		}
	}


	return 0;
}


int cEditBox::OnRender()
{
	/* 카메라 끄기 */
	bool bCameraOn = cCore::Sprite.CameraOnCheck();
	cCore::Sprite.OffCamera();


	/* 배경 */
	if(!m_pTextBox->isActive())
		cCore::Sprite.SetColor(0xc0f0f0f0);

	cCore::Sprite.RenderTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
		m_Pos, 0.f, m_Scale);


	/* 텍스트정보 얻기 */
	std::wstring wStr;

	if(m_bPassword)
	{// 패스워드 모드
		DWORD length = m_pTextBox->Length();

		for(UINT i=0; i<length; i++)
		{
			wStr.push_back('*');
		}
		wStr.push_back('\0');
	}
	else
	{// 일반 모드
		m_pTextBox->GetStr(&wStr);
	}

	SIZE Size = cCore::Resource.Font1.GetStringSize(&wStr);


	/* 텍스트 검사 */
	while(wStr.size() > 0  &&  Size.cx > m_Size.x)
	{
		wStr.erase(wStr.begin());
		Size = cCore::Resource.Font1.GetStringSize(&wStr);
	}


	/* 텍스트 출력 */
	DWORD Color = m_Color;

	if(!m_pTextBox->isActive())
		Color = ~m_Color | 0xc0000000; // 색반전, 반투명화

	cCore::Resource.Font1.ShowText(wStr, CAST(m_Pos.x, int) + 4, CAST(m_Pos.y, int) + 8, Color);


	/* 커서 */
	if(m_bShowCursor)
	{
		cCore::Resource.Font1.ShowText("｜",
			CAST(m_Pos.x, int) + Size.cx - 16,
			CAST(m_Pos.y, int) + 8,
			Color);
	}


	/* 외곽선 */
	/*D3DXVECTOR2 VtxArr[5] = {
		m_Pos, m_Pos + D3DXVECTOR2(m_Size.x, 0.f),
		m_Pos + m_Size, m_Pos + D3DXVECTOR2(0.f, m_Size.y),
		m_Pos
	};

	cCore::Resource.Line.Render(VtxArr, 5, 0xff000000, 2.f);*/


	/* 카메라 복구 */
	if(bCameraOn)
		cCore::Sprite.OnCamera();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cEditBox::IsActivate() const
{
	return m_pTextBox->isActive();
}


int cEditBox::GetStr(std::wstring* pOut)
{
	m_pTextBox->GetStr(pOut);


	return m_pTextBox->Length();
}


UINT cEditBox::Length() const
{
	return m_pTextBox->Length();
}


int cEditBox::Clear()
{
	m_pTextBox->Clear();


	return 0;
}

