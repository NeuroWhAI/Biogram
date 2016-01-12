#include "VoidGameDevice.h"

#include "System.h"

#include "Director.h"



























VoidGameDevice::VoidGameDevice()
	: Device({
		{ 0, 100 },
		{ 1, 100 },
		{ 2, 100 } })

	, m_bBombInLeft(false)
	, m_failCount(0)
	, m_successCount(0)
{

}


VoidGameDevice::~VoidGameDevice()
{

}

//#################################################################

int VoidGameDevice::init()
{
	m_bBombInLeft = false;
	m_failCount = 0;
	m_successCount = 0;


	if (m_bBombInLeft)
	{
		writeCom(0, 1.0);
		writeCom(1, 0.0);
	}
	else
	{
		writeCom(0, 0.0);
		writeCom(1, 1.0);
	}


	return 0;
}


int VoidGameDevice::update(double timeSpeed)
{
	if (m_bBombInLeft)
	{
		if (readCom(2) > 0.0)
		{
			++m_successCount;

			m_bBombInLeft = !m_bBombInLeft;
		}
		else
			++m_failCount;
	}
	else
	{
		if (readCom(2) < 0.0)
		{
			++m_successCount;

			m_bBombInLeft = !m_bBombInLeft;
		}
		else
			++m_failCount;
	}


	if (m_bBombInLeft)
	{
		writeCom(0, 1.0);
		writeCom(1, 0.0);
	}
	else
	{
		writeCom(0, 0.0);
		writeCom(1, 1.0);
	}


	return 0;
}


int VoidGameDevice::render()
{
	System::getInstance().getObjectViewer().
		draw(*this);


	return 0;
}

//#################################################################

double VoidGameDevice::evaluate(std::shared_ptr<Director> pDirector)
{
	return pDirector->evaluate(*this);
}

//#################################################################

size_t VoidGameDevice::getFailCount() const
{
	return m_failCount;
}


size_t VoidGameDevice::getSuccessCount() const
{
	return m_successCount;
}

