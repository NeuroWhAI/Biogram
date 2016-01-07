#include "TimeManager.h"



























TimeManager::TimeManager()
	: m_pitch(1.0)
	, m_pitchF(1.0f)

	, m_elapsedTime(0.0)
{

}


TimeManager::~TimeManager()
{

}

//###############################################################

int TimeManager::update()
{
	m_elapsedTime += m_pitch;


	return 0;
}

//###############################################################

void TimeManager::setPitch(double pitch)
{
	m_pitch = pitch;
	m_pitchF = static_cast<float>(pitch);
}


void TimeManager::setPitch(float pitchF)
{
	m_pitch = static_cast<double>(pitchF);
	m_pitchF = pitchF;
}

//---------------------------------------------------------------

double TimeManager::getPitch() const
{
	return m_pitch;
}


float TimeManager::getPitchF() const
{
	return m_pitchF;
}

//###############################################################

double TimeManager::getElapsedTime() const
{
	return m_elapsedTime;
}


void TimeManager::resetElapsedTime()
{
	m_elapsedTime = 0.0;
}

