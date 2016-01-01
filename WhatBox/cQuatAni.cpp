#include "cQuatAni.h"

#include "cCore.h"

#include "cTextureList.h"






































cQuatAni::cQuatAni(cTextureList* pTxList, int frameNum, int angleNum, DWORD delay)
	: m_pTxList(pTxList)
	, m_frameNum(frameNum)
	, m_angleNum(angleNum)
	, m_delay(delay)

	, m_startNum(0)
	, m_currFrame(0)
	, m_prevAniTime(timeGetTime())

	, m_bOnPlay(false)
	, m_bEnd(false)
{

}


cQuatAni::~cQuatAni()
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAni::Update()
{
	while (m_Angle >= 360.f) m_Angle -= 360.f;
	while (m_Angle < 0.f) m_Angle += 360.f;

	m_startNum = CAST(m_Angle / (360.f / m_angleNum), int) * m_frameNum;


	if (m_bOnPlay)
	{
		if (timeGetTime() - m_prevAniTime >= m_delay)
		{
			if (m_bEnd) m_bEnd = false;

			++m_currFrame;

			if (m_currFrame >= m_frameNum)
			{
				m_currFrame = 0;


				m_bEnd = true;
			}


			m_prevAniTime = timeGetTime();
		}
	}


	return 0;
}


int cQuatAni::Render()
{
	cCore::Sprite.RenderTextureCenter(m_pTxList->GetTexture(CAST(m_startNum + m_currFrame, UINT)),
		*this->GetQuaterPos(), 0.f, m_Scale);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cQuatAni::Play()
{
	m_bOnPlay = true;


	return 0;
}


int cQuatAni::Pause()
{
	m_bOnPlay = false;


	return 0;
}


int cQuatAni::Stop()
{
	m_bOnPlay = false;


	m_currFrame = 0;


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool cQuatAni::IsEnd() const
{
	return m_bEnd;
}

