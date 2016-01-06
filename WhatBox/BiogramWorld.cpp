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
	m_pTimeManager->setPitch(std::pow(2, -6));
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
	if (System::getInstance().getUserInputController().
		onKeyDown(0xdb))
	{
		m_pTimeManager->setPitch(m_pTimeManager->getPitch() / 2.0);
	}
	else if (System::getInstance().getUserInputController().
		onKeyDown(0xdd))
	{
		m_pTimeManager->setPitch(m_pTimeManager->getPitch() * 2.0);
	}

	if (System::getInstance().getUserInputController().
		onKeyDown(0x2E))
	{
		m_pSharedMemory->clear();
	}


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

double BiogramWorld::getTimeSpeed() const
{
	return m_pTimeManager->getPitch();
}


const std::vector<BiogramCagePtr>& BiogramWorld::getCageList() const
{
	return m_pCageList;
}


MemoryPtr BiogramWorld::getSharedMemory() const
{
	return m_pSharedMemory;
}

