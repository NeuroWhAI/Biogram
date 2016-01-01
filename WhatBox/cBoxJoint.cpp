#include "cBoxJoint.h"

#include "cCore.h"

#include "Box2D_Lite\Body.h"


































cBoxJoint::cBoxJoint()
{

}


cBoxJoint::~cBoxJoint()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxJoint::Render(DWORD color)
{
	D3DXVECTOR2 vtxList[2];
	this->GetPointList(vtxList);


	cCore::Resource.Line.Render(vtxList, 2, color, 2.f);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxJoint::SetJoint(Body* pB1, Body* pB2)
{
	this->Set(pB1, pB2, Vec2(0.f, 0.f));


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBoxJoint::GetPointList(D3DXVECTOR2 pOut[])
{
	Body* b1 = this->body1;
	Body* b2 = this->body2;

	Mat22 R1(b1->rotation);
	Mat22 R2(b2->rotation);

	Vec2 x1 = b1->position;
	//Vec2 p1 = x1 + R1 * this->localAnchor1;

	Vec2 x2 = b2->position;
	//Vec2 p2 = x2 + R2 * this->localAnchor2;


	pOut[0].x = x1.x;
	pOut[0].y = x1.y;

	pOut[1].x = x2.x;
	pOut[1].y = x2.y;


	return 0;
}

