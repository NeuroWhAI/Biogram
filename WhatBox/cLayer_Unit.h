#pragma once
#include "cLayer.h"
#include <vector>

class cUnit;


























class cLayer_Unit : public cLayer
{
public:
	cLayer_Unit();
	~cLayer_Unit();


private:
	std::vector<cUnit*> m_pUnitList;


private:
	virtual int OnInit();
	virtual int OnDestory();

	virtual int OnUpdate();
	virtual int OnRender();


public:
	int Reset();


public:
	int AddUnit(cUnit* pUnit);
	int RemoveUnitControl(const cUnit* pUnit);
};

