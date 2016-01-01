#include "cFX_Tail.h"

#include "cCore.h"






































cFX_Tail::cFX_Tail(const D3DXVECTOR2* pos, DWORD color, DWORD delay, float life, float width)
	: cFX()

	, m_pos(pos)
	, m_color(color)
	, m_prevTime(timeGetTime())
	, m_delay(delay)
	, m_life(life)
	, m_width(width)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Tail), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Tail::cFX_Tail(cTexture* pTx, const D3DXVECTOR2* pos, DWORD color, DWORD delay, float life, float width)
	: cFX(pTx)

	, m_pos(pos)
	, m_color(color)
	, m_prevTime(timeGetTime())
	, m_delay(delay)
	, m_life(life)
	, m_width(width)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Tail), 0);


	m_sequencer.SetCurrFuncNum(0);
}


cFX_Tail::~cFX_Tail()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Tail::OnUpdate()
{
	


	return 0;
}


int cFX_Tail::OnRender()
{
	if(m_posList.size() > 0)
	{
		for(UINT i=0; i<m_posList.size()-1; ++i)
		{
			if(m_lifeList[i+1] < 0.f) m_lifeList[i+1] = 0.f;
			DWORD alpha = CAST(255.f*m_lifeList[i+1]/m_life, DWORD);

			cCore::Resource.Line.Render(&m_posList[i], &m_posList[i+1],
				m_color & 0x00ffffff | (alpha << 24), m_width);
		}

		
		if(m_pTx != nullptr)
		{
			cCore::Sprite.BeginDraw();

			for(UINT i=0; i<m_posList.size(); ++i)
			{
				if(m_lifeList[i] < 0.f) m_lifeList[i] = 0.f;
					DWORD alpha = CAST(255.f*m_lifeList[i]/m_life, DWORD);

				cCore::Sprite.SetColor(m_color & 0x00ffffff | (alpha << 24));
				cCore::Sprite.DrawTextureCenter(m_pTx,
					m_posList[i], m_Angle, m_Scale);
			}

			cCore::Sprite.EndDraw();
		}
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Tail::Seq_Tail()
{
	for(UINT i=0; i<m_lifeList.size(); ++i)
	{
		m_lifeList[i] -= cCore::FrameRate;

		if(m_lifeList[i] <= 0.f)
		{
			m_lifeList.erase(m_lifeList.begin() + i);
			m_posList.erase(m_posList.begin() + i);

			--i;
			continue;
		}
	}


	if(timeGetTime() - m_prevTime >= m_delay)
	{
		m_posList.emplace_back(m_pos->x, m_pos->y);
		m_lifeList.emplace_back(m_life);
	}


	return 0;
}

