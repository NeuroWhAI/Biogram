#include "cLayer_Fade.h"

#include "cCore.h"

#include "cFade.h"


























cLayer_Fade::cLayer_Fade()
	: m_pFade(NULL)
	, m_color(0xff000000)
	, m_bWaitOnce(true)
{

}


cLayer_Fade::~cLayer_Fade()
{
	SAFE_DELETE(m_pFade);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Fade::OnInit()
{



	return 0;
}


int cLayer_Fade::OnDestory()
{



	return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

int cLayer_Fade::OnUpdate()
{
	if (m_pFade != NULL)
	{
		m_pFade->Update();

		if (m_pFade->isEnd())
		{
			if (m_bWaitOnce)
			{
				m_bWaitOnce = false;
			}
			else
			{
				delete m_pFade;
				m_pFade = nullptr;
			}
		}
	}


	return 0;
}


int cLayer_Fade::OnRender()
{
	bool PrevCameraState = cCore::Sprite.CameraOnCheck();
	cCore::Sprite.OffCamera();


	SAFE_ACCESS(m_pFade, Render());


	if (PrevCameraState)
		cCore::Sprite.OnCamera();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Fade::FadeOut(float Speed, DWORD color)
{
	m_color = color;


	if (m_pFade != NULL) delete m_pFade;

	m_pFade = new cFade(FADE_OUT, Speed);


	m_bWaitOnce = true;


	return 0;
}


int cLayer_Fade::FadeIn(float Speed, DWORD color)
{
	m_color = color;


	if (m_pFade != NULL) delete m_pFade;

	m_pFade = new cFade(FADE_IN, Speed);


	m_bWaitOnce = true;


	return 0;
}


bool cLayer_Fade::IsEnd() const
{
	if (m_pFade == nullptr) return true;


	return m_pFade->isEnd();
}

