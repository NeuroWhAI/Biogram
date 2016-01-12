#pragma once

#include "Logger.h"



























class WhatboxLogger : public Logger
{
public:
	WhatboxLogger();
	virtual ~WhatboxLogger();


protected:
	virtual void whenLog(std::string text) override;
};

