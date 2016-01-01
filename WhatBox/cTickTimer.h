#pragma once
#include <Windows.h>

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : °��°��
// Desc : ������ �ð�(ms)���� OnTick����Լ��� true�� ��ȯ�մϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTickTimer
{
public:
	cTickTimer();

	// * DWORD interval : Tick�� �ֱ�(ms)
	cTickTimer(DWORD interval);
	~cTickTimer();


private:
	DWORD m_prevTime;
	DWORD m_interval;


public:
	// Tick!
	bool OnTick();

	// ���� Tick���� ���� �ð�(ms)
	DWORD LeftTime();
};

