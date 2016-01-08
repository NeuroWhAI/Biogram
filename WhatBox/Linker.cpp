#include "Linker.h"

#include "Unit.h"



























Linker::Linker()
{

}


Linker::Linker(std::shared_ptr<Unit> pInUnit, std::shared_ptr<Unit> pOutUnit)
	: m_pInUnit(pInUnit)
	, m_pOutUnit(pOutUnit)
{
	
}


Linker::~Linker()
{

}

//###############################################################

int Linker::clear()
{
	m_pInUnit.reset();
	m_pOutUnit.reset();


	return 0;
}

//###############################################################

int Linker::setInUnit(std::shared_ptr<Unit> pInUnit)
{
	m_pInUnit = pInUnit;


	return 0;
}


int Linker::setOutUnit(std::shared_ptr<Unit> pOutUnit)
{
	m_pOutUnit = pOutUnit;


	return 0;
}


std::shared_ptr<Unit> Linker::getInUnit() const
{
	return m_pInUnit.lock();
}


std::shared_ptr<Unit> Linker::getOutUnit() const
{
	return m_pOutUnit.lock();
}

