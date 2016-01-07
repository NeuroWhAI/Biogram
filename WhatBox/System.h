#pragma once

#include <memory>

#include "SystemInfo.h"
#include "UserInputController.h"
#include "Graphic.h"
#include "ObjectViewer.h"


























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
	std::shared_ptr<SystemInfo> m_pSystemInfo;
	std::shared_ptr<UserInputController> m_pUserInputController;
	std::shared_ptr<Graphic> m_pGraphic;
	std::shared_ptr<ObjectViewer> m_pObjectViewer;


public:
	static System& getInstance();


public:
	SystemInfo& getSystemInfo();
	UserInputController& getUserInputController();
	Graphic& getGraphic();
	ObjectViewer& getObjectViewer();
};

