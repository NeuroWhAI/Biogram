#include "BiogramLab.h"

#include <ctime>
#include <fstream>

#include "System.h"
#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"
#include "BiogramEgg.h"
#include "CommandOperator.h"



























BiogramLab::BiogramLab()
	: m_pSelectedUnit(nullptr)
	, m_bLoop(false)
{
	// TODO: 임시
	initBiogram(BiogramDNA(static_cast<unsigned long>(std::time(nullptr))));
}


BiogramLab::~BiogramLab()
{

}

//###############################################################

int BiogramLab::update(double timeSpeed)
{
	BiogramCage::update(timeSpeed);

	if (m_bLoop
		&&
		m_pCmdOperator->getCurrentUnitCount() <= 0
		&&
		m_pUnitList.size() > 0)
	{
		m_pCmdOperator->addUnit(m_pUnitList[0]);
	}


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

	if (inputMgr.onKeyDown('L'))
	{
		m_bLoop = !m_bLoop;
	}

	if (inputMgr.onKeyDown(0x20/*Space*/))
	{
		if (m_pUnitList.size() > 0)
		{
			m_pCmdOperator->addUnit(m_pUnitList[0]);
		}
	}

	if (inputMgr.onKeyDown(0x0D/*Enter*/))
	{
		initBiogram(BiogramDNA(static_cast<unsigned long>(std::time(nullptr))));
	}

	if (inputMgr.onKeyDown(0x2E/*Delete*/))
	{
		this->clear();
	}

	if (inputMgr.onKeyDown('M'))
	{
		double rate = 0.01;
		
		if (inputMgr.onKeyPress(0x10/*Shift*/))
			rate = 1.0;

		m_currentDNA.mutate(static_cast<unsigned long>(std::time(nullptr)),
			rate);

		initBiogram(m_currentDNA);
	}

	if (inputMgr.onKeyDown('S')
		&&
		inputMgr.onKeyPress(0x11/*Control*/))
	{
		std::ofstream fw("./Sample/DNA/saved.bmgn");
		if (fw.is_open())
		{
			const auto& dna = m_currentDNA.getData();
			for (const auto& bit : dna)
			{
				fw << (bit ? '1' : '0');
			}

			fw.close();
		}
	}
	else if (inputMgr.onKeyDown('O')
		&&
		inputMgr.onKeyPress(0x11/*Control*/))
	{
		std::vector<bool> data;

		std::ifstream fr("./Sample/DNA/saved.bmgn");
		if (fr.is_open())
		{
			while (!fr.eof())
			{
				char bit = '\0';
				fr.get(bit);

				data.emplace_back(bit != '0');
			}

			fr.close();
		}

		initBiogram(BiogramDNA(data));
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


int BiogramLab::clear()
{
	m_pSelectedUnit = nullptr;
	m_pUnitList.clear();
	m_pFlowLinkerList.clear();
	m_pParamLinkerList.clear();
	m_pCmdOperator->clear();


	return 0;
}


int BiogramLab::initBiogram(BiogramDNA dna)
{
	// 초기화
	this->clear();


	// 랜덤 Biogram 생성
	m_currentDNA = dna;
	BiogramEgg bioMaker(dna);

	std::vector<std::shared_ptr<Unit>> pUnitList;
	std::vector<std::shared_ptr<Linker>> pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> pParamLinkerList;

	bioMaker.buildBiogram(&pUnitList,
		&pFlowLinkerList, &pParamLinkerList,
		m_pCmdOperator);

	for (auto& unit : pUnitList)
		this->addUnit(unit);
	for (auto& linker : pFlowLinkerList)
		this->addLinker(linker, LinkerTypes::Flow);
	for (auto& linker : pParamLinkerList)
		this->addLinker(linker, LinkerTypes::Param);


	return 0;
}

