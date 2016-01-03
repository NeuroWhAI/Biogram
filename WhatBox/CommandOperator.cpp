#include "CommandOperator.h"

#include "Unit.h"
#include "Linker.h"

#define CMD_FUNC(name) m_cmdFuncList.emplace_back(&CommandOperator::name)



























CommandOperator::CommandOperator()
{
	// ��ɾ����� �Լ����� ��Ͽ� �߰�
#include "CommandFunction.h"
}


CommandOperator::~CommandOperator()
{

}

//###############################################################

int CommandOperator::update(double timePitch)
{
	const double timePerCmd = 1.0; // �������� ��ɾ� ����ӵ��� ������.
	const int funcCount = static_cast<int>(m_cmdFuncList.size());

	for (auto pUnit : m_pCurrentUnitList)
	{
		double leftTime = pUnit->getTimeGage() + timePitch;

		//while (spendTime + timePerCmd <= timePitch)
		while (leftTime >= timePerCmd)
		{
			std::shared_ptr<Unit> nextUnit(nullptr);


			// �ð��������� ����
			leftTime -= timePerCmd;


			// ��ɾ� ����
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


			// �۵������Ƿ� �ð����������� �����ϰ�
			pUnit->setTimeGage(0.0);

			// ��Ͽ��� ������ ������� ���.
			m_pRemovalUnitList.insert(pUnit);


			// Jump��û�� �������� �ϰ� �ƴϸ� ���� �������� �̵�
			if (nextUnit)
			{
				pUnit = nextUnit;
			}
			else
			{
				// ���� ����(��ɾ�)���� �̵�
				auto pOutLinker = pUnit->getOutLinker();
				if (pOutLinker)
					pUnit = pOutLinker->getOutUnit();
				else
					pUnit = nullptr;

				// ���� ������ ������ ��������
				if(pUnit == nullptr) break;
			}
		}

		// ��������� Head Unit�� �ð����� ���� �� ��Ͽ� ���
		if (pUnit)
		{
			pUnit->setTimeGage(leftTime);
			m_pNextUnitList.insert(pUnit);
		}
	}


	// ��Ͽ��� ������ Unit ����
	for (auto& pUnit : m_pRemovalUnitList)
	{
		removeUnit(pUnit);
	}
	m_pRemovalUnitList.clear();


	// ��Ͽ� �߰��� Unit �߰�
	// NOTE: �߰��� �������� ���߿� �ؾ���
	for (auto& pUnit : m_pNextUnitList)
	{
		addUnit(pUnit);
	}
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

