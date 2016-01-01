#pragma once
#include <Windows.h>

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 째깍째깍
// Desc : 지정한 시간(ms)마다 OnTick멤버함수가 true를 반환합니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTickTimer
{
public:
	cTickTimer();

	// * DWORD interval : Tick의 주기(ms)
	cTickTimer(DWORD interval);
	~cTickTimer();


private:
	DWORD m_prevTime;
	DWORD m_interval;


public:
	// Tick!
	bool OnTick();

	// 다음 Tick까지 남은 시간(ms)
	DWORD LeftTime();
};

