#pragma once
#include <string>
#include <vector>

class cNetClient;
class cTransformButton;
class cEditBox;































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��Ʈ��ũ ä��
// Desc : Ŭ�������� ä���� �ϱ����� �������̽��� �����մϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetChating
{
public:
	cNetChating(cNetClient* pClient, std::wstring userName);
	~cNetChating();


private: // ���� ����
	std::wstring m_userName;


private: // Ŭ���̾�Ʈ
	cNetClient* m_pClient;


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

