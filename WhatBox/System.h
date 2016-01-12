#pragma once

#include <memory>

#include "SystemInfo.h"
#include "UserInputController.h"
#include "Graphic.h"
#include "ObjectViewer.h"
#include "Logger.h"


























class System final
{
private:
	System();
	virtual ~System();


protected:
	static System* s_pInstance;

	// s_pInstance 메모리 해제를 위한 도움클래스
	class CleanHelper
	{
	public:
		virtual ~CleanHelper();
	};


protected:
	std::unique_ptr<SystemInfo> m_pSystemInfo;
	std::unique_ptr<UserInputController> m_pUserInputController;
	std::unique_ptr<Graphic> m_pGraphic;
	std::unique_ptr<ObjectViewer> m_pObjectViewer;
	std::unique_ptr<Logger> m_pLogger;


public:
	static System& getInstance();


public:
	SystemInfo& getSystemInfo();
	UserInputController& getUserInputController();
	Graphic& getGraphic();
	ObjectViewer& getObjectViewer();
	Logger& getLogger();
};


#define BIOGRAM_DEBUG_OFF
#ifdef BIOGRAM_DEBUG
#define LOG(...) System::getInstance().getLogger().log(__VA_ARGS__)
#else
#define LOG(...) 
#endif