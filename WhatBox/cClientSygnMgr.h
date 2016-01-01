#pragma once
#include <Windows.h>
#include <vector>

class cSygnVal;
class cMessageSender;
class cNetMessage;
























class cClientSygnMgr
{
public:
	cClientSygnMgr(cMessageSender* pMsgSender);
	~cClientSygnMgr();


private:
	cMessageSender* m_pMsgSender;


private:
	std::vector<cSygnVal*> m_pSygnValList;


private:
	DWORD m_prevTime; // 동기화에 시간 간격을 두기위한 시간값


public:
	int AddSygnVal(cSygnVal* pSygnVal);
	int SetSygnVal(cSygnVal* pSygnVal, int Idx);
	int RemoveSygnVal(const cSygnVal* pSygnVal);
	int RemoveSygnVal(int Idx);


public:
	int Update(int ValType);
	int Recv(const cNetMessage* pMsg, std::vector<int>* pCreateList, std::vector<int>* pDeleteList); // 받은 Idx를 반환해줌
};

