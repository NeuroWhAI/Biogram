#pragma once
#include "cSequence.h"

























class cSq_Main : public cSequence
{
public:
	cSq_Main();
	~cSq_Main();


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //�Ϲ� ������ '����'(������ �ƴ�)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

