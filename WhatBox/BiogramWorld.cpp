#include "BiogramWorld.h"

#include "System.h"

#include "TimeManager.h"
#include "BiogramCage.h"
#include "Memory.h"

#include "BiogramLab.h"

using TimeManagerPtr = BiogramWorld::TimeManagerPtr;
using BiogramCagePtr = BiogramWorld::BiogramCagePtr;
using MemoryPtr = BiogramWorld::MemoryPtr;



























BiogramWorld::BiogramWorld()
	: m_pTimeManager(std::make_shared<TimeManager>())

	, m_pSharedMemory(std::make_shared<Memory>())
{
	// TODO: юс╫ц
	auto lab = std::make_shared<BiogramLab>();
	addCage(lab);
}


BiogramWorld::~BiogramWorld()
{

}

//###############################################################

int BiogramWorld::update()
{
	updateTimeSpeed();

	updateCage();


	return 0;
}

//###############################################################

int BiogramWorld::updateTimeSpeed()
{
	m_pTimeManager->setPitch(1.0);


	return 0;
}


int BiogramWorld::updateCage()
{
	double timeSpeed = m_pTimeManager->getPitch();

	for (auto& pCage : m_pCageList)
	{
		pCage->update(timeSpeed);
	}


	return 0;
}

//###############################################################

int BiogramWorld::addCage(BiogramCagePtr pCage)
{
	pCage->setSharedMemory(m_pSharedMemory);

	m_pCageList.emplace_back(pCage);


	return 0;
}

//###############################################################

const std::vector<BiogramCagePtr>& BiogramWorld::getCageList() const
{
	return m_pCageList;
}


MemoryPtr BiogramWorld::getSharedMemory() const
{
	return m_pSharedMemory;
}

