#pragma once

#include <utility>

#include "Utility.h"



























class SystemInfo
{
public:
	SystemInfo();
	virtual ~SystemInfo();


public:
	// * 작업영역의 크기를 반환합니다.
	virtual Utility::Size getWinSize() const = 0;
};

