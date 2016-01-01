#include "cMessageMgr.h"

#include "cCore.h"

































cMessageMgr::cMyMessage::cMyMessage(std::wstring msg, DWORD Color)
	: m_msg(msg)
	, m_Color(Color)

	, m_Size(0.f, 0.f)
	, m_Pos(0.f, 0.f)

	, m_life(800.f)
	, m_flySpeed(0.f)
{
	std::wstring widthStr;
	long maxSize = 0;
	long Height = 0;
	int lineNum = 0;

	for(UINT i=0; i<msg.size() + 1; i++)
	{
		wchar_t wc;

		if(i >= msg.size())
			wc = '\0';
		else
			wc = msg[i];


		widthStr.push_back(wc);


		if(wc == '\n'  ||  wc == '\0')
		{
			lineNum++;

			
			widthStr.push_back('\0');


			SIZE size = cCore::Resource.Font1.GetStringSize(&widthStr);

			if(size.cx > maxSize)
			{
				maxSize = size.cx;
				Height = size.cy;
			}

			widthStr.clear();
		}
	}


	m_Size.x = CAST(maxSize + 16, float);
	m_Size.y = CAST(lineNum * Height + 32, float);

	m_Pos.x = CAST(cCore::WinSize.x, float) - m_Size.x - 16.f;
	m_Pos.y = CAST(cCore::WinSize.y - cCore::WinSize.y/3, float);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cMessageMgr::cMyMessage::Update()
{
	Util::TempOffCamera tempOffCamera;


	m_life -= VFR(4.f);

	if(m_life < 0.f) m_life = 0.f;


	if(m_life < 256.f)
	{
		m_Pos.y -= VFR(m_flySpeed);

		m_flySpeed += VFR(0.1f);
	}
	else
	{
		if(cCore::Input.MouseDown(VK_LBUTTON))
		{
			D3DXVECTOR2 cursor = cCore::Input.fCursorPos();


			if(cursor.x > m_Pos.x  &&  cursor.x < m_Pos.x + m_Size.x
				&&
				cursor.y > m_Pos.y  &&  cursor.y < m_Pos.y + m_Size.y)
			{
				m_life = 255.f;
			}
		}
	}


	return 0;
}


int cMessageMgr::cMyMessage::Render()
{
	Util::TempOffCamera tempOffCamera;


	int alpha = CAST(m_life, int);

	if(alpha < 0) alpha = 0;
	else if(alpha > 255) alpha = 255;


	D3DXVECTOR2 cursor = cCore::Input.fCursorPos();

	if(cursor.x > m_Pos.x  &&  cursor.x < m_Pos.x + m_Size.x
		&&
		cursor.y > m_Pos.y  &&  cursor.y < m_Pos.y + m_Size.y)
	{
		cCore::Sprite.SetColor(D3DCOLOR_ARGB(alpha, 200, 200, 200));
	}
	else
	{
		cCore::Sprite.SetColor(D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}

	cCore::Sprite.RenderTexture(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(1),
		m_Pos, 0.f, m_Size / 16.f);


	cCore::Resource.Font1.ShowText(m_msg, CAST(m_Pos.x + 16.f, int), CAST(m_Pos.y + 16.f, int),
		D3DCOLOR_ARGB(alpha, 0, 0, 0));


	D3DXVECTOR2 vtxList[5] = {
		m_Pos,
		m_Pos + D3DXVECTOR2(m_Size.x, 0.f),
		m_Pos + m_Size,
		m_Pos + D3DXVECTOR2(0.f, m_Size.y),
		vtxList[0]
	};

	cCore::Resource.Line.Render(vtxList, 5, m_Color & D3DCOLOR_ARGB(alpha, 255,255,255), 4.f);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cMessageMgr::cMyMessage::GetLife() const
{
	return m_life;
}


float cMessageMgr::cMyMessage::GetHeight() const
{
	return m_Size.y;
}


void cMessageMgr::cMyMessage::AddYPos(float y)
{
	if(m_life > 256.f)
	{
		m_Pos.y += y;
	}
}

