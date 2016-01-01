#include "cNetClient.h"

#include "NetMsgType.h"

#include "cNetMessage.h"
#include "cMessageReceiver.h"
#include "cMessageSender.h"
#include "cClientSygnMgr.h"
#include "cBinaryReader.h"
#include "cNetChating.h"

#include "cCore.h"






























cNetClient::cNetClient()
	: m_bInitFunc(false)
	
	, m_pMsgReceiver(new cMessageReceiver())
	, m_pMsgSender(new cMessageSender())
	, m_isEnd(true)
	, m_pUdpMsgReceiver(new cMessageReceiver())
	, m_pUdpMsgSender(new cMessageSender())
	, m_CurrUpdateFuncNum(0)

	, m_OnConnect(nullptr)
	, m_OnClose(nullptr)
	, m_OnReceiveMsg(nullptr)
	, m_OnUpdate(nullptr)
	, m_OnRender(nullptr)
	, m_OnCreateSygnVal(nullptr)
	, m_OnDeleteSygnVal(nullptr)

	, m_pNetChating(nullptr)
	, m_userName(L"")
{
	
}


cNetClient::~cNetClient()
{
	if(m_pMsgReceiver != NULL)
	{
		delete m_pMsgReceiver;
		m_pMsgReceiver = NULL;
	}

	if(m_pMsgSender != NULL)
	{
		delete m_pMsgSender;
		m_pMsgSender = NULL;
	}

	if(m_pUdpMsgReceiver != NULL)
	{
		delete m_pUdpMsgReceiver;
		m_pUdpMsgReceiver = NULL;
	}

	if(m_pUdpMsgSender != NULL)
	{
		delete m_pUdpMsgSender;
		m_pUdpMsgSender = NULL;
	}


	for(UINT i=0; i<m_pSygnMgrList.size(); i++)
	{
		if(m_pSygnMgrList[i] != NULL)
		{
			delete m_pSygnMgrList[i];
			m_pSygnMgrList[i] = NULL;
		}
	}


	if(m_pNetChating != nullptr)
	{
		delete m_pNetChating;
		m_pNetChating = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::Connect(const char IP[], const char Port[], const char UdpPort[])
{
	/* WSA 초기화 */
	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 )
		return -1;


	/* 소켓 생성 */
	m_Clnt = socket(PF_INET, SOCK_STREAM, 0);
	if(m_Clnt == INVALID_SOCKET)
		return -2;

	memset(&m_ClntAdr, 0, sizeof(m_ClntAdr));
	m_ClntAdr.sin_family = AF_INET;
	m_ClntAdr.sin_addr.s_addr = inet_addr(IP);
	m_ClntAdr.sin_port = htons(atoi(Port));

	if( connect(m_Clnt, (SOCKADDR*)&m_ClntAdr, sizeof(m_ClntAdr)) == SOCKET_ERROR )
		return -3;


	/* UDP 소켓 생성 */
	m_UdpClnt = socket(PF_INET, SOCK_DGRAM, 0);
	if(m_UdpClnt == INVALID_SOCKET)
	{
		closesocket(m_Clnt);
		return -4;
	}

	memset(&m_UdpServAdr, 0, sizeof(m_UdpServAdr));
	m_UdpServAdr.sin_family = AF_INET;
	m_UdpServAdr.sin_addr.s_addr = inet_addr(IP);
	m_UdpServAdr.sin_port = htons(atoi(UdpPort));

	if( connect(m_UdpClnt, (SOCKADDR*)&m_UdpServAdr, sizeof(m_UdpServAdr)) == SOCKET_ERROR )
	{
		closesocket(m_Clnt);
		return -5;
	}


	/* 메세지 리스너 작동 */
	m_pMsgSender->Start(m_Clnt);
	m_pMsgReceiver->Start(m_Clnt);
	m_pUdpMsgSender->Start(m_UdpClnt); // NOTE: Connected UDP 소켓이므로 false옵션을 주지 않아도 됨
	m_pUdpMsgReceiver->Start(m_UdpClnt, false);
	// S 계단~ (/^3^)/

	m_isEnd = false;


	if(m_bInitFunc)
		return m_OnConnect();


	return 0;
}


int cNetClient::Close()
{
	if(m_isEnd) return 0;


	int Result = (m_bInitFunc ? m_OnClose() : 0);


	/* 소켓 닫기 */
	closesocket(m_Clnt);
	closesocket(m_UdpClnt);


	/* 메세지 리스너 중지 */
	m_pMsgSender->Stop();
	m_pMsgReceiver->Stop();
	m_pUdpMsgSender->Stop();
	m_pUdpMsgReceiver->Stop();

	m_isEnd = true;


	/* WSA 제거 */
	WSACleanup();


	return Result;
}



int cNetClient::ReceiveMsg(cNetMessage* pMsg)
{
	UINT32 MsgType = pMsg->Header->MsgType;

	if(MsgType == NetMsgType::RP_SygnVal_Info)
	{// 동기화
		cBinaryReader br(pMsg);

		int sygnMgrIdx = br.Read<int>();


		if(static_cast<unsigned int>(sygnMgrIdx) >= m_pSygnMgrList.size())
		{
			while(static_cast<unsigned int>(sygnMgrIdx) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


			m_pSygnMgrList[sygnMgrIdx] = new cClientSygnMgr(m_pUdpMsgSender);
		}
		else if(m_pSygnMgrList[sygnMgrIdx] == nullptr)
		{
			m_pSygnMgrList[sygnMgrIdx] = new cClientSygnMgr(m_pUdpMsgSender);
		}


		std::vector<int> CreateList, DeleteList;

		m_pSygnMgrList[sygnMgrIdx]->Recv(pMsg, &CreateList, &DeleteList);
		
		UpdateSygnVal(sygnMgrIdx, &CreateList, &DeleteList);
	}
	else if(MsgType == NetMsgType::RP_ChatMsg)
	{// 채팅 메세지
		RecvChatMsgRP(pMsg);
	}
	else if(MsgType == NetMsgType::NF_PushMsg)
	{// 서버측의 푸시메세지
		RecvPushMsgNF(pMsg);
	}
	else if(MsgType < m_RecvProcFuncList.size())
	{
		m_RecvProcFuncList[MsgType](pMsg);
	}


	int Result = 0;

	if(pMsg != nullptr)
	{
		Result = (m_bInitFunc ? m_OnReceiveMsg(pMsg) : 0);


		delete pMsg;
		pMsg = nullptr;
	}


	return Result;
}



int cNetClient::Update()
{
	if(m_isEnd == false)
	{// 소켓이 열려있을때
		if(m_pMsgReceiver->isEnd()  ||  m_pUdpMsgReceiver->isEnd()  ||  m_pMsgSender->isEnd())
		{// 서버측에서 연결을 끊음
			Close();
			return -1;
		}


		for(UINT i=0; i<m_pSygnMgrList.size(); i++)
		{
			if(m_pSygnMgrList[i] == nullptr) continue;


			m_pSygnMgrList[i]->Update(static_cast<int>(i));
		}


		if(m_pMsgReceiver->QueSize() > 0)
		{// 수신된 메세지 있음
			cNetMessage* pMsg = m_pMsgReceiver->Enqueue();

			ReceiveMsg(pMsg);
		}


		UINT QueSize = min(m_pUdpMsgReceiver->QueSize(), 1024);

		/*
		while(QueSize > 0)
		{// UDP 수신된 메세지 있음
			QueSize--;

			cNetMessage* pMsg = m_pUdpMsgReceiver->Enqueue();
			m_pUdpMsgReceiver->ClearAdr();
			// 가장 마지막에 온 메세지만 받고 나머진 버림
			
			if(pMsg != NULL)
			{
				ReceiveMsg(pMsg);
			}
		}
		*/

		while(QueSize > 0)
		{
			QueSize--;


			cNetMessage* pMsg = m_pUdpMsgReceiver->Enqueue();

			if(pMsg != NULL)
			{
				ReceiveMsg(pMsg);
			}
		}

		m_pUdpMsgReceiver->Clear();
		m_pUdpMsgReceiver->ClearAdr();
	}


	// 현재 시퀀스에 해당하는 Update 호출
	if(static_cast<UINT>(m_CurrUpdateFuncNum) < m_UpdateFuncList.size())
	{
		m_UpdateFuncList[m_CurrUpdateFuncNum]();
	}


	// 채팅 인터페이스
	if(m_pNetChating != nullptr)
	{
		m_pNetChating->Update();
	}


	if(m_bInitFunc)
		return m_OnUpdate();
	return 0;
}

 
int cNetClient::Render()
{
	// 현재 시퀀스에 해당하는 Render 호출
	if(static_cast<UINT>(m_CurrUpdateFuncNum) < m_RenderFuncList.size())
	{
		m_RenderFuncList[m_CurrUpdateFuncNum]();
	}


	// 채팅 인터페이스
	if(m_pNetChating != nullptr)
	{
		m_pNetChating->Render();
	}


	if(m_bInitFunc)
		return m_OnRender();
	return 0;
}


int cNetClient::UpdateSygnVal(int ValType, std::vector<int>* pCreateIdxList, std::vector<int>* pDeleteIdxList)
{
	/* 생성 */
	if(m_bInitFunc)
	{
		for(UINT i=0; i<pCreateIdxList->size(); i++)
		{
			int CreateIdx = (*pCreateIdxList)[i];

			cSygnVal* pSygnVal = m_OnCreateSygnVal(ValType, CreateIdx);

			m_pSygnMgrList[ValType]->SetSygnVal(pSygnVal, CreateIdx);
		}
	

		/* 제거 */
		for(UINT i=0; i<pDeleteIdxList->size(); i++)
		{
			int DeleteIdx = (*pDeleteIdxList)[i];

			m_OnDeleteSygnVal(ValType, DeleteIdx);

			m_pSygnMgrList[ValType]->RemoveSygnVal(DeleteIdx);
		}
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::InitFunc(std::function<int(void)> OnConnect,
						 std::function<int(void)> OnClose,

						 std::function<int(cNetMessage*)> OnReceiveMsg,

						 std::function<int(void)> OnUpdate,
						 std::function<int(void)> OnRender,

						 std::function<cSygnVal*(int, int)> OnCreateSygnVal,
						 std::function<int(int, int)> OnDeleteSygnVal)
{
	m_bInitFunc = true;


	m_OnConnect = OnConnect;
	m_OnClose = OnClose;

	m_OnReceiveMsg = OnReceiveMsg;

	m_OnUpdate = OnUpdate;
	m_OnRender = OnRender;

	m_OnCreateSygnVal = OnCreateSygnVal;
	m_OnDeleteSygnVal = OnDeleteSygnVal;


	return 0;
}


int cNetClient::InitNetChating(std::wstring userName)
{
	if(m_pNetChating != nullptr) delete m_pNetChating;


	m_pNetChating = new cNetChating(this, userName);


	m_userName = userName;


	return 0;
}


int cNetClient::StopChating()
{
	if(m_pNetChating != nullptr)
	{
		delete m_pNetChating;
		m_pNetChating = nullptr;
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::AddRecvProcFunc(int index, std::function<int _CLNT_FUNC_TYPE_> Func)
{
	while(m_RecvProcFuncList.size() < static_cast<UINT>(index))
		m_RecvProcFuncList.emplace_back();

	m_RecvProcFuncList.emplace_back(Func);


	return 0;
}


int cNetClient::AddUpdateFunc(int index, std::function<int(void)> UpdateFunc)
{
	while(m_UpdateFuncList.size() < static_cast<UINT>(index))
		m_UpdateFuncList.emplace_back();

	m_UpdateFuncList.emplace_back(UpdateFunc);


	return 0;
}


int cNetClient::AddRenderFunc(int index, std::function<int(void)> RenderFunc)
{
	while(m_RenderFuncList.size() < static_cast<UINT>(index))
		m_RenderFuncList.emplace_back();

	m_RenderFuncList.emplace_back(RenderFunc);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::AddSygnVal(int ValType, cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size())
	{
		while(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}
	else if(m_pSygnMgrList[ValType] == nullptr)
	{
		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}


	return m_pSygnMgrList[ValType]->AddSygnVal(pSygnVal);
}


int cNetClient::SetSygnVal(int ValType, int idx, cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size())
	{
		while(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}
	else if(m_pSygnMgrList[ValType] == nullptr)
	{
		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}


	return m_pSygnMgrList[ValType]->SetSygnVal(pSygnVal, idx);
}


int cNetClient::RemoveSygnVal(int ValType, const cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()
		||
		m_pSygnMgrList[ValType] == nullptr) return -1;


	return m_pSygnMgrList[ValType]->RemoveSygnVal(pSygnVal);
}

/*---------------------------------------------------------------------------------------------------*/

int cNetClient::ExtendSygnMgr(int ValType)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size())
	{
		while(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}
	else if(m_pSygnMgrList[ValType] == nullptr)
	{
		m_pSygnMgrList[ValType] = new cClientSygnMgr(m_pUdpMsgSender);
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::PushMessage(cNetMessage* pMsg)
{
	m_pMsgSender->PushSendMsg(pMsg);


	return 0;
}


int cNetClient::PushUdpMessage(cNetMessage* pMsg)
{
	m_pUdpMsgSender->PushSendMsg(pMsg);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cNetClient::isEnd() const
{
	return m_isEnd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::RecvChatMsgRP(cNetMessage* pMsg)
{
	if(m_pNetChating == nullptr) return -1;


	cBinaryReader br(pMsg);

	std::wstring chatMsg;

	br.ReadString(&chatMsg);


	m_pNetChating->PushChatMsg(chatMsg);


	return 0;
}


int cNetClient::RecvPushMsgNF(cNetMessage* pMsg)
{
	cBinaryReader br(pMsg);

	std::wstring pushMsg;
	br.ReadString(&pushMsg);

	DWORD color = br.Read<DWORD>();


	Util::PushMessage(TEXT("[SERVER]\n") + pushMsg, color);


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetClient::GetClntUserName(std::wstring* pOut)
{
	*pOut = m_userName;


	return 0;
}

