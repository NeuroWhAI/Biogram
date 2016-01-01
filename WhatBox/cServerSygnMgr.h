#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>

class cSygnVal;
class cMessageSender;
class cNetMessage;
























class cServerSygnMgr
{
public:
	cServerSygnMgr(cMessageSender* pMsgSender);
	~cServerSygnMgr();


private:
	cMessageSender* m_pMsgSender;


private:
	std::vector<cSygnVal*> m_pSygnValList;


public:
	int AddSygnVal(cSygnVal* pSygnVal);
	int SetSygnVal(cSygnVal* pSygnVal, int Idx);
	int RemoveSygnVal(const cSygnVal* pSygnVal);


public:
	int Recv(const cNetMessage* pMsg, const SOCKADDR_IN* pAdr);
};

