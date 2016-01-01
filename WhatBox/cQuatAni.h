#pragma once
#include "cQuatCoord.h"

class cTextureList;







































class cQuatAni : public cQuatCoord
{
public:
	// pTxList에 필요한 이미지 수 = frameNum*angleNum
	cQuatAni(cTextureList* pTxList, int frameNum, int angleNum, DWORD delay);
	~cQuatAni();


private:
	cTextureList* m_pTxList;
	int m_frameNum;
	int m_angleNum;
	DWORD m_delay;


private:
	int m_startNum;
	int m_currFrame;
	DWORD m_prevAniTime;


private:
	bool m_bOnPlay;
	bool m_bEnd;


public:
	int Update();
	int Render();


public:
	int Play();
	int Pause();
	int Stop();


public:
	bool IsEnd() const;
};

