#include "Memory.h"



























Memory::Memory()
{

}


Memory::~Memory()
{

}

//###############################################################

bool Memory::assignAddress(int address)
{
	auto result = m_memory.insert(std::make_pair(address, 0.0));

	if (result.second)
	{
		m_addressList.emplace_back(address);


		return true;
	}


	return false;
}

//-----------------------------------------------------------------

double Memory::read(int address)
{
	auto it = m_memory.find(address);

	if (it == m_memory.end())
		return 0.0;
	return it->second;
}


void Memory::write(int address, double value)
{
	auto it = m_memory.find(address);

	if (it != m_memory.end())
		it->second = value;
}


void Memory::clear()
{
	m_memory.reserve(0);
	m_memory.clear();
	m_addressList.clear();
}

//-----------------------------------------------------------------

bool Memory::findAddress(int address, int* pOffsetOut) const
{
	auto pos = m_memory.find(address);
	if (pos == m_memory.end())
	{
		int minOffset = std::numeric_limits<int>::max();

		for (auto& currentAdr : m_addressList)
		{
			int offset = std::abs(currentAdr - address);
			if (offset < minOffset)
			{
				minOffset = offset;
			}
		}

		if (pOffsetOut != nullptr)
		{
			*pOffsetOut = minOffset;
		}


		return false;
	}


	if (pOffsetOut != nullptr)
	{
		*pOffsetOut = 0;
	}

	return true;
}

//###############################################################

const std::unordered_map<int, double>& Memory::getMemory() const
{
	return m_memory;
}


size_t Memory::getAssignedCellCount() const
{
	return m_addressList.size();
}

