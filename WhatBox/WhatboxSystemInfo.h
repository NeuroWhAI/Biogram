#pragma once

#include "SystemInfo.h"



























class WhatboxSystemInfo : public SystemInfo
{
public:
	WhatboxSystemInfo();
	virtual ~WhatboxSystemInfo();


public:
	virtual Utility::Size getWinSize() const override;
};

