#include "c2DImgListRender.h"

#include "cTextureList.h"
#include "cCore.h"

























c2DImgListRender::c2DImgListRender()
	: m_pTxList(NULL)
	, m_Delay(0UL)
	, m_CurrIdx(0UL)
	, m_PrevTime(timeGetTime())
	, m_bOnce(false)
	, m_isEnd(false)
{

}

c2DImgListRender::c2DImgListRender(cTextureList* pTxList, DWORD Delay_ms, bool bOnce)
	: m_pTxList(pTxList)
	, m_Delay(Delay_ms)
	, m_CurrIdx(0UL)
	, m_PrevTime(timeGetTime())
	, m_bOnce(bOnce)
	, m_isEnd(false)
{

}


c2DImgListRender::~c2DImgListRender()
{

}

///////////////////////////////////////////////////////////////////////////////////////

int c2DImgListRender::Init(cTextureList* pTxList, DWORD Delay_ms, bool bOnce)
{
	Reset();


	m_pTxList = pTxList;
	m_Delay = Delay_ms;
	m_PrevTime = timeGetTime();
	m_bOnce = bOnce;


	return 0;
}


int c2DImgListRender::Reset()
{
	m_CurrIdx = 0;
	m_PrevTime = timeGetTime();
	m_isEnd = false;


	return 0;
}


bool c2DImgListRender::isEnd() const
{
	return m_isEnd;
}


UINT c2DImgListRender::CurrIdx() const
{
	return m_CurrIdx;
}


const cTexture* c2DImgListRender::GetCurrTexture() const
{
	if(m_isEnd) return nullptr;


	return m_pTxList->GetTexture(m_CurrIdx);
}

///////////////////////////////////////////////////////////////////////////////////////

int c2DImgListRender::Render()
{
	if(m_bOnce && m_isEnd) return 0;


	cCore::Sprite.RenderTexture(m_pTxList->GetTexture(m_CurrIdx));


	return 0;
}


int c2DImgListRender::RenderCenter()
{
	if(m_bOnce && m_isEnd) return 0;


	cCore::Sprite.RenderTextureCenter(m_pTxList->GetTexture(m_CurrIdx));


	return 0;
}


int c2DImgListRender::Render(UINT Idx)
{
	if(m_bOnce && m_isEnd) return 0;


	return cCore::Sprite.RenderTexture(m_pTxList->GetTexture(Idx));
}


int c2DImgListRender::RenderCenter(UINT Idx)
{
	if(m_bOnce && m_isEnd) return 0;


	return cCore::Sprite.RenderTextureCenter(m_pTxList->GetTexture(Idx));
}

///////////////////////////////////////////////////////////////////////////////////////

int c2DImgListRender::Update()
{
	if(timeGetTime() - m_PrevTime >= m_Delay)
	{
		m_CurrIdx++;

		if(m_CurrIdx >= m_pTxList->GetSize())
		{
			if(m_bOnce)
			{
				m_isEnd = true;
			}


			m_CurrIdx = 0;
		}


		m_PrevTime = timeGetTime();
	}


	return 0;
}

