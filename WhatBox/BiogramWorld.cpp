#include "BiogramWorld.h"

#include <algorithm>
#include <ctime>
#include <list>
#include <random>
#include <fstream>

#include "System.h"

#include "TimeManager.h"
#include "BiogramCage.h"
#include "Memory.h"
#include "Device.h"
#include "Director.h"

#include "BiogramDNA.h"
#include "ComPort.h"

using TimeManagerPtr = BiogramWorld::TimeManagerPtr;
using BiogramCagePtr = BiogramWorld::BiogramCagePtr;
using MemoryPtr = BiogramWorld::MemoryPtr;
using DevicePtr = BiogramWorld::DevicePtr;



























BiogramWorld::BiogramWorld()
	: m_pTimeManager(std::make_shared<TimeManager>())
	, m_maxTimePerGeneration(5000.0)
	, m_generationNumber(0)
	, m_mutationRate(0.1)

	, m_focusedCageNum(0)
	, m_pSharedMemory(std::make_shared<Memory>())
{
	
}


BiogramWorld::~BiogramWorld()
{
	this->clear();
}

//###############################################################

bool BiogramWorld::saveTo(std::ostream& osr) const
{
	using std::endl;

	/*
	* ���� ���븦 �ٽ� ���� �� �ִ� ������ ������ �����Ѵ�.
	* ��, �ð��� �޸� ���� ������ �������� �ʴ´�.
	*/

	if (osr.good())
	{
		osr << m_maxTimePerGeneration << endl;
		osr << m_generationNumber << endl;
		osr << m_mutationRate << endl;


		osr << m_pCageList.size() << endl;
		for (auto& cage : m_pCageList)
		{
			auto dna = cage->getDNA();
			dna->saveTo(osr);
		}


		return true;
	}


	return false;
}


bool BiogramWorld::loadFrom(std::istream& isr)
{
	if (isr.good())
	{
		this->clear();


		isr >> m_maxTimePerGeneration;
		isr >> m_generationNumber;
		isr >> m_mutationRate;


		size_t size = 0;
		isr >> size;


		for (size_t i = 0; i < size; ++i)
		{
			auto cage = std::make_shared<BiogramCage>();

			BiogramDNA dna;
			dna.loadFrom(isr);
			cage->buildBiogram(dna);

			this->addCage(cage);
		}


		return true;
	}


	return false;
}

//###############################################################

int BiogramWorld::clear()
{
	m_deviceList.clear();
	m_directorList.clear();

	clearForNextGeneration();

	m_pCageList.clear();
	m_generationNumber = 0;


	return 0;
}


int BiogramWorld::clearForNextGeneration()
{
	for (auto& device : m_deviceList)
	{
		device->init();
	}

	for (auto& director : m_directorList)
	{
		director->init();
	}

	m_pTimeManager->resetElapsedTime();

	m_pSharedMemory->clear();


	return 0;
}


bool BiogramWorld::initWorld(const std::wstring& fileName)
{
	std::ifstream fr(fileName);

	if (fr.is_open())
	{
		bool bResult = this->loadFrom(fr);


		fr.close();


		return bResult;
	}


	return false;
}


bool BiogramWorld::saveWorld(const std::wstring& fileName)
{
	std::ofstream fw(fileName);

	if (fw.is_open())
	{
		bool bResult = this->saveTo(fw);


		fw.close();


		return bResult;
	}


	return false;
}


int BiogramWorld::initWorld(size_t cageCount,
	double maxTimePerGeneration,
	double mutationRate)
{
	this->clear();


	m_maxTimePerGeneration = maxTimePerGeneration;
	m_mutationRate = mutationRate;


	// ������ DNA�� Cage ����
	for (size_t i = 0; i < cageCount; ++i)
	{
		auto cage = std::make_shared<BiogramCage>();

		BiogramDNA randomDNA(true);
		cage->buildBiogram(randomDNA);

		this->addCage(cage);
	}


	return 0;
}


/* // BiogramWorld.inl
template <typename T_DEVICE>
int BiogramWorld::initDeviceForeachCage(const T_DEVICE& originalDevice);
*/


/* // BiogramWorld.inl
template <typename T_DIRECTOR>
int BiogramWorld::initDirector(const T_DIRECTOR& originalDirector);
*/

//###############################################################

int BiogramWorld::update()
{
	// ����� �Է� ó��
	updateTimeControl();

	updateCageFocus();


	// 1��� �ʰ������� ��ü �����۾��� �׸�ŭ �ݺ��ϵ��� ��.

	// * ���� �ð��ӵ�
	const double timeSpeed = m_pTimeManager->getPitch();

	// 1����� �ʰ��ϸ� �����ð�(1)�� �ٲ㼭 �����۾��� �ϵ��� ��.
	if (timeSpeed > 1.0)
		m_pTimeManager->setPitch(1.0);

	// ��Ӹ�ŭ �ݺ�
	for (double timeGage = 0.0; timeGage < timeSpeed;
	timeGage += 1.0)
	{
		// World �ð� ����
		updateTimeSpeed();


		// ������� ����
		updateCage();

		updateDevice();


		// �� Cage ��
		evaluateCage();


		// ���� ����� �� �غ� �Ǿ����� �ǳʰ�
		checkReadyForNext();
	}

	// ���� ������� ����
	m_pTimeManager->setPitch(timeSpeed);


	return 0;
}

//###############################################################

bool BiogramWorld::isReadyForNextGeneration()
{
	// �Ҵ��� �ð��� ����ϸ� ������ ����
	if (m_pTimeManager->getElapsedTime() >= m_maxTimePerGeneration)
		return true;


	// ��� Cage�� Ȱ���� ���߸� ����
	bool isEnd = true;

	for (auto& cage : m_pCageList)
	{
		if (cage->isEnd() == false)
		{
			isEnd = false;
			break;
		}
	}


	return isEnd;
}


int BiogramWorld::stepToNextGeneration()
{
	const size_t cageCount = m_pCageList.size();
	if (cageCount <= 0) return -1;


	std::vector<BiogramDNA> nextGeneList;


	// ���յ��� ���� ������ ����
	std::sort(m_pCageList.begin(), m_pCageList.end(),
		[](BiogramCagePtr pCage1, BiogramCagePtr pCage2) {
			return (pCage1->getGeneScore() > pCage2->getGeneScore());
		}
	);


	// �θ� ����
	std::mt19937 randEngine(static_cast<unsigned>(std::time(nullptr) + rand()));
	std::normal_distribution<> selectionDist(0,
		((cageCount < 4) ? 1 : cageCount / 4));

	size_t parentCount = cageCount / 4;
	if (parentCount < 2) parentCount = 2;

	std::vector<int> parentIndexList;
	for (size_t i = 0; i < parentCount; ++i)
	{
		int index = 0;

		do
		{
			index = static_cast<int>(selectionDist(randEngine));
			if (index < 0) index *= -1;
		} while (static_cast<size_t>(index) >= cageCount);

		parentIndexList.emplace_back(index);
	}


	// ��� ����� �״�� �ļ���� ����
	for (size_t i = 0; i < parentCount && i < cageCount; ++i)
	{
		auto dna = m_pCageList[i]->getDNA();

		if (dna)
		{
			BiogramDNA newDNA(*dna);
			newDNA.mutate(m_mutationRate / parentCount * i);
			nextGeneList.emplace_back(newDNA);
		}
		else
		{
			BiogramDNA randomDNA(true);
			nextGeneList.emplace_back(randomDNA);
		}
	}


	// ����� �ļ��� ������ ���� �� ��������
	std::uniform_int_distribution<> parentDist(0, parentIndexList.size() - 1);
	for (size_t i = parentCount; i < cageCount; ++i)
	{
		auto parent1 = m_pCageList[parentIndexList[parentDist(randEngine)]]->getDNA();
		auto parent2 = m_pCageList[parentIndexList[parentDist(randEngine)]]->getDNA();

		if (parent1 && parent2)
		{
			// ����
			BiogramDNA newDNA;

			std::uniform_int_distribution<> boolDist(0, 1);
			if (boolDist(randEngine) != 0)
			{
				newDNA = *parent1;
				newDNA.combine(*parent2);
			}
			else
			{
				newDNA = *parent2;
				newDNA.combine(*parent1);
			}


			// ��������
			newDNA.mutate(m_mutationRate);


			nextGeneList.emplace_back(newDNA);
		}
		else
		{
			BiogramDNA randomDNA(true);
			nextGeneList.emplace_back(randomDNA);
		}
	}


	// Cage �ʱ�ȭ
	for (auto& cage : m_pCageList)
		cage->clearWithoutComPort();


	// �ʱ�ȭ
	this->clearForNextGeneration();


	// ���� ���� ����
	auto nextGeneListItr = nextGeneList.begin();
	for (auto& cage : m_pCageList)
	{
		cage->buildBiogramWithoutClear(*nextGeneListItr);


		++nextGeneListItr;
		if (nextGeneListItr == nextGeneList.end())
			break;
	}


	// �����ȣ ����
	increaseGenerationNumber();


	return 0;
}

//###############################################################

int BiogramWorld::updateCageFocus()
{
	if (System::getInstance().getUserInputController().
		onKeyDown(0xBC/*<*/))
	{
		if (m_focusedCageNum <= 0)
			m_focusedCageNum = m_pCageList.size() - 1;
		else
			--m_focusedCageNum;
	}
	else if (System::getInstance().getUserInputController().
		onKeyDown(0xBE/*>*/))
	{
		if (m_focusedCageNum < m_pCageList.size() - 1)
			++m_focusedCageNum;
		else
			m_focusedCageNum = 0;
	}


	return 0;
}


int BiogramWorld::updateTimeControl()
{
	if (System::getInstance().getUserInputController().
		onKeyDown(0xdb/*[*/))
	{
		m_pTimeManager->setPitch(m_pTimeManager->getPitch() / 2.0);
	}
	else if (System::getInstance().getUserInputController().
		onKeyDown(0xdd/*]*/))
	{
		m_pTimeManager->setPitch(m_pTimeManager->getPitch() * 2.0);
	}


	return 0;
}


int BiogramWorld::updateTimeSpeed()
{
	// �� ����ð� ����
	m_pTimeManager->update();


	return 0;
}


int BiogramWorld::updateCage()
{
	const double timeSpeed = m_pTimeManager->getPitch();

	for (auto& pCage : m_pCageList)
	{
		pCage->update(timeSpeed);
	}


	return 0;
}


int BiogramWorld::updateDevice()
{
	const double timeSpeed = m_pTimeManager->getPitch();

	for (auto& device : m_deviceList)
	{
		device->update(timeSpeed);
	}

	
	return 0;
}


int BiogramWorld::evaluateCage()
{
	const double timeSpeed = m_pTimeManager->getPitch();


	// Device�� �۵��� ���ؼ� ����� Cage�� ������ ����
	for (auto& device : m_deviceList)
	{
		auto cage = device->getConnectedCage();
		if (!cage) continue;

		double score = 0.0;


		// ���� ��
		auto comPort = device->getComPort();
		auto mem = comPort->getConnectedMemory();

		// pair(port, address) ����� ���´�.
		const auto& portInfo = comPort->getConnectionInfo();

		for (const auto& info : portInfo)
		{
			int offset = 0;
			bool bExist = mem->findAddress(info.second, &offset);

			// ������ �Ǿ������� �����̰�
			// �ƴϸ� �ٸ� ������ ����� ��ŭ ������ ��
			if (bExist)
			{
				score += 1.0;
			}
			else
			{
				score += 1.0 / static_cast<double>(offset + 1);
			}
		}


		// ��Ʈ���� ���� ���� �Ҵ�� Cage Mem�� ���� ���̰� ���� ��ŭ
		// ���� ������ ��
		const double validPortCount = cage->getValidPortCount();
		const double assignedCellCount = mem->getAssignedCellCount();
		
		double portOffset = std::abs(assignedCellCount - validPortCount);
		if (portOffset < validPortCount*2.0)
			score += validPortCount;
		else
			score += validPortCount / portOffset;


		// �۵� ��
		for (auto& director : m_directorList)
		{
			score += device->evaluate(director);
		}


		cage->setGeneScore(score * timeSpeed + cage->getGeneScore());
	}


	return 0;
}


int BiogramWorld::checkReadyForNext()
{
	if (isReadyForNextGeneration())
	{
		stepToNextGeneration();
	}


	return 0;
}

//###############################################################

void BiogramWorld::increaseGenerationNumber()
{
	++m_generationNumber;

	// ���������� ��ȭ
	if (m_generationNumber % 100 == 0)
	{
		if (m_generationNumber / 100 % 2 == 0)
			m_mutationRate /= 10.0;
		else
			m_mutationRate *= 10.0;
	}
}

//###############################################################

int BiogramWorld::addCage(BiogramCagePtr pCage)
{
	pCage->setSharedMemory(m_pSharedMemory);

	m_pCageList.emplace_back(pCage);


	return 0;
}


int BiogramWorld::addDevice(DevicePtr pDevice)
{
	m_deviceList.emplace_back(pDevice);


	return 0;
}

//###############################################################

size_t BiogramWorld::getGenerationNumber() const
{
	return m_generationNumber;
}


double BiogramWorld::getMutationRate() const
{
	return m_mutationRate;
}


double BiogramWorld::getTimeSpeed() const
{
	return m_pTimeManager->getPitch();
}


double BiogramWorld::getElapsedTime() const
{
	return m_pTimeManager->getElapsedTime();
}


size_t BiogramWorld::getFocusedCageNumber() const
{
	return m_focusedCageNum;
}


const std::vector<BiogramCagePtr>& BiogramWorld::getCageList() const
{
	return m_pCageList;
}


MemoryPtr BiogramWorld::getSharedMemory() const
{
	return m_pSharedMemory;
}


const std::vector<DevicePtr>& BiogramWorld::getDeviceList() const
{
	return m_deviceList;
}

