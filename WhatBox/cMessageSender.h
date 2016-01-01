#pragma once
#include <queue>
#include <thread>

#include "cLock.h"

class cNetMessage;
























class cMessageSender
{
public:
	cMessageSender();
	~cMessageSender();


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
	std::queue<cNetMessage*> m_SendQueue;
	std::queue<SOCKADDR_IN> m_AdrQueue;


private:
	bool m_isEnd;
	std::thread* m_pThread;


public:
	static void ThreadJob(cMessageSender* pThis);
	static void UdpThreadJob(cMessageSender* pThis);


public:
	void PushSendMsg(cNetMessage* pMsg);
	void PushUdpSendMsg(cNetMessage* pMsg, const SOCKADDR_IN* pAdr);
	cNetMessage* Enqueue();
	SOCKADDR_IN AdrEnqueue();
	UINT QueSize();
	UINT AdrQueSize();
	void SetEnd(bool isEnd);
	bool isEnd();
	void SetSock(SOCKET Sock);
	SOCKET GetSock();
	void Clear();


public:
	int Start(SOCKET Sock, bool isTcp = true);
	int Stop();
};

