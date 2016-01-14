#pragma once

#include <vector>
#include <ostream>
#include <istream>
#include <random>



























class BiogramDNA
{
public:
	explicit BiogramDNA(bool bFillRandomly = false);
	explicit BiogramDNA(const std::vector<bool> bitData);
	virtual ~BiogramDNA();


protected:
	static std::mt19937 s_randEngine;
	std::vector<bool> m_data;


public:
	int saveTo(std::ostream& osr) const;
	int loadFrom(std::istream& isr);
	const std::vector<bool>& getData() const;
	size_t getLength() const;


public:
	int mutate(double rate);
	int combine(const BiogramDNA& other);
};

