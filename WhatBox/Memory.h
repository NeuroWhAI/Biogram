#pragma once

#include <unordered_map>



























class Memory
{
public:
	Memory();
	virtual ~Memory();


protected:
	std::unordered_map<int, double> m_memory;


public:
	/*
	* 메모리의 address에 접근해 데이터를 읽어옵니다.
	* 단, 해당 주소가 없다면 0.0을 반환합니다.
	* @Return: address에 해당하는 값
	*/
	double read(int address);
	/*
	* 메모리의 address에 접근해 value를 덮어씁니다.
	* 해당 주소가 없다면 만들고 씁니다.
	*/
	void write(int address, double value);
	void clear();

	/*
	* 메모리에 address에 해당하는 공간이 있는지 확인합니다.
	  없다면 가장 가까운 공간과의 주소차(절대값)를 pOffsetOut에 씁니다.
	* @Return: 공간존재 여부
	*/
	bool findAddress(int address, int* pOffsetOut = nullptr) const;


public:
	const std::unordered_map<int, double>& getMemory() const;
};

