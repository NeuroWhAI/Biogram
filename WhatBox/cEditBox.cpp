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
	/* �ؽ�Ʈ�ڽ� Ŭ�� */
	if(cCore::Input.MouseDown(VK_LBUTTON)  ||  cCore::Input.MouseDown(VK_RBUTTON))
	{
		bool bCameraOn = cCore::Sprite.CameraOnCheck();
		cCore::Sprite.OffCamera();


		D3DXVECTOR2 Cursor = cCore::Input.fCursorPos();


		if(Cursor.x > m_Pos.x  &&  Cursor.x < m_Pos.x + m_Size.x
			&&
			Cursor.y > m_Pos.y  &&  Cursor.y < m_Pos.y + m_Size.y)
		{// Ŀ���� �ȿ� ����
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


	/* Ŀ�� ������ */
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
	/* ī�޶� ���� */
	bool bCameraOn = cCore::Sprite.CameraOnCheck();
	cCore::Sprite.OffCamera();


	/* ��� */
	if(!m_pTextBox->isActive())
		cCore::Sprite.SetColor(0xc0f0f0f0);

	cCore::Sprite.RenderTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
		m_Pos, 0.f, m_Scale);


	/* �ؽ�Ʈ���� ��� */
	std::wstring wStr;

	if(m_bPassword)
	{// �н����� ���
		DWORD length = m_pTextBox->Length();

		for(UINT i=0; i<length; i++)
		{
			wStr.push_back('*');
		}
		wStr.push_back('\0');
	}
	else
	{// �Ϲ� ���
		m_pTextBox->GetStr(&wStr);
	}

	SIZE Size = cCore::Resource.Font1.GetStringSize(&wStr);


	/* �ؽ�Ʈ �˻� */
	while(wStr.size() > 0  &&  Size.cx > m_Size.x)
	{
		wStr.erase(wStr.begin());
		Size = cCore::Resource.Font1.GetStringSize(&wStr);
	}


	/* �ؽ�Ʈ ��� */
	DWORD Color = m_Color;

	if(!m_pTextBox->isActive())
		Color = ~m_Color | 0xc0000000; // ������, ������ȭ

	cCore::Resource.Font1.ShowText(wStr, CAST(m_Pos.x, int) + 4, CAST(m_Pos.y, int) + 8, Color);


	/* Ŀ�� */
	if(m_bShowCursor)
	{
		cCore::Resource.Font1.ShowText("��",
			CAST(m_Pos.x, int) + Size.cx - 16,
			CAST(m_Pos.y, int) + 8,
			Color);
	}


	/* �ܰ��� */
	/*D3DXVECTOR2 VtxArr[5] = {
		m_Pos, m_Pos + D3DXVECTOR2(m_Size.x, 0.f),
		m_Pos + m_Size, m_Pos + D3DXVECTOR2(0.f, m_Size.y),
		m_Pos
	};

	cCore::Resource.Line.Render(VtxArr, 5, 0xff000000, 2.f);*/


	/* ī�޶� ���� */
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

