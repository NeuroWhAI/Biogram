#include "cLine.h"

#include "cCore.h"
#include "cD3DVtxBuffer.h"





















cLine::cLine()
	: m_pVB(new cD3DVtxBuffer)
{

}


cLine::~cLine()
{
	Release();
	SAFE_DELETE(m_pVB);
}

/*---------------------------------------------------------------------------------------*/

int cLine::Create(D3DXVECTOR3 P1, D3DXVECTOR3 P2, DWORD Color)
{
	// 버퍼에 씌울 값 생성
	sVertex Vertex[2] = {
		{P1, Color},
		{P2, Color}
	};


	// 정점버퍼 생성
	m_pVB->Create(sizeof(sVertex), 2, sVertex::FVF);
	// 값 씌우기
	m_pVB->VtxCpy(Vertex);


	return 0;
}


int cLine::Release()
{
	m_pVB->Release();


	return 0;
}


int cLine::Draw()
{
	Util::TempRenderState SetRenderState(D3DRS_LIGHTING, FALSE); // 조명효과끔
	Util::TempRenderState SetRenderState2(D3DRS_CULLMODE, D3DCULL_NONE); // 컬링끔

	cCore::pd3dDevice->SetTexture(0, NULL); // 텍스쳐사용 안함


	m_pVB->Draw(D3DPT_LINELIST);


	return 0;
}

