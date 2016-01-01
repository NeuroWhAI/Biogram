#pragma once
#include "cSequence.h"

















class cSq_End : public cSequence
{
public:
	cSq_End();
	~cSq_End();


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

