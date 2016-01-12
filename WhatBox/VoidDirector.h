#pragma once

#include "Director.h"

#include <string>



























class VoidDirector : public Director
{
public:
	VoidDirector();
	virtual ~VoidDirector();


public:
	virtual int init() override;
	virtual double evaluate(const VoidGameDevice& device) override;
};

