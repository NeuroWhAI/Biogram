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
	// ���ۿ� ���� �� ����
	sVertex Vertex[2] = {
		{P1, Color},
		{P2, Color}
	};


	// �������� ����
	m_pVB->Create(sizeof(sVertex), 2, sVertex::FVF);
	// �� �����
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
	Util::TempRenderState SetRenderState(D3DRS_LIGHTING, FALSE); // ����ȿ����
	Util::TempRenderState SetRenderState2(D3DRS_CULLMODE, D3DCULL_NONE); // �ø���

	cCore::pd3dDevice->SetTexture(0, NULL); // �ؽ��Ļ�� ����


	m_pVB->Draw(D3DPT_LINELIST);


	return 0;
}

