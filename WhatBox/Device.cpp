#include "Device.h"

#include "ComPort.h"
#include "BiogramCage.h"



























Device::Device(const std::vector<std::pair<int, int>>& portNum_address)
	: m_pConnectedCage(nullptr)
	
	, m_pComPort(nullptr)
	, m_connectionInfo(portNum_address)
{

}


Device::~Device()
{

}

//#################################################################

int Device::readyForNextG()
{



	return 0;
}


int Device::update(double timeSpeed)
{



	return 0;
}


int Device::render()
{
	


	return 0;
}

//#################################################################

int Device::connectTo(std::shared_ptr<BiogramCage> pCage)
{
	m_pConnectedCage = pCage;

	m_pComPort = pCage->assignComPort(m_connectionInfo);


	return 0;
}

//#################################################################

double Device::readCom(int portNum)
{
	if (m_pComPort)
	{
		return m_pComPort->readPort(portNum);
	}


	return 0.0;
}


bool Device::writeCom(int portNum, double value)
{
	if (m_pComPort)
	{
		return m_pComPort->writePort(portNum, value);
	}


	return false;
}

//#################################################################

double Device::evaluate(std::shared_ptr<Director> pDirector)
{
	return 0.0;
}

//#################################################################

std::shared_ptr<BiogramCage> Device::getConnectedCage()
{
	return m_pConnectedCage;
}


std::shared_ptr<const ComPort> Device::getComPort() const
{
	return m_pComPort;
}

