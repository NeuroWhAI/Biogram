#pragma once
#include <d3dx9.h>







#define EXIT_SEQ NULL

enum SEQ_
{
	SEQ_NONE,        //NULL
	SEQ_CONTINUE,    //��ȭ ����
	SEQ_EXIT,        //���α׷� ����
	SEQ_CHANGE       //��ȭ ����
};








///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ������
// Desc : ������Ŭ������ ����µ� �ʼ��� ����ؾ��� Ŭ����. �߿� �������̽� Ʋ�� �����Ѵ�.
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

	int Delete() {return OnDelete();}   //�Ϲ� ������ '����'(������ �ƴ�)
	
	cSequence* Update() {return OnUpdate();}
	int Render() {return OnRender();}


protected:
	virtual int OnInit()=0;
	virtual int OnCleanUp()=0;

	virtual int OnRestore()=0;
	virtual int OnRelease()=0;

	virtual int OnDelete()=0;   //�Ϲ� ������ '����'(������ �ƴ�)
	
	virtual cSequence* OnUpdate()=0;
	virtual int OnRender()=0;


public:
	cSequence* GetNextSq() {return m_pNextSq;}
};




