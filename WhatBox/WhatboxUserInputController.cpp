#include "WhatboxUserInputController.h"

#include "cCore.h"



























WhatboxUserInputController::WhatboxUserInputController()
{

}


WhatboxUserInputController::~WhatboxUserInputController()
{

}

//###############################################################

bool WhatboxUserInputController::onKeyDown(int vKey) const
{
	return cCore::Input.KeyDown(vKey);
}


bool WhatboxUserInputController::onKeyPress(int vKey) const
{
	return cCore::Input.KeyPress(vKey);
}


bool WhatboxUserInputController::onKeyUp(int vKey) const
{
	return cCore::Input.KeyUp(vKey);
}

