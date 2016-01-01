#include "cNumberRender.h"

#include "cTextureList.h"

#include "cCore.h"

























cNumberRender::cNumberRender()
	: m_pTxList(NULL)
	, m_Number(0)
	, m_TxWidth(0.f)
{

}


cNumberRender::cNumberRender(cTextureList* pTxList)
	: m_pTxList(pTxList)
	, m_Number(0)
	, m_TxWidth(0.f)
{
	if(pTxList != NULL)
	{
		if(pTxList->GetSize() > 0)
		{
			m_TxWidth = CAST(pTxList->GetTexture(0)->Width(), float);
		}
	}
}


cNumberRender::~cNumberRender()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////

int cNumberRender::SetTextureList(cTextureList* pTxList)
{
	m_pTxList = pTxList;

	if(pTxList != NULL)
	{
		if(pTxList->GetSize() > 0)
		{
			m_TxWidth = CAST(pTxList->GetTexture(0)->Width(), float);
		}
	}


	return 0;
}


int cNumberRender::SetNumber(int Number)
{
	m_Number = Number;


	return 0;
}


int cNumberRender::GetNumber() const
{
	return m_Number;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int cNumberRender::Render(float x, float y) const
{
	return Render(m_Number, x, y);
}


int cNumberRender::Render(int Number, float x, float y) const
{
	if(m_pTxList == NULL) return -1;


	cCore::Sprite.BeginDraw();


	if(Number < 0)
	{// 음수
		cCore::Sprite.DrawTexture(m_pTxList->GetTexture(10/*'-'*/), D3DXVECTOR2(x, y));

		Number *= -1;
	
		x += m_TxWidth;
	}
	else if(Number == 0)
	{// 그냥 0
		cCore::Sprite.DrawTexture(m_pTxList->GetTexture(0/*'0'*/), D3DXVECTOR2(x, y));


		cCore::Sprite.EndDraw();
		return 0;
	}
	

	bool bDrawZero = false;

	for(int i = 10/* 최대 10자리면 충분하지 */; i >= 0; i--)
	{
		// 숫자 계산
		int Num = Number % Pow(10, i+1) / Pow(10, i);

		// 유효숫자가 아닌 0은 무시
		if(bDrawZero == false)
		{
			if(Num == 0)
			{
				continue;
			}
			else
			{
				bDrawZero = true;
			}
		}

		// 그리기
		cCore::Sprite.DrawTexture(m_pTxList->GetTexture(Num), D3DXVECTOR2(x, y));

		x += m_TxWidth;
	}


	cCore::Sprite.EndDraw();


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int cNumberRender::Pow(int x, int y) const
{
	if(y == 0)
		return 1;


	int Result = x;

	for(int i=1; i<y; i++)
	{
		Result *= x;
	}


	return Result;
}

