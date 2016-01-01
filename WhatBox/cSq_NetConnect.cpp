#include "cSq_NetConnect.h"

#include "cCore.h"

#include "cSq_LoginUser.h"

#include "cNetClient.h"
#include "cNetMessage.h"

#include "cEditBox.h"
#include "cTransformButton.h"
#include "cLabel.h"

























cSq_NetConnect::cSq_NetConnect()
	: m_pNetClient(new cNetClient())
	, m_bSuccess(false)

	, m_pTextBox_IP(new cEditBox(D3DCOLOR_ARGB(255, 0, 0, 0)))
	, m_pTextBox_Port(new cEditBox(D3DCOLOR_ARGB(255, 0, 0, 0)))
	, m_pTextBox_UdpPort(new cEditBox(D3DCOLOR_ARGB(255, 0, 0, 0)))

	, m_pButton_Connect(new cTransformButton(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(2)))

	, m_pLabel_IP(new cLabel("IP :"))
	, m_pLabel_Port(new cLabel("Port :"))
	, m_pLabel_UdpPort(new cLabel("Port2 :"))
{
	
}


cSq_NetConnect::~cSq_NetConnect()
{
	SAFE_DELETE(m_pTextBox_IP);
	SAFE_DELETE(m_pTextBox_Port);
	SAFE_DELETE(m_pTextBox_UdpPort);

	SAFE_DELETE(m_pButton_Connect);

	SAFE_DELETE(m_pLabel_IP);
	SAFE_DELETE(m_pLabel_Port);
	SAFE_DELETE(m_pLabel_UdpPort);


	if(m_bSuccess == false)
	{
		if(m_pNetClient != nullptr)
		{
			delete m_pNetClient;
			m_pNetClient = nullptr;
		}
	}
}

/*----------------------------------------------------------------------------------*/

int cSq_NetConnect::OnInit()
{
	const D3DXVECTOR2& CenterPt = Util::CenterPos();


	m_pTextBox_IP->Init(CenterPt.x - 128.f, CenterPt.y - 40.f, 256.f, 32.f);
	m_pTextBox_Port->Init(CenterPt.x - 128.f, CenterPt.y + 8.f, 256.f, 32.f);
	m_pTextBox_UdpPort->Init(CenterPt.x - 128.f, CenterPt.y + 56.f, 256.f, 32.f);

	cCore::World->GetUILayer()->AddUIControl(m_pTextBox_IP);
	cCore::World->GetUILayer()->AddUIControl(m_pTextBox_Port);
	cCore::World->GetUILayer()->AddUIControl(m_pTextBox_UdpPort);


	m_pButton_Connect->SetPos(CenterPt.x + 8.f, CenterPt.y + 8.f + 64.f + 32.f);

	cCore::World->GetUILayer()->AddUIControl(m_pButton_Connect);


	m_pLabel_IP->SetPos(CenterPt.x - 170.f, CenterPt.y - 40.f + 8.f);
	m_pLabel_Port->SetPos(CenterPt.x - 191.f, CenterPt.y + 8.f + 8.f);
	m_pLabel_UdpPort->SetPos(CenterPt.x - 203.f, CenterPt.y + 56.f + 8.f);

	cCore::World->GetUILayer()->AddUIControl(m_pLabel_IP);
	cCore::World->GetUILayer()->AddUIControl(m_pLabel_Port);
	cCore::World->GetUILayer()->AddUIControl(m_pLabel_UdpPort);
	

	return 0;
}


int cSq_NetConnect::OnCleanUp()
{
	


	return 0;
}



int cSq_NetConnect::OnRestore()
{



	return 0;
}


int cSq_NetConnect::OnRelease()
{



	return 0;
}



int cSq_NetConnect::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_NetConnect::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESC키로 종료. 필요시 삭제.
		return EXIT_SEQ;


	if(m_pButton_Connect->ButtonUp())
	{
		if(m_pTextBox_IP->Length() < 1)
		{
			Util::PushMessage(TEXT("아이피주소를 입력하세요."), 0xffff0000);
		}
		else if(m_pTextBox_Port->Length() < 1)
		{
			Util::PushMessage(TEXT("포트를 입력하세요."), 0xffff0000);
		}
		else if(m_pTextBox_UdpPort->Length() < 1)
		{
			Util::PushMessage(TEXT("포트2를 입력하세요."), 0xffff0000);
		}
		else
		{
			std::wstring wIp, wPort, wUdpPort;

			m_pTextBox_IP->GetStr(&wIp);
			m_pTextBox_Port->GetStr(&wPort);
			m_pTextBox_UdpPort->GetStr(&wUdpPort);


			std::string ip, port, udpPort;

			Util::WStrToStr(wIp, &ip);
			Util::WStrToStr(wPort, &port);
			Util::WStrToStr(wUdpPort, &udpPort);

			
			if(m_pNetClient->Connect(ip.c_str(), port.c_str(), udpPort.c_str()) < 0)
			{// 접속 실패
				Util::PushMessage(TEXT("서버에 접속할 수 없습니다."), 0xffff0000);
			}
			else
			{// 접속 성공
				m_bSuccess = true;
				return new cSq_LoginUser(m_pNetClient);
			}
		}
	}


	/*--------------------------------*/
	return pNext;
}


int cSq_NetConnect::OnRender()
{
	


	return 0;
}

