#include "BiogramApp.h"

#include "System.h"



























BiogramApp::BiogramApp()
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



	return 0;
}


int BiogramApp::render()
{
	System::getInstance().getGraphic().
		drawText("Hello, World!", 32, 32, false,
			0, 255, 255);


	return 0;
}

