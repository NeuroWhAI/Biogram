#include "BiogramWorld.h"

#include <algorithm>
#include <ctime>
#include <list>
#include <random>

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

	, m_pSharedMemory(std::make_shared<Memory>())
{
	
}


BiogramWorld::~BiogramWorld()
{

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
	m_pTimeManager->resetElapsedTime();

	m_pSharedMemory->clear();


	return 0;
}


int BiogramWorld::initWorld(size_t cageCount, double maxTimePerGeneration)
{
	this->clear();


	m_maxTimePerGeneration = maxTimePerGeneration;


	// 랜덤한 DNA로 Cage 생성
	for (size_t i = 0; i < cageCount; ++i)
	{
		auto cage = std::make_shared<BiogramCage>();

		BiogramDNA randomDNA(static_cast<unsigned long>(std::time(nullptr)));
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
	// 1배속 초과에서는 전체 단위작업을 그만큼 반복하도록 함.


	// * 실제 시간속도
	const double timeSpeed = m_pTimeManager->getPitch();

	// 1배속을 초과하면 단위시간(1)로 바꿔서 단위작업을 하도록 함.
	if (timeSpeed > 1.0)
		m_pTimeManager->setPitch(1.0);


	// 배속만큼 반복
	for (double timeGage = 0.0; timeGage < timeSpeed;
	timeGage += 1.0)
	{
		// World 시간 갱신
		updateTimeSpeed();


		// 구성요소 갱신
		updateCage();

		updateDevice();


		// 각 Cage 평가
		evaluateCage();


		// 다음 세대로 갈 준비가 되었으면 건너감
		checkReadyForNext();
	}


	// 원래 배속으로 복구
	m_pTimeManager->setPitch(timeSpeed);


	return 0;
}

//###############################################################

bool BiogramWorld::isReadyForNextGeneration()
{
	return (m_pTimeManager->getElapsedTime() >= m_maxTimePerGeneration);
}


int BiogramWorld::stepToNextGeneration()
{
	const size_t cageCount = m_pCageList.size();
	if (cageCount <= 0) return -1;


	std::vector<BiogramDNA> nextGeneList;


	// 적합도가 높은 순으로 정렬
	std::sort(m_pCageList.begin(), m_pCageList.end(),
		[](BiogramCagePtr pCage1, BiogramCagePtr pCage2) {
			return (pCage1->getGeneScore() > pCage2->getGeneScore());
		}
	);


	// 부모 선택
	std::mt19937 randEngine(static_cast<unsigned>(std::time(nullptr)));
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


	// 우수 세대는 그대로 후세대로 전달
	for (size_t i = 0; i < parentCount && i < cageCount; ++i)
	{
		auto dna = m_pCageList[i]->getDNA();

		if(dna)
			nextGeneList.emplace_back(*dna);
		else
		{
			BiogramDNA randomDNA(static_cast<unsigned long>(std::time(nullptr)));
			nextGeneList.emplace_back(randomDNA);
		}
	}


	// 교배로 후세대 유전자 생성 및 돌연변이
	std::uniform_int_distribution<> parentDist(0, parentIndexList.size() - 1);
	for (size_t i = parentCount; i < cageCount; ++i)
	{
		auto parent1 = m_pCageList[parentIndexList[parentDist(randEngine)]]->getDNA();
		auto parent2 = m_pCageList[parentIndexList[parentDist(randEngine)]]->getDNA();

		if (parent1 && parent2)
		{
			// 교배
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

			// 돌연변이
			newDNA.mutate(static_cast<unsigned>(std::time(nullptr)),
				1.0);

			nextGeneList.emplace_back(newDNA);
		}
		else
		{
			BiogramDNA randomDNA(static_cast<unsigned long>(std::time(nullptr)));
			nextGeneList.emplace_back(randomDNA);
		}
	}


	// 초기화
	this->clearForNextGeneration();


	// 다음 세대 생성
	auto nextGeneListItr = nextGeneList.begin();
	for (auto& cage : m_pCageList)
	{
		cage->clearWithoutComPort();
		cage->buildBiogramWithoutClear(*nextGeneListItr);


		++nextGeneListItr;
		if (nextGeneListItr == nextGeneList.end())
			break;
	}


	// 세대번호 증가
	++m_generationNumber;


	return 0;
}

//###############################################################

int BiogramWorld::updateTimeSpeed()
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


	// 총 경과시간 누적
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


	// Device의 작동을 평가해서 연결된 Cage의 점수를 갱신
	for (auto& device : m_deviceList)
	{
		auto cage = device->getConnectedCage();
		if (!cage) continue;

		double score = 0.0;


		// 연결 평가
		auto comPort = device->getComPort();
		auto mem = comPort->getConnectedMemory();

		// pair(port, address) 목록을 얻어온다.
		const auto& portInfo = comPort->getConnectionInfo();

		for (const auto& info : portInfo)
		{
			int offset = 0;
			bool bExist = mem->findAddress(info.second, &offset);

			// 연결이 되어있으면 만점이고
			// 아니면 다른 연결이 가까운 만큼 점수를 줌
			if (bExist)
			{
				score += 11.0;
			}
			else
			{
				score += 10.0 / static_cast<double>(offset);
			}
		}


		// 작동 평가
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


double BiogramWorld::getTimeSpeed() const
{
	return m_pTimeManager->getPitch();
}


double BiogramWorld::getElapsedTime() const
{
	return m_pTimeManager->getElapsedTime();
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

