#pragma once
#include "cForce.h"







































class cForce_AirResist : public cForce
{
public:
	cForce_AirResist(float resist,
		std::vector<cParticle*>* pPartList, float life = -99999.f, DWORD delay = 0);
	~cForce_AirResist();


private:
	float m_resist;


private:
	virtual int OnUpdate() override;
	virtual int OnForce() override;
	virtual int OnRender() override;


public:
	int SetResist(float resist);
	float GetResist() const;
};

