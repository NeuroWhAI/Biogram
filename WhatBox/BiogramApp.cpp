#include "BiogramApp.h"

#include <sstream>

#include "System.h"

#include "BiogramWorld.h"

#include "TextPrinterDevice.h"
#include "TextCheckDirector.h"
#include "VoidGameDevice.h"
#include "VoidDirector.h"



























BiogramApp::BiogramApp()
	: m_pBiogramWorld(std::make_shared<BiogramWorld>())
	, m_geneNum(0)

	, m_bDrawWorld(true)
{

}


BiogramApp::~BiogramApp()
{

}

//###############################################################

int BiogramApp::init()
{
	if (!m_pBiogramWorld->initWorld(L"./Sample/World/auto-saved.biow"))
	{
		m_pBiogramWorld->initWorld(64, 10000.0, 0.01);
	}

	m_geneNum = m_pBiogramWorld->getGenerationNumber();

	TextPrinterDevice printer;
	m_pBiogramWorld->initDeviceForeachCage(printer);

	TextCheckDirector checker(L"42!");
	m_pBiogramWorld->initDirector(checker);

	/*VoidGameDevice game;
	m_pBiogramWorld->initDeviceForeachCage(game);

	VoidDirector director;
	m_pBiogramWorld->initDirector(director);*/


	return 0;
}


int BiogramApp::release()
{
	m_pBiogramWorld->saveWorld(L"./Sample/World/auto-saved.biow");


	return 0;
}


int BiogramApp::update()
{
	m_beginTime = std::chrono::system_clock::now();


	m_pBiogramWorld->update();

	if (m_geneNum != m_pBiogramWorld->getGenerationNumber()
		&&
		m_pBiogramWorld->getGenerationNumber() % 100 == 0)
	{
		m_pBiogramWorld->saveWorld(L"./Sample/World/auto-saved.biow");

		m_geneNum = m_pBiogramWorld->getGenerationNumber();
	}


	if (System::getInstance().getUserInputController().
		onKeyDown(0x20/*Space*/))
	{
		m_bDrawWorld = !m_bDrawWorld;
	}


	m_elapsedTime = std::chrono::system_clock::now() - m_beginTime;


	return 0;
}


int BiogramApp::render()
{
	std::chrono::system_clock::time_point beginRender =
		std::chrono::system_clock::now();

	if (m_bDrawWorld)
	{
		System::getInstance().getObjectViewer().
			drawBiogramWorld(*m_pBiogramWorld);
	}

	std::chrono::duration<double> renderTime =
		std::chrono::system_clock::now() - beginRender;


	auto winSize = System::getInstance().getSystemInfo().
		getWinSize();
	
	std::wostringstream oss;
	oss << std::fixed;
	oss << L"Update: " << m_elapsedTime.count() << L"s" << std::endl;
	oss << L"Render: " << renderTime.count() << L"s";

	System::getInstance().getGraphic().
		drawText(oss.str(), Utility::Point(winSize.width / 2 - 200, 8),
			true, Utility::Color::BLACK);


	return 0;
}

