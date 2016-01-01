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



int cSqMgr::Delete()   //일반 변수들 '삭제'(해제가 아님)
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
	{//종료 요청 받음
		// 월드 리셋
		cCore::World->Reset();

		m_CurrSq->Delete();
		m_CurrSq->CleanUp();

		delete m_CurrSq; m_CurrSq = NULL;

		cCore::Exit = true; // 프로그램 종료요청
		return SEQ_EXIT;
	}
	else if(pNext != m_CurrSq)
	{//시퀀스 이동 요청 받음
		// 2D카메라 초기화
		cCore::Camera2D.Reset();

		// 월드 리셋
		cCore::World->Reset();


		// 이동
		cSequence* pNext2 = m_CurrSq->GetNextSq(); // 이전 시퀀스로부터 요청된 다음 시퀀스

		m_CurrSq->Delete();
		m_CurrSq->CleanUp();

		delete m_CurrSq; m_CurrSq = NULL;


		m_CurrSq = (pNext2 != NULL) ? pNext2 : pNext;

		m_CurrSq->Init();


		return SEQ_CHANGE;
	}


	return SEQ_CONTINUE;
}

