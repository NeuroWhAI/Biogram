#pragma once
#include "cSequence.h"

class cNetClient;































class cSq_NetGame : public cSequence
{
public:
	cSq_NetGame(cNetClient* pNetClient);
	~cSq_NetGame();


private:
	cNetClient* m_pNetClient;


private:
	virtual int OnInit();
	virtual int OnCleanUp();

	virtual int OnRestore();
	virtual int OnRelease();

	virtual int OnDelete();   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate();
	virtual int OnRender();
};

