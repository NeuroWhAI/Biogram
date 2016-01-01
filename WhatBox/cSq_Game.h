#pragma once
#include "cSequence.h"

#include <memory>

class BiogramApp;








































class cSq_Game : public cSequence
{
public:
	cSq_Game();
	~cSq_Game();


protected:
	std::shared_ptr<BiogramApp> m_pApp;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

