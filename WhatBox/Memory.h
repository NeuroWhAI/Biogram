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
	* �޸��� address�� ������ �����͸� �о�ɴϴ�.
	* ��, �ش� �ּҰ� ���ٸ� 0.0�� ��ȯ�մϴ�.
	* @Return: address�� �ش��ϴ� ��
	*/
	double read(int address);
	/*
	* �޸��� address�� ������ value�� ����ϴ�.
	* �ش� �ּҰ� ���ٸ� ����� ���ϴ�.
	*/
	void write(int address, double value);
	void clear();

	/*
	* �޸𸮿� address�� �ش��ϴ� ������ �ִ��� Ȯ���մϴ�.
	  ���ٸ� ���� ����� �������� �ּ���(���밪)�� pOffsetOut�� ���ϴ�.
	* @Return: �������� ����
	*/
	bool findAddress(int address, int* pOffsetOut = nullptr) const;


public:
	const std::unordered_map<int, double>& getMemory() const;
};

