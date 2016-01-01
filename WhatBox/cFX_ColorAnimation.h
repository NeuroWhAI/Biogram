#pragma once
#include "cFX.h"

#include <d3dx9.h>

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 점점작아지게
// Desc : 이미지가 점점 작아지다가 사라짐
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_ColorAnimation : public cFX
{
public:
	cFX_ColorAnimation(cTexture* pTx, DWORD startColor, DWORD endColor, float speed);
	~cFX_ColorAnimation();


private:
	class cARGB
	{
	public:
		cARGB() {}
		cARGB(DWORD color)
			: a(static_cast<float>((color & 0xff000000) >> 24))
			, r(static_cast<float>((color & 0x00ff0000) >> 16))
			, g(static_cast<float>((color & 0x0000ff00) >> 8))
			, b(static_cast<float>(color & 0x000000ff))
		{

		}


		float a, r, g, b;


		DWORD GetColor() const
		{
			return D3DCOLOR_ARGB((int)a, (int)r, (int)g, (int)b);
		}
	};


private:
	cARGB m_startColor, m_endColor;
	cARGB m_speed;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_ColorAni();


private:
	bool isColorEnd(float speed, float *curr, float end);
};

