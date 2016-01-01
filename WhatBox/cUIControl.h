#pragma once
#include "c2DCoord.h"

























class cUIControl : public c2DCoord
{
public:
	cUIControl();
	virtual ~cUIControl();


public:
	int Update();
	int Render();


protected:
	virtual int OnUpdate() = 0;
	virtual int OnRender() = 0;
};

