#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"
#include "Memory.h"

#define CMD_FUNC(name) m_cmdFuncList.emplace_back(&CommandOperator::name)



























CommandOperator::CommandOperator()
	: m_pSharedMemory(nullptr)
{
	// 명령어실행용 함수들을 목록에 추가
#include "CommandFunction.h"
}


CommandOperator::~CommandOperator()
{

}

//###############################################################

int CommandOperator::update(double timePitch)
{
	const double timePerCmd = 1.0; // 작을수록 명령어 실행속도가 빨라짐.
	const int funcCount = static_cast<int>(m_cmdFuncList.size());

	for (auto pUnit : m_pCurrentUnitList)
	{
		double leftTime = pUnit->getTimeGage() + timePitch;

		while (leftTime >= timePerCmd)
		{
			std::shared_ptr<Unit> nextUnit(nullptr);


			// 시간진행지수 누적
			leftTime -= timePerCmd;


			// 명령어 실행
			int cmdNum = pUnit->getCmdNumber();
			if (cmdNum < funcCount)
			{
				auto linker1 = pUnit->getParamLinker(0);
				auto linker2 = pUnit->getParamLinker(1);

				(this->*m_cmdFuncList[cmdNum])(&nextUnit,
					pUnit,
					(linker1 ? linker1->getInUnit() : nullptr),
					(linker2 ? linker2->getInUnit() : nullptr));
			}


			// 작동했으므로 시간진행지수를 리셋하고
			pUnit->setTimeGage(0.0);

			// 목록에서 제거할 대상으로 등록.
			m_pRemovalUnitList.insert(pUnit);


			// Jump요청이 들어왔으면 하고 아니면 다음 유닛으로 이동
			if (nextUnit)
			{
				pUnit = nextUnit;
			}
			else
			{
				// 다음 유닛(명령어)으로 이동
				auto pOutLinker = pUnit->getOutLinker();
				if (pOutLinker)
					pUnit = pOutLinker->getOutUnit();
				else
					pUnit = nullptr;

				// 다음 유닛이 없으면 진행종료
				if(pUnit == nullptr) break;
			}
		}

		// 종료시점의 Head Unit의 시간진행 설정 및 목록에 등록
		if (pUnit)
		{
			pUnit->setTimeGage(leftTime);
			m_pNextUnitList.insert(pUnit);
		}
	}


	// 목록에서 제거할 Unit 제거
	for (auto& pUnit : m_pRemovalUnitList)
	{
		removeUnit(pUnit);
	}
	m_pRemovalUnitList.clear();


	// 목록에 추가할 Unit 추가
	// NOTE: 추가를 삭제보다 나중에 해야함
	for (auto& pUnit : m_pNextUnitList)
	{
		addUnit(pUnit);
	}
	m_pNextUnitList.clear();


	return 0;
}


int CommandOperator::clear()
{
	m_pCurrentUnitList.clear();
	m_pRemovalUnitList.clear();
	m_pNextUnitList.clear();


	return 0;
}

//###############################################################

bool CommandOperator::addUnit(std::shared_ptr<Unit> pUnit)
{
	auto insertResult = m_pCurrentUnitList.insert(pUnit);


	return insertResult.second;
}


void CommandOperator::removeUnit(std::shared_ptr<Unit> pUnit)
{
	m_pCurrentUnitList.erase(pUnit);
}

//###############################################################

size_t CommandOperator::getCurrentUnitCount() const
{
	return m_pCurrentUnitList.size();
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

