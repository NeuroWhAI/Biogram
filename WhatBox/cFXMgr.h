#pragma once
#include <vector>

class cFX;


































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 특수효과 관리자
// Desc : 특수효과를 진행시키고 종료시 메모리에서 제거함
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFXMgr
{
public:
	cFXMgr();
	~cFXMgr();


private:
	std::vector<cFX*> m_pFXList;


public:
	int Update();
	int Render();


public:
	int AddFX(cFX* pFX);
	int RemoveFX(const cFX* pFX);
	int RemoveAll();
};

