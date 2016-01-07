#include "BiogramApp.h"

#include <sstream>

#include "System.h"

#include "BiogramWorld.h"

#include "TextPrinterDevice.h"
#include "TextCheckDirector.h"



























BiogramApp::BiogramApp()
	: m_pBiogramWorld(std::make_shared<BiogramWorld>())
{

}


BiogramApp::~BiogramApp()
{

}

//###############################################################

int BiogramApp::init()
{
	m_pBiogramWorld->initWorld(32, 5000.0);

	TextPrinterDevice printer;
	m_pBiogramWorld->initDeviceForeachCage(printer);

	TextCheckDirector checker(L"Hello!");
	m_pBiogramWorld->initDirector(checker);


	return 0;
}


int BiogramApp::release()
{



	return 0;
}


int BiogramApp::update()
{
	m_beginTime = std::chrono::system_clock::now();


	m_pBiogramWorld->update();


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

