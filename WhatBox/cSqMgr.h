#pragma once

class cSequence;









///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �������Ŵ���
// Desc : �������� �ʱ�ȭ, ����, ���� �׸��� ���������̸� ����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSqMgr
{
public:
	cSqMgr();
	~cSqMgr();


private:
	cSequence* m_CurrSq;	//���� ������


public:
	int Init();
	int CleanUp();
	
	int Release();
	int Restore();

	int Delete();   //�Ϲ� ������ '����'(������ �ƴ�)

	int Render();
	int/*SEQ*/ Update();
};

