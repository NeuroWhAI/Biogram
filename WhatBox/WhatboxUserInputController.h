#pragma once

#include "UserInputController.h"



























class WhatboxUserInputController : public UserInputController
{
public:
	WhatboxUserInputController();
	virtual ~WhatboxUserInputController();


public:
	virtual bool onKeyDown(int vKey) const override;
	virtual bool onKeyPress(int vKey) const override;
	virtual bool onKeyUp(int vKey) const override;


public:
	virtual bool onTouchDown() const override;
	virtual bool onTouchPress() const override;
	virtual bool onTouchUp() const override;


public:
	virtual Utility::Point getCursorLocation() const override;
};

