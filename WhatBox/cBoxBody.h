#pragma once
#include <d3dx9.h>
#include "Box2D_Lite/Body.h"




































class cBoxBody : public Body
{
public:
	cBoxBody();
	virtual ~cBoxBody();


public:
	int Render(DWORD color);


public:
	int SetPos(float x, float y);
	int SetSpeed(float x, float y);
	int SetSizeAndMass(float width, float height, float mass = FLT_MAX);
	int SetAngle(float degree);
	int SetFriction(float friction);
	int SetAngleSpeed(float degree);


public:
	void AddForce(float x, float y);
	int AddSpeed(float x, float y);
	int AddAngleSpeed(float degree);


public:
	int GetVtxList(D3DXVECTOR2 pOut[]);
};

