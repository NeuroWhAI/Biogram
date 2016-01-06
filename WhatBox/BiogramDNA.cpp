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
	std::uniform_int_distribution<int> sizeDist(1, 200000);

	int size = sizeDist(engine);

	for (int i = 0; i < size; ++i)
	{
		m_data.emplace_back(bitDist(engine) != 0);
	}
}


BiogramDNA::BiogramDNA(const std::vector<bool> bitData)
	: m_data(bitData)
{

}


BiogramDNA::~BiogramDNA()
{

}

//###############################################################

const std::vector<bool>& BiogramDNA::getData() const
{
	return m_data;
}


//###############################################################

int BiogramDNA::mutate(unsigned long seed, double rate)
{
	int rateNum = static_cast<int>(rate * 100000.0) + 1;

	std::mt19937 engine(seed);
	std::uniform_int_distribution<int> rateDist(1, 10000000);


	for (auto& bit : m_data)
	{
		if (rateDist(engine) < rateNum)
		{
			bit = !bit;
		}
	}


	if (rateDist(engine) < rateNum)
	{
		std::uniform_int_distribution<int> sizeDist(1, m_data.size() / 4);

		int deltaSize = sizeDist(engine);
		if (sizeDist(engine) % 2 != 0)
			deltaSize *= -1;

		if (deltaSize < 0)
		{
			std::uniform_int_distribution<int> rangeDist(0, m_data.size() + deltaSize);
		
			int sliceBeginIndex = rangeDist(engine);

			m_data.erase(m_data.begin() + sliceBeginIndex,
				m_data.begin() + (sliceBeginIndex - deltaSize));
		}
		else
		{
			std::uniform_int_distribution<int> bitDist(0, 1);

			for (int d = 0; d < deltaSize; ++d)
			{
				m_data.emplace_back(bitDist(engine) != 0);
			}
		}
	}


	return 0;
}

