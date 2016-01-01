#pragma once
#include "cFX.h"

#include <vector>

































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 꼬리
// Desc : 이동흔적을 보여줍니다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFX_Tail : public cFX
{
public:
	cFX_Tail(const D3DXVECTOR2* pos, DWORD color, DWORD delay, float life, float width);
	cFX_Tail(cTexture* pTx, const D3DXVECTOR2* pos, DWORD color, DWORD delay, float life, float width);
	~cFX_Tail();


private:
	const D3DXVECTOR2* m_pos;
	DWORD m_color;
	DWORD m_prevTime, m_delay;
	float m_life;
	float m_width;


private:
	std::vector<D3DXVECTOR2> m_posList;
	std::vector<float> m_lifeList;


private:
	virtual int OnUpdate();
	virtual int OnRender();
	

private:
	int Seq_Tail();
};

