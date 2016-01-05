#pragma once

#include "Utility.h"



























class UserInputController
{
public:
	UserInputController();
	virtual ~UserInputController();


public:
	virtual bool onKeyDown(int vKey) const = 0;
	virtual bool onKeyPress(int vKey) const = 0;
	virtual bool onKeyUp(int vKey) const = 0;


public:
	virtual bool onTouchDown() const = 0;
	virtual bool onTouchPress() const = 0;
	virtual bool onTouchUp() const = 0;


public:
	virtual Utility::Point getCursorLocation() const = 0;
};

