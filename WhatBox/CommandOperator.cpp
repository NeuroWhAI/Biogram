#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"
#include "Memory.h"

#define CMD_FUNC(name) m_cmdFuncList.emplace_back(&CommandOperator::name)



























CommandOperator::CommandOperator()
	: m_pSharedMemory(nullptr)
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

	if(m_pCurrentUnit)
	{
		double leftTime = m_pCurrentUnit->getTimeGage() + timePitch;

		while (leftTime >= timePerCmd)
		{
			std::shared_ptr<Unit> nextUnit(nullptr);


			// 시간진행지수 누적
			leftTime -= timePerCmd;


			// 명령어 실행
			int cmdNum = m_pCurrentUnit->getCmdNumber();
			if (cmdNum < funcCount)
			{
				auto linker1 = m_pCurrentUnit->getParamLinker(0);
				auto linker2 = m_pCurrentUnit->getParamLinker(1);

				(this->*m_cmdFuncList[cmdNum])(&nextUnit,
					m_pCurrentUnit,
					(linker1 ? linker1->getInUnit() : nullptr),
					(linker2 ? linker2->getInUnit() : nullptr));
			}


			// 작동했으므로 시간진행지수를 리셋
			m_pCurrentUnit->setTimeGage(0.0);


			// Jump요청이 들어왔으면 하고 아니면 다음 유닛으로 이동
			if (nextUnit)
			{
				m_pCurrentUnit = nextUnit;
			}
			else
			{
				// 다음 유닛(명령어)으로 이동
				auto pOutLinker = m_pCurrentUnit->getOutLinker();
				if (pOutLinker)
					m_pCurrentUnit = pOutLinker->getOutUnit();
				else
					m_pCurrentUnit = nullptr;

				// 다음 유닛이 없으면 진행종료
				if(m_pCurrentUnit == nullptr) break;
			}
		}

		// 종료시점의 Head Unit의 시간진행 설정 및 목록에 등록
		if (m_pCurrentUnit)
		{
			m_pCurrentUnit->setTimeGage(leftTime);
		}
	}


	return 0;
}


int CommandOperator::clear()
{
	m_pCurrentUnit = nullptr;


	return 0;
}

//###############################################################

bool CommandOperator::addUnit(std::shared_ptr<Unit> pUnit)
{
	if (m_pCurrentUnit)
		return false;


	m_pCurrentUnit = pUnit;


	return true;
}


void CommandOperator::removeUnit(std::shared_ptr<Unit> pUnit)
{
	if (m_pCurrentUnit == pUnit)
		m_pCurrentUnit = nullptr;
}

//###############################################################

size_t CommandOperator::getCurrentUnitCount() const
{
	return 1;
}


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

