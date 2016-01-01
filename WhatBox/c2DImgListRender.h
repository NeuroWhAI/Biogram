#pragma once
#include <d3dx9.h>

class cTextureList;
class cTexture;



















class c2DImgListRender
{
public:
	c2DImgListRender();
	c2DImgListRender(cTextureList* pTxList, DWORD Delay_ms, bool bOnce);

	~c2DImgListRender();


private:
	cTextureList* m_pTxList;
	DWORD m_Delay;
	bool m_bOnce;


private:
	UINT m_CurrIdx;
	DWORD m_PrevTime;
	bool m_isEnd;


public:
	int Init(cTextureList* pTxList, DWORD Delay_ms, bool bOnce);
	int Reset();

	bool isEnd() const;
	UINT CurrIdx() const;

	const cTexture* GetCurrTexture() const;
	cTexture* GetCurrTexture();


public:
	int Render();
	int RenderCenter();

	int Render(UINT Idx);
	int RenderCenter(UINT Idx);


public:
	int Update();
};

