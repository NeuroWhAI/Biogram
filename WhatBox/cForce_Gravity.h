#pragma once
#include "cForce.h"







































class cForce_Gravity : public cForce
{
public:
	// mass : ����� �η�, ������ ô��
	cForce_Gravity(float mass,
		std::vector<cParticle*>* pPartList, cTexture* pTx = nullptr, float life = -99999.f, DWORD delay = 0);
	~cForce_Gravity();


private:
	float m_mass;


private:
	virtual int OnUpdate() override;
	virtual int OnForce() override;
	virtual int OnRender() override;


public:
	int SetMass(float mass);
	float GetMass() const;
};

