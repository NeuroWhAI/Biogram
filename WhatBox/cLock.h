#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>




















class cLock
{
public:
	~cLock();


private:
	std::vector<CRITICAL_SECTION> m_SecList;
	std::vector<bool> m_IsReadyList;


public: // 크리티컬 섹션 생성, 제거
	UINT Create(UINT Id);
	void Delete(UINT Id);
	void DeleteAll();


public: // 크리티컬 섹션을 이용해 Lock, UnLock
	void Begin(UINT Id);
	void End(UINT Id);
};

