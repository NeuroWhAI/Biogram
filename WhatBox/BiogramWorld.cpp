#include "BiogramWorld.h"

#include "System.h"

#include "LinkHelper.h"

#include "TimeManager.h"
#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"
#include "TileMap.h"

#include "CloseUnitTile.h"



























BiogramWorld::BiogramWorld(float width, float height)
	: m_pTimeManager(std::make_shared<TimeManager>())

	, m_pCloseUnitBoard(std::make_shared<TileMap<Unit>>())

	, m_pCmdOperator(std::make_shared<CommandOperator>())
{
	// Ÿ�ϸ� �ʱ�ȭ
	m_pCloseUnitBoard->init<CloseUnitTile>(
		static_cast<int>(width/64.0f) + 1,
		static_cast<int>(height/64.0f) + 1,
		64.0f);


	// TODO: �ӽ�
	auto unit = std::make_shared<Unit>();
	this->addUnit(unit);
}


BiogramWorld::~BiogramWorld()
{

}

//###############################################################

int BiogramWorld::update()
{
	updateTimeSpeed();

	updateUnit();

	updateLinker();

	updateCommand();

	updateCloseUnitBoard();

	// TODO: �ӽ�
	float timePitchF = m_pTimeManager->getPitchF();
	if (System::getInstance().getUserInputController().
		onKeyDown('U'))
	{
		auto unit = std::make_shared<Unit>();

		unit->setLocation(m_pUnitList.size()*100.0f,
			m_pUnitList.size() % 2 * 100.0f);
		unit->setCmdNumber(0);

		auto linker = LinkHelper::ConnectFlow(m_pUnitList[m_pUnitList.size() - 1],
			unit);

		this->addUnit(unit);
		this->addLinker(linker, LinkerTypes::Flow);
	}
	if (System::getInstance().getUserInputController().
		onKeyDown('R'))
	{
		m_pCmdOperator->addUnit(m_pUnitList[0]);
	}
	if (System::getInstance().getUserInputController().
		onKeyPress('W'))
	{
		m_pUnitList[0]->addSpeed(0.0f, -0.1f * timePitchF);
	}
	if (System::getInstance().getUserInputController().
		onKeyPress('S'))
	{
		m_pUnitList[0]->addSpeed(0.0f, 0.1f * timePitchF);
	}
	if (System::getInstance().getUserInputController().
		onKeyPress('A'))
	{
		m_pUnitList[0]->addSpeed(-0.1f * timePitchF, 0.0f);
	}
	if (System::getInstance().getUserInputController().
		onKeyPress('D'))
	{
		m_pUnitList[0]->addSpeed(0.1f * timePitchF, 0.0f);
	}


	return 0;
}

//###############################################################

int BiogramWorld::updateTimeSpeed()
{
	const double limitSpeed = 1.0; // �� �ӵ��� ������ �ð��� ������
	double maxSpeedSq = limitSpeed * limitSpeed;

	for (auto& pUnit : m_pUnitList)
	{
		double speedSq = pUnit->getSpeed().getLengthSq();

		if (speedSq > maxSpeedSq)
		{
			maxSpeedSq = speedSq;
		}
	}


	double pitch = limitSpeed / std::sqrt(maxSpeedSq);
	if (pitch > 1.0) pitch = 1.0; // 1��� �ʰ��� �ȵ�

	m_pTimeManager->setPitch(pitch);


	return 0;
}


int BiogramWorld::updateUnit()
{
	double timePitch = m_pTimeManager->getPitch();
	float timePitchF = m_pTimeManager->getPitchF();

	for (auto& pUnit : m_pUnitList)
	{
		pUnit->update(timePitch);

		// ��������
		auto brakeVec = -pUnit->getSpeed() / 128.0f * timePitchF;
		pUnit->addSpeed(brakeVec);
	}


	return 0;
}


int BiogramWorld::updateLinker()
{	
	double timePitch = m_pTimeManager->getPitch();

	for (auto& pLinker : m_pFlowLinkerList)
	{
		pLinker->update(timePitch);
	}

	for (auto& pLinker : m_pParamLinkerList)
	{
		pLinker->update(timePitch);
	}


	return 0;
}


int BiogramWorld::updateCommand()
{
	m_pCmdOperator->update(m_pTimeManager->getPitch());


	return 0;
}


int BiogramWorld::updateCloseUnitBoard()
{
	m_pCloseUnitBoard->update(m_pTimeManager->getPitch());


	return 0;
}

//###############################################################

bool BiogramWorld::addUnit(std::shared_ptr<Unit> pUnit)
{
	bool bFail = false;


	// ��Ͽ� �߰�
	m_pUnitList.emplace_back(pUnit);


	// �������� ó���� �ʿ� �߰�
	bFail |= !m_pCloseUnitBoard->addObject(pUnit);


	return !bFail;
}


bool BiogramWorld::removeUnit(std::shared_ptr<Unit> pUnit)
{
	bool bFail = false;


	// �������� ó���� �ʿ��� ����
	bFail |= !m_pCloseUnitBoard->removeObject(pUnit);


	// Flow Linker ����
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


	// Param Linker ����
	int paramCount = static_cast<int>(pUnit->getParamCount());
	for (int paramIndex = 0; paramIndex < paramCount; ++paramIndex)
	{
		auto paramLinker = pUnit->getParamLinker(paramIndex);
		if (paramLinker)
		{
			LinkHelper::DisconnectParam(paramLinker, pUnit, paramIndex);
		}
	}


	// Out Param Linker ����
	auto outParamLinkerList = pUnit->getOutParamLinkerList();
	for (auto& linker : outParamLinkerList)
	{
		LinkHelper::DisconnectParam(pUnit, linker);
	}


	// ��ɾ� �����ڿ��� ����
	m_pCmdOperator->removeUnit(pUnit);


	// ��Ͽ��� ����
	Utility::removeFrom(&m_pUnitList, pUnit);


	return !bFail;
}


bool BiogramWorld::addLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type)
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


bool BiogramWorld::removeLinker(std::shared_ptr<Linker> pLinker, LinkerTypes type)
{
	std::shared_ptr<Unit> inUnit = pLinker->getInUnit();
	std::shared_ptr<Unit> outUnit = pLinker->getOutUnit();

	switch (type)
	{
	case LinkerTypes::Flow:
		// �����帧 ����
		LinkHelper::DisconnectFlow(inUnit, pLinker);
		LinkHelper::DisconnectFlow(pLinker, outUnit);

		// ��Ͽ��� ����
		Utility::removeFrom(&m_pFlowLinkerList, pLinker);
		break;

	case LinkerTypes::Param:
		// ���ڿ��� ����
		LinkHelper::DisconnectParam(inUnit, pLinker);
		LinkHelper::DisconnectParam(pLinker, outUnit);

		// ��Ͽ��� ����
		Utility::removeFrom(&m_pParamLinkerList, pLinker);
		break;

	default:
		return false;
	}


	return true;
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

