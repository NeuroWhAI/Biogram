#include "BiogramDNA.h"

#include <ctime>

#include "System.h"


























std::mt19937 BiogramDNA::s_randEngine(static_cast<unsigned>(time(nullptr)));

//###############################################################

BiogramDNA::BiogramDNA(bool bFillRandomly)
{
	if (bFillRandomly)
	{
		// 랜덤 DNA 생성
		std::uniform_int_distribution<int> bitDist(0, 1);
		std::uniform_int_distribution<int> sizeDist(1, 100000);

		int size = sizeDist(s_randEngine);

		for (int i = 0; i < size; ++i)
		{
			m_data.emplace_back(bitDist(s_randEngine) != 0);
		}
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

int BiogramDNA::mutate(double rate)
{
	int rateNum = static_cast<int>(rate * 1000000.0) + 1;

	std::uniform_int_distribution<> rateDist(1, 100000000);


	// 단순 비트 반전 작업
	for (auto& bit : m_data)
	{
		if (rateDist(s_randEngine) < rateNum)
			bit = !bit;
	}


	// 유전자 길이가 변하는 돌연변이
	if (rateDist(s_randEngine) < rateNum)
	{
		std::normal_distribution<> sizeDist(64, m_data.size() / 256);
		std::uniform_int_distribution<> bitDist(0, 1);

		int deltaSize = std::abs(static_cast<int>(sizeDist(s_randEngine)));
		if (static_cast<size_t>(deltaSize) > m_data.size() / 4)
			deltaSize = m_data.size() / 4;
		if (bitDist(s_randEngine) != 0)
			deltaSize *= -1;

		if (deltaSize < 0)
		{
			// 유전자 결실 작업

			std::uniform_int_distribution<> posDist(0, m_data.size() + deltaSize);
		
			int sliceBeginIndex = posDist(s_randEngine);

			m_data.erase(m_data.begin() + sliceBeginIndex,
				m_data.begin() + (sliceBeginIndex - deltaSize));


			LOG("Slice DNA from ",
				sliceBeginIndex, " by ",
				-deltaSize);
		}
		else
		{
			// 유전자 중복 작업

			std::uniform_int_distribution<> posDist(0, m_data.size() - deltaSize);

			int duplicationIndex = posDist(s_randEngine);

			m_data.insert(m_data.begin() + (duplicationIndex + deltaSize),
				m_data.begin() + duplicationIndex,
				m_data.begin() + (duplicationIndex + deltaSize));


			LOG("Duplicate DNA from ",
				duplicationIndex, " by ",
				deltaSize);
		}
	}


	// 유전자 역위 작업
	if (rateDist(s_randEngine) < rateNum)
	{
		std::normal_distribution<> rangeDist(16, m_data.size() / 256);

		int reverseRange = std::abs(static_cast<int>(rangeDist(s_randEngine)));
		if (static_cast<size_t>(reverseRange) >= m_data.size() / 4)
			reverseRange = static_cast<int>(m_data.size() / 4);
		

		std::uniform_int_distribution<> posDist(0, m_data.size() - reverseRange);

		size_t beginIndex = static_cast<size_t>(posDist(s_randEngine));

		
		std::reverse(m_data.begin() + beginIndex,
			m_data.begin() + (beginIndex + reverseRange));


		LOG("Reverse DNA from ",
			beginIndex, " by ",
			reverseRange);
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


	std::uniform_int_distribution<> boolDist(0, 1);


	// 길이 변환
	if (boolDist(s_randEngine) != 0)
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

	for (size_t i = rangeDist(s_randEngine);
	i < thisCount && i < otherCount;
	i += rangeDist(s_randEngine))
	{
		size_t end = i + rangeDist(s_randEngine);

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

