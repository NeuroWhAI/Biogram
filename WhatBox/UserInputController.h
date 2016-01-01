#pragma once



























class UserInputController
{
public:
	UserInputController();
	virtual ~UserInputController();


public:
	virtual bool onKeyDown(int vKey) const = 0;
	virtual bool onKeyPress(int vKey) const = 0;
	virtual bool onKeyUp(int vKey) const = 0;
};

