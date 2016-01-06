#pragma once

#include <vector>



























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
	const std::vector<bool>& getData() const;


public:
	int mutate(unsigned long seed, double rate);
};
