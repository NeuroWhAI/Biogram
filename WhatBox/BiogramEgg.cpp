#include "BiogramEgg.h"

#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"
#include "CommandOperator.h"

using UnitPtr = BiogramEgg::UnitPtr;
using LinkerPtr = BiogramEgg::LinkerPtr;
using CmdOperatorPtr = BiogramEgg::CmdOperatorPtr;



























BiogramEgg::BiogramEgg()
	: m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
	, m_dataFromPast(0)
{

}


BiogramEgg::BiogramEgg(const BiogramDNA& dna)
	: m_dna(dna)

	, m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
	, m_dataFromPast(0)
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


int BiogramEgg::buildBiogram(std::vector<UnitPtr>* pUnitOut,
	std::vector<LinkerPtr>* pFlowLinkerOut,
	std::vector<LinkerPtr>* pParamLinkerOut,
	CmdOperatorPtr pCmdOperator)
{
	// ó���� None Unit�� �ΰ� ����
	m_pUnitOnProcess = std::make_shared<Unit>();
	m_pUnitOnProcess->setLocation(0.0f, 0.0f);
	m_pUnitOnProcess->setCmdNumber(0);
	// Unit ��Ͽ� ���
	pUnitOut->emplace_back(m_pUnitOnProcess);
	// �� None Unit�� ���α׷��� ���� ������ �� ����
	// ��ɾ� �����ڿ� ���
	pCmdOperator->addUnit(m_pUnitOnProcess);

	// ù��° Unit�� �Է������ϴ� Flow Linker ������ ����
	m_pLinkerOnProcess = std::make_shared<Linker>();
	LinkHelper::ConnectFlow(m_pUnitOnProcess, m_pLinkerOnProcess);
	// Flow Linker ��Ͽ� ���
	pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);


	// DNA �ؼ� ����
	const auto& data = m_dna.getData();

	// * ���� ó���ϴ� �ܰ踦 ��Ÿ��
	int sequence = 0;
	// * DNA���� ���� ��Ʈ�� ���� ��Ÿ��
	size_t bufferSize = 16;
	// * DNA���� ���� ��Ʈ�����͸� ������ ����
	std::vector<bool> partialData;
	size_t readCount = 0;
	// * DNA ������ ��
	const size_t halfSize = data.size() / 2;

	for (const auto& bit : data)
	{
		// �� ��Ʈ�� ����
		partialData.emplace_back(bit);

		// ���� DNA�� ���� �о����� Param���� �ܰ�(-1)�� ����
		// �̶����� readCount�� �������� �ʴ´�.
		if (readCount < halfSize)
			++readCount;
		else if(sequence == 0)
		{
			m_pUnitOnProcess = pUnitOut->at(0);

			sequence = -1;
		}
		
		// �о���� ��ŭ DNA�� �о�����
		if (partialData.size() >= bufferSize)
		{
			// �����͸� ó���ϰ�
			// ���� �ܰ迡�� �ʿ��� ������ ��Ʈ ���� �޴´�.
			bufferSize = proceedData(sequence,
				partialData,
				pUnitOut,
				pFlowLinkerOut,
				pParamLinkerOut,
				pCmdOperator);
			
			// ������ �ʱ�ȭ
			partialData.clear();

			// ���� ���� �ܰ迡�� �ʿ��� ������ ��Ʈ ���� ���ٸ�
			// DNA �ؼ��۾��� �����Ѵ�.
			if (bufferSize <= 0) break;
		}
	}


	m_pUnitOnProcess = nullptr;
	m_pLinkerOnProcess = nullptr;


	return 0;
}

//###############################################################

size_t BiogramEgg::proceedData(int& sequence,
	const std::vector<bool>& data,
	std::vector<UnitPtr>* pUnitOut,
	std::vector<LinkerPtr>* pFlowLinkerOut,
	std::vector<LinkerPtr>* pParamLinkerOut,
	CmdOperatorPtr pCmdOperator)
{
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
			// data�� 16��Ʈ�� ���̹Ƿ� �ִ밪�� 32767��� ����
			// �̿��ؼ� �ִ밪�� ���� �Ѵ� ���� ������ �����.
			int relativeIndex = toInt(data);
			if (relativeIndex > 32767 / 2)
			{
				relativeIndex -= 32767 / 2;
				relativeIndex *= -1;
			}

			// �Է����� �� Unit�� ã�� �����Ѵ�.
			auto relativeUnit = m_pUnitOnProcess->getRelativeFlowUnit(relativeIndex);
			if (relativeUnit)
			{
				// Param Linker ���� �� ����
				auto paramLinker = LinkHelper::ConnectParam(relativeUnit,
					m_pUnitOnProcess,
					m_dataFromPast % m_pUnitOnProcess->getParamCount());

				// Param Linker ��Ͽ� �߰�
				pParamLinkerOut->emplace_back(paramLinker);


				// ���� ���õ� Unit�� ���� Param ������ �� ���� ���θ�
				// ���� �ܰ�(-1)���� ���� �����κ��� �����Ѵ�.
				if (m_dataFromPast < 2)
				{
					// ���� Unit�� ������ Param �����۾��� �ϵ��� �Ѵ�.
					m_pUnitOnProcess = m_pUnitOnProcess->getRelativeFlowUnit(1);

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
		else return 0;
	} return 16;

	case -1: {
		// �����ܰ�(-2)���� �� ���� �޴´�.
		m_dataFromPast = bitTotal(data) % 4;

		sequence = -2;
	} return 16;

	case 0: {
		/*
		* ���ο� Unit�� �����ϰ� �� Unit���� ���õǾ��ִ� Unit��
		* �Է������Ͽ� Flow Linker�� �����Ѵ�.
		*/

		// ���� ���� Unit�� ��ǥ�� ���õ� Unit�� ��ǥ������ ������̴�.
		float angle = static_cast<float>(toInt(data));
		float length = angle / 32767.0f * 16.0f;
		Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
		if (m_pUnitOnProcess)
			pos += m_pUnitOnProcess->getLocation();

		// �� Unit ���� �� ��ġ ����
		auto unit = std::make_shared<Unit>();
		unit->setLocation(pos);

		if (m_pLinkerOnProcess)
			LinkHelper::ConnectFlow(m_pLinkerOnProcess, unit);

		// ������ ���� �� Flow Linker�� ������ �����ص�
		m_pLinkerOnProcess = std::make_shared<Linker>();
		LinkHelper::ConnectFlow(unit, m_pLinkerOnProcess);
		// Flow Linker ��Ͽ� �߰�
		pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);

		// ���⼭ �����ߴ� Unit�� ����
		m_pUnitOnProcess = unit;

		// Unit ��Ͽ� �߰�
		pUnitOut->emplace_back(unit);

		sequence = 1;
	} return 16;

	case 1: {
		/*
		* ���õ� Unit�� �ִٸ� DNA�κ��� ���� ����
		* �ش� Unit�� ��ɾ� ��ȣ�� �����Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			int cmdNum = toInt(data) % pCmdOperator->getCmdFunctionCount();
			m_pUnitOnProcess->setCmdNumber(cmdNum);
		}

		sequence = 2;
	} return 16;

	case 2: {
		/*
		* ���õ� Unit�� �ִٸ� DNA�κ��� ���� ����
		* �ش� Unit�� �޸� ������ �����Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			// ���� ���� �ٷ� ���°� �ƴ϶�
			// �ִ밪�� ���� �������� ������ ����� ��ȯ�Ѵ�.
			int memory = toInt(data);
			if (memory > 32767 / 2)
			{
				memory -= 32767 / 2;
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

		m_dataFromPast = bitTotal(data);
		if (m_dataFromPast < 4)
		{
			sequence = 4;
		}
		else
		{
			m_dataFromPast = 0;

			sequence = 0;
		}
	} return 16;

	case 4: {
		/*
		* ���õ� Unit�� �ִٸ� �� Unit�� ��������Ͽ�
		* ���ο� None Unit�� ������ Param ������ �Ѵ�.
		*/

		if (m_pUnitOnProcess)
		{
			// �� Unit�� ��ġ�� ����Ѵ�.
			float angle = static_cast<float>(toInt(data));
			float length = angle / 32767.0f * 8.0f;
			Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
			pos += m_pUnitOnProcess->getLocation();

			// �� Unit�� �����ϰ� �����Ѵ�.
			auto unit = std::make_shared<Unit>();
			unit->setLocation(pos);
			unit->setCmdNumber(0);
			unit->setMemory(static_cast<double>(angle / 32767.0f) * 64.0);
			// Unit ��Ͽ� �߰�
			pUnitOut->emplace_back(unit);

			// �� Param Linker�� �����ϰ� �����Ѵ�.
			auto paramLinker = LinkHelper::ConnectParam(unit,
				m_pUnitOnProcess,
				m_dataFromPast % m_pUnitOnProcess->getParamCount());
			// Param Linker ��Ͽ� �߰�
			pParamLinkerOut->emplace_back(paramLinker);
			
			// ���� �ܰ�(3)�κ��� ���� ���� ����
			// ���� Unit�� ���� Param ������ �ѹ� �� ����
			// ó�� �ܰ�(0)�� ���ư��� �����Ѵ�.
			if (m_dataFromPast < 2)
				sequence = 0;
			else
			{
				m_dataFromPast = 3 - m_dataFromPast;

				sequence = 4;
			}
		}
	} return 16;
	}


	return 0;
}


int BiogramEgg::toInt(const std::vector<bool>& data)
{
	int result = 0;

	int count = 0;
	for (const auto& bit : data)
	{
		result |= ((bit ? 1 : 0) << count);

		++count;
	}


	return result;
}


int BiogramEgg::bitTotal(const std::vector<bool>& data)
{
	int result = 0;

	for (const auto& bit : data)
	{
		if (bit)
			++result;
	}


	return result;
}

