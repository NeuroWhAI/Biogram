#pragma once
#include <queue>
#include <thread>

#include "cLock.h"

class cNetMessage;
























class cMessageReceiver
{
public:
	cMessageReceiver();
	~cMessageReceiver();


private:
	cLock m_Locker;
	enum LockNum
	{
		LockNum_isEnd,
		LockNum_Queue,
		LockNum_Sock,
		LockNum_Adr,


		//-----------------
		LockNum_LockNum_Count
	};


private:
	bool m_isTcp;
	SOCKET m_Sock;
	std::queue<cNetMessage*> m_RecvQueue;
	std::queue<SOCKADDR_IN> m_AdrQueue;


private:
	bool m_isEnd;
	std::thread* m_pThread;


public:
	static void ThreadJob(cMessageReceiver* pThis);
	static void UdpThreadJob(cMessageReceiver* pThis);


public:
	void PushRecvMsg(cNetMessage* pMsg);
	void PushAdr(SOCKADDR_IN Adr);
	cNetMessage* Enqueue();
	SOCKADDR_IN AdrEnqueue();
	cNetMessage* GetBackAndClear();
	SOCKADDR_IN GetAdrBackAndClear();
	UINT QueSize();
	UINT AdrQueSize();
	void SetEnd(bool isEnd);
	bool isEnd();
	void SetSock(SOCKET Sock);
	SOCKET GetSock();
	void Clear(cNetMessage* pNotDeleteMsg = NULL);
	void ClearAdr();


public:
	int Start(SOCKET Sock, bool isTcp = true);
	int Stop();
};

