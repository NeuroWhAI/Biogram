#include "Unit.h"



























Unit::Unit()
	: m_cmdNumber(0)
	, m_memory(0.0)
{

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

