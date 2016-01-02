#include "BiogramWorld.h"

#include "System.h"

#include "TimeManager.h"
#include "Unit.h"



























BiogramWorld::BiogramWorld()
	: m_pTimeManager(std::make_shared<TimeManager>())
{
	
}


BiogramWorld::~BiogramWorld()
{

}

//###############################################################

int BiogramWorld::update()
{
	updateTimeSpeed();

	updateUnit();


	return 0;
}

//###############################################################

int BiogramWorld::updateTimeSpeed()
{
	double maxSpeedSq = 1.0;

	for (auto& pUnit : m_pUnitList)
	{
		double speedSq = pUnit->getSpeed().getLengthSq();

		if (speedSq > maxSpeedSq)
		{
			maxSpeedSq = speedSq;
		}
	}


	double pitch = 1.0 / std::sqrt(maxSpeedSq);
	if (pitch > 1.0) pitch = 1.0; // 1배속 초과는 안됨

	m_pTimeManager->setPitch(pitch);


	return 0;
}


int BiogramWorld::updateUnit()
{
	double timePitch = m_pTimeManager->getPitch();

	for (auto& pUnit : m_pUnitList)
	{
		pUnit->update(timePitch);
	}


	return 0;
}

//###############################################################

double BiogramWorld::getTimeSpeed() const
{
	return m_pTimeManager->getPitch();
}


const std::vector<std::shared_ptr<Unit>>& BiogramWorld::getUnitList() const
{
	return m_pUnitList;
}

