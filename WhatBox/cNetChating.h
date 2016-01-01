#pragma once
#include <string>
#include <vector>

class cNetClient;
class cTransformButton;
class cEditBox;































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 네트워크 채팅
// Desc : 클라측에서 채팅을 하기위한 인터페이스를 제공합니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetChating
{
public:
	cNetChating(cNetClient* pClient, std::wstring userName);
	~cNetChating();


private: // 유저 정보
	std::wstring m_userName;


private: // 클라이언트
	cNetClient* m_pClient;


private: // 인터페이스
	cTransformButton* m_pSendButton;
	cEditBox* m_pTextBox;


private: // 수신 채팅메세지
	std::vector<std::wstring> m_chatList;


public:
	int Update();
	int Render();


public:
	int PushChatMsg(std::wstring msg);
};

