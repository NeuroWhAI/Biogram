#include "cParticle_Basic.h"

#include "cCore.h"







































cParticle_Basic::cParticle_Basic(DWORD color, float mass, cTexture* pTx, float life)
	: cParticle(color, mass, pTx, life)
{

}


cParticle_Basic::~cParticle_Basic()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cParticle_Basic::OnUpdate()
{



	return 0;
}


int cParticle_Basic::OnRender()
{
	if(m_pTx != nullptr)
	{
		cCore::Sprite.SetColor(m_color);
		cCore::Sprite.RenderTextureCenter(m_pTx, m_Pos, m_Angle, m_Scale);
	}


	return 0;
}


