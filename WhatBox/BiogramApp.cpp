#include "BiogramApp.h"

#include "System.h"

#include "BiogramWorld.h"



























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
	


	return 0;
}


int BiogramApp::release()
{



	return 0;
}


int BiogramApp::update()
{
	m_pBiogramWorld->update();


	return 0;
}


int BiogramApp::render()
{
	System::getInstance().getGraphic().
		drawBiogramWorld(*m_pBiogramWorld);


	return 0;
}

