#include "BiogramApp.h"

#include <sstream>

#include "System.h"

#include "BiogramWorld.h"



























BiogramApp::BiogramApp()
	: m_pBiogramWorld(std::make_shared<BiogramWorld>(1024.0f, 1024.0f))
{

}


BiogramApp::~BiogramApp()
{

}

//###############################################################

int BiogramApp::init()
{
	


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
	System::getInstance().getGraphic().
		drawBiogramWorld(*m_pBiogramWorld);


	m_elapsedTime = std::chrono::system_clock::now() - m_beginTime;

	auto winSize = System::getInstance().getSystemInfo().
		getWinSize();
	
	std::wostringstream oss;
	oss << 1.0 / m_elapsedTime.count() << "fps";

	System::getInstance().getGraphic().
		drawText(oss.str(), Utility::Point(winSize.width / 2, 8),
			true, Utility::Color::BLACK);


	return 0;
}

