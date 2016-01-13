#pragma once

#include <unordered_map>
#include <vector>



























class Memory
{
public:
	static const int MAX_ADDRESS;


public:
	Memory();
	virtual ~Memory();


protected:
	// * first: �Ҵ翩��
	// * second: �޸� ��
	std::vector<std::pair<bool, double>> m_memory, m_negativeMemory;
	std::vector<int> m_addressList, m_negativeAddressList;


public:
	/*
	* �޸𸮿��� address�� �ش��ϴ� ������ �Ҵ��մϴ�.
	* �ش� ������ 0���� �ʱ�ȭ �˴ϴ�.
	* @Return: �̹� �Ҵ�Ǿ����� false
	*/
	bool assignAddress(int address);

	/*
	* �޸��� address�� ������ �����͸� �о�ɴϴ�.
	* ��, �ش� �ּҰ� ���ٸ� 0.0�� ��ȯ�մϴ�.
	* @Return: address�� �ش��ϴ� ��
	*/
	double read(int address) const;
	/*
	* �޸��� address�� ������ value�� ����ϴ�.
	* �ش� �ּҰ� ���ٸ� �����ʽ��ϴ�.
	*/
	void write(int address, double value);
	void clear();

	/*
	* �޸𸮿� address�� �ش��ϴ� ������ �ִ��� Ȯ���մϴ�.
	  ���ٸ� ���� ����� �������� �ּ���(���밪)�� pOffsetOut�� ���ϴ�.
	* @Return: �������� ����
	*/
	bool findAddress(int address, int* pOffsetOut = nullptr) const;


protected:
	std::pair<bool, double>& findCell(int address);
	const std::pair<bool, double>& findCell(int address) const;
	bool assignAddressTo(
		std::vector<std::pair<bool, double>>& memory,
		size_t index,
		std::vector<int>& addressList,
		int address);


public:
	const std::vector<std::pair<bool, double>>&
		getMemory() const;
	const std::vector<std::pair<bool, double>>&
		getNegativeMemory() const;
	size_t getAssignedCellCount() const;
};

