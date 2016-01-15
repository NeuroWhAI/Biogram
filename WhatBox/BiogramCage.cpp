#include "BiogramCage.h"

#include <fstream>

#include "LinkHelper.h"

#include "Unit.h"
#include "Linker.h"
#include "CommandOperator.h"
#include "Memory.h"
#include "ComPort.h"
#include "BiogramDNA.h"
#include "ObjectPool.h"

#include "BiogramEgg.h"



























BiogramCage::BiogramCage()
	: m_pUnitPool(std::make_shared<ObjectPool<Unit>>())
	, m_pLinkerPool(std::make_shared<ObjectPool<Linker>>())
	
	, m_elapsedTime(0.0)

	, m_DNA(nullptr)
	, m_geneScore(0.0)
	, m_prevGeneScore(0.0)
	
	, m_cageMemory(std::make_shared<Memory>())
	, m_assignedPortCount(0)

	, m_pCmdOperator(std::make_shared<CommandOperator>())
{
	m_pCmdOperator->setCageMemory(m_cageMemory);
}


BiogramCage::~BiogramCage()
{
	this->clear();
}

//###############################################################

int BiogramCage::setSharedMemory(std::shared_ptr<Memory> sharedMemory)
{
	m_pCmdOperator->setSharedMemory(sharedMemory);


	return 0;
}


int BiogramCage::update(double timeSpeed)
{
	// ��ɾ� ���� ����
	updateCommand(timeSpeed);


	// �� ����ð� ����
	m_elapsedTime += timeSpeed;


	return 0;
}


bool BiogramCage::isEnd() const
{
	return m_pCmdOperator->isEnd();
}

//###############################################################

int BiogramCage::updateCommand(double timeSpeed)
{
	m_pCmdOperator->setGeneScore(m_geneScore);

	m_pCmdOperator->update(timeSpeed, m_elapsedTime);


	return 0;
}

//###############################################################

std::shared_ptr<const BiogramDNA> BiogramCage::getDNA() const
{
	return m_DNA;
}


void BiogramCage::setGeneScore(double score)
{
	m_geneScore = score;
	m_prevGeneScore = score;
}


double BiogramCage::getGeneScore() const
{
	return m_geneScore;
}


double BiogramCage::getOldGeneScore() const
{
	return m_prevGeneScore;
}

//###############################################################

int BiogramCage::buildBiogram(const BiogramDNA& dna)
{
	this->clear();


	buildBiogramWithoutClear(dna);


	return 0;
}


int BiogramCage::buildBiogramWithoutClear(const BiogramDNA& dna)
{
	m_DNA = std::make_shared<BiogramDNA>(dna);
	BiogramEgg bioMaker(dna);

	std::vector<std::shared_ptr<Unit>> pUnitList;
	std::vector<std::shared_ptr<Linker>> pFlowLinkerList;
	std::vector<std::shared_ptr<Linker>> pParamLinkerList;

	bioMaker.buildBiogram(*m_pUnitPool,
		*m_pLinkerPool,
		&pUnitList,
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


int BiogramCage::clear()
{
	clearWithoutComPort();

	m_prevGeneScore = 0.0;
	
	m_comPortList.clear();
	m_assignedPortCount = 0;


	return 0;
}


int BiogramCage::clearWithoutComPort()
{
	m_elapsedTime = 0.0;


	m_DNA = nullptr;
	m_geneScore = 0.0;


	m_pCmdOperator->clear();


	// ��ü�� ��Ȱ���ϱ� ���� �ʱ�ȭ �� Pool�� ȸ��
	for (auto& linker : m_pFlowLinkerList)
	{
		linker->clear();
		m_pLinkerPool->releaseObject(linker);
	}
	for (auto& linker : m_pParamLinkerList)
	{
		linker->clear();
		m_pLinkerPool->releaseObject(linker);
	}
	for (auto& unit : m_pUnitList)
	{
		unit->clear();
		m_pUnitPool->releaseObject(unit);
	}

	m_pFlowLinkerList.clear();
	m_pParamLinkerList.clear();
	m_pUnitList.clear();

	m_cageMemory->clear();


	return 0;
}

//###############################################################

double BiogramCage::getElapsedTime() const
{
	return m_elapsedTime;
}

//###############################################################

bool BiogramCage::addUnit(std::shared_ptr<Unit> pUnit)
{
	// ��Ͽ� �߰�
	m_pUnitList.emplace_back(pUnit);


	return true;
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

//###############################################################

std::shared_ptr<ComPort> BiogramCage::assignComPort(
	std::vector<std::pair<int, int>> portNum_address)
{
	// ComPort ���� �� Cage �޸𸮿� ����
	auto pNewCom = std::make_shared<ComPort>();
	pNewCom->connectMemory(m_cageMemory);


	// ComPort�� �޸𸮰��� ������Ʈ ����
	for (const auto& info : portNum_address)
	{
		bool result = pNewCom->assignPort(info.first, info.second);
		
		// ��Ʈ������ �����ϸ� ComPort ������ ���
		if (result == false)
		{
			return nullptr;
		}
	}


	// ���ᰳ�� ����
	m_assignedPortCount += portNum_address.size();


	// ��Ͽ� ���
	m_comPortList.emplace_back(pNewCom);


	return pNewCom;
}


size_t BiogramCage::getValidPortCount() const
{
	return m_assignedPortCount;
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


std::shared_ptr<const Memory> BiogramCage::getCageMemory() const
{
	return m_cageMemory;
}


std::shared_ptr<const CommandOperator> BiogramCage::getCmdOperator() const
{
	return m_pCmdOperator;
}

