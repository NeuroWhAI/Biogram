#include "BiogramEgg.h"

#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"

using UnitPtr = BiogramEgg::UnitPtr;
using LinkerPtr = BiogramEgg::LinkerPtr;



























BiogramEgg::BiogramEgg()
	: m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
{

}


BiogramEgg::BiogramEgg(const BiogramDNA& dna)
	: m_dna(dna)

	, m_pUnitOnProcess(nullptr)
	, m_pLinkerOnProcess(nullptr)
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
	std::vector<LinkerPtr>* pParamLinkerOut)
{
	// 처음은 None Unit으로
	m_pUnitOnProcess = std::make_shared<Unit>();
	m_pUnitOnProcess->setLocation(0.0f, 0.0f);
	m_pUnitOnProcess->setCmdNumber(0);
	pUnitOut->emplace_back(m_pUnitOnProcess);

	m_pLinkerOnProcess = std::make_shared<Linker>();
	LinkHelper::ConnectFlow(m_pUnitOnProcess, m_pLinkerOnProcess);
	pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);


	// DNA 해석 시작
	const auto& data = m_dna.getData();

	int sequence = 0;
	size_t bufferSize = sizeof(short) * 8;
	size_t readCount = 0;
	std::vector<bool> partialData;

	for (const auto& bit : data)
	{
		partialData.emplace_back(bit);

		++readCount;
		if (readCount >= bufferSize)
		{
			while (partialData.size() > bufferSize)
				partialData.pop_back();

			bufferSize = proceedData(sequence,
				partialData,
				pUnitOut,
				pFlowLinkerOut,
				pParamLinkerOut);
			
			partialData.clear();
			readCount = 0;

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
	std::vector<LinkerPtr>* pParamLinkerOut)
{
	switch (sequence)
	{
	case 0: {
		float angle = static_cast<float>(toInt(data));
		float length = angle / 32767.0f * 64.0f;
		Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
		if (m_pUnitOnProcess)
			pos += m_pUnitOnProcess->getLocation();

		auto unit = std::make_shared<Unit>();
		unit->setLocation(pos);

		if (m_pLinkerOnProcess)
			LinkHelper::ConnectFlow(m_pLinkerOnProcess, unit);

		m_pLinkerOnProcess = std::make_shared<Linker>();
		LinkHelper::ConnectFlow(unit, m_pLinkerOnProcess);
		pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);

		m_pUnitOnProcess = unit;

		pUnitOut->emplace_back(unit);

		sequence = 1;
	} return sizeof(short) * 8;

	case 1: {
		if (m_pUnitOnProcess)
		{
			int cmdNum = toInt(data) % 32;
			m_pUnitOnProcess->setCmdNumber(cmdNum);
		}

		sequence = 0;
	} return sizeof(short) * 8;
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

