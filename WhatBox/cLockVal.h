#pragma once
#include <Windows.h>
#include <WinSock2.h>
























template <typename T>
class cLockVal
{
public:
	cLockVal();
	~cLockVal();


private:
	CRITICAL_SECTION m_Sec;
	T m_Value;


public:
	T GetValue();
	void SetValue(T Val);


private:
	void Lock();
	void UnLock();
};


#include"cLockVal_Def.h"