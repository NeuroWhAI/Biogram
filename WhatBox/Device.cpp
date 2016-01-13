#include "Device.h"

#include "ComPort.h"
#include "BiogramCage.h"



























Device::Device(const std::vector<std::pair<int, int>>& portNum_address,
	int thickness)
	: m_pConnectedCage(nullptr)
	
	, m_pComPort(nullptr)
	, m_connectionInfo(createThickComPort(portNum_address, thickness))
{

}


Device::~Device()
{

}

//#################################################################

int Device::init()
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

double Device::readCom(int portNum) const
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

//#################################################################

std::vector<std::pair<int, int>> Device::createThickComPort(
	const std::vector<std::pair<int, int>>& portNum_address,
	int thickness)
{
	std::vector<std::pair<int, int>> portInfo;

	if (thickness == 0)
		return portInfo;

	for (const auto& info : portNum_address)
	{
		int dir = ((thickness < 0) ? -1 : 1);
		thickness = std::abs(thickness);
		for (int i = 0; i < thickness; ++i)
		{
			portInfo.emplace_back(std::make_pair(
				info.first, i * dir + info.second));
		}
	}


	return portInfo;
}

