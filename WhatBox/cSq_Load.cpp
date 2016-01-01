#include "cSq_Load.h"

#include "cCore.h"

#include "cResourceLoad.h"
#include "cFade.h"

#include "cSq_Intro.h"


















cSq_Load::cSq_Load()
	: m_pResourceLoad(NULL)
	, m_pFadeOut(NULL)
{
	
}


cSq_Load::~cSq_Load()
{
	SAFE_DELETE(m_pResourceLoad);
	SAFE_DELETE(m_pFadeOut);
}

/*----------------------------------------------------------------------------------*/

int cSq_Load::OnInit()
{
	m_pResourceLoad = new cResourceLoad;
	m_pResourceLoad->Init();


	return 0;
} 


int cSq_Load::OnCleanUp()
{
	


	return 0;
}



int cSq_Load::OnRestore()
{



	return 0;
}


int cSq_Load::OnRelease()
{



	return 0;
}



int cSq_Load::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_Load::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(m_pFadeOut == NULL)
	{
		m_pResourceLoad->Loading();

		if(m_pResourceLoad->isEnd())
			m_pFadeOut = new cFade(FADE_OUT, 16.f);
	}
	else
	{
		m_pFadeOut->Update();
		
		if(m_pFadeOut->isEnd())
			return new cSq_Intro;
	}


	/*--------------------------------*/
	return pNext;
}


int cSq_Load::OnRender()
{
	m_pResourceLoad->Render();

	if(m_pFadeOut != NULL)
		m_pFadeOut->Render();


	return 0;
}

