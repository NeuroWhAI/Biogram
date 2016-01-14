#include "ComPort.h"

#include "Memory.h"



























ComPort::ComPort()
	: m_connectedMem(nullptr)
{

}


ComPort::~ComPort()
{

}

//#################################################################

int ComPort::connectMemory(std::shared_ptr<Memory> pMem)
{
	m_connectedMem = pMem;


	return 0;
}


bool ComPort::assignPort(int portNum, int address)
{
	if (portNum < 0)
		throw std::invalid_argument("portNum < 0");


	size_t portCount = static_cast<size_t>(portNum);
	while (portCount >= m_assignedInfo.size())
		m_assignedInfo.emplace_back();


	for (auto& adr : m_assignedInfo[portNum])
	{
		if (adr == address)
			return false;
	}

	m_assignedInfo[portNum].emplace_back(address);


	return true;
}

//#################################################################

double ComPort::readPort(int portNum) const
{
	if (portNum < 0)
		throw std::invalid_argument("portNum < 0");


	if (m_connectedMem)
	{
		if (static_cast<size_t>(portNum) < m_assignedInfo.size())
		{
			double result = 0.0;

			for (auto& address : m_assignedInfo[portNum])
			{
				result += m_connectedMem->read(address);
			}

			return result;
		}
	}


	return 0.0;
}


bool ComPort::writePort(int portNum, double value)
{
	if (portNum < 0)
		return 0.0;

	if (m_connectedMem)
	{
		if (static_cast<size_t>(portNum) < m_assignedInfo.size())
		{
			for (auto& address : m_assignedInfo[portNum])
			{
				m_connectedMem->write(address, value);
			}


			return true;
		}
	}


	return false;
}

//#################################################################

std::shared_ptr<const Memory> ComPort::getConnectedMemory() const
{
	return m_connectedMem;
}


const std::vector<std::vector<int>>& ComPort::getConnectionInfo() const
{
	return m_assignedInfo;
}

