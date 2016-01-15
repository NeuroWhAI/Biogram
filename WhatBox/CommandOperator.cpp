#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"
#include "Memory.h"

#include "System.h"

#define CMD_FUNC(name) m_cmdFuncList.emplace_back(&CommandOperator::name)



























CommandOperator::CommandOperator()
	: m_currentFlowIndex(0)
	, m_bIsEnd(false)
	
	, m_pSharedMemory(nullptr)
	, m_pCageMemory(nullptr)
	, m_elapsedTime(0.0)
	, m_geneScore(0.0)
{
	// 명령어실행용 함수들을 목록에 추가
#include "CommandFunction.h"
}


CommandOperator::~CommandOperator()
{

}

//###############################################################

int CommandOperator::update(double timePitch, double totalTime)
{
	m_elapsedTime = totalTime;


	const double timePerCmd = 1.0; // 작을수록 명령어 실행속도가 빨라짐.
	const int funcCount = static_cast<int>(m_cmdFuncList.size());

	if(!m_bIsEnd
		&&
		m_currentFlowIndex < m_pFlowUnitList.size())
	{
		auto currentUnit = m_pFlowUnitList[m_currentFlowIndex];

		// 시간 속도를 이용해 반복 횟수 계산
		double leftTime = currentUnit->getTimeGage() + timePitch;

		while (leftTime >= timePerCmd)
		{
			int jumpPosition = 1;


			// 시간진행지수 누적
			leftTime -= timePerCmd;


			// 명령어 실행
			int cmdNum = currentUnit->getCmdNumber();
			if (cmdNum < funcCount)
			{
				auto linker1 = currentUnit->getParamLinker(0);
				auto linker2 = currentUnit->getParamLinker(1);

				(this->*m_cmdFuncList[cmdNum])(&jumpPosition,
					currentUnit,
					(linker1 ? linker1->getInUnit() : nullptr),
					(linker2 ? linker2->getInUnit() : nullptr));
			}


			// 작동했으므로 시간진행지수를 리셋
			currentUnit->setTimeGage(0.0);


			// Jump좌표가 유효하지 않으면 종료하고
			// 유효하면 다음 유닛(명령어)으로 이동
			if ((jumpPosition < 0
				&&
				static_cast<size_t>(-jumpPosition) > m_currentFlowIndex)
				||
				jumpPosition == 0)
			{
				m_bIsEnd = true;
				currentUnit = nullptr;

				break;
			}
			else
			{
				// 좌표 이동
				m_currentFlowIndex += jumpPosition;

				// 다음 유닛을 선택하거나
				// 범위를 벗어났다면 종료
				if (m_currentFlowIndex < m_pFlowUnitList.size())
					currentUnit = m_pFlowUnitList[m_currentFlowIndex];
				else
				{
					m_bIsEnd = true;
					currentUnit = nullptr;

					break;
				}
			}
		}

		// 종료시점의 Head Unit의 시간진행 설정 및 목록에 등록
		if (currentUnit)
		{
			currentUnit->setTimeGage(leftTime);
		}
	}


	return 0;
}


int CommandOperator::restart()
{
	m_currentFlowIndex = 0;
	m_bIsEnd = false;


	return 0;
}


int CommandOperator::clear()
{
	m_currentFlowIndex = 0;
	m_pFlowUnitList.clear();
	m_bIsEnd = false;


	return 0;
}


bool CommandOperator::isEnd() const
{
	return m_bIsEnd;
}

//###############################################################

int CommandOperator::addFlowUnit(std::shared_ptr<Unit> pUnit)
{
	m_pFlowUnitList.emplace_back(pUnit);


	return 0;
}


const std::vector<std::shared_ptr<Unit>>& CommandOperator::getFlowUnitList() const
{
	return m_pFlowUnitList;
}

//###############################################################

size_t CommandOperator::getCmdFunctionCount() const
{
	return m_cmdFuncList.size();
}

//###############################################################

int CommandOperator::setSharedMemory(std::shared_ptr<Memory> pSharedMemory)
{
	m_pSharedMemory = pSharedMemory;


	return 0;
}


double CommandOperator::readSharedMem(int address)
{
	if (m_pSharedMemory)
	{
		return m_pSharedMemory->read(address);
	}


	return 0.0;
}


void CommandOperator::writeSharedMem(int address, double value)
{
	if (m_pSharedMemory)
	{
		return m_pSharedMemory->write(address, value);
	}
}


//-----------------------------------------------------------------

int CommandOperator::setCageMemory(std::shared_ptr<Memory> pCageMemory)
{
	m_pCageMemory = pCageMemory;


	return 0;
}


double CommandOperator::readCageMem(int address)
{
	if (m_pCageMemory)
	{
		return m_pCageMemory->read(address);
	}


	return 0.0;
}


void CommandOperator::writeCageMem(int address, double value)
{
	if (m_pCageMemory)
	{
		return m_pCageMemory->write(address, value);
	}
}

//###############################################################

void CommandOperator::setGeneScore(double score)
{
	m_geneScore = score;
}

