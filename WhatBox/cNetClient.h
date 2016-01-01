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
// Name : 네트워크 클라이언트
// Desc : TCP/UDP 클라이언트입니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cNetClient
{
public:
	cNetClient();
	virtual ~cNetClient();


private:
	bool m_bInitFunc;				// InitFunc함수가 호출되었는가?


protected: /* TCP 소켓 */
	SOCKET m_Clnt;
	SOCKADDR_IN m_ClntAdr;
	bool m_isEnd;


protected: /* UDP 소켓 */
	 SOCKET m_UdpClnt;
	 SOCKADDR_IN m_UdpServAdr;


protected:
	cMessageReceiver* m_pMsgReceiver; // Enqueue()를 사용해 메세지 수신
	cMessageSender* m_pMsgSender; // PushSendMsg()를 사용해 메세지 전송


protected: /* UDP 소켓 메세지 리스너 */
	cMessageReceiver* m_pUdpMsgReceiver;
	cMessageSender* m_pUdpMsgSender;


protected:
	std::vector<std::function<int _CLNT_FUNC_TYPE_>> m_RecvProcFuncList;


protected: /*시퀀스용 Update, Render함수 목록 */
	int m_CurrUpdateFuncNum;

	std::vector<std::function<int(void)>> m_UpdateFuncList;
	std::vector<std::function<int(void)>> m_RenderFuncList;


protected: /* 동기화 */
	std::vector<cClientSygnMgr*> m_pSygnMgrList;


protected: /* 메인 루틴 함수들 */
	std::function<int(void)> m_OnConnect;
	std::function<int(void)> m_OnClose;

	std::function<int(cNetMessage*)> m_OnReceiveMsg;
		
	std::function<int(void)> m_OnUpdate;
	std::function<int(void)> m_OnRender;
		
	std::function<cSygnVal*(int, int)> m_OnCreateSygnVal;
	std::function<int(int, int)> m_OnDeleteSygnVal;


protected: /* 채팅 */
	cNetChating* m_pNetChating;
	std::wstring m_userName;


public:
	int Connect(const char IP[], const char Port[], const char UdpPort[]);
	int Close();

	int ReceiveMsg(cNetMessage* pMsg);

	int Update();
	int Render();

	// 동기화중 SygnVal을 생성, 제거해야 할때
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
	// 수신 메시지 처리용 함수 추가
	int AddRecvProcFunc(int index, std::function<int _CLNT_FUNC_TYPE_> Func);

	// 시퀀스용 Update, Render함수 추가
	int AddUpdateFunc(int index, std::function<int(void)> UpdateFunc);
	int AddRenderFunc(int index, std::function<int(void)> RenderFunc);


public:
	int AddSygnVal(int ValType, cSygnVal* pSygnVal);
	int SetSygnVal(int ValType, int idx, cSygnVal* pSygnVal);
	int RemoveSygnVal(int ValType, const cSygnVal* pSygnVal);

	// 넘겨준 번호에 해당하는 동기화 매니저를 생성해서 가동합니다
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

