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
	if (m_assignedInfo.find(portNum) == m_assignedInfo.end())
	{
		m_assignedInfo.insert(std::make_pair(portNum, address));


		return true;
	}


	return false;
}

//#################################################################

double ComPort::readPort(int portNum)
{
	if (m_connectedMem)
	{
		auto pos = m_assignedInfo.find(portNum);
		if (pos != m_assignedInfo.end())
		{
			return m_connectedMem->read(pos->second);
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
			m_connectedMem->write(pos->second, value);


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


const std::unordered_map<int, int>& ComPort::getConnectionInfo() const
{
	return m_assignedInfo;
}

