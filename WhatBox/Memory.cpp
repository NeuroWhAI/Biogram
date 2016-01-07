#include "Memory.h"



























Memory::Memory()
{

}


Memory::~Memory()
{

}

//###############################################################

double Memory::read(int address)
{
	auto it = m_memory.find(address);

	if (it == m_memory.end())
		return 0.0;
	return m_memory[address];
}


void Memory::write(int address, double value)
{
	m_memory[address] = value;
}


void Memory::clear()
{
	m_memory.reserve(0);
	m_memory.clear();
}

//-----------------------------------------------------------------

bool Memory::findAddress(int address, int* pOffsetOut) const
{
	auto pos = m_memory.find(address);
	if (pos == m_memory.end())
	{
		int minOffset = std::numeric_limits<int>::max();

		for (auto& cell : m_memory)
		{
			int offset = std::abs(cell.first - address);
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

