#include "TimeManager.h"



























TimeManager::TimeManager()
	: m_pitch(1.0)
	, m_pitchF(1.0f)
{

}


TimeManager::~TimeManager()
{

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

