#pragma once

#include <vector>



























class BiogramDNA
{
public:
	BiogramDNA();
	explicit BiogramDNA(unsigned long seed);
	virtual ~BiogramDNA();


protected:
	std::vector<bool> m_data;


public:
	const std::vector<bool>& getData() const;
};

