#include "BiogramApp.h"

#include <sstream>

#include "System.h"

#include "BiogramWorld.h"

#include "TextPrinterDevice.h"
#include "TextCheckDirector.h"



























BiogramApp::BiogramApp()
	: m_pBiogramWorld(std::make_shared<BiogramWorld>())
	, m_geneNum(0)
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


	return 0;
}


int BiogramApp::render()
{
	System::getInstance().getObjectViewer().
		drawBiogramWorld(*m_pBiogramWorld);


	m_elapsedTime = std::chrono::system_clock::now() - m_beginTime;

	auto winSize = System::getInstance().getSystemInfo().
		getWinSize();
	
	std::wostringstream oss;
	oss << std::fixed;
	oss.precision(1);
	oss << 1.0 / m_elapsedTime.count() << "fps";

	System::getInstance().getGraphic().
		drawText(oss.str(), Utility::Point(winSize.width / 2 - 200, 8),
			true, Utility::Color::BLACK);


	return 0;
}

