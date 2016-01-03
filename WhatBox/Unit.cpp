#include "Unit.h"

#include "Linker.h"



























Unit::Unit()
	: m_cmdNumber(0)
	, m_memory(0.0)

	, m_pInFlowLinker(nullptr)
	, m_pOutFlowLinker(nullptr)

	, m_timeGage(0.0)
{
	for (auto& paramLinker : m_pParamLinkers)
		paramLinker = nullptr;
}


Unit::~Unit()
{

}

//###############################################################

int Unit::update(double timePitch)
{
	m_location += m_speed * timePitch;


	return 0;
}

//###############################################################

void Unit::setCmdNumber(int cmdNumber)
{
	m_cmdNumber = cmdNumber;
}


int Unit::getCmdNumber() const
{
	return m_cmdNumber;
}

//---------------------------------------------------------------

void Unit::setMemory(double memory)
{
	m_memory = memory;
}


void Unit::addMemory(double deltaMemory)
{
	m_memory += deltaMemory;
}


double Unit::getMemory() const
{
	return m_memory;
}

//###############################################################

int Unit::setInLinker(std::shared_ptr<Linker> pInLinker)
{
	m_pInFlowLinker = pInLinker;


	return 0;
}


int Unit::setOutLinker(std::shared_ptr<Linker> pOutLinker)
{
	m_pOutFlowLinker = pOutLinker;


	return 0;
}


std::shared_ptr<Linker> Unit::getInLinker() const
{
	return m_pInFlowLinker;
}


std::shared_ptr<Linker> Unit::getOutLinker() const
{
	return m_pOutFlowLinker;
}

//---------------------------------------------------------------

int Unit::setParamLinker(std::shared_ptr<Linker> pParamLinker, int index)
{
	m_pParamLinkers[index] = pParamLinker;


	return 0;
}


std::shared_ptr<Linker> Unit::getParamLinker(int index) const
{
	return m_pParamLinkers[index];
}

//---------------------------------------------------------------

std::shared_ptr<Unit> Unit::getRelativeFlowUnit(int relativeIndex) const
{
	std::shared_ptr<Unit> pNext = nullptr;


	if (relativeIndex < 0)
	{
		if (m_pInFlowLinker)
		{
			pNext = m_pInFlowLinker->getInUnit();

			relativeIndex = -relativeIndex;

			for (int i = 1; i < relativeIndex && pNext; ++i)
			{
				auto pInLinker = pNext->getInLinker();

				if (pInLinker)
					pNext = pInLinker->getInUnit();
				else
				{
					pNext = nullptr;
					break;
				}
			}
		}
	}
	else if (relativeIndex > 0)
	{
		if (m_pOutFlowLinker)
		{
			pNext = m_pOutFlowLinker->getOutUnit();

			for (int i = 1; i < relativeIndex && pNext; ++i)
			{
				auto pOutLinker = pNext->getOutLinker();

				if (pOutLinker)
					pNext = pOutLinker->getOutUnit();
				else
				{
					pNext = nullptr;
					break;
				}
			}
		}
	}
	else
	{
		// 스마트포인터를 반환하기 위해서 다른 곳에서 찾아봄
		if (m_pInFlowLinker && m_pInFlowLinker->getOutUnit())
			return m_pInFlowLinker->getOutUnit();
		else if (m_pOutFlowLinker && m_pOutFlowLinker->getInUnit())
			return m_pOutFlowLinker->getInUnit();
		else
		{
			for (const auto& pLinker : m_pParamLinkers)
			{
				if (pLinker && pLinker->getOutUnit())
					return pLinker->getOutUnit();
			}
		}
	}


	return pNext;
}

//###############################################################

void Unit::setTimeGage(double gage)
{
	m_timeGage = gage;
}


void Unit::addTimeGage(double deltaGage)
{
	m_timeGage += deltaGage;
}


double Unit::getTimeGage() const
{
	return m_timeGage;
}

