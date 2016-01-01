#pragma once
#include <d3dx9.h>
#include "Box2D_Lite\Joint.h"




































class cBoxJoint : public Joint
{
public:
	cBoxJoint();
	virtual ~cBoxJoint();


public:
	int Render(DWORD color);


public:
	int SetJoint(Body* pB1, Body* pB2);


public:
	int GetPointList(D3DXVECTOR2 pOut[]);
};

