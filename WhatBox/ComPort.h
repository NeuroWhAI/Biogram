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
	* portNum���� �޸��� address�� ������ �� �ֵ���
	  ����մϴ�.
	* @Return: �̹� ��ϵ� portNum�̸� false�� ��ȯ.
	*/
	bool assignPort(int portNum, int address);


public:
	double readPort(int portNum) const;
	bool writePort(int portNum, double value);


public:
	std::shared_ptr<const Memory> getConnectedMemory() const;
	const std::unordered_map<int, std::vector<int>>& getConnectionInfo() const;
};

