#include "BiogramDNA.h"

#include <random>
#include <ctime>



























BiogramDNA::BiogramDNA()
{

}


BiogramDNA::BiogramDNA(unsigned long seed)
{
	// 랜덤 DNA 생성
	std::mt19937 engine(seed);
	std::uniform_int_distribution<int> bitDist(0, 1);
	std::uniform_int_distribution<int> sizeDist(1, 100000);

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

int BiogramDNA::saveTo(std::ostream& osr) const
{
	if (osr.good())
	{
		osr << m_data.size() << std::endl;
		for (const auto& bit : m_data)
		{
			osr << (bit ? '1' : '0');
		}
		osr << std::endl;
	}


	return 0;
}


int BiogramDNA::loadFrom(std::istream& isr)
{
	if (isr.good())
	{
		size_t size = 0;
		isr >> size;

		for (size_t i = 0; i < size; ++i)
		{
			char bit = 0;

			do
			{
				isr.get(bit);
			} while (bit == '\n');

			m_data.emplace_back((bit != '0') ? true : false);
		}
	}


	return 0;
}


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


int BiogramDNA::combine(const BiogramDNA& other)
{
	if (m_data.empty())
	{
		m_data = other.m_data;
		return 0;
	}


	std::mt19937 engine(static_cast<unsigned>(std::time(nullptr)));
	std::uniform_int_distribution<> boolDist(0, 1);


	// 길이 변환
	if (boolDist(engine) != 0)
	{
		if (other.m_data.size() > m_data.size())
		{
			m_data.insert(m_data.end(),
				other.m_data.begin() + m_data.size(),
				other.m_data.end());
		}
		else if (other.m_data.size() < m_data.size())
		{
			m_data.erase(m_data.begin() + other.m_data.size(),
				m_data.end());
		}
	}


	// 합치기
	size_t thisCount = m_data.size();
	size_t otherCount = other.m_data.size();
	std::uniform_int_distribution<> rangeDist(0,
		((thisCount < otherCount) ? thisCount : otherCount) / 8);

	for (size_t i = rangeDist(engine);
	i < thisCount && i < otherCount;
	i += rangeDist(engine))
	{
		size_t end = i + rangeDist(engine);

		// 범위 초과 방지
		if (end > thisCount || end > otherCount)
		{
			if (thisCount < otherCount)
				end = thisCount;
			else
				end = otherCount;
		}

		// 교배
		for (size_t c = i; c < end; ++c)
		{
			m_data[c] = other.m_data[c];
		}


		i = end;
	}


	return 0;
}

