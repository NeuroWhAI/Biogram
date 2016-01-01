#include "cUnit.h"






























cUnit::cUnit()
{

}


cUnit::~cUnit()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cUnit::Update()
{



	return OnUpdate();
}


int cUnit::Render()
{
	int Result = OnRender();


	return Result;
}

