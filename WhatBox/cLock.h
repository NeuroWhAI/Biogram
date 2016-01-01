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


public: // ũ��Ƽ�� ���� ����, ����
	UINT Create(UINT Id);
	void Delete(UINT Id);
	void DeleteAll();


public: // ũ��Ƽ�� ������ �̿��� Lock, UnLock
	void Begin(UINT Id);
	void End(UINT Id);
};

