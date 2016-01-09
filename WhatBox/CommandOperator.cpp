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
	// ��ɾ����� �Լ����� ��Ͽ� �߰�
#include "CommandFunction.h"
}


CommandOperator::~CommandOperator()
{

}

//###############################################################

int CommandOperator::update(double timePitch, double totalTime)
{
	m_elapsedTime = totalTime;


	const double timePerCmd = 1.0; // �������� ��ɾ� ����ӵ��� ������.
	const int funcCount = static_cast<int>(m_cmdFuncList.size());

	if(m_pCurrentUnit)
	{
		double leftTime = m_pCurrentUnit->getTimeGage() + timePitch;

		while (leftTime >= timePerCmd)
		{
			std::shared_ptr<Unit> nextUnit(nullptr);


			// �ð��������� ����
			leftTime -= timePerCmd;


			// ��ɾ� ����
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


			// �۵������Ƿ� �ð����������� ����
			m_pCurrentUnit->setTimeGage(0.0);


			// Jump��û�� �������� �ϰ� �ƴϸ� ���� �������� �̵�
			if (nextUnit)
			{
				m_pCurrentUnit = nextUnit;
			}
			else
			{
				// ���� ����(��ɾ�)���� �̵�
				auto pOutLinker = m_pCurrentUnit->getOutLinker();
				if (pOutLinker)
					m_pCurrentUnit = pOutLinker->getOutUnit();
				else
					m_pCurrentUnit = nullptr;

				// ���� ������ ������ ��������
				if(m_pCurrentUnit == nullptr) break;
			}
		}

		// ��������� Head Unit�� �ð����� ���� �� ��Ͽ� ���
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

