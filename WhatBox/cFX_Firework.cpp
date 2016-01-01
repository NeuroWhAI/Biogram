#include "cFX_Firework.h"

#include "cCore.h"





































cFX_Firework::cFX_Firework(cTexture* pTx, float randomize, float speed)
	: cFX(pTx)
{
	m_sequencer.AddFunction(LAMBDA_FUNC(Seq_Firework), 0);


	m_sequencer.SetCurrFuncNum(0);


	for(float angle=0.f; angle<360.f; angle += 4.f)
	{
		int count = 1 + CAST(speed, int) / 2;

		for(int p=0; p<count; p++)
		{
			float randAngle = angle + CAST(rand(), float)/CAST(RAND_MAX, float) * randomize;

			CreateParticle(randAngle, CAST(rand(), float)/CAST(RAND_MAX, float) * randomize + CAST(p + 1, float)*(speed/CAST(count, float)),
				16 * speed / 2.f, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}


cFX_Firework::~cFX_Firework()
{
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Firework::OnUpdate()
{
	


	return 0;
}


int cFX_Firework::OnRender()
{
	cCore::Sprite.BeginDraw();

	for(UINT i=0; i<m_particleList.size(); i++)
	{
		int alpha = CAST(m_particleList[i].life, int);
		if(alpha > 255) alpha = 255;


		cCore::Sprite.SetColor(m_particleList[i].color & 0x00ffffff | (CAST(alpha, DWORD) << 24));

		cCore::Sprite.DrawTextureCenter(m_pTx,
			m_particleList[i].pos + m_Pos, m_particleList[i].angle,
			D3DXVECTOR2(m_particleList[i].scale, m_particleList[i].scale));
	}

	cCore::Sprite.EndDraw();


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Firework::Seq_Firework()
{
	for(UINT i=0; i<m_particleList.size(); ++i)
	{
		m_particleList[i].life -= VFR(2.f);

		if(m_particleList[i].life < 0.f)
		{
			m_particleList.erase(m_particleList.begin() + i);
			--i;
			continue;
		}

		D3DXVECTOR2 breakVec;
		D3DXVec2Normalize(&breakVec, &m_particleList[i].speed);

		m_particleList[i].speed -= VFR(breakVec*0.4f);
		m_particleList[i].pos += VFR(m_particleList[i].speed);
	}


	if(m_particleList.size() <= 0U)
		return FUNCRESULT_End;


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int cFX_Firework::CreateParticle(float angle, float speed, float life, DWORD color)
{
	D3DXVECTOR2 speedVec;
	cCore::ShapeMath.GetPosition(&speedVec, speed, angle);


	m_particleList.emplace_back(cParticle(life, m_Pos, m_Speed+speedVec, angle,
		0.1f + CAST(rand(), float)/CAST(RAND_MAX, float)*2.f,
		color));


	return 0;
}

