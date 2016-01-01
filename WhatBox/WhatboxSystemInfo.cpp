#include "WhatboxSystemInfo.h"

#include "cCore.h"



























WhatboxSystemInfo::WhatboxSystemInfo()
{

}


WhatboxSystemInfo::~WhatboxSystemInfo()
{

}

//###############################################################

Utility::Size WhatboxSystemInfo::getWinSize() const
{
	return Utility::Size(
		static_cast<int>(cCore::WinSize.x),
		static_cast<int>(cCore::WinSize.y));
}

