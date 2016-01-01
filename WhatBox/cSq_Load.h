#pragma once
#include "cSequence.h"

class cResourceLoad;
class cFade;
















class cSq_Load : public cSequence
{
public:
	cSq_Load();
	~cSq_Load();


private:
	cResourceLoad* m_pResourceLoad;


private:
	cFade* m_pFadeOut;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

