#include "cTickTimer.h"



































cTickTimer::cTickTimer()
	: m_prevTime(timeGetTime())
	, m_interval(0UL)
{

}


cTickTimer::cTickTimer(DWORD interval)
	: m_prevTime(timeGetTime())
	, m_interval(interval)
{

}


cTickTimer::~cTickTimer()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cTickTimer::OnTick()
{
	if(timeGetTime() - m_prevTime >= m_interval)
	{
		m_prevTime = timeGetTime();


		return true;
	}


	return false;
}


DWORD cTickTimer::LeftTime()
{
	if(timeGetTime() - m_prevTime >= m_interval)
	{
		m_prevTime = timeGetTime();


		return 0UL;
	}


	return (m_interval - (timeGetTime() - m_prevTime));
}

