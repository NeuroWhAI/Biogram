#include "System.h"

// SystemInfo
#include "WhatboxSystemInfo.h"

// UserInputController
#include "WhatboxUserInputController.h"

// Graphic
#include "WhatboxGraphic.h"



























System* System::s_pInstance = nullptr;

System::CleanHelper::~CleanHelper()
{
	if (s_pInstance != nullptr)
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}
}

//###############################################################

// 여기서 생성되는 객체를 수평적으로 달리함으로서
// 다른 플랫폼에 대응할 수도 있게된다.
System::System()
	: m_pSystemInfo(std::make_shared<WhatboxSystemInfo>())
	, m_pUserInputController(std::make_shared<WhatboxUserInputController>())
	, m_pGraphic(std::make_shared<WhatboxGraphic>())
{

}


System::~System()
{

}

//###############################################################

System& System::getInstance()
{
	static CleanHelper s_cleanHelper;

	if (s_pInstance == nullptr)
		s_pInstance = new System();


	return *s_pInstance;
}

//###############################################################

SystemInfo& System::getSystemInfo()
{
	return *m_pSystemInfo;
}


UserInputController& System::getUserInputController()
{
	return *m_pUserInputController;
}


Graphic& System::getGraphic()
{
	return *m_pGraphic;
}

