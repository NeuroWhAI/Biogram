#include "cSq_NetGame.h"

#include "cCore.h"

#include "cNetClient.h"

























cSq_NetGame::cSq_NetGame(cNetClient* pNetClient)
	: m_pNetClient(pNetClient)
{
	
}


cSq_NetGame::~cSq_NetGame()
{
	SAFE_DELETE(m_pNetClient);
}

/*----------------------------------------------------------------------------------*/

int cSq_NetGame::OnInit()
{
	cCore::Sprite.OnCamera(); // 2D ī�޶� �ѱ�
	

	return 0;
}


int cSq_NetGame::OnCleanUp()
{
	


	return 0;
}



int cSq_NetGame::OnRestore()
{



	return 0;
}


int cSq_NetGame::OnRelease()
{



	return 0;
}



int cSq_NetGame::OnDelete()   //�Ϲ� ������ '����'(������ �ƴ�)
{
	m_pNetClient->Close();


	return 0;
}



cSequence* cSq_NetGame::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESCŰ�� ����. �ʿ�� ����.
		return EXIT_SEQ;


	cCore::Camera.Control(); // 3D ī�޶� ����
	cCore::Camera2D.Control(); // 2D ��������Ʈ ī�޶� ����


	m_pNetClient->Update();


	/*--------------------------------*/
	return pNext;
}


int cSq_NetGame::OnRender()
{
	m_pNetClient->Render();


	return 0;
}

