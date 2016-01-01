#pragma once
#include "c2DCoord.h"

class cTextureList;
class c2DImgListRender;



























class cEffect : public c2DCoord
{
public:
	cEffect();
	cEffect(cTextureList* pTxList, DWORD Delay, bool bOnce);
	virtual ~cEffect();


protected:
	c2DImgListRender* m_pRender;


public:
	int Init(cTextureList* pTxList, DWORD Delay, bool bOnce);

	int Update();
	int RenderCenter();


public:
	bool isEnd() const;
};

