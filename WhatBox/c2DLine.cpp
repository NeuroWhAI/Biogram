#include "c2DLine.h"

#include "cCore.h"



















c2DLine::c2DLine()
	: m_pLine(NULL)
{

}


c2DLine::~c2DLine()
{
	CleanUp();
}

//////////////////////////////////////////////////////////////////////////////////////

int c2DLine::Init()
{
	CleanUp();


	D3DXCreateLine(cCore::pd3dDevice, &m_pLine);

	
	m_pLine->SetAntialias(TRUE);


	return 0;
}


int c2DLine::CleanUp()
{
	SAFE_RELEASE(m_pLine);


	return 0;
}


int c2DLine::Render(float left, float top, float right, float bottom, DWORD Color, float Width)
{
	m_pLine->SetWidth(Width);


	D3DXVECTOR2 Temp(0.f, 0.f);
	const D3DXVECTOR2* CameraPos = &Temp;

	if(cCore::Sprite.CameraOnCheck())
		CameraPos = cCore::Camera2D.Pos();
	

	D3DXVECTOR2 vList[2]=
	{
		D3DXVECTOR2(left, top) - *CameraPos,
		D3DXVECTOR2(right, bottom) - *CameraPos
	};

	m_pLine->Begin();
	m_pLine->Draw(vList, 2, Color);
	m_pLine->End();


	return 0;
}


int c2DLine::Render(const D3DXVECTOR2* pP1, const D3DXVECTOR2* pP2, DWORD Color, float Width)
{
	return Render(pP1->x, pP1->y, pP2->x, pP2->y, Color, Width);
}


int c2DLine::Render(const D3DXVECTOR2 VtxArr[], int VtxNum, DWORD Color, float Width)
{
	m_pLine->SetWidth(Width);


	if(cCore::Sprite.CameraOnCheck())
	{
		D3DXVECTOR2* Vtxs = new D3DXVECTOR2[VtxNum];
		D3DXVECTOR2 CameraPos = *cCore::Camera2D.Pos();

		for(int i=0; i<VtxNum; i++)
		{
			Vtxs[i] = VtxArr[i] - CameraPos;
		}


		m_pLine->Begin();
		m_pLine->Draw(Vtxs, VtxNum, Color);
		m_pLine->End();


		delete[] Vtxs;
	}
	else
	{
		m_pLine->Begin();
		m_pLine->Draw(VtxArr, VtxNum, Color);
		m_pLine->End();
	}


	return 0;
}


int c2DLine::Begin()
{
	m_pLine->Begin();


	return 0;
}


int c2DLine::End()
{
	m_pLine->End();


	return 0;
}


int c2DLine::Draw(float left, float top, float right, float bottom, DWORD Color)
{
	D3DXVECTOR2 Temp(0.f, 0.f);
	const D3DXVECTOR2* CameraPos = &Temp;

	if(cCore::Sprite.CameraOnCheck())
		CameraPos = cCore::Camera2D.Pos();
	

	D3DXVECTOR2 vList[2]=
	{
		D3DXVECTOR2(left, top) - *CameraPos,
		D3DXVECTOR2(right, bottom) - *CameraPos
	};

	m_pLine->Draw(vList, 2, Color);


	return 0;
}


int c2DLine::Draw(const D3DXVECTOR2* pP1, const D3DXVECTOR2* pP2, DWORD Color)
{
	return Draw(pP1->x, pP1->y, pP2->x, pP2->y, Color);
}


int c2DLine::Draw(const D3DXVECTOR2 VtxArr[], int VtxNum, DWORD Color)
{
	if(cCore::Sprite.CameraOnCheck())
	{
		D3DXVECTOR2* Vtxs = new D3DXVECTOR2[VtxNum];
		D3DXVECTOR2 CameraPos = *cCore::Camera2D.Pos();

		for(int i=0; i<VtxNum; i++)
		{
			Vtxs[i] = VtxArr[i] - CameraPos;
		}


		m_pLine->Draw(Vtxs, VtxNum, Color);


		delete[] Vtxs;
	}
	else
	{
		m_pLine->Draw(VtxArr, VtxNum, Color);
	}


	return 0;
}


int c2DLine::SetWidth(float width)
{
	m_pLine->SetWidth(width);


	return 0;
}

