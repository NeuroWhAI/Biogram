#pragma once
#include <d3d9.h>


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���
// Desc : ���۰����� �������� ���ϴ� �ð����� ���� ���������
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

