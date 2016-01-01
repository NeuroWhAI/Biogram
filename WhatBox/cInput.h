#pragma once
#include <windows.h>
#include <d3dx9.h>













///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �Է���ġ
// Desc : Ű����� ���콺�� �Է»��¸� ���´�.
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


private:    //Ű����
	BYTE m_KeyCurr[256];
	BYTE m_KeyOld[256];
	BYTE m_KeyMap[256]; //Ű ���� ����


private:    //���콺
	BYTE m_MouseCurr[8];
	BYTE m_MouseOld[8];
	BYTE m_MouseMap[8]; //��ư ���� ����.

	D3DXVECTOR3 m_vcCurr;   //z���� ���콺���� ��Ÿ��.
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;    //���콺 ��ȭ��


public:
	//Ű���� ('a':X, 'A':O)
	bool KeyDown(INT VK);
	bool KeyUp(INT VK);
	bool KeyPress(INT VK);

	INT KeyState(INT VK);


	//���콺
	bool MouseDown(INT VK);
	bool MouseUp(INT VK);
	bool MousePress(INT VK);

	INT MouseState(INT VK);

	D3DXVECTOR3 GetMousePos();  //z: ��
	POINT CursorPos();  //���������� ��ǥ ����.
	POINT RealCursorPos();
	D3DXVECTOR2 fCursorPos(); // �Ǽ������� ��ǥ ����.
	D3DXVECTOR3 GetMouseEps();  //���콺 �̵���


public:
	INT FrameMove();
	int FrameMove_Limit();
	LRESULT MsgProc(UINT, WPARAM, LPARAM);
};


