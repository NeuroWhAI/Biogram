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

bool WhatboxUserInputController::onTouchDown() const
{
	return cCore::Input.MouseDown(VK_LBUTTON);
}


bool WhatboxUserInputController::onTouchPress() const
{
	return cCore::Input.MousePress(VK_LBUTTON);
}


bool WhatboxUserInputController::onTouchUp() const
{
	return cCore::Input.MouseUp(VK_LBUTTON);
}

//###############################################################

Utility::Point WhatboxUserInputController::getCursorLocation() const
{
	POINT cursor = cCore::Input.CursorPos();
	return Utility::Point(
		static_cast<int>(cursor.x),
		static_cast<int>(cursor.y));
}

