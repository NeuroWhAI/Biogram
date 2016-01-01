#include "cNetChating.h"

#include "cNetClient.h"
#include "cTransformButton.h"
#include "cEditBox.h"

#include "cNetMessage.h"
#include "cBinaryWriter.h"
#include "NetMsgType.h"
#include "NetMsgUtil.h"

#include "cCore.h"



































cNetChating::cNetChating(cNetClient* pClient, std::wstring userName)
	: m_userName(userName)

	, m_pClient(pClient)

	, m_pSendButton(new cTransformButton(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(4)))
	, m_pTextBox(new cEditBox(0xff000000))
{
	m_pTextBox->Init(8.f, CAST(cCore::WinSize.y - 32 - 8, float),
		512.f, 32.f);

	m_pSendButton->SetPos(528.f, CAST(cCore::WinSize.y - 32 - 8, float));
}


cNetChating::~cNetChating()
{
	SAFE_DELETE(m_pSendButton);
	SAFE_DELETE(m_pTextBox);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetChating::Update()
{
	m_pTextBox->Update();
	m_pSendButton->Update();


	if(cCore::Input.KeyDown(VK_RETURN)  ||  m_pSendButton->ButtonUp())
	{
		if(m_pTextBox->Length() > 0)
		{
			std::wstring textMsg;
			m_pTextBox->GetStr(&textMsg);


			cBinaryWriter bw;

			bw.Write(m_userName.c_str());			// 보내는 유저 이름
			bw.Write(textMsg.c_str());				// 보내는 채팅 메세지


			m_pClient->PushMessage(NetMsgUtil::MakeMessage(NetMsgType::RQ_ChatMsg, &bw));


			m_pTextBox->Clear(); // 텍스트박스 비움
		}
	}


	return 0;
}


int cNetChating::Render()
{
	m_pTextBox->Render();
	m_pSendButton->Render();


	int chatCount = static_cast<int>(m_chatList.size());

	for(int i=chatCount-1; i>=0; i--)
	{
		cCore::Resource.Font0.ShowText(m_chatList[i], 8 + 2,
			cCore::WinSize.y - 32 - 8 - 32 -18*(chatCount - i),
			0xffffffff);
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetChating::PushChatMsg(std::wstring msg)
{
	m_chatList.emplace_back(msg);

	if(m_chatList.size() > 15)
	{
		m_chatList.erase(m_chatList.begin());
	}


	return 0;
}

