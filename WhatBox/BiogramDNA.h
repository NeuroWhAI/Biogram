#pragma once

#include <vector>
#include <ostream>
#include <istream>



























class BiogramDNA
{
public:
	BiogramDNA();
	explicit BiogramDNA(unsigned long seed);
	explicit BiogramDNA(const std::vector<bool> bitData);
	virtual ~BiogramDNA();


protected:
	std::vector<bool> m_data;


public:
	int saveTo(std::ostream& osr) const;
	int loadFrom(std::istream& isr);
	const std::vector<bool>& getData() const;


public:
	int mutate(unsigned long seed, double rate);
	int combine(const BiogramDNA& other);
};

