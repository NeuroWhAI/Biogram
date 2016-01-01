#pragma once

#include <memory>

#include "SystemInfo.h"
#include "UserInputController.h"
#include "Graphic.h"


























class System final
{
private:
	System();
	virtual ~System();


protected:
	static System* s_pInstance;

	// s_pInstance �޸� ������ ���� ����Ŭ����
	class CleanHelper
	{
	public:
		virtual ~CleanHelper();
	};


protected:
	std::shared_ptr<SystemInfo> m_pSystemInfo;
	std::shared_ptr<UserInputController> m_pUserInputController;
	std::shared_ptr<Graphic> m_pGraphic;


public:
	static System& getInstance();


public:
	SystemInfo& getSystemInfo();
	UserInputController& getUserInputController();
	Graphic& getGraphic();
};

