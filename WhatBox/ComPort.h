#pragma once

#include <memory>
#include <unordered_map>

class Memory;



























class ComPort
{
public:
	ComPort();
	virtual ~ComPort();


protected:
	std::shared_ptr<Memory> m_connectedMem;
	std::unordered_map<int, int> m_assignedInfo;


public:
	int connectMemory(std::shared_ptr<Memory> pMem);
	/*
	* portNum���� �޸��� address�� ������ �� �ֵ���
	  ����մϴ�.
	* @Return: �̹� ��ϵ� portNum�̸� false�� ��ȯ.
	*/
	bool assignPort(int portNum, int address);


public:
	double readPort(int portNum);
	bool writePort(int portNum, double value);


public:
	std::shared_ptr<const Memory> getConnectedMemory() const;
	const std::unordered_map<int, int>& getConnectionInfo() const;
};

