#pragma once
#include "cFX.h"
#include <vector>

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ÆøÁ×
// Desc : ÀÌ¹ÌÁö¸¦ ÆøÁ×Ã³·³ Èð»Ñ¸²
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Firework : public cFX
{
public:
	cFX_Firework(cTexture* pTx, float randomize, float speed);
	~cFX_Firework();
	

private:
	class cParticle
	{
	public:
		cParticle(float life,
			const D3DXVECTOR2& pos,
			const D3DXVECTOR2& speed,
			float angle,
			float scale,
			DWORD color)
			: life(life)
			, pos(pos)
			, speed(speed)
			, angle(angle)
			, scale(scale)
			, color(color)
		{}

		float life;
		D3DXVECTOR2 pos;
		D3DXVECTOR2 speed;
		float angle;
		float scale;
		DWORD color;
	};

	std::vector<cParticle> m_particleList;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_Firework();


private:
	int CreateParticle(float angle, float speed, float life, DWORD color);
};

