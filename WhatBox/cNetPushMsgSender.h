#pragma once
#include <string>
#include <vector>

class cNetServer;
class cTransformButton;
class cEditBox;
































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ������ �޼��� �Ŵ���
// Desc : Ǫ�ø޼����� Ŭ��� ������ �������̽� ���� �� ä�� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetPushMsgSender
{
public:
	cNetPushMsgSender(cNetServer* pServer);
	~cNetPushMsgSender();


private: // Ŭ���̾�Ʈ
	cNetServer* m_pServer;


private: // �������̽�
	cTransformButton* m_pSendButton;
	cEditBox* m_pTextBox;


private: // ���� ä�ø޼���
	std::vector<std::wstring> m_chatList;


public:
	int Update();
	int Render();


public:
	int PushChatMsg(std::wstring msg);
};

