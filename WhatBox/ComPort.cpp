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
	if (m_connectedMem)
	{
		auto pos = m_assignedInfo.find(portNum);
		if (pos != m_assignedInfo.end())
		{
			double result = 0.0;

			for (auto& address : pos->second)
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
	if (m_connectedMem)
	{
		auto pos = m_assignedInfo.find(portNum);
		if (pos != m_assignedInfo.end())
		{
			for (auto& address : pos->second)
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


const std::unordered_map<int, std::vector<int>>& ComPort::getConnectionInfo() const
{
	return m_assignedInfo;
}

