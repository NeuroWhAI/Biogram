#pragma once
#include "cSequence.h"

















class cSq_Intro : public cSequence
{
public:
	cSq_Intro();
	~cSq_Intro();


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //�Ϲ� ������ '����'(������ �ƴ�)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

