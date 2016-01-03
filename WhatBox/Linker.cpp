#include "Linker.h"



























Linker::Linker()
	: m_pInUnit(nullptr)
	, m_pOutUnit(nullptr)
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
	return m_pInUnit;
}


std::shared_ptr<Unit> Linker::getOutUnit() const
{
	return m_pOutUnit;
}

