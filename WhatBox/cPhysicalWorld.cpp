#include "cPhysicalWorld.h"

#include "cCore.h"





































cPhysicalWorld::cPhysicalWorld()
	: m_timeStep(1.0f / 60.0f)
	, m_iterations(10)
	, m_gravity(0.f, 9.8f * 16.f)

	, m_world(m_gravity, m_iterations)
{
	Reset();
}


cPhysicalWorld::cPhysicalWorld(D3DXVECTOR2 gravityVec)
	: m_timeStep(1.0f / 60.0f)
	, m_iterations(10)
	, m_gravity(gravityVec.x, gravityVec.y)

	, m_world(m_gravity, m_iterations)
{
	Reset();
}


cPhysicalWorld::~cPhysicalWorld()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int cPhysicalWorld::Reset()
{
	m_pBodyList.clear();
	m_pJointList.clear();

	m_world.Clear();


	return 0;
}


int cPhysicalWorld::Update()
{
	m_world.Step(m_timeStep);


	return 0;
}


int cPhysicalWorld::Render()
{
	


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int cPhysicalWorld::AddBody(Body* pBody)
{
	BodyToDX(pBody);


	m_pBodyList.emplace_back(pBody);
	m_world.Add(pBody);


	return 0;
}


int cPhysicalWorld::AddJoint(Joint* pJoint)
{
	JointToDX(pJoint);

	
	m_pJointList.emplace_back(pJoint);
	m_world.Add(pJoint);


	return 0;
}

/*----------------------------------------------------------------------------------------------------*/

int cPhysicalWorld::RemoveBody(const Body* pBody)
{



	return 0;
}


int cPhysicalWorld::RemoveJoint(const Joint* pJoint)
{
	


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int cPhysicalWorld::BodyToDX(Body* pBody)
{
	/*Vec2 vec = pBody->width;
	vec.x /= 2.f;
	vec.y /= 2.f;

	pBody->position += vec;*/


	return 0;
}


int cPhysicalWorld::JointToDX(Joint* pJoint)
{
	/*Vec2 vec = pJoint->body1->width;
	vec.x /= 2.f;
	vec.y /= 2.f;

	pJoint->localAnchor1 += vec;


	vec = pJoint->body2->width;
	vec.x /= 2.f;
	vec.y /= 2.f;

	pJoint->localAnchor2 += vec;*/


	return 0;
}

