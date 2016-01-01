#include "cEffect.h"

#include "cTextureList.h"
#include "c2DImgListRender.h"





























cEffect::cEffect()
	: m_pRender(new c2DImgListRender())
{

}


cEffect::cEffect(cTextureList* pTxList, DWORD Delay, bool bOnce)
	: m_pRender(new c2DImgListRender(pTxList, Delay, bOnce))
{

}


cEffect::~cEffect()
{
	if(m_pRender != NULL)
	{
		delete m_pRender;
		m_pRender = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cEffect::Init(cTextureList* pTxList, DWORD Delay, bool bOnce)
{
	m_pRender->Init(pTxList, Delay, bOnce);


	return 0;
}


int cEffect::Update()
{
	m_Pos += m_Speed;
	m_Angle += m_AngleSpeed;


	m_pRender->Update();


	return 0;
}


int cEffect::RenderCenter()
{
	m_pRender->RenderCenter();


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cEffect::isEnd() const
{
	return m_pRender->isEnd();
}

