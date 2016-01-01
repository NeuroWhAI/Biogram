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
	/* WSA 초기화 */
	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 )
	{
		PushServerLog("WSA초기화 실패");
		return -1;
	}


	/* 소켓 생성 */
	m_Serv = socket(PF_INET, SOCK_STREAM, 0);
	if(m_Serv == INVALID_SOCKET)
	{
		PushServerLog("서버소켓 생성 실패");
		return -2;
	}

	memset(&m_ServAdr, 0, sizeof(m_ServAdr));
	m_ServAdr.sin_family = AF_INET;
	m_ServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_ServAdr.sin_port= htons(atoi(Port));

	// NOTE: thread.h에도 std::bind가 있기때문에 WinSock2.h의 bind를 호출하려면 ::bind로 해줘야한다.
	if( ::bind(m_Serv, (SOCKADDR*)&m_ServAdr, sizeof(m_ServAdr)) == SOCKET_ERROR )
	{
		PushServerLog("서버소켓 bind실패");
		return -3;
	}

	if( listen(m_Serv, 5) == SOCKET_ERROR )
	{
		PushServerLog("서버소켓 listen실패");
		return -4;
	}

	FD_ZERO(&m_Reads);
	FD_SET(m_Serv, &m_Reads);


	const int Delay_ms = 10;
	m_TimeOut.tv_sec= Delay_ms/1000;
	m_TimeOut.tv_usec = Delay_ms%1000;


	/* UDP 소켓 생성 */
	m_UdpSock = socket(PF_INET, SOCK_DGRAM, 0);
	if(m_UdpSock == INVALID_SOCKET)
	{
		PushServerLog("UDP소켓 생성 실패");
		return -5;
	}

	memset(&m_UdpServAdr, 0, sizeof(m_UdpServAdr));
	m_UdpServAdr.sin_family = AF_INET;
	m_UdpServAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_UdpServAdr.sin_port = htons(atoi(UdpPort));

	if( ::bind(m_UdpSock, (SOCKADDR*)&m_UdpServAdr, sizeof(m_UdpServAdr)) == SOCKET_ERROR )
	{
		PushServerLog("UDP소켓 bind 실패");
		return -6;
	}


	/* UDP 메세지 리스너 시작 */
	m_pUdpMsgReceiver->Start(m_UdpSock, false);
	m_pUdpMsgSender->Start(m_UdpSock, false);


	/* 정보 초기화 */
	m_isEnd = false;


	PushServerLog("#####################################서버 열림#####################################");


	if(m_bOnInit)
		return m_OnOpen();


	return 0;
}


int cNetServer::Close()
{
	if(m_isEnd) return 0;


	int Result = (m_bOnInit ? m_OnClose() : 0);


	/* 소켓 닫기 */
	for(UINT i=0; i<m_ConnectedSockList.size(); i++)
	{
		closesocket(m_ConnectedSockList[i]);
	}

	closesocket(m_UdpSock);
	closesocket(m_Serv);

	
	/* 메세지 리스너 중지 */
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


	/* WSA 제거 */
	WSACleanup();


	PushServerLog("#####################################서버 종료#####################################\n");


	return Result;
}



int cNetServer::ClntConnect(SOCKET Clnt, int Id)
{
	// 리스너 생성 및 시작
	assert(m_pMsgReceiverList.size() == m_pMsgSenderList.size());

	UINT uId = static_cast<UINT>(Id);

	while(uId >= m_pMsgReceiverList.size()) m_pMsgReceiverList.push_back(NULL);
	while(uId >= m_pMsgSenderList.size()) m_pMsgSenderList.push_back(NULL);

	assert(m_pMsgReceiverList[Id] == NULL  &&  m_pMsgSenderList[Id] == NULL);

	m_pMsgReceiverList[Id] = new cMessageReceiver();
	m_pMsgSenderList[Id] = new cMessageSender();

	m_pMsgReceiverList[Id]->Start(Clnt);
	m_pMsgSenderList[Id]->Start(Clnt);


	PushServerLog("클라이언트 %d 연결됨", Id);


	if(m_bOnInit)
		return m_OnClntConnect(Id);


	return 0;
}


int cNetServer::ClntClose(int Id)
{
	int Result = (m_bOnInit ? m_OnClntClose(Id) : 0);


	// 리스너 종료 및 제거
	assert(static_cast<UINT>(Id) < m_pMsgReceiverList.size()  &&  static_cast<UINT>(Id) < m_pMsgSenderList.size());

	m_pMsgReceiverList[Id]->Stop();
	m_pMsgSenderList[Id]->Stop();

	delete m_pMsgReceiverList[Id]; m_pMsgReceiverList[Id] = NULL; // NOTE: NULL로 비워주는 작업은 중요함
	delete m_pMsgSenderList[Id]; m_pMsgSenderList[Id] = NULL;


	PushServerLog("클라이언트 %d 연결해제됨", Id);


	return Result;
}



int cNetServer::ReceiveMsg(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	UINT32 MsgType = pMsg->Header->MsgType;

	if(MsgType == NetMsgType::RQ_LoginUser)
	{// 로그인 요청
		RecvLoginRQ(Sock, Id, pMsg);
	}
	else if(MsgType == NetMsgType::RQ_RegisterUser)
	{// 회원가입 요청
		RecvRegisterRQ(Sock, Id, pMsg);
	}
	else if(MsgType == NetMsgType::RQ_ChatMsg)
	{
		RecvChatMsgRQ(Sock, Id, pMsg);
	}
	else if(MsgType < m_RecvProcFuncList.size()  &&  m_RecvProcFuncList[MsgType] != NULL)
	{
		// 받은 메시지로 처리
		cNetMessage* pSendMsg = m_RecvProcFuncList[MsgType](pMsg, Id);

		// 응답 전송
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
	{// 동기화
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
		// 받은 메시지로 처리
		cNetMessage* pSendMsg = m_RecvProcFuncList[MsgType](pMsg, -1);

		// 응답 전송큐에 넣음
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
	{// 소켓이 열려있을때
		if(m_pUdpMsgReceiver->isEnd())
		{// 서버측에서 연결을 끊음
			Close();
		}


		/* 멀티플렉싱 */
		m_CpyReads = m_Reads;
		TIMEVAL TimeOut = m_TimeOut;


		int fdNum = select(0, &m_CpyReads, 0, 0, &TimeOut);

		if(fdNum == SOCKET_ERROR)
			return -1;


		if(fdNum > 0)
		{// 파일 디스크립터에 변화 있음
			for(u_int i=0; i<m_Reads.fd_count; i++)
			{
				if(FD_ISSET(m_Reads.fd_array[i], &m_CpyReads))
				{
					if(m_Reads.fd_array[i] == m_Serv)
					{// 연결요청 있음
						SOCKADDR_IN ClntAdr;
						int adrSz = sizeof(ClntAdr);
						SOCKET Clnt = accept(m_Serv, (SOCKADDR*)&ClntAdr, &adrSz);
						FD_SET(Clnt, &m_Reads);

						
						// 아이디 생성
						bool bFind = false;

						for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
						{
							if(m_pMsgReceiverList[i] == NULL)
							{// 빈공간 있으면 거기를 씀
								m_ClntId[Clnt] = i;
								m_ClntSock[i] = Clnt;
								bFind = true;

								break;
							}
						}

						if(bFind == false)
						{// 빈공간 없으면 새로 만들게 함
							int idx = static_cast<int>(m_pMsgReceiverList.size());

							m_ClntId[Clnt] = idx;
							m_ClntSock[idx] = Clnt;
						}


						// 연결된 소켓 목록에 추가
						m_ConnectedSockList.push_back(Clnt);


						// 연결처리 (리스너 생성 등등)
						ClntConnect(Clnt, m_ClntId[Clnt]);
					}
					else
					{// 수신 있음
						int Id = m_ClntId[m_Reads.fd_array[i]];

						
						assert(m_pMsgReceiverList[Id] != NULL);


						if(m_pMsgReceiverList[Id]->isEnd())
						{// 클라측에서 연결을 끊음
							// 아이디 제거 및 유저 로그아웃
							if(m_bOnInit)
								m_OnUserLogout(Id);

							std::wstring userID = m_UserIdBySock[m_Reads.fd_array[i]];

							m_ClntId.erase(m_Reads.fd_array[i]);
							m_ClntSock.erase(Id);
							m_UserIdBySock.erase(m_Reads.fd_array[i]);
							m_bConnectedUserList.erase(userID);


							// 연결된 소켓 목록에서 제거
							for(UINT cs=0; cs<m_ConnectedSockList.size(); cs++)
							{
								if(m_ConnectedSockList[cs] == m_Reads.fd_array[i])
								{
									m_ConnectedSockList.erase(m_ConnectedSockList.begin() + cs);
									break;
								}
							}


							// 연결해제처리 (리스너 제거 등등)
							closesocket(m_CpyReads.fd_array[i]);
							ClntClose(Id);


							FD_CLR(m_Reads.fd_array[i], &m_Reads);
						}
						else if(m_pMsgReceiverList[Id]->QueSize() > 0)
						{// 수신메시지 있음
							cNetMessage* pMsg = m_pMsgReceiverList[Id]->Enqueue();

							ReceiveMsg(m_Reads.fd_array[i], Id, pMsg); // 메시지 처리 및 응답 전송
						}
					}
				} // if(FD_ISSET(m_Reads.fd_array[i], &m_CpyReads))
			} // for(int i=0; i<m_Reads.fd_count; i++)
		} // if(fdNum > 0)


		/* 수신 메시지 큐 처리 */
		for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
		{
			if(m_pMsgReceiverList[i] == NULL) continue;


			if(m_pMsgReceiverList[i]->QueSize() > 0)
			{// 수신메시지 있음
				cNetMessage* pMsg = m_pMsgReceiverList[i]->Enqueue();

				ReceiveMsg(m_ClntSock[i], i, pMsg); // 메시지 처리 및 응답 전송
			}
		}


		// 수신된 UDP 메세지 처리
		UINT QueSize = min(m_pUdpMsgReceiver->QueSize(), m_pUdpMsgReceiver->AdrQueSize());
		// if(QueSize > m_pMsgReceiverList.size()) QueSize = m_pMsgReceiverList.size(); // FIX: 이게 있어서 UDP 메세지 처리가 지연됨

		while(QueSize > 0)
		{// UDP 수신 메시지 있음
			QueSize--;

			cNetMessage* pMsg = m_pUdpMsgReceiver->Enqueue();
			SOCKADDR_IN Adr = m_pUdpMsgReceiver->AdrEnqueue();

			
			ReceiveUdpMsg(&Adr, pMsg);
		}


		// 수신된 UDP 메세지가 일정갯수 이상이 되면 일정갯수까지 비움
		QueSize = min(m_pUdpMsgReceiver->QueSize(), m_pUdpMsgReceiver->AdrQueSize());

		while(QueSize > 100)
		{
			QueSize--;

			m_pUdpMsgReceiver->Enqueue();
			m_pUdpMsgReceiver->AdrEnqueue();
		}
	}


	// 푸시메세지 매니저
	m_pPushMsgMgr->Update();


	if(m_bOnInit)
		return m_OnUpdate();
	return 0;
}


int cNetServer::Render()
{
	Util::ShowText("RecvBuffer : %d", 820.f, 32.f, 0xffffffff, m_pUdpMsgReceiver->QueSize());
	Util::ShowText("SendBuffer : %d", 820.f, 64.f, 0xffffffff, m_pUdpMsgSender->QueSize());


	Util::ShowText("접속된 클라이언트 수 : %d", 460.f, 32.f, 0xffffffff,
		m_ConnectedSockList.size());

	for(UINT i=0; i<m_pMsgReceiverList.size(); i++)
	{
		if(m_pMsgReceiverList[i] == nullptr)
		{
			Util::ShowText("클라(%d) : NULL", 460.f, 64.f + CAST(32*i, float), 0xffffffff,
				i);
		}
		else
		{
			SOCKET clntSock = m_ClntSock[i];

			std::string userID;
			Util::WStrToStr(m_UserIdBySock[clntSock], &userID);

			Util::ShowText("클라(%d) : 아이디=\"%s\" %s", 460.f, 64.f + CAST(32*i, float), 0xffffffff,
				i, userID.c_str(), (UserOnline(m_UserIdBySock[clntSock]) ? "로그인" : "로그아웃"));
		}
	}


	// 푸시메세지 매니저
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
	va_start(vlist, format); //인자의 시작 주소 설정


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
	// 로그인정보 추출
	cBinaryReader br(pMsg);

	std::wstring userID, userPwd;

	br.ReadString(&userID);
	br.ReadString(&userPwd);


	std::string tempUserID;
	Util::WStrToStr(userID, &tempUserID);


	// 계정 확인
	int loginResult = -999;

	std::ifstream inFile(TEXT("Data/Server/User/") + userID);

	if(inFile.is_open())
	{// 아이디 있음
		char buf[1024];
		inFile.getline(buf, 1023);

		inFile.close();


		std::wstring correctPwd;
		Util::StrToWStr(buf, &correctPwd);

		if(lstrcmpW(userPwd.c_str(), correctPwd.c_str()) == 0)
		{// 비밀번호 맞음
			if(UserOnline(userID))
			{// 이미 로그인 되어 있음
				loginResult = -3;


				PushServerLog("클라이언트 %d : \"%s\" 로그인 실패 (사유 : 이미 로그인된 계정)",
					Id, tempUserID.c_str());
			}
			else
			{// 로그인 성공
				m_bConnectedUserList[userID] = true;
				m_UserIdBySock[Sock] = userID;


				if(m_bOnInit)
					m_OnUserLogin(Id);


				loginResult = 0;


				PushServerLog("클라이언트 %d : \"%s\" 로그인 성공",
					Id, tempUserID.c_str());
			}
		}
		else
		{// 비밀번호 틀림
			loginResult = -1;


			PushServerLog("클라이언트 %d : \"%s\" 로그인 실패 (사유 : 잘못된 비밀번호)",
				Id, tempUserID.c_str());
		}
	}
	else
	{// 아이디 없음
		loginResult = -2;


		PushServerLog("클라이언트 %d : \"%s\" 로그인 실패 (사유 : 없는 계정)",
			Id, tempUserID.c_str());
	}


	// 결과 전송
	cBinaryWriter bw;

	bw.Write(loginResult);

	m_pMsgSenderList[Id]->PushSendMsg(NetMsgUtil::MakeMessage(NetMsgType::RP_LoginUser, &bw));


	return 0;
}


int cNetServer::RecvRegisterRQ(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	// 회원가입정보 추출
	cBinaryReader br(pMsg);

	std::wstring userID, userPwd;

	br.ReadString(&userID);
	br.ReadString(&userPwd);


	std::string tempUserID;
	Util::WStrToStr(userID, &tempUserID);


	// 계정 중복 확인
	int registerResult = -999;

	std::ifstream inFile(TEXT("Data/Server/User/") + userID);

	if(inFile.is_open())
	{// 아이디가 이미 있음
		inFile.close();


		registerResult = -3;


		PushServerLog("클라이언트 %d : \"%s\" 회원가입 실패 (사유 : 아이디 중복)",
			Id, tempUserID.c_str());
	}
	else
	{// 계정 생성
		std::ofstream outFile(TEXT("Data/Server/User/") + userID);

		if(outFile.is_open())
		{
			std::string tempPwd;
			Util::WStrToStr(userPwd, &tempPwd);

			outFile << tempPwd.c_str();


			registerResult = 0;


			PushServerLog("클라이언트 %d : \"%s\" 회원가입 성공",
				Id, tempUserID.c_str());
		}
		else
		{// 아이디가 유효하지 않거나 서버측 문제
			registerResult = -999;


			PushServerLog("클라이언트 %d : \"%s\" 회원가입 실패 (사유 : 아이디가 파일생성에 유효하지 않거나 알 수 없는 예외)",
				Id, tempUserID.c_str());
		}
	}


	// 결과 전송
	cBinaryWriter bw;

	bw.Write(registerResult);

	m_pMsgSenderList[Id]->PushSendMsg(NetMsgUtil::MakeMessage(NetMsgType::RP_RegisterUser, &bw));


	return 0;
}


int cNetServer::RecvChatMsgRQ(SOCKET Sock, int Id, cNetMessage* pMsg)
{
	// 수신 메세지 읽기
	cBinaryReader br(pMsg);

	std::wstring userName, chatMsg;

	br.ReadString(&userName);
	br.ReadString(&chatMsg);


	// 보여줄 채팅 메세지 생성
	wchar_t tempBuf[2048];
	wsprintf(tempBuf, TEXT("%s :  %s"), userName.c_str(), chatMsg.c_str());
	std::wstring finalMsg(tempBuf);

	cBinaryWriter bw;

	bw.Write(finalMsg.c_str());


	// 서버 자신에게도 보여줌
	m_pPushMsgMgr->PushChatMsg(finalMsg);


	// 모두에게 뿌림
	PushSendMsgToAll(NetMsgUtil::MakeMessage(NetMsgType::RP_ChatMsg, &bw));


	return 0;
}

