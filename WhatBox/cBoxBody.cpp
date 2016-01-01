#include "cBoxBody.h"

#include "cCore.h"




































cBoxBody::cBoxBody()
{

}


cBoxBody::~cBoxBody()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxBody::Render(DWORD color)
{
	D3DXVECTOR2 vtxList[4+1];
	this->GetVtxList(vtxList);

	vtxList[4] = vtxList[0];


	cCore::Resource.Line.Render(vtxList, 5, color, 2.f);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxBody::SetPos(float x, float y)
{
	this->position.Set(x, y);


	return 0;
}


int cBoxBody::SetSpeed(float x, float y)
{
	this->velocity.Set(x, y);


	return 0;
}


int cBoxBody::SetSizeAndMass(float width, float height, float mass)
{
	this->Set(Vec2(width, height), mass);


	return 0;
}


int cBoxBody::SetAngle(float degree)
{
	this->rotation = D3DXToRadian(degree);


	return 0;
}


int cBoxBody::SetFriction(float friction)
{
	this->friction = friction;


	return 0;
}


int cBoxBody::SetAngleSpeed(float degree)
{
	this->angularVelocity = D3DXToRadian(degree);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cBoxBody::AddForce(float x, float y)
{
	this->force.x += x;
	this->force.y += y;
}


int cBoxBody::AddSpeed(float x, float y)
{
	this->velocity.x += x;
	this->velocity.y += y;


	return 0;
}


int cBoxBody::AddAngleSpeed(float degree)
{
	this->angularVelocity += D3DXToRadian(degree);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxBody::GetVtxList(D3DXVECTOR2 pOut[])
{
	Mat22 R(this->rotation);
	Vec2 x = this->position;
	Vec2 h = 0.5f * this->width;

	Vec2 v1 = x + R * Vec2(-h.x, -h.y);
	Vec2 v2 = x + R * Vec2( h.x, -h.y);
	Vec2 v3 = x + R * Vec2( h.x,  h.y);
	Vec2 v4 = x + R * Vec2(-h.x,  h.y);

	pOut[0].x = v1.x;
	pOut[0].y = v1.y;
	
	pOut[1].x = v2.x;
	pOut[1].y = v2.y;
	
	pOut[2].x = v3.x;
	pOut[2].y = v3.y;
	
	pOut[3].x = v4.x;
	pOut[3].y = v4.y;


	return 0;
}

