#include "System.h"

// SystemInfo
#include "WhatboxSystemInfo.h"

// UserInputController
#include "WhatboxUserInputController.h"

// Graphic
#include "WhatboxGraphic.h"

// ObjectViewer
#include "WhatboxObjectViewer.h"

// Logger
#include "WhatboxLogger.h"



























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

// ���⼭ �����Ǵ� ��ü�� ���������� �޸������μ�
// �ٸ� �÷����� ������ ���� �ְԵȴ�.
System::System()
	: m_pSystemInfo(std::make_unique<WhatboxSystemInfo>())
	, m_pUserInputController(std::make_unique<WhatboxUserInputController>())
	, m_pGraphic(std::make_unique<WhatboxGraphic>())
	, m_pObjectViewer(std::make_unique<WhatboxObjectViewer>())
	, m_pLogger(std::make_unique<WhatboxLogger>())
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


ObjectViewer& System::getObjectViewer()
{
	return *m_pObjectViewer;
}


Logger& System::getLogger()
{
	return *m_pLogger;
}

