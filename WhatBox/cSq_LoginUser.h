#pragma once
#include "cSequence.h"

class cNetClient;

class cEditBox;
class cTransformButton;
class cLabel;

class cNetMessage;




























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �α��� ������
// Desc : ��Ʈ��ũ ���������� �����ؼ� �� ���� �ֽ��ϴ�. ȸ������, �α��� �������̽��� �����մϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSq_LoginUser : public cSequence
{
public:
	cSq_LoginUser(cNetClient* pNetClient);
	~cSq_LoginUser();


private:
	cNetClient* m_pNetClient;
	bool m_bLoginSuccess;
	bool m_bOnWaitRP;					// ���� ���� �����


private:
	cEditBox *m_pTextBox_ID, *m_pTextBox_Password;
	cTransformButton *m_pButton_Login, *m_pButton_Register;
	cLabel *m_pLabel_ID, *m_pLabel_Password;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //�Ϲ� ������ '����'(������ �ƴ�)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();


private:
	int RecvFunc_RP_Login(cNetMessage* pMsg);
	int RecvFunc_RP_Register(cNetMessage* pMsg);
};

