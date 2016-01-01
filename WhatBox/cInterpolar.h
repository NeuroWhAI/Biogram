#pragma once
#include <d3d9.h>


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 양극
// Desc : 시작값에서 끝값까지 원하는 시간동안 값을 진행시켜줌
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cInterpolar
{
public:
	cInterpolar(float Start, float End, DWORD Time/*ms*/);
	~cInterpolar();


private:
	float m_CurrVal;
	float m_EndVal;

	float m_Bigger;

	float m_Speed;

	bool m_isEnd;


public:
	int FrameMove();
	bool isEnd() const;

	float Value() const;
};

