#include "BiogramCage.h"

#include "LinkHelper.h"

#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"
#include "Memory.h"



























BiogramCage::BiogramCage()
	: m_pCmdOperator(std::make_shared<CommandOperator>())
{
	
}


BiogramCage::~BiogramCage()
{

}

//###############################################################

int BiogramCage::setSharedMemory(std::shared_ptr<Memory> sharedMemory)
{
	m_pCmdOperator->setSharedMemory(sharedMemory);


	return 0;
}


int BiogramCage::update(double timeSpeed)
{
	//updateUnit(timeSpeed);

	//updateLinker(timeSpeed);

	updateCommand(timeSpeed);


	return 0;
}

//###############################################################

int BiogramCage::updateUnit(double timeSpeed)
{
	for (auto& pUnit : m_pUnitList)
	{
		pUnit->update(timeSpeed);
	}


	return 0;
}


int BiogramCage::updateLinker(double timeSpeed)
{	
	for (auto& pLinker : m_pFlowLinkerList)
	{
		pLinker->update(timeSpeed);
	}

	for (auto& pLinker : m_pParamLinkerList)
	{
		pLinker->update(timeSpeed);
	}


	return 0;
}


int BiogramCage::updateCommand(double timeSpeed)
{
	m_pCmdOperator->update(timeSpeed);


	return 0;
}

//###############################################################

bool BiogramCage::addUnit(std::shared_ptr<Unit> pUnit)
{
	bool bFail = false;


	// 목록에 추가
	m_pUnitList.emplace_back(pUnit);


	return !bFail;
}


bool BiogramCage::removeUnit(std::shared_ptr<Unit> pUnit)
{
	bool bFail = false;


	// Flow Linker 끊기
	auto inLinker = pUnit->getInLinker();
	auto outLinker = pUnit->getOutLinker();
	if (inLinker)
	{
		LinkHelper::DisconnectFlow(inLinker, pUnit);
	}
	if (outLinker)
	{
		LinkHelper::DisconnectFlow(pUnit, outLinker);
	}


	// Param Linker 끊기
	int paramCount = static_cast<int>(pUnit->getParamCount());
	for (int paramIndex = 0; paramIndex < paramCount; ++paramIndex)
	{
		auto paramLinker = pUnit->getParamLinker(paramIndex);
		if (paramLinker)
		{
			LinkHelper::DisconnectParam(paramLinker, pUnit, paramIndex);
		}
	}


	// Out Param Linker 끊기
	auto outParamLinkerList = pUnit->getOutParamLinkerList();
	for (auto& linker : outParamLinkerList)
	{
		LinkHelper::DisconnectParam(pUnit, linker);
	}


	// 명령어 수행자에서 제거
	m_pCmdOperator->removeUnit(pUnit);


	// 목록에서 제거
	Utility::removeFrom(&m_pUnitList, pUnit);


	return !bFail;
}


bool BiogramCage::addLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type)
{
	switch (type)
	{
	case LinkerTypes::Flow:
		m_pFlowLinkerList.emplace_back(pLinker);
		break;

	case LinkerTypes::Param:
		m_pParamLinkerList.emplace_back(pLinker);
		break;

	default:
		return false;
	}


	return true;
}


bool BiogramCage::removeLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type)
{
	std::shared_ptr<Unit> inUnit = pLinker->getInUnit();
	std::shared_ptr<Unit> outUnit = pLinker->getOutUnit();

	switch (type)
	{
	case LinkerTypes::Flow:
		// 실행흐름 끊기
		LinkHelper::DisconnectFlow(inUnit, pLinker);
		LinkHelper::DisconnectFlow(pLinker, outUnit);

		// 목록에서 제거
		Utility::removeFrom(&m_pFlowLinkerList, pLinker);
		break;

	case LinkerTypes::Param:
		// 인자연결 끊기
		LinkHelper::DisconnectParam(inUnit, pLinker);
		LinkHelper::DisconnectParam(pLinker, outUnit);

		// 목록에서 제거
		Utility::removeFrom(&m_pParamLinkerList, pLinker);
		break;

	default:
		return false;
	}


	return true;
}

//###############################################################

const std::vector<std::shared_ptr<Unit>>& BiogramCage::getUnitList() const
{
	return m_pUnitList;
}


const std::vector<std::shared_ptr<Linker>>& BiogramCage::getFlowLinkerList() const
{
	return m_pFlowLinkerList;
}


const std::vector<std::shared_ptr<Linker>>& BiogramCage::getParamLinkerList() const
{
	return m_pParamLinkerList;
}


std::shared_ptr<const CommandOperator> BiogramCage::getCmdOperator() const
{
	return m_pCmdOperator;
}

