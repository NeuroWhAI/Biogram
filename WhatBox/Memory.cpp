#include "Memory.h"


























const int Memory::MAX_ADDRESS = 100000;

//###############################################################

Memory::Memory()
{
	// 음주소 메모리의 0번지는 null로 사용되므로 항상 존재해야함.
	m_negativeMemory.emplace_back(std::make_pair(false, 0.0));
}


Memory::~Memory()
{

}

//###############################################################

bool Memory::assignAddress(int address)
{
	// 메모리의 최대 범위를 넘어서면 할당하지 않음
	if (std::abs(address) > MAX_ADDRESS)
		return false;

	// 메모리 할당
	if (address < 0)
	{
		size_t index = static_cast<size_t>(-address);
		return assignAddressTo(m_negativeMemory, index,
			m_negativeAddressList, address);
	}
	else
	{
		size_t index = static_cast<size_t>(address);
		return assignAddressTo(m_memory, index,
			m_addressList, address);
	}


	return false;
}

//-----------------------------------------------------------------

double Memory::read(int address) const
{
	const auto& cell = findCell(address);
	
	
	return cell.second;
}


void Memory::write(int address, double value)
{
	auto& cell = findCell(address);

	if (cell.first)
		cell.second = value;
}


void Memory::clear()
{
	m_memory.clear();
	m_negativeMemory.clear();

	m_addressList.clear();
	m_negativeAddressList.clear();

	// 음주소 메모리의 0번지는 사용하지 않지만 항상 존재해야함.
	m_negativeMemory.emplace_back(std::make_pair(false, 0.0));
}

//-----------------------------------------------------------------

bool Memory::findAddress(int address, int* pOffsetOut) const
{
	const auto& cell = findCell(address);


	// 해당 메모리 공간이 유효하면
	if (cell.first)
	{
		if (pOffsetOut != nullptr)
		{
			*pOffsetOut = 0;
		}


		return true;
	}


	// 해당 메모리 공간이 유효하지 않으면
	int minOffset = std::numeric_limits<int>::max();

	if (address < 0)
	{
		if (m_negativeAddressList.size() <= 0)
		{
			if (m_addressList.size() > 0)
				minOffset = std::abs(m_addressList[0] - address);
		}
		else
		{
			const size_t negativeAdrCount = m_negativeAddressList.size();
			for (size_t i = 0; i < negativeAdrCount; ++i)
			{
				if (m_negativeAddressList[i] < address)
				{
					minOffset = std::abs(m_negativeAddressList[i] - address);

					if (i > 0)
					{
						int offset = std::abs(m_negativeAddressList[i - 1] - address);
						if (offset < minOffset)
							minOffset = offset;
					}
					else if(m_addressList.size() > 0)
					{
						int offset = std::abs(m_addressList[0] - address);
						if (offset < minOffset)
							minOffset = offset;
					}

					break;
				}
			}
		}
	}
	else
	{
		if (m_addressList.size() <= 0)
		{
			if (m_negativeAddressList.size() > 0)
				minOffset = std::abs(m_negativeAddressList[0] - address);
		}
		else
		{
			const size_t adrCount = m_addressList.size();
			for (size_t i = 0; i < adrCount; ++i)
			{
				if (m_addressList[i] > address)
				{
					minOffset = std::abs(m_addressList[i] - address);

					if (i > 0)
					{
						int offset = std::abs(m_addressList[i - 1] - address);
						if (offset < minOffset)
							minOffset = offset;
					}
					else if (m_negativeAddressList.size() > 0)
					{
						int offset = std::abs(m_negativeAddressList[0] - address);
						if (offset < minOffset)
							minOffset = offset;
					}

					break;
				}
			}
		}
	}

	if (pOffsetOut != nullptr)
	{
		*pOffsetOut = minOffset;
	}


	return false;
}

//###############################################################

std::pair<bool, double>& Memory::findCell(int address) 
{
	if (address < 0)
	{
		size_t index = static_cast<size_t>(-address);

		if (index < m_negativeMemory.size())
		{
			return m_negativeMemory[index];
		}
	}
	else
	{
		size_t index = static_cast<size_t>(address);

		if (index < m_memory.size())
		{
			return m_memory[index];
		}
	}


	return m_negativeMemory[0];
}


const std::pair<bool, double>& Memory::findCell(int address) const
{
	if (address < 0)
	{
		size_t index = static_cast<size_t>(-address);

		if (index < m_negativeMemory.size())
		{
			return m_negativeMemory[index];
		}
	}
	else
	{
		size_t index = static_cast<size_t>(address);

		if (index < m_memory.size())
		{
			return m_memory[index];
		}
	}


	return m_negativeMemory[0];
}


bool Memory::assignAddressTo(
	std::vector<std::pair<bool, double>>& memory,
	size_t index,
	std::vector<int>& addressList,
	int address)
{
	// 메모리의 최대범위를 넘어서면 할당하지 않음
	if (index > MAX_ADDRESS)
		return false;

	// 메모리 할당
	if (index >= memory.size())
	{
		while (index > memory.size())
			memory.emplace_back(std::make_pair(false, 0.0));

		memory.emplace_back(std::make_pair(true, 0.0));
		addressList.emplace_back(address);
	}
	else
	{
		if (memory[index].first)
			return false;
		else
		{
			memory[index].first = true;
			addressList.emplace_back(address);
		}
	}


	return true;
}

//###############################################################

const std::vector<std::pair<bool, double>>&
Memory::getMemory() const
{
	return m_memory;
}


const std::vector<std::pair<bool, double>>&
Memory::getNegativeMemory() const
{
	return m_negativeMemory;
}


size_t Memory::getAssignedCellCount() const
{
	return m_addressList.size() + m_negativeAddressList.size();
}

