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
	* 현재 세대를 다시 만들 수 있는 정도의 정보만 저장한다.
	* 즉, 시간과 메모리 상태 같은건 저장하지 않는다.
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


	// 랜덤한 DNA로 Cage 생성
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
	// 사용자 입력 처리
	updateTimeControl();

	updateCageFocus();


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
	// 할당한 시간이 경과하면 무조건 종료
	if (m_pTimeManager->getElapsedTime() >= m_maxTimePerGeneration)
		return true;


	// 모든 Cage가 활동을 멈추면 종료
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


	// 적합도가 높은 순으로 정렬
	std::sort(m_pCageList.begin(), m_pCageList.end(),
		[](BiogramCagePtr pCage1, BiogramCagePtr pCage2) {
			return (pCage1->getGeneScore() > pCage2->getGeneScore());
		}
	);


	// 부모 선택
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


	// 우수 세대는 그대로 후세대로 전달
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
			newDNA.mutate(m_mutationRate);


			nextGeneList.emplace_back(newDNA);
		}
		else
		{
			BiogramDNA randomDNA(true);
			nextGeneList.emplace_back(randomDNA);
		}
	}


	// Cage 초기화
	for (auto& cage : m_pCageList)
		cage->clearWithoutComPort();


	// 초기화
	this->clearForNextGeneration();


	// 다음 세대 생성
	auto nextGeneListItr = nextGeneList.begin();
	for (auto& cage : m_pCageList)
	{
		cage->buildBiogramWithoutClear(*nextGeneListItr);


		++nextGeneListItr;
		if (nextGeneListItr == nextGeneList.end())
			break;
	}


	// 세대번호 증가
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
				score += 1.0;
			}
			else
			{
				score += 1.0 / static_cast<double>(offset + 1);
			}
		}


		// 포트연결 수와 실제 할당된 Cage Mem의 수가 차이가 나는 만큼
		// 낮은 점수를 줌
		const double validPortCount = cage->getValidPortCount();
		const double assignedCellCount = mem->getAssignedCellCount();
		
		double portOffset = std::abs(assignedCellCount - validPortCount);
		if (portOffset < validPortCount*2.0)
			score += validPortCount;
		else
			score += validPortCount / portOffset;


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

void BiogramWorld::increaseGenerationNumber()
{
	++m_generationNumber;

	// 돌연변이율 변화
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

