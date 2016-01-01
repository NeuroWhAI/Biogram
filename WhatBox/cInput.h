#pragma once
#include <windows.h>
#include <d3dx9.h>













///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 입력장치
// Desc : 키보드와 마우스의 입력상태를 얻어온다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cInput
{
public:
	cInput();
	~cInput();


public:
	enum STATE
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};


private:    //키보드
	BYTE m_KeyCurr[256];
	BYTE m_KeyOld[256];
	BYTE m_KeyMap[256]; //키 상태 저장


private:    //마우스
	BYTE m_MouseCurr[8];
	BYTE m_MouseOld[8];
	BYTE m_MouseMap[8]; //버튼 상태 저장.

	D3DXVECTOR3 m_vcCurr;   //z값은 마우스휠을 나타냄.
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;    //마우스 변화량


public:
	//키보드 ('a':X, 'A':O)
	bool KeyDown(INT VK);
	bool KeyUp(INT VK);
	bool KeyPress(INT VK);

	INT KeyState(INT VK);


	//마우스
	bool MouseDown(INT VK);
	bool MouseUp(INT VK);
	bool MousePress(INT VK);

	INT MouseState(INT VK);

	D3DXVECTOR3 GetMousePos();  //z: 휠
	POINT CursorPos();  //정수형으로 좌표 얻어옴.
	POINT RealCursorPos();
	D3DXVECTOR2 fCursorPos(); // 실수형으로 좌표 얻어옴.
	D3DXVECTOR3 GetMouseEps();  //마우스 이동량


public:
	INT FrameMove();
	int FrameMove_Limit();
	LRESULT MsgProc(UINT, WPARAM, LPARAM);
};


