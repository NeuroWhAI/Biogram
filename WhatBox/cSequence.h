#pragma once
#include <d3dx9.h>







#define EXIT_SEQ NULL

enum SEQ_
{
	SEQ_NONE,        //NULL
	SEQ_CONTINUE,    //변화 없음
	SEQ_EXIT,        //프로그램 종료
	SEQ_CHANGE       //변화 있음
};








///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 시퀀스
// Desc : 시퀀스클래스를 만드는데 필수로 상속해야할 클래스. 중요 인터페이스 틀을 제공한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSequence
{
public:
	cSequence(cSequence* pNextSq = NULL) : m_pNextSq(pNextSq)
	{}
	virtual ~cSequence()
	{}


protected:
	cSequence* m_pNextSq;

	
public:
	int Init() {return OnInit();}
	int CleanUp() {return OnCleanUp();}

	int Restore() {return OnRestore();}
	int Release() {return OnRelease();}

	int Delete() {return OnDelete();}   //일반 변수들 '삭제'(해제가 아님)
	
	cSequence* Update() {return OnUpdate();}
	int Render() {return OnRender();}


protected:
	virtual int OnInit()=0;
	virtual int OnCleanUp()=0;

	virtual int OnRestore()=0;
	virtual int OnRelease()=0;

	virtual int OnDelete()=0;   //일반 변수들 '삭제'(해제가 아님)
	
	virtual cSequence* OnUpdate()=0;
	virtual int OnRender()=0;


public:
	cSequence* GetNextSq() {return m_pNextSq;}
};




