#pragma once
#include <d3dx9.h>





enum FADE_
{
	FADE_OUT = 0,
	FADE_IN = 1
};












///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���̵���/�ƿ�
// Desc : ȭ���� ���̵���/�ƿ��� �����Ѵ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFade
{
public:
	cFade(bool isFadeIn, float Speed);
	~cFade();


private:
	float m_Speed;
	float m_Alpha;

	bool m_isEnd;


public:
	int Update();
	int Render();

	bool isEnd() const;
};

