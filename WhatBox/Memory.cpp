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
	return m_memory[address];
}


void Memory::write(int address, double value)
{
	m_memory[address] = value;
}


void Memory::clear()
{
	m_memory.clear();
}

//###############################################################

const std::unordered_map<int, double>& Memory::getMemory() const
{
	return m_memory;
}

