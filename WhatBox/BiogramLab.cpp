#include "BiogramLab.h"

#include <time.h>

#include "System.h"
#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"
#include "BiogramDNA.h"
#include "BiogramEgg.h"
#include "CommandOperator.h"



























BiogramLab::BiogramLab()
	: m_pSelectedUnit(nullptr)
{
	// TODO: юс╫ц
	BiogramDNA randomDNA(static_cast<unsigned long>(time(nullptr)));
	BiogramEgg bioMaker(randomDNA);

	std::vector<std::shared_ptr<Unit>> pUnitList;
	std::vector<std::shared_ptr<Linker>> pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> pParamLinkerList;

	bioMaker.buildBiogram(&pUnitList,
		&pFlowLinkerList, &pParamLinkerList);

	for (auto& unit : pUnitList)
		this->addUnit(unit);
	for (auto& linker : pFlowLinkerList)
		this->addLinker(linker, LinkerTypes::Flow);
	for (auto& linker : pParamLinkerList)
		this->addLinker(linker, LinkerTypes::Param);

	if(pUnitList.size() > 0)
		m_pCmdOperator->addUnit(pUnitList[0]);
}


BiogramLab::~BiogramLab()
{

}

//###############################################################

int BiogramLab::update(double timeSpeed)
{
	BiogramCage::update(timeSpeed);


	auto& inputMgr = System::getInstance().getUserInputController();


	if (inputMgr.onTouchDown())
	{
		touchDownCallback(inputMgr.getCursorLocation());
	}
	if (inputMgr.onTouchPress())
	{
		touchPressCallback(inputMgr.getCursorLocation());
	}
	if (inputMgr.onTouchUp())
	{
		touchUpCallback(inputMgr.getCursorLocation());
	}


	return 0;
}

//###############################################################

int BiogramLab::touchDownCallback(Utility::Point cursor)
{
	auto selectedUnit = getUnitContain(cursor);

	if (selectedUnit)
	{
		m_pSelectedUnit = selectedUnit;
	}
	else
	{
		auto pNewUnit = std::make_shared<Unit>();
		pNewUnit->setLocation(cursor);


		this->addUnit(pNewUnit);
	}


	return 0;
}


int BiogramLab::touchPressCallback(Utility::Point cursor)
{
	if (m_pSelectedUnit)
	{
		m_pSelectedUnit->setLocation(cursor);
	}


	return 0;
}


int BiogramLab::touchUpCallback(Utility::Point cursor)
{
	m_pSelectedUnit = nullptr;


	return 0;
}

//###############################################################

std::shared_ptr<Unit> BiogramLab::getUnitContain(Utility::Point point) const
{
	for (auto& pUnit : m_pUnitList)
	{
		float radius = pUnit->getRadius();
		auto subVec = pUnit->getLocation() - point;

		if (subVec.getLengthSq() < radius*radius)
		{
			return pUnit;
		}
	}


	return nullptr;
}

