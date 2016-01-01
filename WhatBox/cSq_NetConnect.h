#pragma once
#include "cSequence.h"

class cNetClient;
class cNetMessage;

class cEditBox;
class cTransformButton;
class cLabel;































class cSq_NetConnect : public cSequence
{
public:
	cSq_NetConnect();
	~cSq_NetConnect();


private:
	cNetClient* m_pNetClient;
	bool m_bSuccess;


private:
	cEditBox *m_pTextBox_IP, *m_pTextBox_Port, *m_pTextBox_UdpPort;
	cTransformButton *m_pButton_Connect;
	cLabel *m_pLabel_IP, *m_pLabel_Port, *m_pLabel_UdpPort;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

