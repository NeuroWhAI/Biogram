#pragma once

#include <utility>

#include "Utility.h"



























class SystemInfo
{
public:
	SystemInfo();
	virtual ~SystemInfo();


public:
	// * �۾������� ũ�⸦ ��ȯ�մϴ�.
	virtual Utility::Size getWinSize() const = 0;
};

