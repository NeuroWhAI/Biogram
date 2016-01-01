#pragma once

class cSequence;









///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 시퀀스매니저
// Desc : 시퀀스의 초기화, 갱신, 종료 그리고 시퀀이전이를 담당한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSqMgr
{
public:
	cSqMgr();
	~cSqMgr();


private:
	cSequence* m_CurrSq;	//현재 시퀀스


public:
	int Init();
	int CleanUp();
	
	int Release();
	int Restore();

	int Delete();   //일반 변수들 '삭제'(해제가 아님)

	int Render();
	int/*SEQ*/ Update();
};

