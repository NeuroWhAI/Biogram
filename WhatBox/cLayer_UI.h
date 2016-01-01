#pragma once
#include "cLayer.h"
#include <vector>

class cUIControl;


























class cLayer_UI : public cLayer
{
public:
	cLayer_UI();
	~cLayer_UI();


private:
	std::vector<cUIControl*> m_pUIList;


private:
	virtual int OnInit();
	virtual int OnDestory();

	virtual int OnUpdate();
	virtual int OnRender();


public:
	int Reset();


public:
	int AddUIControl(cUIControl* pUI);
	int RemoveUIControl(const cUIControl* pUI);
};

