#include "cMessageSender.h"

#include "NetMsgUtil.h"

#include "cNetMessage.h"






























cMessageSender::cMessageSender()
	: m_isTcp(true)
	, m_isEnd(false)
	, m_pThread(NULL)
{
	for(int i=LockNum_isEnd; i<LockNum_LockNum_Count; i++)
		m_Locker.Create(i);
}


cMessageSender::~cMessageSender()
{
	if(m_pThread != NULL)
	{
		delete m_pThread;
		m_pThread = NULL;
	}


	for(UINT i=0; i<m_SendQueue.size(); i++)
	{
		delete m_SendQueue.front();
		m_SendQueue.pop();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void cMessageSender::ThreadJob(cMessageSender* pThis)
{
	Sleep(100);


	while(!pThis->isEnd())
	{
		UINT queSize = pThis->QueSize();


		while(queSize > 0)
		{
			queSize--;


			cNetMessage* pMsg = pThis->Enqueue();


			if(pMsg != NULL)
			{
				if(NetMsgUtil::Send(pThis->GetSock(), pMsg) == false)
				{
					pThis->SetEnd(true);
				}


				delete pMsg; pMsg = NULL;
			}
		}


		Sleep(1);
	}
}


void cMessageSender::UdpThreadJob(cMessageSender* pThis)
{
	Sleep(100);


	while(!pThis->isEnd())
	{
		UINT queSize = min(pThis->QueSize(), pThis->AdrQueSize());


		while(queSize > 0)
		{
			queSize--;


			cNetMessage* pMsg = pThis->Enqueue();
			SOCKADDR_IN Adr = pThis->AdrEnqueue();


			if(pMsg != NULL)
			{
				if(NetMsgUtil::UdpSend(pThis->GetSock(), pMsg, &Adr) == false)
				{
					pThis->SetEnd(true);
				}


				delete pMsg; pMsg = NULL;
			}
		}


		Sleep(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void cMessageSender::PushSendMsg(cNetMessage* pMsg)
{
	m_Locker.Begin(LockNum_Queue);

	m_SendQueue.push(pMsg);

	m_Locker.End(LockNum_Queue);
}


void cMessageSender::PushUdpSendMsg(cNetMessage* pMsg, const SOCKADDR_IN* pAdr)
{
	m_Locker.Begin(LockNum_Queue);

	m_SendQueue.push(pMsg);

	m_Locker.End(LockNum_Queue);


	m_Locker.Begin(LockNum_Adr);

	m_AdrQueue.push(*pAdr);

	m_Locker.End(LockNum_Adr);
}


cNetMessage* cMessageSender::Enqueue()
{
	m_Locker.Begin(LockNum_Queue);

	cNetMessage* Temp = m_SendQueue.front();
	m_SendQueue.pop();

	m_Locker.End(LockNum_Queue);


	return Temp;
}


SOCKADDR_IN cMessageSender::AdrEnqueue()
{
	m_Locker.Begin(LockNum_Adr);

	SOCKADDR_IN Temp = m_AdrQueue.front();
	m_AdrQueue.pop();

	m_Locker.End(LockNum_Adr);


	return Temp;
}


UINT cMessageSender::QueSize()
{
	m_Locker.Begin(LockNum_Queue);

	UINT Temp = m_SendQueue.size();

	m_Locker.End(LockNum_Queue);


	return Temp;
}


UINT cMessageSender::AdrQueSize()
{
	m_Locker.Begin(LockNum_Adr);

	UINT Temp = m_AdrQueue.size();

	m_Locker.End(LockNum_Adr);


	return Temp;
}


void cMessageSender::SetEnd(bool isEnd)
{
	m_Locker.Begin(LockNum_isEnd);

	m_isEnd = isEnd;

	m_Locker.End(LockNum_isEnd);
}


bool cMessageSender::isEnd()
{
	m_Locker.Begin(LockNum_isEnd);

	bool Temp = m_isEnd;

	m_Locker.End(LockNum_isEnd);


	return Temp;
}


void cMessageSender::SetSock(SOCKET Sock)
{
	m_Locker.Begin(LockNum_Sock);

	m_Sock = Sock;

	m_Locker.End(LockNum_Sock);
}


SOCKET cMessageSender::GetSock()
{
	m_Locker.Begin(LockNum_Sock);

	SOCKET Temp = m_Sock;

	m_Locker.End(LockNum_Sock);


	return Temp;
}


void cMessageSender::Clear()
{
	m_Locker.Begin(LockNum_Queue);

	while(m_SendQueue.size() > 0)
	{
		delete m_SendQueue.front();
		m_SendQueue.pop();
	}

	m_Locker.End(LockNum_Queue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int cMessageSender::Start(SOCKET Sock, bool isTcp)
{
	if(isEnd() == false)
	{
		Stop();
	}


	SetEnd(false);
	SetSock(Sock);


	if(isTcp)
		m_pThread = new std::thread(ThreadJob, this);
	else
		m_pThread = new std::thread(UdpThreadJob, this);


	return 0;
}


int cMessageSender::Stop()
{
	if(isEnd()) return -1;


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

