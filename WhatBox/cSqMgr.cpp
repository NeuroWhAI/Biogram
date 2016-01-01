#include "cSqMgr.h"

#include "cSequence.h"
#include "cSq_Load.h"

#include "cCore.h"










cSqMgr::cSqMgr()
	: m_CurrSq(NULL)
{
	
}


cSqMgr::~cSqMgr()
{
	if(m_CurrSq != NULL)
	{
		delete m_CurrSq;
		m_CurrSq = NULL;
	}
}

/*--------------------------------------------------------------*/

int cSqMgr::Init()
{
	m_CurrSq = new cSq_Load;
	m_CurrSq->Init();


	return 0;
}


int cSqMgr::CleanUp()
{
	if(m_CurrSq == NULL) return -1;


	m_CurrSq->CleanUp();


	return 0;
}



int cSqMgr::Release()
{
	if(m_CurrSq == NULL) return -1;


	m_CurrSq->Release();


	return 0;
}


int cSqMgr::Restore()
{
	if(m_CurrSq == NULL) return -1;


	m_CurrSq->Restore();


	return 0;
}



int cSqMgr::Delete()   //�Ϲ� ������ '����'(������ �ƴ�)
{
	if(m_CurrSq == NULL) return -1;


	m_CurrSq->Delete();


	return 0;
}



int cSqMgr::Render()
{
	m_CurrSq->Render();


	return 0;
}


int cSqMgr::Update()
{
	cSequence* pNext = m_CurrSq->Update();


	if(pNext == EXIT_SEQ)
	{//���� ��û ����
		// ���� ����
		cCore::World->Reset();

		m_CurrSq->Delete();
		m_CurrSq->CleanUp();

		delete m_CurrSq; m_CurrSq = NULL;

		cCore::Exit = true; // ���α׷� �����û
		return SEQ_EXIT;
	}
	else if(pNext != m_CurrSq)
	{//������ �̵� ��û ����
		// 2Dī�޶� �ʱ�ȭ
		cCore::Camera2D.Reset();

		// ���� ����
		cCore::World->Reset();


		// �̵�
		cSequence* pNext2 = m_CurrSq->GetNextSq(); // ���� �������κ��� ��û�� ���� ������

		m_CurrSq->Delete();
		m_CurrSq->CleanUp();

		delete m_CurrSq; m_CurrSq = NULL;


		m_CurrSq = (pNext2 != NULL) ? pNext2 : pNext;

		m_CurrSq->Init();


		return SEQ_CHANGE;
	}


	return SEQ_CONTINUE;
}

