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
	// * first: 할당여부
	// * second: 메모리 값
	std::vector<std::pair<bool, double>> m_memory, m_negativeMemory;
	std::vector<int> m_addressList, m_negativeAddressList;


public:
	/*
	* 메모리에서 address에 해당하는 공간을 할당합니다.
	* 해당 공간은 0으로 초기화 됩니다.
	* @Return: 이미 할당되었으면 false
	*/
	bool assignAddress(int address);

	/*
	* 메모리의 address에 접근해 데이터를 읽어옵니다.
	* 단, 해당 주소가 없다면 0.0을 반환합니다.
	* @Return: address에 해당하는 값
	*/
	double read(int address) const;
	/*
	* 메모리의 address에 접근해 value를 덮어씁니다.
	* 해당 주소가 없다면 쓰지않습니다.
	*/
	void write(int address, double value);
	void clear();

	/*
	* 메모리에 address에 해당하는 공간이 있는지 확인합니다.
	  없다면 가장 가까운 공간과의 주소차(절대값)를 pOffsetOut에 씁니다.
	* @Return: 공간존재 여부
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

