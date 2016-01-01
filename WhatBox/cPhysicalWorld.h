#pragma once
#include <vector>
#include <d3dx9.h>
#include "Box2D_Lite/World.h"
#include "Box2D_Lite/Body.h"
#include "Box2D_Lite/Joint.h"

































class cPhysicalWorld
{
public:
	cPhysicalWorld();
	cPhysicalWorld(D3DXVECTOR2 gravityVec);
	~cPhysicalWorld();


private:
	std::vector<Body*> m_pBodyList;
	std::vector<Joint*> m_pJointList;

	const float m_timeStep;
	int m_iterations;
	Vec2 m_gravity;

	World m_world;


public:
	int Reset();
	int Update();
	int Render();


public:
	int AddBody(Body* pBody);
	int AddJoint(Joint* pJoint);

	int RemoveBody(const Body* pBody);
	int RemoveJoint(const Joint* pJoint);


public:
	int BodyToDX(Body* pBody);
	int JointToDX(Joint* pJoint);
};

