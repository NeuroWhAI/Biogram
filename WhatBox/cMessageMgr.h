#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cFuncSequence;



































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 푸시메세지
// Desc : 우측하단에서 튀어나오고 일정시간뒤 사라지는 메세지를 관리합니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cMessageMgr
{
public:
	cMessageMgr();
	~cMessageMgr();


private:
	class cMyMessage
	{
	public:
		cMyMessage(std::wstring msg, DWORD Color);


	private:
		std::wstring m_msg;
		DWORD m_Color;


	private:
		D3DXVECTOR2 m_Size;
		D3DXVECTOR2 m_Pos;
		float m_life;
		float m_flySpeed;


	public:
		int Update();
		int Render();


	public:
		float GetLife() const;
		float GetHeight() const;
		void AddYPos(float y);
	};

	std::vector<cMyMessage> m_msgList;


public:
	int Update();
	int Render();


public:
	int PushMessage(std::wstring msg, DWORD color);
};

