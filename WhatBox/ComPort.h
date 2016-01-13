#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

class Memory;



























class ComPort
{
public:
	ComPort();
	virtual ~ComPort();


protected:
	std::shared_ptr<Memory> m_connectedMem;
	std::unordered_map<int, std::vector<int>> m_assignedInfo;


public:
	int connectMemory(std::shared_ptr<Memory> pMem);
	/*
	* portNum으로 메모리의 address에 접근할 수 있도록
	  등록합니다.
	* @Return: 이미 등록된 portNum이면 false를 반환.
	*/
	bool assignPort(int portNum, int address);


public:
	double readPort(int portNum) const;
	bool writePort(int portNum, double value);


public:
	std::shared_ptr<const Memory> getConnectedMemory() const;
	const std::unordered_map<int, std::vector<int>>& getConnectionInfo() const;
};

