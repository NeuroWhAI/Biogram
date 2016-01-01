#include "cSq_Main.h"

#include "cCore.h"

#include "cSq_Game.h"
#include "cSq_NetConnect.h"






















cSq_Main::cSq_Main()
{

}


cSq_Main::~cSq_Main()
{

}

/*----------------------------------------------------------------------------------*/

int cSq_Main::OnInit()
{
	


	return 0;
}


int cSq_Main::OnCleanUp()
{
	


	return 0;
}



int cSq_Main::OnRestore()
{



	return 0;
}


int cSq_Main::OnRelease()
{



	return 0;
}



int cSq_Main::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_Main::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


#ifndef SINGLE_GAME
	return new cSq_NetConnect;
#else
	return new cSq_Game;
#endif


	/*--------------------------------*/
	return pNext;
}


int cSq_Main::OnRender()
{
	


	return 0;
}

