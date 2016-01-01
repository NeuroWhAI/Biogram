#pragma once

#include <memory>



























class BiogramApp
{
public:
	BiogramApp();
	virtual ~BiogramApp();


public:
	int init();
	int release();
	int update();
	int render();
};

