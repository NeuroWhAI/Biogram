#include "cLayer.h"






























cLayer::cLayer()
{

}


cLayer::~cLayer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer::Init()
{
	


	return OnInit();
}


int cLayer::Destroy()
{
	int Result = OnDestory();	


	return Result;
}

/*-----------------------------------------------------------------------------------------------------*/

int cLayer::Update()
{



	return OnUpdate();
}


int cLayer::Render()
{
	int Result = OnRender();


	return Result;
}

