#pragma once

#include <memory>

class BiogramWorld;



























class BiogramApp
{
public:
	BiogramApp();
	virtual ~BiogramApp();


protected:
	std::shared_ptr<BiogramWorld> m_pBiogramWorld;


public:
	int init();
	int release();
	int update();
	int render();
};

