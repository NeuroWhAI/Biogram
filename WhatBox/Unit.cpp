#include "Unit.h"

#include "Linker.h"



























Unit::Unit()
	: m_cmdNumber(0)
	, m_memory(0.0)

	, m_timeGage(0.0)
{
	m_mass = 1.0 + m_cmdNumber;

	updateRadius();
}


Unit::~Unit()
{

}

//###############################################################

int Unit::clear()
{
	m_pInFlowLinker = nullptr;
	m_pOutFlowLinker = nullptr;

	for (auto& linker : m_pParamLinkers)
		linker = nullptr;

	for (auto& linker : m_pOutParamLinkers)
		linker = nullptr;
	m_pOutParamLinkers.clear();


	return 0;
}

//###############################################################

void Unit::updateRadius()
{
	m_radius = 0.0625f * m_cmdNumber + 4.0f;
}

//###############################################################

void Unit::setCmdNumber(int cmdNumber)
{
	m_mass += cmdNumber - m_cmdNumber;

	m_cmdNumber = cmdNumber;

	updateRadius();
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

size_t Unit::getParamCount() const
{
	return m_pParamLinkers.size();
}


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

bool Unit::addOutParamLinker(std::shared_ptr<Linker> pOutParamLinker)
{
	m_pOutParamLinkers.emplace_back(pOutParamLinker);


	return true;
}


bool Unit::removeOutParamLinker(std::shared_ptr<Linker> pOutParamLinker)
{
	size_t count = 0;
	for (auto& linkerPtr : m_pOutParamLinkers)
	{
		if (linkerPtr == pOutParamLinker)
		{
			m_pOutParamLinkers.erase(m_pOutParamLinkers.begin() + count);
			
			
			return true;
		}

		++count;
	}


	return false;
}


const std::vector<std::shared_ptr<Linker>>& Unit::getOutParamLinkerList() const
{
	return m_pOutParamLinkers;
}

//---------------------------------------------------------------

std::shared_ptr<Unit> Unit::getRelativeFlowUnit(int relativeIndex) const
{
	const Unit* pNext = nullptr;


	if (relativeIndex < 0)
	{
		if (m_pInFlowLinker)
		{
			pNext = m_pInFlowLinker->getInUnit().get();

			for (int i = -1; i > relativeIndex && pNext != nullptr;
			--i)
			{
				const auto pInLinker = pNext->getInLinker().get();

				if (pInLinker != nullptr)
					pNext = pInLinker->getInUnit().get();
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
			pNext = m_pOutFlowLinker->getOutUnit().get();

			for (int i = 1; i < relativeIndex && pNext != nullptr;
			++i)
			{
				const auto pOutLinker = pNext->getOutLinker().get();

				if (pOutLinker != nullptr)
					pNext = pOutLinker->getOutUnit().get();
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
		return getSharedPtrOfThis();
	}


	if (pNext != nullptr)
		return pNext->getSharedPtrOfThis();
	return nullptr;
}


std::shared_ptr<Unit> Unit::getSharedPtrOfThis() const
{
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

		for (const auto& pLinker : m_pOutParamLinkers)
		{
			if (pLinker && pLinker->getInUnit())
				return pLinker->getInUnit();
		}
	}


	return nullptr;
}

//###############################################################

void Unit::setTimeGage(double gage)
{
	m_timeGage = gage;
}


double Unit::getTimeGage() const
{
	return m_timeGage;
}

