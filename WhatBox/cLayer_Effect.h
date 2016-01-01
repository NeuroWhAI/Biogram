#pragma once
#include "cLayer.h"
#include <vector>

class cEffect;


























class cLayer_Effect : public cLayer
{
public:
	cLayer_Effect();
	~cLayer_Effect();


private:
	std::vector<cEffect*> m_pEffectList;
	std::vector<bool> m_DeleteWhenEndList;


private:
	virtual int OnInit();
	virtual int OnDestory();

	virtual int OnUpdate();
	virtual int OnRender();


public:
	int Reset();


public:
	int AddEffect(cEffect* pEffect, bool DeleteWhenEnd);
	int RemoveEffectControl(const cEffect* pEffect);
};

