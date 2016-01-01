#pragma once
#include <string>
#include <vector>

class cNetServer;
class cTransformButton;
class cEditBox;
































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 서버측 메세지 매니저
// Desc : 푸시메세지를 클라로 보내는 인터페이스 제공 및 채팅 보기
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetPushMsgSender
{
public:
	cNetPushMsgSender(cNetServer* pServer);
	~cNetPushMsgSender();


private: // 클라이언트
	cNetServer* m_pServer;


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

