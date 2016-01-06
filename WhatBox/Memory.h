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
	double read(int address);
	void write(int address, double value);
	void clear();


public:
	const std::unordered_map<int, double>& getMemory() const;
};

