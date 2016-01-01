#include "cTimer.h"



























cTimer::cTimer()
	: m_bStop(true)
	, m_bPause(false)
	
	, m_StartTime(0UL)
	, m_PauseTime(0UL)

	, m_BeginPauseTime(0UL)
{

}


cTimer::~cTimer()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////

DWORD cTimer::ElapsedTime() const
{
	if(m_bStop) return 0UL;


	DWORD Time = timeGetTime() - m_StartTime - m_PauseTime;


	if(m_bPause)
	{
		Time -= timeGetTime() - m_BeginPauseTime;
	}


	return Time;
}


DWORD cTimer::PausedTime() const
{
	return m_PauseTime;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void cTimer::Start()
{
	if(m_BeginPauseTime != 0UL)
	{
		m_PauseTime += timeGetTime() - m_BeginPauseTime;
		m_BeginPauseTime = 0UL;

		m_bPause = false;
	}


	if(m_PauseTime == 0UL)
	{
		m_StartTime = timeGetTime();

		m_bStop = false;
	}
}


void cTimer::Stop()
{
	// √ ±‚»≠
	m_StartTime = 0UL;
	m_PauseTime = 0UL;
	m_BeginPauseTime = 0UL;

	m_bStop = true;
}


void cTimer::Pause()
{
	m_BeginPauseTime = timeGetTime();
	m_bPause = true;
}

