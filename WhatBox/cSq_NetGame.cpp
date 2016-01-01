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
	cCore::Sprite.OnCamera(); // 2D 카메라 켜기
	

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



int cSq_NetGame::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	m_pNetClient->Close();


	return 0;
}



cSequence* cSq_NetGame::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	if(cCore::Input.KeyDown(VK_ESCAPE)) // NOTE: ESC키로 종료. 필요시 삭제.
		return EXIT_SEQ;


	cCore::Camera.Control(); // 3D 카메라 조작
	cCore::Camera2D.Control(); // 2D 스프라이트 카메라 조작


	m_pNetClient->Update();


	/*--------------------------------*/
	return pNext;
}


int cSq_NetGame::OnRender()
{
	m_pNetClient->Render();


	return 0;
}

