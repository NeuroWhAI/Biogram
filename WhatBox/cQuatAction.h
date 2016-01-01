#pragma once
#include "cQuatCoord.h"
#include <vector>

class cQuatAni;
class cTextureList;



































class cQuatAction : public cQuatCoord
{
public:
	cQuatAction();
	~cQuatAction();


private:
	std::vector<cQuatAni*> m_pAniList;
	int m_currAniNum;
	bool m_bOnLock;


public:
	int Update();
	int Render();


public:
	// aniNum : 애니메이션 번호 지정
	// pTxList에 필요한 이미지 수 = frameNum*angleNum
	int AddQuatAni(int aniNum, cTextureList* pTxList, int frameNum, int angleNum, DWORD delay);
	int SetCurrAniNum(int currAniNum);
	int GetCurrAniNum() const;


public:
	int Play();
	int Pause();
	int Stop();


public:
	// 현재 애니메이션이 끝날때까지 애니메이션 변경을 무시함.
	int Lock();
	int UnLock();
};

