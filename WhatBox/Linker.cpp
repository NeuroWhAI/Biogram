#include "Linker.h"

#include "Unit.h"



























Linker::Linker()
	: m_pInUnit(nullptr)
	, m_pOutUnit(nullptr)

	, m_realLength(1.0f)
{

}


Linker::Linker(std::shared_ptr<Unit> pInUnit, std::shared_ptr<Unit> pOutUnit)
	: m_pInUnit(pInUnit)
	, m_pOutUnit(pOutUnit)
{
	updateRealLength();
}


Linker::~Linker()
{

}

//###############################################################

int Linker::update(double timePitch)
{
	


	return 0;
}

//###############################################################

int Linker::setInUnit(std::shared_ptr<Unit> pInUnit)
{
	m_pInUnit = pInUnit;

	updateRealLength();


	return 0;
}


int Linker::setOutUnit(std::shared_ptr<Unit> pOutUnit)
{
	m_pOutUnit = pOutUnit;

	updateRealLength();


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

//###############################################################

float Linker::getRealLength() const
{
	return m_realLength;
}

//###############################################################

bool Linker::updateRealLength()
{
	if (m_pInUnit && m_pOutUnit)
	{
		auto subVec = m_pInUnit->getLocation() - m_pOutUnit->getLocation();
		m_realLength = subVec.getLength();


		return true;
	}
	else
	{
		m_realLength = 1.0f;
	}


	return false;
}

