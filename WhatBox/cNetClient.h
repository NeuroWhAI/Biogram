#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>
#include <functional>

class cNetMessage;
class cMessageReceiver;
class cMessageSender;
class cClientSygnMgr;
class cBinaryReader;
class cSygnVal;
class cNetChating;

#ifndef _CLNT_FUNC_TYPE_
#define _CLNT_FUNC_TYPE_ (cNetMessage* pMsg)
#endif

#ifndef LAMBDA_FUNC
#define LAMBDA_FUNC(Func) [&] () -> int {return (Func)();}
#endif




























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��Ʈ��ũ Ŭ���̾�Ʈ
// Desc : TCP/UDP Ŭ���̾�Ʈ�Դϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetClient
{
public:
	cNetClient();
	virtual ~cNetClient();


private:
	bool m_bInitFunc;				// InitFunc�Լ��� ȣ��Ǿ��°�?


protected: /* TCP ���� */
	SOCKET m_Clnt;
	SOCKADDR_IN m_ClntAdr;
	bool m_isEnd;


protected: /* UDP ���� */
	 SOCKET m_UdpClnt;
	 SOCKADDR_IN m_UdpServAdr;


protected:
	cMessageReceiver* m_pMsgReceiver; // Enqueue()�� ����� �޼��� ����
	cMessageSender* m_pMsgSender; // PushSendMsg()�� ����� �޼��� ����


protected: /* UDP ���� �޼��� ������ */
	cMessageReceiver* m_pUdpMsgReceiver;
	cMessageSender* m_pUdpMsgSender;


protected:
	std::vector<std::function<int _CLNT_FUNC_TYPE_>> m_RecvProcFuncList;


protected: /*�������� Update, Render�Լ� ��� */
	int m_CurrUpdateFuncNum;

	std::vector<std::function<int(void)>> m_UpdateFuncList;
	std::vector<std::function<int(void)>> m_RenderFuncList;


protected: /* ����ȭ */
	std::vector<cClientSygnMgr*> m_pSygnMgrList;


protected: /* ���� ��ƾ �Լ��� */
	std::function<int(void)> m_OnConnect;
	std::function<int(void)> m_OnClose;

	std::function<int(cNetMessage*)> m_OnReceiveMsg;
		
	std::function<int(void)> m_OnUpdate;
	std::function<int(void)> m_OnRender;
		
	std::function<cSygnVal*(int, int)> m_OnCreateSygnVal;
	std::function<int(int, int)> m_OnDeleteSygnVal;


protected: /* ä�� */
	cNetChating* m_pNetChating;
	std::wstring m_userName;


public:
	int Connect(const char IP[], const char Port[], const char UdpPort[]);
	int Close();

	int ReceiveMsg(cNetMessage* pMsg);

	int Update();
	int Render();

	// ����ȭ�� SygnVal�� ����, �����ؾ� �Ҷ�
	int UpdateSygnVal(int ValType, std::vector<int>* pCreateIdxList, std::vector<int>* pDeleteIdxList);


public:
	int InitFunc(std::function<int(void)> OnConnect,
		std::function<int(void)> OnClose,

		std::function<int(cNetMessage*)> OnReceiveMsg,

		std::function<int(void)> OnUpdate,
		std::function<int(void)> OnRender,

		std::function<cSygnVal*(int valType, int idx)> OnCreateSygnVal,
		std::function<int(int valType, int idx)> OnDeleteSygnVal);
	int InitNetChating(std::wstring userName);
	int StopChating();


public:
	// ���� �޽��� ó���� �Լ� �߰�
	int AddRecvProcFunc(int index, std::function<int _CLNT_FUNC_TYPE_> Func);

	// �������� Update, Render�Լ� �߰�
	int AddUpdateFunc(int index, std::function<int(void)> UpdateFunc);
	int AddRenderFunc(int index, std::function<int(void)> RenderFunc);


public:
	int AddSygnVal(int ValType, cSygnVal* pSygnVal);
	int SetSygnVal(int ValType, int idx, cSygnVal* pSygnVal);
	int RemoveSygnVal(int ValType, const cSygnVal* pSygnVal);

	// �Ѱ��� ��ȣ�� �ش��ϴ� ����ȭ �Ŵ����� �����ؼ� �����մϴ�
	int ExtendSygnMgr(int ValType);


public:
	int PushMessage(cNetMessage* pMsg);
	int PushUdpMessage(cNetMessage* pMsg);


public:
	bool isEnd() const;


private:
	int RecvChatMsgRP(cNetMessage* pMsg);
	int RecvPushMsgNF(cNetMessage* pMsg);


public:
	int GetClntUserName(std::wstring* pOut);
};

