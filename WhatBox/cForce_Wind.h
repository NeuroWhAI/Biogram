#pragma once
#include "cForce.h"







































class cForce_Wind : public cForce
{
public:
	cForce_Wind(float maxSpeed, const D3DXVECTOR2* dir,
		std::vector<cParticle*>* pPartList, float life = -99999.f, DWORD delay = 0);
	~cForce_Wind();


private:
	float m_maxSpeedSq;
	D3DXVECTOR2 m_force;


private:
	virtual int OnUpdate() override;
	virtual int OnForce() override;
	virtual int OnRender() override;


public:
	int SetMaxSpeed(float speed);
	float GetMaxSpeed() const;
	
	int SetForce(const D3DXVECTOR2* force);
	const D3DXVECTOR2* GetForce() const;
};

