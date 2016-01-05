#include "BiogramDNA.h"

#include <random>



























BiogramDNA::BiogramDNA()
{

}


BiogramDNA::BiogramDNA(unsigned long seed)
{
	// ·£´ý DNA »ý¼º
	std::mt19937 engine(seed);
	std::uniform_int_distribution<int> bitDist(0, 1);
	std::uniform_int_distribution<int> sizeDist(1, 10000);

	int size = sizeDist(engine);

	for (int i = 0; i < size; ++i)
	{
		m_data.emplace_back(bitDist(engine) != 0);
	}
}


BiogramDNA::~BiogramDNA()
{

}

//###############################################################

const std::vector<bool>& BiogramDNA::getData() const
{
	return m_data;
}


