#pragma once
#include <d3dx9.h>
#include <vector>

#include "c2DCoord.h"

class c2DImgListRender;
class cTextureList;


























class cAction : public c2DCoord
{
public:
	cAction();
	~cAction();


private:
	std::vector<cTextureList*> m_pActionList;
	std::vector<DWORD> m_DelayList;
	std::vector<bool> m_bOnceList;
	std::vector<int> m_NextActionNumList;

	int m_BasicActionNum;


private:
	c2DImgListRender* m_pRender;
	int m_CurrActionNum;
	bool m_bWasEnd;


public:
	int Init(int BasicActionNum);
	int AddAction(cTextureList* pTxList, DWORD Delay, bool bOnce = false, int NextActionNum = -1);
	int AddAction(UINT Idx, cTextureList* pTxList, DWORD Delay, bool bOnce = false, int NextActionNum = -1);
	int RemoveAction(UINT Idx);


public:
	int Update();
	int Render();
	int RenderCenter();


public:
	int SetAction(int Idx); // ������ �⺻ �׼����� ��
	int SetActionNoReset(int Idx); // �ִϸ��̼��� �������� ����
	int SetActionToBasic();

	int CurrActionNum() const;
	bool isEnd() const;
};

