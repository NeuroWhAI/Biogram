#include "cLayer_Back.h"

#include "cCore.h"

#include "cTextureList.h"



























cLayer_Back::cLayer_Back()
	: m_pTxList(NULL)
{

}


cLayer_Back::~cLayer_Back()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Back::OnInit()
{



	return 0;
}


int cLayer_Back::OnDestory()
{
	


	return 0;
}

/*-------------------------------------------------------------------------------------------------------*/

int cLayer_Back::OnUpdate()
{
	


	return 0;
}


int cLayer_Back::OnRender()
{
	if(m_pTxList != NULL)
	{
		int CurrPos = 0;

		cCore::Sprite.BeginDraw();

		for(UINT i=0; i<m_pTxList->GetSize(); i++)
		{
			cCore::Sprite.DrawTexture(m_pTxList->GetTexture(i), D3DXVECTOR2(CAST(CurrPos, float), 0.f));


			CurrPos += m_pTxList->GetTexture(i)->Width();
		}

		cCore::Sprite.EndDraw();
	}


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cLayer_Back::Reset()
{
	m_pTxList = NULL;


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


