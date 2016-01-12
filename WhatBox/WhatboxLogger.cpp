#include "WhatboxLogger.h"

#include "cCore.h"



























WhatboxLogger::WhatboxLogger()
{

}


WhatboxLogger::~WhatboxLogger()
{

}

//#################################################################

void WhatboxLogger::whenLog(std::string text)
{
	cCore::Log.AddLog("%s", text.c_str());
}

