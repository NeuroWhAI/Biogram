#pragma once
#include "c2DCoord.h"





























class cUnit : public c2DCoord
{
public:
	cUnit();
	virtual ~cUnit();


public:
	int Update();
	int Render();


public:
	virtual int OnUpdate() = 0;
	virtual int OnRender() = 0;
};

