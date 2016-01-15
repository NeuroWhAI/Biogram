#include "BiogramEgg.h"

#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"
#include "CommandOperator.h"
#include "ObjectPool.h"

using UnitPtr = BiogramEgg::UnitPtr;
using LinkerPtr = BiogramEgg::LinkerPtr;
using CmdOperatorPtr = BiogramEgg::CmdOperatorPtr;

#define TO_RADIAN(x) ((x) * 0.01745329251f)



























BiogramEgg::BiogramEgg()
	: m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
	, m_dataFromPast(0)
	, m_prevAngle(0.0f)
	, m_currentFlowIndex(0)
{

}


BiogramEgg::BiogramEgg(const BiogramDNA& dna)
	: m_dna(dna)

	, m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
	, m_dataFromPast(0)
	, m_prevAngle(0.0f)
{

}


BiogramEgg::~BiogramEgg()
{

}

//###############################################################

int BiogramEgg::setDNA(const BiogramDNA& dna)
{
	m_dna = dna;


	return 0;
}


int BiogramEgg::buildBiogram(ObjectPool<Unit>& unitPool,
	ObjectPool<Linker>& linkerPool,
	std::vector<UnitPtr>* pUnitOut,
	std::vector<LinkerPtr>* pFlowLinkerOut,
	std::vector<LinkerPtr>* pParamLinkerOut,
	CmdOperatorPtr pCmdOperator)
{
	// ó���� None Unit�� �ΰ� ����
	m_pUnitOnProcess = unitPool.acquireObject();
	m_pUnitOnProcess->setLocation(0.0f, 0.0f);
	m_pUnitOnProcess->setCmdNumber(0);
	// Unit ��Ͽ� ���
	pUnitOut->emplace_back(m_pUnitOnProcess);
	// �� None Unit�� ���α׷��� ���� ������ �� ����
	// ��ɾ� �����ڿ� ���
	pCmdOperator->addFlowUnit(m_pUnitOnProcess);

	// ù��° Unit�� �Է������ϴ� Flow Linker ������ ����
	m_pLinkerOnProcess = linkerPool.acquireObject();
	LinkHelper::ConnectFlow(m_pUnitOnProcess, m_pLinkerOnProcess);
	// Flow Linker ��Ͽ� ���
	pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);


	// DNA �ؼ� ����
	const auto& data = m_dna.getData();

	// * ���� ó���ϴ� �ܰ踦 ��Ÿ��
	int sequence = 0;
	// * DNA���� ���� ��Ʈ�� ���� ��Ÿ��
	size_t bufferSize = 64;
	// * DNA���� ���� ��ġ�� ��Ÿ��
	auto currentPos = data.cbegin();
	// * DNA ����
	const size_t dnaLength = data.size();
	// * DNA ������ ��
	const size_t halfSize = dnaLength / 2;

	for (size_t d = 0; d < dnaLength; d += bufferSize)
	{
		currentPos = data.cbegin() + d;

		// �о�� �� ��ŭ ���� ���̰� ������� ������ ����
		if (d + bufferSize > dnaLength) break;

		// ���� DNA�� ���� �о����� Param���� �ܰ�(-1)�� ����
		if(d >= halfSize
			&&
			sequence == 0)
		{
			m_pUnitOnProcess = (*pUnitOut)[0];
			m_currentFlowIndex = 0;

			sequence = -1;
		}
		
		// �����͸� ó���ϰ�
		// ���� �ܰ迡�� �ʿ��� ������ ��Ʈ ���� �޴´�.
		bufferSize = proceedData(sequence,
			currentPos, bufferSize,
			unitPool,
			linkerPool,
			pUnitOut,
			pFlowLinkerOut,
			pParamLinkerOut,
			pCmdOperator);

		// ���� ���� �ܰ迡�� �ʿ��� ������ ��Ʈ ���� ���ٸ�
		// DNA �ؼ��۾��� �����Ѵ�.
		if (bufferSize <= 0) break;
	}


	m_pUnitOnProcess = nullptr;
	m_pLinkerOnProcess = nullptr;


	return 0;
}

//###############################################################

size_t BiogramEgg::proceedData(int& sequence,
	std::vector<bool>::const_iterator begin,
	size_t bufferSize,
	ObjectPool<Unit>& unitPool,
	ObjectPool<Linker>& linkerPool,
	std::vector<UnitPtr>* pUnitOut,
	std::vector<LinkerPtr>* pFlowLinkerOut,
	std::vector<LinkerPtr>* pParamLinkerOut,
	CmdOperatorPtr pCmdOperator)
{
	//const int dataInt = toInt(begin, bufferSize);
	//const int dataBitTotal = bitTotal(begin, bufferSize);
	//const int dataPartialInt = toPartialInt(begin, bufferSize);


	switch (sequence)
	{
	case -2: {
		/*
		* ���� ���õ� Unit�� ��������Ͽ�
		* DNA�κ��� ������ Unit�� �Է�����
		* Param Linker�� ���� �� �����Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			int dataInt = toInt(begin, bufferSize);

			// data�� 16��Ʈ�� ���̹Ƿ� �ִ밪�� 32767��� ����
			// �̿��ؼ� �ִ밪�� ���� �Ѵ� ���� ������ �����.
			int relativeIndex = dataInt;
			if (relativeIndex > 32767 / 2)
			{
				relativeIndex -= 32767 / 2;
				relativeIndex *= -1;
			}


			const auto& flowUnitList = pCmdOperator->getFlowUnitList();

			// �����Ϸ��� �����ǥ�� ��ȿ�� �� ������
			if ((relativeIndex >= 0
				||
				static_cast<size_t>(-relativeIndex) <= m_currentFlowIndex)
				&&
				m_currentFlowIndex + relativeIndex < flowUnitList.size())
			{
				// �Է����� �� Unit�� ã�� �����Ѵ�.
				auto relativeUnit = flowUnitList[m_currentFlowIndex + relativeIndex];
				if (relativeUnit)
				{
					// Param Linker ���� �� ����
					auto paramLinker = LinkHelper::ConnectParam(relativeUnit,
						m_pUnitOnProcess,
						m_dataFromPast % m_pUnitOnProcess->getParamCount(),
						&linkerPool);

					// Param Linker ��Ͽ� �߰�
					pParamLinkerOut->emplace_back(paramLinker);


					// ���� ���õ� Unit�� ���� Param ������ �� ���� ���θ�
					// ���� �ܰ�(-1)���� ���� �����κ��� �����Ѵ�.
					if (m_dataFromPast < 2)
					{
						// ���� Unit�� ������ Param �����۾��� �ϵ��� �Ѵ�.
						auto nextLinker = m_pUnitOnProcess->getOutLinker();
						if (nextLinker)
						{
							m_pUnitOnProcess = nextLinker->getOutUnit();
							++m_currentFlowIndex;
						}
						else
							m_pUnitOnProcess = nullptr;

						sequence = -1;
					}
					else
					{
						// ���� Unit������ �ѹ� �� Param ������ �õ��Ѵ�.
						m_dataFromPast = 3 - m_dataFromPast;

						sequence = -2;
					}
				}
			}
		}
		else return 0;
	} return 16;

	case -1: {
		// �����ܰ�(-2)���� �� ���� �޴´�.
		const int dataBitTotal = bitTotal(begin, bufferSize);

		m_dataFromPast = dataBitTotal % 4;

		sequence = -2;
	} return 16;

	case 0: {
		/*
		* ���ο� Unit�� �����ϰ� ��ɾ� ��ȣ�� �����Ѵ���
		* �� Unit���� ���õǾ��ִ� Unit��
		* �Է������Ͽ� Flow Linker�� �����Ѵ�.
		*/

		const int dataPartialInt = toPartialInt(begin, bufferSize);

		// ���� ���� Unit�� ��ǥ�� ���õ� Unit�� ��ǥ������ ������̴�.
		float angle = static_cast<float>(dataPartialInt);
		m_prevAngle += TO_RADIAN(dataPartialInt % 360);

		float length = angle / 2040.0f * 16.0f + 4.0f;

		Utility::PointF pos(cosf(m_prevAngle) * length,
			sinf(m_prevAngle) * length);

		if (m_pUnitOnProcess)
			pos += m_pUnitOnProcess->getLocation();

		// �� Unit ���� �� ��ġ ����
		auto unit = unitPool.acquireObject();
		unit->setLocation(pos);
		
		// ��ɾ� ����
		int cmdNum = dataPartialInt % pCmdOperator->getCmdFunctionCount();
		m_pUnitOnProcess->setCmdNumber(cmdNum);

		if (m_pLinkerOnProcess)
			LinkHelper::ConnectFlow(m_pLinkerOnProcess, unit);

		// ������ ���� �� Flow Linker�� ������ �����ص�
		m_pLinkerOnProcess = linkerPool.acquireObject();
		LinkHelper::ConnectFlow(unit, m_pLinkerOnProcess);
		// Flow Linker ��Ͽ� �߰�
		pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);

		// ���⼭ �����ߴ� Unit�� ����
		m_pUnitOnProcess = unit;

		// Unit ��Ͽ� �߰�
		pUnitOut->emplace_back(unit);

		// ��ɾ� ������ ��Ͽ� �߰�
		pCmdOperator->addFlowUnit(unit);

		sequence = 2;
	} return 64;

	case 2: {
		/*
		* ���õ� Unit�� �ִٸ� DNA�κ��� ���� ����
		* �ش� Unit�� �޸� ������ �����Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			const int dataPartialInt = toPartialInt(begin, bufferSize);

			// ���� ���� �ٷ� ���°� �ƴ϶�
			// �ִ밪�� ���� �������� ������ ����� ��ȯ�Ѵ�.
			int memory = dataPartialInt;
			if (memory > 2040 / 2)
			{
				memory -= 2040 / 2;
				memory *= -1;
			}

			// �޸� �� ����
			m_pUnitOnProcess->setMemory(memory);
		}

		sequence = 3;
	} return 8;

	case 3: {
		/*
		* DNA���� ����
		* Param ���� �ܰ�(4)�� ���� ó�� �ܰ�(0)�� ���� �����Ѵ�.
		*/

		const int dataBitTotal = bitTotal(begin, bufferSize);

		m_dataFromPast = dataBitTotal;
		if (m_dataFromPast < 4)
		{
			sequence = 4;


			return 64;
		}
		else
		{
			m_dataFromPast = 0;

			sequence = 0;


			return 64;
		}
	} return 0;

	case 4: {
		/*
		* ���õ� Unit�� �ִٸ� �� Unit�� ��������Ͽ�
		* ���ο� None Unit�� ������ Param ������ �Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			const int dataPartialInt = toPartialInt(begin, bufferSize);

			// �� Unit�� ��ġ�� ����Ѵ�.
			float angle = static_cast<float>(dataPartialInt);
			float length = angle / 2040.0f * 8.0f + 4.0f;
			Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
			pos += m_pUnitOnProcess->getLocation();

			// �� Unit�� �����ϰ� �����Ѵ�.
			auto unit = unitPool.acquireObject();
			unit->setLocation(pos);
			unit->setCmdNumber(0);
			// �޸� �ʱ갪 ����
			double memory = dataPartialInt;
			if (memory > 2040 / 2)
			{
				memory -= 2040 / 2;
				memory *= -1;
			}
			unit->setMemory(memory);
			// Unit ��Ͽ� �߰�
			pUnitOut->emplace_back(unit);

			// �� Param Linker�� �����ϰ� �����Ѵ�.
			auto paramLinker = LinkHelper::ConnectParam(unit,
				m_pUnitOnProcess,
				m_dataFromPast % m_pUnitOnProcess->getParamCount(),
				&linkerPool);
			// Param Linker ��Ͽ� �߰�
			pParamLinkerOut->emplace_back(paramLinker);
			
			// ���� �ܰ�(3)�κ��� ���� ���� ����
			// ���� Unit�� ���� Param ������ �ѹ� �� ����
			// ó�� �ܰ�(0)�� ���ư��� �����Ѵ�.
			if (m_dataFromPast < 2)
			{
				sequence = 0;


				return 64;
			}
			else
			{
				m_dataFromPast = 3 - m_dataFromPast;

				sequence = 4;


				return 64;
			}
		}
	} return 0;
	}


	return 0;
}


int BiogramEgg::toInt(std::vector<bool>::const_iterator begin,
	size_t size)
{
	if (size > sizeof(int) * 8)
		size = sizeof(int) * 8;


	int result = 0;

	for (size_t i = 0; i < size; ++i)
	{
		result |= ((*begin ? 1 : 0) << i);

		++begin;
	}


	return result;
}


int BiogramEgg::bitTotal(std::vector<bool>::const_iterator begin,
	size_t size)
{
	int result = 0;

	for (size_t i = 0; i < size; ++i)
	{
		if (*begin)
			++result;

		++begin;
	}


	return result;
}


int BiogramEgg::toPartialInt(std::vector<bool>::const_iterator begin,
	size_t size)
{
	int result = 0;

	for (size_t i = 0; i < size; ++i)
	{
		result += ((*begin ? 1 : 0) << (i % 8));

		++begin;
	}


	return result;
}

