#include "cUIControl.h"

#include "cCore.h"
































cUIControl::cUIControl()
{

}


cUIControl::~cUIControl()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cUIControl::Update()
{
	Util::TempOffCamera tempOffCamera;


	return OnUpdate();
}


int cUIControl::Render()
{
	Util::TempOffCamera tempOffCamera;


	int Result = OnRender();


	return Result;
}

