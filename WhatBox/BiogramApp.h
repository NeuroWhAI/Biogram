#pragma once

#include <memory>
#include <chrono>

class BiogramWorld;



























class BiogramApp
{
public:
	BiogramApp();
	virtual ~BiogramApp();


protected:
	std::chrono::time_point<std::chrono::system_clock> m_beginTime;
	std::chrono::duration<double> m_elapsedTime;


protected:
	std::shared_ptr<BiogramWorld> m_pBiogramWorld;
	size_t m_geneNum;


public:
	int init();
	int release();
	int update();
	int render();
};

