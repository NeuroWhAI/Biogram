#include "cSq_Game.h"

#include "cCore.h"

#include "BiogramApp.h"





































cSq_Game::cSq_Game()
	: m_pApp(std::make_shared<BiogramApp>())
{
	
}


cSq_Game::~cSq_Game()
{
	
}

/*----------------------------------------------------------------------------------*/

int cSq_Game::OnInit()
{
	cCore::Sprite.OnCamera(); // 2D ī�޶� �ѱ�


	m_pApp->init();


	return 0;
}


int cSq_Game::OnCleanUp()
{
	


	return 0;
}



int cSq_Game::OnRestore()
{



	return 0;
}


int cSq_Game::OnRelease()
{



	return 0;
}



int cSq_Game::OnDelete()   //�Ϲ� ������ '����'(������ �ƴ�)
{
	m_pApp->release();


	return 0;
}



cSequence* cSq_Game::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESCŰ�� ����. �ʿ�� ����.
		return EXIT_SEQ;


	cCore::Camera2D.Control(); // 2D ��������Ʈ ī�޶� ����


	m_pApp->update();


	/*--------------------------------*/
	return pNext;
}


int cSq_Game::OnRender()
{
	m_pApp->render();


	return 0;
}

