#include "BiogramEgg.h"

#include "Unit.h"
#include "Linker.h"
#include "LinkHelper.h"
#include "CommandOperator.h"
#include "ObjectPool.h"

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


int BiogramEgg::buildBiogram(ObjectPool<Unit>& unitPool,
	ObjectPool<Linker>& linkerPool,
	std::vector<UnitPtr>* pUnitOut,
	std::vector<LinkerPtr>* pFlowLinkerOut,
	std::vector<LinkerPtr>* pParamLinkerOut,
	CmdOperatorPtr pCmdOperator)
{
	// 처음은 None Unit을 두고 시작
	m_pUnitOnProcess = unitPool.acquireObject();
	m_pUnitOnProcess->setLocation(0.0f, 0.0f);
	m_pUnitOnProcess->setCmdNumber(0);
	// Unit 목록에 등록
	pUnitOut->emplace_back(m_pUnitOnProcess);
	// 이 None Unit이 프로그램의 시작 지점이 될 것임
	// 명령어 수행자에 등록
	pCmdOperator->addUnit(m_pUnitOnProcess);

	// 첫번째 Unit을 입력으로하는 Flow Linker 생성후 연결
	m_pLinkerOnProcess = linkerPool.acquireObject();
	LinkHelper::ConnectFlow(m_pUnitOnProcess, m_pLinkerOnProcess);
	// Flow Linker 목록에 등록
	pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);


	// DNA 해석 시작
	const auto& data = m_dna.getData();

	// * 값을 처리하는 단계를 나타냄
	int sequence = 0;
	// * DNA에서 읽을 비트의 수를 나타냄
	size_t bufferSize = 16;
	// * DNA에서 읽을 위치를 나타냄
	auto currentPos = data.cbegin();
	// * DNA 길이
	const size_t dnaLength = data.size();
	// * DNA 길이의 반
	const size_t halfSize = dnaLength / 2;

	for (size_t d = 0; d < dnaLength; d += bufferSize)
	{
		currentPos = data.cbegin() + d;

		// 읽어야 할 만큼 남은 길이가 충분하지 않으면 종료
		if (d + bufferSize > dnaLength) break;

		// 만약 DNA의 반을 읽었으면 Param연결 단계(-1)로 설정
		// 이때부터 readCount는 증가하지 않는다.
		if(d >= halfSize
			&&
			sequence == 0)
		{
			m_pUnitOnProcess = (*pUnitOut)[0];

			sequence = -1;
		}
		
		// 데이터를 처리하고
		// 다음 단계에서 필요한 데이터 비트 수를 받는다.
		bufferSize = proceedData(sequence,
			currentPos, bufferSize,
			unitPool,
			linkerPool,
			pUnitOut,
			pFlowLinkerOut,
			pParamLinkerOut,
			pCmdOperator);

		// 만약 다음 단계에서 필요한 데이터 비트 수가 없다면
		// DNA 해석작업을 종료한다.
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
	int dataInt = toInt(begin, bufferSize);
	int dataBitTotal = bitTotal(begin, bufferSize);


	switch (sequence)
	{
	case -2: {
		/*
		* 현재 선택된 Unit을 출력으로하여
		* DNA로부터 지정된 Unit을 입력으로
		* Param Linker를 생성 및 연결한다.
		*/

		if (m_pUnitOnProcess)
		{
			// data는 16비트일 것이므로 최대값은 32767라는 것을
			// 이용해서 최대값의 반을 넘는 수는 음수로 만든다.
			int relativeIndex = dataInt;
			if (relativeIndex > 32767 / 2)
			{
				relativeIndex -= 32767 / 2;
				relativeIndex *= -1;
			}

			// 입력으로 할 Unit을 찾고 연결한다.
			auto relativeUnit = m_pUnitOnProcess->getRelativeFlowUnit(relativeIndex);
			if (relativeUnit)
			{
				// Param Linker 생성 및 연결
				auto paramLinker = LinkHelper::ConnectParam(relativeUnit,
					m_pUnitOnProcess,
					m_dataFromPast % m_pUnitOnProcess->getParamCount(),
					&linkerPool);

				// Param Linker 목록에 추가
				pParamLinkerOut->emplace_back(paramLinker);


				// 현재 선택된 Unit에 대해 Param 연결을 더 할지 여부를
				// 이전 단계(-1)에서 받은 값으로부터 결정한다.
				if (m_dataFromPast < 2)
				{
					// 다음 Unit을 선택해 Param 연결작업을 하도록 한다.
					m_pUnitOnProcess = m_pUnitOnProcess->getRelativeFlowUnit(1);

					sequence = -1;
				}
				else
				{
					// 현재 Unit에대해 한번 더 Param 연결을 시도한다.
					m_dataFromPast = 3 - m_dataFromPast;

					sequence = -2;
				}
			}
		}
		else return 0;
	} return 16;

	case -1: {
		// 다음단계(-2)에서 쓸 값을 받는다.
		m_dataFromPast = dataBitTotal % 4;

		sequence = -2;
	} return 16;

	case 0: {
		/*
		* 새로운 Unit을 생성하고 이 Unit에게 선택되어있는 Unit을
		* 입력으로하여 Flow Linker를 연결한다.
		*/

		// 새로 만들 Unit의 좌표는 선택된 Unit의 좌표에대해 상대적이다.
		float angle = static_cast<float>(dataInt);
		float length = angle / 32767.0f * 16.0f;
		Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
		if (m_pUnitOnProcess)
			pos += m_pUnitOnProcess->getLocation();

		// 새 Unit 생성 후 위치 설정
		auto unit = unitPool.acquireObject();
		unit->setLocation(pos);

		if (m_pLinkerOnProcess)
			LinkHelper::ConnectFlow(m_pLinkerOnProcess, unit);

		// 다음을 위한 새 Flow Linker를 생성후 연결해둠
		m_pLinkerOnProcess = linkerPool.acquireObject();
		LinkHelper::ConnectFlow(unit, m_pLinkerOnProcess);
		// Flow Linker 목록에 추가
		pFlowLinkerOut->emplace_back(m_pLinkerOnProcess);

		// 여기서 생성했던 Unit을 선택
		m_pUnitOnProcess = unit;

		// Unit 목록에 추가
		pUnitOut->emplace_back(unit);

		sequence = 1;
	} return 16;

	case 1: {
		/*
		* 선택된 Unit이 있다면 DNA로부터 얻은 값을
		* 해당 Unit의 명령어 번호로 설정한다.
		*/

		if (m_pUnitOnProcess)
		{
			int cmdNum = dataInt % pCmdOperator->getCmdFunctionCount();
			m_pUnitOnProcess->setCmdNumber(cmdNum);
		}

		sequence = 2;
	} return 16;

	case 2: {
		/*
		* 선택된 Unit이 있다면 DNA로부터 얻은 값을
		* 해당 Unit의 메모리 값으로 설정한다.
		*/

		if (m_pUnitOnProcess)
		{
			// 얻은 값을 바로 쓰는게 아니라
			// 최대값의 반을 기준으로 음수나 양수로 변환한다.
			int memory = dataInt;
			if (memory > 32767 / 2)
			{
				memory -= 32767 / 2;
				memory *= -1;
			}

			// 메모리 값 설정
			m_pUnitOnProcess->setMemory(memory);
		}

		sequence = 3;
	} return 8;

	case 3: {
		/*
		* DNA값을 토대로
		* Param 연결 단계(4)로 갈지 처음 단계(0)로 갈지 선택한다.
		*/

		m_dataFromPast = dataBitTotal;
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
		* 선택된 Unit이 있다면 이 Unit을 출력으로하여
		* 새로운 None Unit을 생성해 Param 연결을 한다.
		*/

		if (m_pUnitOnProcess)
		{
			// 새 Unit의 위치를 계산한다.
			float angle = static_cast<float>(dataInt);
			float length = angle / 32767.0f * 8.0f;
			Utility::PointF pos(cosf(angle) * length, sinf(angle) * length);
			pos += m_pUnitOnProcess->getLocation();

			// 새 Unit을 생성하고 설정한다.
			auto unit = unitPool.acquireObject();
			unit->setLocation(pos);
			unit->setCmdNumber(0);
			unit->setMemory(static_cast<double>(angle / 32767.0f) * 64.0);
			// Unit 목록에 추가
			pUnitOut->emplace_back(unit);

			// 새 Param Linker를 생성하고 연결한다.
			auto paramLinker = LinkHelper::ConnectParam(unit,
				m_pUnitOnProcess,
				m_dataFromPast % m_pUnitOnProcess->getParamCount(),
				&linkerPool);
			// Param Linker 목록에 추가
			pParamLinkerOut->emplace_back(paramLinker);
			
			// 이전 단계(3)로부터 받은 값을 토대로
			// 현재 Unit에 대해 Param 연결을 한번 더 할지
			// 처음 단계(0)로 돌아갈지 결정한다.
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


int BiogramEgg::toInt(std::vector<bool>::const_iterator begin,
	size_t size)
{
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

