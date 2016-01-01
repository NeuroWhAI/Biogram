#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>
#include <map>
#include <functional>

class cNetMessage;
class cMessageReceiver;
class cMessageSender;
class cServerSygnMgr;
class cNetPushMsgSender;
class cSygnVal;

#ifndef _SERV_FUNC_TYPE_
#define _SERV_FUNC_TYPE_ (cNetMessage* pMsg, int Id)
#endif

#ifndef LAMBDA_FUNC
#define LAMBDA_FUNC(Func) [&] () -> int {return (Func)();}
#endif


























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��Ʈ��ũ ����
// Desc : TCP/UDP ��Ƽ�÷��� �����Դϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetServer
{
public:
	cNetServer();
	virtual ~cNetServer();


private:
	bool m_bOnInit;					// Init�Լ��� ȣ��Ǿ��°�?


protected: /* TCP ��Ƽ�÷��� */
	SOCKET m_Serv;
	SOCKADDR_IN m_ServAdr;
	TIMEVAL m_TimeOut;
	fd_set m_Reads, m_CpyReads;
	bool m_isEnd;

	std::map<SOCKET, int> m_ClntId;
	std::map<int, SOCKET> m_ClntSock;
	std::vector<SOCKET> m_ConnectedSockList;
	std::map<SOCKET, std::wstring> m_UserIdBySock;
	std::map<std::wstring, bool> m_bConnectedUserList;


protected: /* UDP */
	SOCKET m_UdpSock;
	SOCKADDR_IN m_UdpServAdr;


protected:
	std::vector<cMessageReceiver*> m_pMsgReceiverList; // Enqueue()�� ����� �޼��� ����
	std::vector<cMessageSender*> m_pMsgSenderList; // PushSendMsg()�� ����� �޼��� ����


protected: /* UDP ���� �޼��� ������ */
	cMessageReceiver* m_pUdpMsgReceiver;
	cMessageSender* m_pUdpMsgSender;


protected:
	std::vector<std::function<cNetMessage* _SERV_FUNC_TYPE_>> m_RecvProcFuncList;


protected: /* ����ȭ */
	std::vector<cServerSygnMgr*> m_pSygnMgrList;


protected: /* �̺�Ʈ �Լ��� */
	std::function<int(void)> m_OnOpen;
	std::function<int(void)> m_OnClose;

	std::function<int(int)> m_OnClntConnect;
	std::function<int(int)> m_OnClntClose;

	std::function<int(cNetMessage*, int)> m_OnReceiveMsg;
	std::function<int(const SOCKADDR_IN*, cNetMessage*)> m_OnReceiveUdpMsg;

	std::function<int(void)> m_OnUpdate;

	std::function<int(int)> m_OnUserLogin;
	std::function<int(int)> m_OnUserLogout;


protected: /* Ǫ�ø޼��� �Ŵ��� */
	cNetPushMsgSender* m_pPushMsgMgr;


public:
	int Open(const char Port[], const char UdpPort[]);
	int Close();

	int ClntConnect(SOCKET Clnt, int Id);
	int ClntClose(int Id);

	int ReceiveMsg(SOCKET Sock, int Id, cNetMessage* pMsg);
	int ReceiveUdpMsg(const SOCKADDR_IN* pAdr, cNetMessage* pMsg);

	int Update();
	int Render();


public:
	int AddSygnVal(int ValType, cSygnVal* pSygnVal);
	int SetSygnVal(int ValType, int idx, cSygnVal* pSygnVal);
	int RemoveSygnVal(int ValType, const cSygnVal* pSygnVal);


public:
	int PushSendMsgToAll(cNetMessage* pMsg);
	int SendPushMsg(int id, std::wstring msg, DWORD color = 0xff000000);
	int SendPushMsgToAll(std::wstring msg, DWORD color = 0xff000000);


public:
	int Init(std::function<int(void)> OnOpen,
		std::function<int(void)> OnClose,

		std::function<int(int)> OnClntConnect,
		std::function<int(int)> OnClntClose,

		std::function<int(cNetMessage*, int)> OnReceiveMsg,
		std::function<int(const SOCKADDR_IN*, cNetMessage*)> OnReceiveUdpMsg,
		
		std::function<int(void)> OnUpdate,
		
		std::function<int(int)> OnUserLogin,
		std::function<int(int)> OnUserLogout);

	int AddRecvProcFunc(int index, std::function<cNetMessage* _SERV_FUNC_TYPE_> RecvProcFunc);


public:
	bool isEnd() const;
	bool IdCheck(int Id) const;


public:
	bool UserOnline(const std::wstring& userId);
	int GetUserNameByClntId(int clntId, std::wstring* pOut);


public:
	int PushServerLog(const char format[], ...);


private:
	int RecvLoginRQ(SOCKET Sock, int Id, cNetMessage* pMsg);
	int RecvRegisterRQ(SOCKET Sock, int Id, cNetMessage* pMsg);
	int RecvChatMsgRQ(SOCKET Sock, int Id, cNetMessage* pMsg);
};

