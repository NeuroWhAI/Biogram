#include "cSq_Intro.h"

#include "cCore.h"

#include "cSq_Main.h"


















cSq_Intro::cSq_Intro()
{

}


cSq_Intro::~cSq_Intro()
{

}

/*----------------------------------------------------------------------------------*/

int cSq_Intro::OnInit()
{
	


	return 0;
}


int cSq_Intro::OnCleanUp()
{
	


	return 0;
}



int cSq_Intro::OnRestore()
{



	return 0;
}


int cSq_Intro::OnRelease()
{



	return 0;
}



int cSq_Intro::OnDelete()   //일반 변수들 '삭제'(해제가 아님)
{
	


	return 0;
}



cSequence* cSq_Intro::OnUpdate()
{
	cSequence* pNext = this;
	/*--------------------------------*/


	return new cSq_Main;


	/*--------------------------------*/
	return pNext;
}


int cSq_Intro::OnRender()
{
	


	return 0;
}

