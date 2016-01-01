#include "cMessageReceiver.h"

#include "NetMsgUtil.h"

#include "cNetMessage.h"

#include <assert.h>






























cMessageReceiver::cMessageReceiver()
	: m_isTcp(true)
	, m_isEnd(false)
	, m_pThread(NULL)
{
	for(int i=LockNum_isEnd; i<LockNum_LockNum_Count; i++)
		m_Locker.Create(i);
}


cMessageReceiver::~cMessageReceiver()
{
	if(m_pThread != NULL)
	{
		delete m_pThread;
		m_pThread = NULL;
	}


	for(UINT i=0; i<m_RecvQueue.size(); i++)
	{
		delete m_RecvQueue.front();
		m_RecvQueue.pop();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void cMessageReceiver::ThreadJob(cMessageReceiver* pThis)
{
	Sleep(100);


	while(!pThis->isEnd())
	{
		cNetMessage* pMsg = new cNetMessage();


		if(NetMsgUtil::Receive(pThis->GetSock(), pMsg) == false)
		{// ¿¬°á ²÷±è
			if(pMsg != NULL) delete pMsg;
			pThis->SetEnd(true);
			break;
		}


		if(pMsg != NULL)
		{
			pThis->PushRecvMsg(pMsg);
		}


		Sleep(1);
	}
}


void cMessageReceiver::UdpThreadJob(cMessageReceiver* pThis)
{
	Sleep(100);


	while(!pThis->isEnd())
	{
		cNetMessage* pMsg = new cNetMessage();
		SOCKADDR_IN Adr;


		if(NetMsgUtil::UdpReceive(pThis->GetSock(), pMsg, &Adr) == false)
		{// ¿¬°á ²÷±è
			if(pMsg != NULL)
			{
				delete pMsg;
				pMsg = NULL;
			}
			//pThis->SetEnd(true);
			//break;
		}


		if(pMsg != NULL)
		{
			pThis->PushRecvMsg(pMsg);
			pThis->PushAdr(Adr);
		}


		Sleep(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void cMessageReceiver::PushRecvMsg(cNetMessage* pMsg)
{
	m_Locker.Begin(LockNum_Queue);

	m_RecvQueue.push(pMsg);

	m_Locker.End(LockNum_Queue);
}


void cMessageReceiver::PushAdr(SOCKADDR_IN Adr)
{
	m_Locker.Begin(LockNum_Adr);

	m_AdrQueue.push(Adr);

	m_Locker.End(LockNum_Adr);
}


cNetMessage* cMessageReceiver::Enqueue()
{
	m_Locker.Begin(LockNum_Queue);

	cNetMessage* Temp = m_RecvQueue.front();
	m_RecvQueue.pop();

	m_Locker.End(LockNum_Queue);


	return Temp;
}


SOCKADDR_IN cMessageReceiver::AdrEnqueue()
{
	m_Locker.Begin(LockNum_Adr);

	SOCKADDR_IN Temp = m_AdrQueue.front();
	m_AdrQueue.pop();

	m_Locker.End(LockNum_Adr);


	return Temp;
}


cNetMessage* cMessageReceiver::GetBackAndClear()
{
	m_Locker.Begin(LockNum_Queue);

	cNetMessage* Temp = m_RecvQueue.back();

	Clear(Temp); // ÀüºÎ popÇÏ´Âµ¥ Temp´Â delete¿¡¼­ Á¦¿ÜµÊ

	m_Locker.End(LockNum_Queue);


	return Temp;
}


SOCKADDR_IN cMessageReceiver::GetAdrBackAndClear()
{
	m_Locker.Begin(LockNum_Adr);

	SOCKADDR_IN Temp = m_AdrQueue.back();
	m_AdrQueue.pop();

	ClearAdr();

	m_Locker.End(LockNum_Adr);


	return Temp;
}


UINT cMessageReceiver::QueSize()
{
	m_Locker.Begin(LockNum_Queue);

	UINT Temp = m_RecvQueue.size();

	m_Locker.End(LockNum_Queue);


	return Temp;
}


UINT cMessageReceiver::AdrQueSize()
{
	m_Locker.Begin(LockNum_Adr);

	UINT Temp = m_AdrQueue.size();

	m_Locker.End(LockNum_Adr);


	return Temp;
}


void cMessageReceiver::SetEnd(bool isEnd)
{
	m_Locker.Begin(LockNum_isEnd);

	m_isEnd = isEnd;

	m_Locker.End(LockNum_isEnd);
}


bool cMessageReceiver::isEnd()
{
	m_Locker.Begin(LockNum_isEnd);

	bool Temp = m_isEnd;

	m_Locker.End(LockNum_isEnd);


	return Temp;
}


void cMessageReceiver::SetSock(SOCKET Sock)
{
	m_Locker.Begin(LockNum_Sock);

	m_Sock = Sock;

	m_Locker.End(LockNum_Sock);
}


SOCKET cMessageReceiver::GetSock()
{
	m_Locker.Begin(LockNum_Sock);

	SOCKET Temp = m_Sock;

	m_Locker.End(LockNum_Sock);


	return Temp;
}


void cMessageReceiver::Clear(cNetMessage* pNotDeleteMsg)
{
	m_Locker.Begin(LockNum_Queue);
	
	while(m_RecvQueue.size() > 0)
	{
		cNetMessage* pMsg = m_RecvQueue.front();
		
		if(pNotDeleteMsg != pMsg)
			delete pMsg;
		m_RecvQueue.pop();
	}

	m_Locker.End(LockNum_Queue);
}


void cMessageReceiver::ClearAdr()
{
	UINT Size = AdrQueSize();


	while(Size > 0)
	{
		Size--;

		m_Locker.Begin(LockNum_Adr);

		m_AdrQueue.pop();

		m_Locker.End(LockNum_Adr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cMessageReceiver::Start(SOCKET Sock, bool isTcp)
{
	m_isTcp = isTcp;

	if(isEnd() == false)
	{
		Stop();
	}


	SetEnd(false);
	SetSock(Sock);


	if(m_isTcp)
		m_pThread = new std::thread(ThreadJob, this);
	else
		m_pThread = new std::thread(UdpThreadJob, this);


	return 0;
}


int cMessageReceiver::Stop()
{
	//if(isEnd()) return -1;


	SetEnd(true);
	Sleep(100);


	if(m_pThread != NULL)
	{
		m_pThread->join();


		delete m_pThread;
		m_pThread = NULL;
	}


	return 0;
}

