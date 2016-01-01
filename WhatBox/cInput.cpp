#include "cInput.h"

#include "cCore.h"











cInput::cInput()
{
	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCurr, 0, sizeof(m_KeyCurr));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	GetKeyboardState(m_KeyCurr);


	memset(m_MouseCurr, 0, sizeof(m_MouseCurr));
	memset(m_MouseOld, 0, sizeof(m_MouseOld));
	memset(m_MouseMap, 0, sizeof(m_MouseMap));

	m_MouseCurr[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0;
	m_MouseCurr[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0;
	m_MouseCurr[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 1 : 0;
}


cInput::~cInput()
{
	
}

/*--------------------------------------------------------------------------------------*/

INT cInput::FrameMove()
{
	memcpy(m_KeyOld, m_KeyCurr, sizeof(m_KeyOld));


	memset(m_KeyCurr, 0, sizeof(m_KeyCurr));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));


	GetKeyboardState(m_KeyCurr);


	for(INT i=0; i<256; i++)
	{
		BYTE vk = m_KeyCurr[i] & 0x80;
		m_KeyCurr[i] = (vk) ? 1 : 0;

		INT old = m_KeyOld[i];
		INT curr = m_KeyCurr[i];


		if(0 == old && 1 == curr) m_KeyMap[i] = DOWN;
		else if(1 == old && 0 == curr) m_KeyMap[i] = UP;
		else if(1 == old && 1 == curr) m_KeyMap[i] = PRESS;
		else m_KeyMap[i] = NONE;
	}

	/*--------------------------------------------------------*/

	POINT cursor;
	::GetCursorPos(&cursor);


	RECT WindowRect;
	GetWindowRect(cCore::hWnd, &WindowRect);


	memcpy(m_MouseOld, m_MouseCurr, sizeof(m_MouseOld));


	memset(m_MouseCurr, 0, sizeof(m_MouseCurr));
	memset(m_MouseMap, 0, sizeof(m_MouseMap));


	if(cursor.x >= WindowRect.left  &&  cursor.x <= WindowRect.right
		&&
		cursor.y >= WindowRect.top  &&  cursor.y <= WindowRect.bottom
		&&
		GetForegroundWindow() == cCore::hWnd)
	{// 커서가 창 안에 있고 포커스 상태임
		m_MouseCurr[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0;
		m_MouseCurr[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0;
		m_MouseCurr[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 1 : 0;
	}
	else
	{
		m_MouseCurr[0] = NONE;
		m_MouseCurr[1] = NONE;
		m_MouseCurr[2] = NONE;
	}

	for(INT i=0; i<8; i++)
	{
		INT old = m_MouseOld[i];
		INT curr = m_MouseCurr[i];

		if(0 == old && 1 == curr) m_MouseMap[i] = DOWN;
		else if(1 == old && 0 == curr) m_MouseMap[i] = UP;
		else if(1 == old && 1 == curr) m_MouseMap[i] = PRESS;
	}


	::ScreenToClient(cCore::hWnd, &cursor);


	//m_vcOld.x = m_vcCurr.x;
	//m_vcOld.y = m_vcCurr.y;

	m_vcCurr.x = static_cast<FLOAT>(cursor.x);
	m_vcCurr.y = static_cast<FLOAT>(cursor.y);

	m_vcEps = m_vcCurr - m_vcOld;
	m_vcOld.z = m_vcCurr.z;


	return 0;
}


int cInput::FrameMove_Limit()
{
	m_vcOld = m_vcCurr;


	return 0;
}



bool cInput::KeyDown(INT VK)
{
	return m_KeyMap[VK]==DOWN;
}


bool cInput::KeyUp(INT VK)
{
	return m_KeyMap[VK]==UP;
}


bool cInput::KeyPress(INT VK)
{
	return m_KeyMap[VK]==PRESS;
}



INT cInput::KeyState(INT VK)
{
	return m_KeyMap[VK];
}



bool cInput::MouseDown(INT VK)
{
	return m_MouseMap[(VK==0x04) ? 2 : VK-1] == DOWN;
}


bool cInput::MouseUp(INT VK)
{
	return m_MouseMap[(VK==0x04) ? 2 : VK-1] == UP;
}


bool cInput::MousePress(INT VK)
{
	return m_MouseMap[(VK==0x04) ? 2 : VK-1] == PRESS;
}



INT cInput::MouseState(INT VK)
{
	return m_MouseMap[(VK==0x04) ? 2 : VK-1];
}



D3DXVECTOR3 cInput::GetMousePos()
{
	if(cCore::Sprite.CameraOnCheck())
	{
		const D3DXVECTOR2* Pos = cCore::Camera2D.Pos();


		return D3DXVECTOR3(m_vcCurr.x + Pos->x, m_vcCurr.y + Pos->y, m_vcCurr.z);
	}
	
	
	return m_vcCurr;
}


POINT cInput::CursorPos()
{
	POINT cursor;
	::GetCursorPos(&cursor);
	::ScreenToClient(cCore::hWnd, &cursor);


	if(cCore::Sprite.CameraOnCheck())
	{
		const D3DXVECTOR2* MoveVal = cCore::Camera2D.Pos();


		cursor.x += CAST(MoveVal->x, LONG);
		cursor.y += CAST(MoveVal->y, LONG);
	}


	return cursor;
}


POINT cInput::RealCursorPos()
{
	POINT cursor;
	::GetCursorPos(&cursor);
	::ScreenToClient(cCore::hWnd, &cursor);


	return cursor;
}


D3DXVECTOR2 cInput::fCursorPos()
{
	if(cCore::Sprite.CameraOnCheck())
	{
		const D3DXVECTOR2* Pos = cCore::Camera2D.Pos();

		
		return D3DXVECTOR2(m_vcCurr.x + Pos->x, m_vcCurr.y + Pos->y);
	}


	return D3DXVECTOR2(m_vcCurr.x, m_vcCurr.y);
}


D3DXVECTOR3 cInput::GetMouseEps()
{
	return m_vcEps;
}

/*--------------------------------------------------------------------------------------*/

LRESULT cInput::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_MOUSEWHEEL)
	{
		INT d = LOWORD(wParam);
		INT c = HIWORD(wParam);

		c = static_cast<short>(c);
		m_vcCurr.z += static_cast<FLOAT>(c);
	}

	return 0;
}

