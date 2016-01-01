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
	// aniNum : �ִϸ��̼� ��ȣ ����
	// pTxList�� �ʿ��� �̹��� �� = frameNum*angleNum
	int AddQuatAni(int aniNum, cTextureList* pTxList, int frameNum, int angleNum, DWORD delay);
	int SetCurrAniNum(int currAniNum);
	int GetCurrAniNum() const;


public:
	int Play();
	int Pause();
	int Stop();


public:
	// ���� �ִϸ��̼��� ���������� �ִϸ��̼� ������ ������.
	int Lock();
	int UnLock();
};

