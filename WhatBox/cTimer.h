#pragma once
#include <Windows.h>




















class cTimer
{
public:
	cTimer();
	~cTimer();


private:
	bool m_bStop;
	bool m_bPause;

	DWORD m_StartTime;						// 타이머 최초 시작 시간
	DWORD m_PauseTime;						// 중간중간 일시정지된 총 시간

	DWORD m_BeginPauseTime;					// 마지막으로 Pause한 시간


public:
	DWORD ElapsedTime() const;				// 일시정지 시간을 제외하고 Start부터 흐른 시간
	DWORD PausedTime() const;				// Start부터 일시정지 총 시간


public:
	void Start();
	void Stop();
	void Pause();
};

