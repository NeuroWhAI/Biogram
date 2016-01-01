#include <assert.h>

#include "cNetServer.h"

#include "NetMsgUtil.h"

#include "cNetMessage.h"
#include "cMessageReceiver.h"
#include "cMessageSender.h"
#include "cServerSygnMgr.h"
#include "cNetPushMsgSender.h"
#include "cSygnVal.h"

#include "cBinaryReader.h"
#include "cBinaryWriter.h"

#include <fstream>

#include "cCore.h"



























cNetServer::cNetServer()
	: m_bOnInit(false)
	
	, m_isEnd(false)
	, m_pUdpMsgReceiver(new cMessageReceiver())
	, m_pUdpMsgSender(new cMessageSender())
	, m_pPushMsgMgr(new cNetPushMsgSender(this))

	, m_OnOpen(nullptr)
	, m_OnClose(nullptr)
	, m_OnClntConnect(nullptr)
	, m_OnClntClose(nullptr)
	, m_OnReceiveMsg(nullptr)
	, m_OnReceiveUdpMsg(nullptr)
	, m_OnUpdate(nullptr)
	, m_OnUserLogin(nullptr)
	, m_OnUserLogout(nullptr)
{

}


cNetServer::~cNetServer()
{
	for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
	{
		if(m_pMsgReceiverList[i] == NULL) continue;


		delete m_pMsgReceiverList[i];
	}

	for(UINT i=0; i<m_pMsgSenderList.size(); i++)
	{
		if(m_pMsgSenderList[i] == NULL) continue;


		delete m_pMsgSenderList[i];
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


	if(m_pPushMsgMgr != nullptr)
	{
		delete m_pPushMsgMgr;
		m_pPushMsgMgr = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::Open(const char Port[], const char UdpPort[])
{
	/* WSA �ʱ�ȭ */
	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 )
	{
		PushServerLog("WSA�ʱ�ȭ ����");
		return -1;
	}


	/* ���� ���� */
	m_Serv = socket(PF_INET, SOCK_STREAM, 0);
	if(m_Serv == INVALID_SOCKET)
	{
		PushServerLog("�������� ���� ����");
		return -2;
	}

	memset(&m_ServAdr, 0, sizeof(m_ServAdr));
	m_ServAdr.sin_family = AF_INET;
	m_ServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_ServAdr.sin_port= htons(atoi(Port));

	// NOTE: thread.h���� std::bind�� �ֱ⶧���� WinSock2.h�� bind�� ȣ���Ϸ��� ::bind�� ������Ѵ�.
	if( ::bind(m_Serv, (SOCKADDR*)&m_ServAdr, sizeof(m_ServAdr)) == SOCKET_ERROR )
	{
		PushServerLog("�������� bind����");
		return -3;
	}

	if( listen(m_Serv, 5) == SOCKET_ERROR )
	{
		PushServerLog("�������� listen����");
		return -4;
	}

	FD_ZERO(&m_Reads);
	FD_SET(m_Serv, &m_Reads);


	const int Delay_ms = 10;
	m_TimeOut.tv_sec= Delay_ms/1000;
	m_TimeOut.tv_usec = Delay_ms%1000;


	/* UDP ���� ���� */
	m_UdpSock = socket(PF_INET, SOCK_DGRAM, 0);
	if(m_UdpSock == INVALID_SOCKET)
	{
		PushServerLog("UDP���� ���� ����");
		return -5;
	}

	memset(&m_UdpServAdr, 0, sizeof(m_UdpServAdr));
	m_UdpServAdr.sin_family = AF_INET;
	m_UdpServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_UdpServAdr.sin_port = htons(atoi(UdpPort));

	if( ::bind(m_UdpSock, (SOCKADDR*)&m_UdpServAdr, sizeof(m_UdpServAdr)) == SOCKET_ERROR )
	{
		PushServerLog("UDP���� bind ����");
		return -6;
	}


	/* UDP �޼��� ������ ���� */
	m_pUdpMsgReceiver->Start(m_UdpSock, false);
	m_pUdpMsgSender->Start(m_UdpSock, false);


	/* ���� �ʱ�ȭ */
	m_isEnd = false;


	PushServerLog("#####################################���� ����#####################################");


	if(m_bOnInit)
		return m_OnOpen();


	return 0;
}


int cNetServer::Close()
{
	if(m_isEnd) return 0;


	int Result = (m_bOnInit ? m_OnClose() : 0);


	/* ���� �ݱ� */
	for(UINT i=0; i<m_ConnectedSockList.size(); i++)
	{
		closesocket(m_ConnectedSockList[i]);
	}

	closesocket(m_UdpSock);
	closesocket(m_Serv);

	
	/* �޼��� ������ ���� */
	for(UINT i=0; i<m_pMsgSenderList.size(); i++)
	{
		if(m_pMsgSenderList[i] == NULL) continue;


		m_pMsgSenderList[i]->Stop();
	}
	for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
	{
		if(m_pMsgReceiverList[i] == NULL) continue;


		m_pMsgReceiverList[i]->Stop();
	}
	
	m_pUdpMsgReceiver->Stop();
	m_pUdpMsgSender->Stop();
	
	m_isEnd = true;


	/* WSA ���� */
	WSACleanup();


	PushServerLog("#####################################���� ����#####################################\n");


	return Result;
}



int cNetServer::ClntConnect(SOCKET Clnt, int Id)
{
	// ������ ���� �� ����
	assert(m_pMsgReceiverList.size() == m_pMsgSenderList.size());

	UINT uId = static_cast<UINT>(Id);

	while(uId >= m_pMsgReceiverList.size()) m_pMsgReceiverList.push_back(NULL);
	while(uId >= m_pMsgSenderList.size()) m_pMsgSenderList.push_back(NULL);

	assert(m_pMsgReceiverList[Id] == NULL  &&  m_pMsgSenderList[Id] == NULL);

	m_pMsgReceiverList[Id] = new cMessageReceiver();
	m_pMsgSenderList[Id] = new cMessageSender();

	m_pMsgReceiverList[Id]->Start(Clnt);
	m_pMsgSenderList[Id]->Start(Clnt);


	PushServerLog("Ŭ���̾�Ʈ %d �����", Id);


	if(m_bOnInit)
		return m_OnClntConnect(Id);


	return 0;
}


int cNetServer::ClntClose(int Id)
{
	int Result = (m_bOnInit ? m_OnClntClose(Id) : 0);


	// ������ ���� �� ����
	assert(static_cast<UINT>(Id) < m_pMsgReceiverList.size()  &&  static_cast<UINT>(Id) < m_pMsgSenderList.size());

	m_pMsgReceiverList[Id]->Stop();
	m_pMsgSenderList[Id]->Stop();

	delete m_pMsgReceiverList[Id]; m_pMsgReceiverList[Id] = NULL; // NOTE: NULL�� ����ִ� �۾��� �߿���
	delete m_pMsgSenderList[Id]; m_pMsgSenderList[Id] = NULL;


	PushServerLog("Ŭ���̾�Ʈ %d ����������", Id);


	return Result;
}



int cNetServer::ReceiveMsg(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	UINT32 MsgType = pMsg->Header->MsgType;

	if(MsgType == NetMsgType::RQ_LoginUser)
	{// �α��� ��û
		RecvLoginRQ(Sock, Id, pMsg);
	}
	else if(MsgType == NetMsgType::RQ_RegisterUser)
	{// ȸ������ ��û
		RecvRegisterRQ(Sock, Id, pMsg);
	}
	else if(MsgType == NetMsgType::RQ_ChatMsg)
	{
		RecvChatMsgRQ(Sock, Id, pMsg);
	}
	else if(MsgType < m_RecvProcFuncList.size()  &&  m_RecvProcFuncList[MsgType] != NULL)
	{
		// ���� �޽����� ó��
		cNetMessage* pSendMsg = m_RecvProcFuncList[MsgType](pMsg, Id);

		// ���� ����
		if(pSendMsg != NULL)
		{
			if(static_cast<UINT>(Id) < m_pMsgSenderList.size())
			{
				m_pMsgSenderList[Id]->PushSendMsg(pSendMsg);
			}
			else
			{
				delete pSendMsg;
				pSendMsg = NULL;
			}
		}
	}


	int Result = (m_bOnInit ? m_OnReceiveMsg(pMsg, Id) : 0);


	delete pMsg;
	return Result;
}


int cNetServer::ReceiveUdpMsg(const SOCKADDR_IN* pAdr, cNetMessage* pMsg)
{
	UINT32 MsgType = pMsg->Header->MsgType;

	if(MsgType == NetMsgType::RQ_SygnVal_Info)
	{// ����ȭ
		cBinaryReader br(pMsg);

		int sygnMgrIdx = br.Read<int>();

		if(static_cast<unsigned int>(sygnMgrIdx) < m_pSygnMgrList.size())
		{
			if(m_pSygnMgrList[sygnMgrIdx] != nullptr)
			{
				m_pSygnMgrList[sygnMgrIdx]->Recv(pMsg, pAdr);
			}
		}
	}
	else if(MsgType < m_RecvProcFuncList.size()  &&  m_RecvProcFuncList[MsgType] != NULL)
	{
		// ���� �޽����� ó��
		cNetMessage* pSendMsg = m_RecvProcFuncList[MsgType](pMsg, -1);

		// ���� ����ť�� ����
		if(pSendMsg != NULL)
		{
			m_pUdpMsgSender->PushUdpSendMsg(pSendMsg, pAdr);
		}
	}


	int Result = (m_bOnInit ? m_OnReceiveUdpMsg(pAdr, pMsg) : 0);


	delete pMsg;
	return Result;
}



int cNetServer::Update()
{
	if(m_isEnd == false)
	{// ������ ����������
		if(m_pUdpMsgReceiver->isEnd())
		{// ���������� ������ ����
			Close();
		}


		/* ��Ƽ�÷��� */
		m_CpyReads = m_Reads;
		TIMEVAL TimeOut = m_TimeOut;


		int fdNum = select(0, &m_CpyReads, 0, 0, &TimeOut);

		if(fdNum == SOCKET_ERROR)
			return -1;


		if(fdNum > 0)
		{// ���� ��ũ���Ϳ� ��ȭ ����
			for(u_int i=0; i<m_Reads.fd_count; i++)
			{
				if(FD_ISSET(m_Reads.fd_array[i], &m_CpyReads))
				{
					if(m_Reads.fd_array[i] == m_Serv)
					{// �����û ����
						SOCKADDR_IN ClntAdr;
						int adrSz = sizeof(ClntAdr);
						SOCKET Clnt = accept(m_Serv, (SOCKADDR*)&ClntAdr, &adrSz);
						FD_SET(Clnt, &m_Reads);

						
						// ���̵� ����
						bool bFind = false;

						for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
						{
							if(m_pMsgReceiverList[i] == NULL)
							{// ����� ������ �ű⸦ ��
								m_ClntId[Clnt] = i;
								m_ClntSock[i] = Clnt;
								bFind = true;

								break;
							}
						}

						if(bFind == false)
						{// ����� ������ ���� ����� ��
							int idx = static_cast<int>(m_pMsgReceiverList.size());

							m_ClntId[Clnt] = idx;
							m_ClntSock[idx] = Clnt;
						}


						// ����� ���� ��Ͽ� �߰�
						m_ConnectedSockList.push_back(Clnt);


						// ����ó�� (������ ���� ���)
						ClntConnect(Clnt, m_ClntId[Clnt]);
					}
					else
					{// ���� ����
						int Id = m_ClntId[m_Reads.fd_array[i]];

						
						assert(m_pMsgReceiverList[Id] != NULL);


						if(m_pMsgReceiverList[Id]->isEnd())
						{// Ŭ�������� ������ ����
							// ���̵� ���� �� ���� �α׾ƿ�
							if(m_bOnInit)
								m_OnUserLogout(Id);

							std::wstring userID = m_UserIdBySock[m_Reads.fd_array[i]];

							m_ClntId.erase(m_Reads.fd_array[i]);
							m_ClntSock.erase(Id);
							m_UserIdBySock.erase(m_Reads.fd_array[i]);
							m_bConnectedUserList.erase(userID);


							// ����� ���� ��Ͽ��� ����
							for(UINT cs=0; cs<m_ConnectedSockList.size(); cs++)
							{
								if(m_ConnectedSockList[cs] == m_Reads.fd_array[i])
								{
									m_ConnectedSockList.erase(m_ConnectedSockList.begin() + cs);
									break;
								}
							}


							// ��������ó�� (������ ���� ���)
							closesocket(m_CpyReads.fd_array[i]);
							ClntClose(Id);


							FD_CLR(m_Reads.fd_array[i], &m_Reads);
						}
						else if(m_pMsgReceiverList[Id]->QueSize() > 0)
						{// ���Ÿ޽��� ����
							cNetMessage* pMsg = m_pMsgReceiverList[Id]->Enqueue();

							ReceiveMsg(m_Reads.fd_array[i], Id, pMsg); // �޽��� ó�� �� ���� ����
						}
					}
				} // if(FD_ISSET(m_Reads.fd_array[i], &m_CpyReads))
			} // for(int i=0; i<m_Reads.fd_count; i++)
		} // if(fdNum > 0)


		/* ���� �޽��� ť ó�� */
		for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
		{
			if(m_pMsgReceiverList[i] == NULL) continue;


			if(m_pMsgReceiverList[i]->QueSize() > 0)
			{// ���Ÿ޽��� ����
				cNetMessage* pMsg = m_pMsgReceiverList[i]->Enqueue();

				ReceiveMsg(m_ClntSock[i], i, pMsg); // �޽��� ó�� �� ���� ����
			}
		}


		// ���ŵ� UDP �޼��� ó��
		UINT QueSize = min(m_pUdpMsgReceiver->QueSize(), m_pUdpMsgReceiver->AdrQueSize());
		// if(QueSize > m_pMsgReceiverList.size()) QueSize = m_pMsgReceiverList.size(); // FIX: �̰� �־ UDP �޼��� ó���� ������

		while(QueSize > 0)
		{// UDP ���� �޽��� ����
			QueSize--;

			cNetMessage* pMsg = m_pUdpMsgReceiver->Enqueue();
			SOCKADDR_IN Adr = m_pUdpMsgReceiver->AdrEnqueue();

			
			ReceiveUdpMsg(&Adr, pMsg);
		}


		// ���ŵ� UDP �޼����� �������� �̻��� �Ǹ� ������������ ���
		QueSize = min(m_pUdpMsgReceiver->QueSize(), m_pUdpMsgReceiver->AdrQueSize());

		while(QueSize > 100)
		{
			QueSize--;

			m_pUdpMsgReceiver->Enqueue();
			m_pUdpMsgReceiver->AdrEnqueue();
		}
	}


	// Ǫ�ø޼��� �Ŵ���
	m_pPushMsgMgr->Update();


	if(m_bOnInit)
		return m_OnUpdate();
	return 0;
}


int cNetServer::Render()
{
	Util::ShowText("RecvBuffer : %d", 820.f, 32.f, 0xffffffff, m_pUdpMsgReceiver->QueSize());
	Util::ShowText("SendBuffer : %d", 820.f, 64.f, 0xffffffff, m_pUdpMsgSender->QueSize());


	Util::ShowText("���ӵ� Ŭ���̾�Ʈ �� : %d", 460.f, 32.f, 0xffffffff,
		m_ConnectedSockList.size());

	for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
	{
		if(m_pMsgReceiverList[i] == nullptr)
		{
			Util::ShowText("Ŭ��(%d) : NULL", 460.f, 64.f + CAST(32*i, float), 0xffffffff,
				i);
		}
		else
		{
			SOCKET clntSock = m_ClntSock[i];

			std::string userID;
			Util::WStrToStr(m_UserIdBySock[clntSock], &userID);

			Util::ShowText("Ŭ��(%d) : ���̵�=\"%s\" %s", 460.f, 64.f + CAST(32*i, float), 0xffffffff,
				i, userID.c_str(), (UserOnline(m_UserIdBySock[clntSock]) ? "�α���" : "�α׾ƿ�"));
		}
	}


	// Ǫ�ø޼��� �Ŵ���
	m_pPushMsgMgr->Render();


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::AddSygnVal(int ValType, cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size())
	{
		while(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


		m_pSygnMgrList[ValType] = new cServerSygnMgr(m_pUdpMsgSender);
	}
	else if(m_pSygnMgrList[ValType] == nullptr)
	{
		m_pSygnMgrList[ValType] = new cServerSygnMgr(m_pUdpMsgSender);
	}


	return m_pSygnMgrList[ValType]->AddSygnVal(pSygnVal);
}


int cNetServer::SetSygnVal(int ValType, int idx, cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size())
	{
		while(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()) m_pSygnMgrList.push_back(nullptr);


		m_pSygnMgrList[ValType] = new cServerSygnMgr(m_pUdpMsgSender);
	}
	else if(m_pSygnMgrList[ValType] == nullptr)
	{
		m_pSygnMgrList[ValType] = new cServerSygnMgr(m_pUdpMsgSender);
	}


	return m_pSygnMgrList[ValType]->SetSygnVal(pSygnVal, idx);
}


int cNetServer::RemoveSygnVal(int ValType, const cSygnVal* pSygnVal)
{
	if(static_cast<unsigned int>(ValType) >= m_pSygnMgrList.size()
		||
		m_pSygnMgrList[ValType] == nullptr) return -1;


	return m_pSygnMgrList[ValType]->RemoveSygnVal(pSygnVal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::PushSendMsgToAll(cNetMessage* pMsg)
{
	if(pMsg == nullptr) return -1;


	for(UINT i=0; i<m_pMsgSenderList.size(); i++)
	{
		if(m_pMsgSenderList[i] == NULL) continue;


		m_pMsgSenderList[i]->PushSendMsg(new cNetMessage(pMsg));
	}


	delete pMsg; pMsg = nullptr;


	return 0;
}


int cNetServer::SendPushMsg(int id, std::wstring msg, DWORD color)
{
	if(static_cast<unsigned int>(id) >= m_pMsgSenderList.size()
		||
		m_pMsgSenderList[id] == nullptr) return -1;


	cBinaryWriter bw;

	bw.Write(msg.c_str());
	bw.Write(color);


	m_pMsgSenderList[id]->PushSendMsg(NetMsgUtil::MakeMessage(NetMsgType::NF_PushMsg, &bw));


	return 0;
}


int cNetServer::SendPushMsgToAll(std::wstring msg, DWORD color)
{
	cBinaryWriter bw;

	bw.Write(msg.c_str());
	bw.Write(color);


	PushSendMsgToAll(NetMsgUtil::MakeMessage(NetMsgType::NF_PushMsg, &bw));


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::Init(std::function<int(void)> OnOpen,
					 std::function<int(void)> OnClose,

					 std::function<int(int)> OnClntConnect,
					 std::function<int(int)> OnClntClose,

					 std::function<int(cNetMessage*, int)> OnReceiveMsg,
					 std::function<int(const SOCKADDR_IN*, cNetMessage*)> OnReceiveUdpMsg,

					 std::function<int(void)> OnUpdate,

					 std::function<int(int)> OnUserLogin,
					 std::function<int(int)> OnUserLogout)
{
	m_bOnInit = true;


	m_OnOpen = OnOpen;
	m_OnClose = OnClose;

	m_OnClntConnect = OnClntConnect;
	m_OnClntClose = OnClntClose;

	m_OnReceiveMsg = OnReceiveMsg;
	m_OnReceiveUdpMsg = OnReceiveUdpMsg;

	m_OnUpdate = OnUpdate;

	m_OnUserLogin = OnUserLogin;
	m_OnUserLogout = OnUserLogout;


	return 0;
}



int cNetServer::AddRecvProcFunc(int index, std::function<cNetMessage* _SERV_FUNC_TYPE_> RecvProcFunc)
{
	while(m_RecvProcFuncList.size() < static_cast<UINT>(index))
		m_RecvProcFuncList.emplace_back();

	m_RecvProcFuncList.emplace_back(RecvProcFunc);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cNetServer::isEnd() const
{
	return m_isEnd;
}


bool cNetServer::IdCheck(int Id) const
{
	return (static_cast<UINT>(Id) < m_pMsgReceiverList.size()  &&  m_pMsgReceiverList[Id] != NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cNetServer::UserOnline(const std::wstring& userId)
{
	return (m_bConnectedUserList[userId]);
}


int cNetServer::GetUserNameByClntId(int clntId, std::wstring* pOut)
{
	*pOut = m_UserIdBySock[m_ClntSock[clntId]];


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::PushServerLog(const char format[], ...)
{
	va_list vlist;
	va_start(vlist, format); //������ ���� �ּ� ����


	char buffer[1024];
	vsprintf_s(buffer, 1023, format, vlist);


	Util::Log(buffer);

	std::ofstream outFile("Data/Server/Log.txt", std::ios::app);

	if(outFile.is_open())
	{
		outFile << buffer << std::endl;


		outFile.close();
	}
	else
	{
		std::ofstream outFile2("Data/Server/Log.txt");

		if(outFile2.is_open())
		{
			outFile2 << buffer << std::endl;


			outFile2.close();
		}
	}


	va_end(vlist);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetServer::RecvLoginRQ(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	// �α������� ����
	cBinaryReader br(pMsg);

	std::wstring userID, userPwd;

	br.ReadString(&userID);
	br.ReadString(&userPwd);


	std::string tempUserID;
	Util::WStrToStr(userID, &tempUserID);


	// ���� Ȯ��
	int loginResult = -999;

	std::ifstream inFile(TEXT("Data/Server/User/") + userID);

	if(inFile.is_open())
	{// ���̵� ����
		char buf[1024];
		inFile.getline(buf, 1023);

		inFile.close();


		std::wstring correctPwd;
		Util::StrToWStr(buf, &correctPwd);

		if(lstrcmpW(userPwd.c_str(), correctPwd.c_str()) == 0)
		{// ��й�ȣ ����
			if(UserOnline(userID))
			{// �̹� �α��� �Ǿ� ����
				loginResult = -3;


				PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" �α��� ���� (���� : �̹� �α��ε� ����)",
					Id, tempUserID.c_str());
			}
			else
			{// �α��� ����
				m_bConnectedUserList[userID] = true;
				m_UserIdBySock[Sock] = userID;


				if(m_bOnInit)
					m_OnUserLogin(Id);


				loginResult = 0;


				PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" �α��� ����",
					Id, tempUserID.c_str());
			}
		}
		else
		{// ��й�ȣ Ʋ��
			loginResult = -1;


			PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" �α��� ���� (���� : �߸��� ��й�ȣ)",
				Id, tempUserID.c_str());
		}
	}
	else
	{// ���̵� ����
		loginResult = -2;


		PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" �α��� ���� (���� : ���� ����)",
			Id, tempUserID.c_str());
	}


	// ��� ����
	cBinaryWriter bw;

	bw.Write(loginResult);

	m_pMsgSenderList[Id]->PushSendMsg(NetMsgUtil::MakeMessage(NetMsgType::RP_LoginUser, &bw));


	return 0;
}


int cNetServer::RecvRegisterRQ(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	// ȸ���������� ����
	cBinaryReader br(pMsg);

	std::wstring userID, userPwd;

	br.ReadString(&userID);
	br.ReadString(&userPwd);


	std::string tempUserID;
	Util::WStrToStr(userID, &tempUserID);


	// ���� �ߺ� Ȯ��
	int registerResult = -999;

	std::ifstream inFile(TEXT("Data/Server/User/") + userID);

	if(inFile.is_open())
	{// ���̵� �̹� ����
		inFile.close();


		registerResult = -3;


		PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" ȸ������ ���� (���� : ���̵� �ߺ�)",
			Id, tempUserID.c_str());
	}
	else
	{// ���� ����
		std::ofstream outFile(TEXT("Data/Server/User/") + userID);

		if(outFile.is_open())
		{
			std::string tempPwd;
			Util::WStrToStr(userPwd, &tempPwd);

			outFile << tempPwd.c_str();


			registerResult = 0;


			PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" ȸ������ ����",
				Id, tempUserID.c_str());
		}
		else
		{// ���̵� ��ȿ���� �ʰų� ������ ����
			registerResult = -999;


			PushServerLog("Ŭ���̾�Ʈ %d : \"%s\" ȸ������ ���� (���� : ���̵� ���ϻ����� ��ȿ���� �ʰų� �� �� ���� ����)",
				Id, tempUserID.c_str());
		}
	}


	// ��� ����
	cBinaryWriter bw;

	bw.Write(registerResult);

	m_pMsgSenderList[Id]->PushSendMsg(NetMsgUtil::MakeMessage(NetMsgType::RP_RegisterUser, &bw));


	return 0;
}


int cNetServer::RecvChatMsgRQ(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	// ���� �޼��� �б�
	cBinaryReader br(pMsg);

	std::wstring userName, chatMsg;

	br.ReadString(&userName);
	br.ReadString(&chatMsg);


	// ������ ä�� �޼��� ����
	wchar_t tempBuf[2048];
	wsprintf(tempBuf, TEXT("%s :  %s"), userName.c_str(), chatMsg.c_str());
	std::wstring finalMsg(tempBuf);

	cBinaryWriter bw;

	bw.Write(finalMsg.c_str());


	// ���� �ڽſ��Ե� ������
	m_pPushMsgMgr->PushChatMsg(finalMsg);


	// ��ο��� �Ѹ�
	PushSendMsgToAll(NetMsgUtil::MakeMessage(NetMsgType::RP_ChatMsg, &bw));


	return 0;
}

