#include "cSq_LoginUser.h"

#include "cCore.h"

#include "cSq_NetGame.h"

#include "cNetClient.h"

#include "cEditBox.h"
#include "cTransformButton.h"
#include "cLabel.h"

#include "cNetMessage.h"
#include "NetMsgType.h"
#include "NetMsgUtil.h"
#include "NetDefine.h"
#include "cBinaryReader.h"
#include "cBinaryWriter.h"




























cSq_LoginUser::cSq_LoginUser(cNetClient* pNetClient)
	: m_pNetClient(pNetClient)
	, m_bLoginSuccess(false)
	, m_bOnWaitRP(false)
	
	, m_pTextBox_ID(new cEditBox(D3DCOLOR_ARGB(255, 0, 0, 0)))
	, m_pTextBox_Password(new cEditBox(D3DCOLOR_ARGB(255, 0, 0, 0), true))

	, m_pButton_Login(new cTransformButton(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(2)))
	, m_pButton_Register(new cTransformButton(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(3)))

	, m_pLabel_ID(new cLabel("ID :"))
	, m_pLabel_Password(new cLabel("PW :"))
{
	
}


cSq_LoginUser::~cSq_LoginUser()
{
	SAFE_DELETE(m_pTextBox_ID);
	SAFE_DELETE(m_pTextBox_Password);

	SAFE_DELETE(m_pButton_Login);
	SAFE_DELETE(m_pButton_Register);

	SAFE_DELETE(m_pLabel_ID);
	SAFE_DELETE(m_pLabel_Password);


	if(m_bLoginSuccess == false)
	{
		if(m_pNetClient != nullptr)
		{
			m_pNetClient->Close();

			delete m_pNetClient;
			m_pNetClient = nullptr;
		}
	}
}

/*----------------------------------------------------------------------------------*/

int cSq_LoginUser::OnInit()
{
	const D3DXVECTOR2& CenterPt = Util::CenterPos();


	m_pTextBox_ID->Init(CenterPt.x - 128.f, CenterPt.y - 40.f, 256.f, 32.f);
	m_pTextBox_Password->Init(CenterPt.x - 128.f, CenterPt.y + 8.f, 256.f, 32.f);

	cCore::World->GetUILayer()->AddUIControl(m_pTextBox_ID);
	cCore::World->GetUILayer()->AddUIControl(m_pTextBox_Password);


	m_pButton_Login->SetPos(CenterPt.x + 8.f, CenterPt.y + 8.f + 32.f + 16.f);
	m_pButton_Register->SetPos(CenterPt.x - 128.f - 8.f, CenterPt.y + 8.f + 32.f + 16.f);

	cCore::World->GetUILayer()->AddUIControl(m_pButton_Login);
	cCore::World->GetUILayer()->AddUIControl(m_pButton_Register);


	m_pLabel_ID->SetPos(CenterPt.x - 170.f, CenterPt.y - 40.f + 8.f);
	m_pLabel_Password->SetPos(CenterPt.x - 183.f, CenterPt.y + 8.f + 8.f);

	cCore::World->GetUILayer()->AddUIControl(m_pLabel_ID);
	cCore::World->GetUILayer()->AddUIControl(m_pLabel_Password);


	// �α���, ȸ������ ����ó�� �Լ� ���
	m_pNetClient->AddRecvProcFunc(NetMsgType::RP_LoginUser,
		[&](cNetMessage* pMsg) {return RecvFunc_RP_Login(pMsg);});
	m_pNetClient->AddRecvProcFunc(NetMsgType::RP_RegisterUser,
		[&](cNetMessage* pMsg) {return RecvFunc_RP_Register(pMsg);});
	

	return 0;
}


int cSq_LoginUser::OnCleanUp()
{
	


	return 0;
}



int cSq_LoginUser::OnRestore()
{



	return 0;
}


int cSq_LoginUser::OnRelease()
{



	return 0;
}



int cSq_LoginUser::OnDelete()   //�Ϲ� ������ '����'(������ �ƴ�)
{
	


	return 0;
}



cSequence* cSq_LoginUser::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESCŰ�� ����. �ʿ�� ����.
		return EXIT_SEQ;


	if(m_pButton_Login->ButtonUp())
	{// �α���
		if(m_bOnWaitRP)
		{
			Util::PushMessage(TEXT("������ ������ ��ٸ��� ���Դϴ�."), 0xffff0000);
		}
		else if(m_pTextBox_ID->Length() < 1)
		{
			Util::PushMessage(TEXT("���̵� �Է����ּ���."), 0xffff0000);
		}
		else if(m_pTextBox_Password->Length() < 1)
		{
			Util::PushMessage(TEXT("��й�ȣ�� �Է����ּ���."), 0xffff0000);
		}
		else
		{// �α��� ��û
			std::wstring userID, userPwd;

			m_pTextBox_ID->GetStr(&userID);
			m_pTextBox_Password->GetStr(&userPwd);


			cBinaryWriter bw;

			bw.Write(userID.c_str());
			bw.Write(userPwd.c_str());


			m_pNetClient->PushMessage(NetMsgUtil::MakeMessage(NetMsgType::RQ_LoginUser, &bw));


			m_bOnWaitRP = true;
		}
	}
	else if(m_pButton_Register->ButtonUp())
	{// ȸ������
		if(m_bOnWaitRP)
		{
			Util::PushMessage(TEXT("������ ������ ��ٸ��� ���Դϴ�."), 0xffff0000);
		}
		else if(m_pTextBox_ID->Length() < 1)
		{
			Util::PushMessage(TEXT("���̵� �Է����ּ���."), 0xffff0000);
		}
		else if(m_pTextBox_Password->Length() < 1)
		{
			Util::PushMessage(TEXT("��й�ȣ�� �Է����ּ���."), 0xffff0000);
		}
		else
		{// ȸ������ ��û
			std::wstring userID, userPwd;

			m_pTextBox_ID->GetStr(&userID);
			m_pTextBox_Password->GetStr(&userPwd);


			cBinaryWriter bw;

			bw.Write(userID.c_str());
			bw.Write(userPwd.c_str());


			m_pNetClient->PushMessage(NetMsgUtil::MakeMessage(NetMsgType::RQ_RegisterUser, &bw));


			m_bOnWaitRP = true;
		}
	}


	if(m_bLoginSuccess)
	{// �α��� ����
		// ä��â �ʱ�ȭ
		std::wstring userID;
		m_pTextBox_ID->GetStr(&userID);

		m_pNetClient->InitNetChating(userID);


		return new cSq_NetGame(m_pNetClient);
	}


	m_pNetClient->Update();


	/*--------------------------------*/
	return pNext;
}


int cSq_LoginUser::OnRender()
{
	

	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cSq_LoginUser::RecvFunc_RP_Login(cNetMessage* pMsg)
{
	m_bOnWaitRP = false;


	cBinaryReader br(pMsg);


	int loginResult = br.Read<int>();

	if(loginResult == 0)
	{// �α��� ����
		m_bLoginSuccess = true;
	}
	else if(loginResult == -1)
	{
		Util::PushMessage(TEXT("��й�ȣ�� Ʋ���ϴ�."), 0xffff0000);
	}
	else if(loginResult == -2)
	{
		Util::PushMessage(TEXT("�������� �ʴ� �����Դϴ�."), 0xffff0000);
	}
	else if(loginResult == -3)
	{
		Util::PushMessage(TEXT("�̹� �α��� �� �����Դϴ�."), 0xffff0000);
	}
	else
	{
		Util::PushMessage(TEXT("�� �� ���� ����."), 0xffff0000);
	}

	
	return 0;
}


int cSq_LoginUser::RecvFunc_RP_Register(cNetMessage* pMsg)
{
	m_bOnWaitRP = false;


	cBinaryReader br(pMsg);


	int regResult = br.Read<int>();

	if(regResult == 0)
	{// ȸ������ ����
		Util::PushMessage(TEXT("������� ����."), 0xff00ff00);
	}
	else if(regResult == -1)
	{
		Util::PushMessage(TEXT("��ȿ���� �ʴ� ���̵��Դϴ�."), 0xffff0000);
	}
	else if(regResult == -2)
	{
		Util::PushMessage(TEXT("��ȿ���� �ʴ� ��й�ȣ�Դϴ�."), 0xffff0000);
	}
	else if(regResult == -3)
	{
		Util::PushMessage(TEXT("�ߺ��� ���̵��Դϴ�."), 0xffff0000);
	}
	else
	{
		Util::PushMessage(TEXT("�� �� ���� ����."), 0xffff0000);
	}


	return 0;
}

