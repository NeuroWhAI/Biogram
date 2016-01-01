#pragma once
#include "cLayer.h"
#include <vector>

class cTextureList;


























class cLayer_Back : public cLayer
{
public:
	cLayer_Back();
	~cLayer_Back();


private:
	cTextureList* m_pTxList;


private:
	virtual int OnInit();
	virtual int OnDestory();

	virtual int OnUpdate();
	virtual int OnRender();


public:
	int Reset();


public:
	int SetTextureList(cTextureList* pTxList);
};

