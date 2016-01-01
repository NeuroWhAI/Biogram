#include "cFade.h"

#include "cCore.h"




















cFade::cFade(bool isFadeIn, float Speed)
	: m_Speed(isFadeIn?-fabsf(Speed):fabsf(Speed))
	, m_Alpha(isFadeIn?255.f:0.f)

	, m_isEnd(false)
{

}


cFade::~cFade()
{

}

/*----------------------------------------------------------------------------------------*/

int cFade::Update()
{
	m_Alpha += VFR(m_Speed);

	if(m_Speed < 0.f)
	{
		if(m_Alpha <= 0.f)
		{
			m_isEnd = true;
			m_Alpha = 0.f;
		}
	}
	else
	{
		if(m_Alpha >= 255.f)
		{
			m_isEnd = true;
			m_Alpha = 255.f;
		}
	}


	return 0;
}


int cFade::Render()
{
	cCore::Sprite.BeginDraw();

	cCore::Sprite.SetColor(D3DCOLOR_ARGB(static_cast<int>(m_Alpha), 255,255,255));
	cCore::Sprite.DrawTextureCenter(cCore::Resource.m_pTxList[TxList_Framework]->GetTexture(0)
		, Util::CenterPos());

	cCore::Sprite.EndDraw();


	return 0;
}



bool cFade::isEnd() const
{
	return m_isEnd;
}

