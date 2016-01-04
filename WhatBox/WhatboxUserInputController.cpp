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

//###############################################################

Utility::Point WhatboxUserInputController::getCursorLocation() const
{
	POINT cursor = cCore::Input.CursorPos();
	return Utility::Point(
		static_cast<int>(cursor.x),
		static_cast<int>(cursor.y));
}

