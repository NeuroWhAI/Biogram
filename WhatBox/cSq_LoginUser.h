#pragma once
#include "cSequence.h"

class cNetClient;

class cEditBox;
class cTransformButton;
class cLabel;

class cNetMessage;




























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 로그인 시퀀스
// Desc : 네트워크 전용이지만 수정해서 쓸 수도 있습니다. 회원가입, 로그인 인터페이스를 지원합니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSq_LoginUser : public cSequence
{
public:
	cSq_LoginUser(cNetClient* pNetClient);
	~cSq_LoginUser();


private:
	cNetClient* m_pNetClient;
	bool m_bLoginSuccess;
	bool m_bOnWaitRP;					// 서버 응답 대기중


private:
	cEditBox *m_pTextBox_ID, *m_pTextBox_Password;
	cTransformButton *m_pButton_Login, *m_pButton_Register;
	cLabel *m_pLabel_ID, *m_pLabel_Password;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();


private:
	int RecvFunc_RP_Login(cNetMessage* pMsg);
	int RecvFunc_RP_Register(cNetMessage* pMsg);
};

