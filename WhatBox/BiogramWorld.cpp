#include "BiogramWorld.h"

#include "System.h"

#include "LinkHelper.h"

#include "TimeManager.h"
#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"



























BiogramWorld::BiogramWorld()
	: m_pTimeManager(std::make_shared<TimeManager>())

	, m_pCmdOperator(std::make_shared<CommandOperator>())
{
	// TODO: 임시
	auto unit = std::make_shared<Unit>();
	m_pUnitList.emplace_back(unit);
}


BiogramWorld::~BiogramWorld()
{

}

//###############################################################

int BiogramWorld::update()
{
	updateTimeSpeed();

	updateUnit();

	updateCommand();

	// TODO: 임시
	if (System::getInstance().getUserInputController().
		onKeyDown('U'))
	{
		auto unit = std::make_shared<Unit>();
		auto linker = LinkHelper::ConnectFlow(m_pUnitList[m_pUnitList.size() - 1],
			unit);

		unit->setLocation(m_pUnitList.size()*100.0f,
			m_pUnitList.size() % 2 * 100.0f);
		unit->setCmdNumber(0);

		m_pUnitList.emplace_back(unit);
		m_pFlowLinkerList.emplace_back(linker);
	}
	if (System::getInstance().getUserInputController().
		onKeyDown('R'))
	{
		m_pCmdOperator->addUnit(m_pUnitList[0]);
	}
	if (System::getInstance().getUserInputController().
		onKeyDown('W'))
	{
		m_pUnitList[0]->addSpeed(0.0, -0.1);
	}
	if (System::getInstance().getUserInputController().
		onKeyDown('S'))
	{
		m_pUnitList[0]->addSpeed(0.0, 0.1);
	}


	return 0;
}

//###############################################################

int BiogramWorld::updateTimeSpeed()
{
	double maxSpeedSq = 1.0 * 1.0;

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


int BiogramWorld::updateCommand()
{
	m_pCmdOperator->update(m_pTimeManager->getPitch());


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


const std::vector<std::shared_ptr<Linker>>& BiogramWorld::getFlowLinkerList() const
{
	return m_pFlowLinkerList;
}


const std::vector<std::shared_ptr<Linker>>& BiogramWorld::getParamLinkerList() const
{
	return m_pParamLinkerList;
}


std::shared_ptr<const CommandOperator> BiogramWorld::getCmdOperator() const
{
	return m_pCmdOperator;
}

