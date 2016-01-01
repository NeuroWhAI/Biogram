#include "cImgListRender.h"

#include "cTextureList.h"
#include "cPlane.h"

#include "cCore.h"




















cImgListRender::cImgListRender(cTextureList* pTxList, bool isCenter)
	: m_pPlane(NULL)
	, m_pTxList(pTxList)

	, m_onMt(false)
{
	D3DXVECTOR3 Axis(0, 1, 0);

	D3DXMatrixTranslation(&m_Mat[T], 0, 0, 0);
	D3DXMatrixIdentity(&m_Mat[R]);
	D3DXMatrixScaling(&m_Mat[S], 1.f, 1.f, 1.f);


	// 보드 생성
	m_pPlane = new cPlane;
	m_pPlane->Create(0, 0, static_cast<float>(pTxList->GetTexture(0)->Width())/32.f
		, static_cast<float>(pTxList->GetTexture(0)->Height())/32.f, 1, 1
		, true, isCenter);
}


cImgListRender::~cImgListRender()
{
	SAFE_DELETE(m_pPlane);
}

/*-------------------------------------------------------------------------------------*/

int cImgListRender::SetPos(const D3DXVECTOR3& Pos)
{
	D3DXMatrixTranslation(&m_Mat[T], Pos.x, Pos.y, Pos.z);


	m_onMt = true;
	return 0;
}


int cImgListRender::SetAngle(const D3DXVECTOR3& Axis, float Radian)
{
	D3DXMATRIX Mat;
	D3DXMatrixRotationAxis(&Mat, &Axis, Radian);

	m_Mat[R] *= Mat;

	
	m_onMt = true;
	return 0;
}


int cImgListRender::SetScale(const D3DXVECTOR3& Scale)
{
	D3DXMatrixScaling(&m_Mat[S], Scale.x, Scale.y, Scale.z);

	
	m_onMt = true;
	return 0;
}

/*-------------------------------------------------------------------------------------*/

int cImgListRender::Render(int index)
{
	// 행렬곱
	D3DXMATRIX Mat = m_Mat[S] * m_Mat[R] * m_Mat[T];


	return Draw(index, Mat, m_pTxList);
}


int cImgListRender::RenderBillboard(int index)
{
	// 빌보드 행렬 구함
	/*D3DXMATRIX BillMt;
	D3DXMatrixIdentity(&BillMt);

	D3DXMATRIX View = cCore::Camera.GetView();

	BillMt._11 = View._11;
	BillMt._13 = View._13;
	BillMt._31 = View._31;
	BillMt._33 = View._33;

	D3DXMatrixInverse(&BillMt, NULL, &BillMt);*/


	// 행렬곱
	D3DXMATRIX Mat = m_Mat[S] * cCore::BillboardMt * m_Mat[T];


	return Draw(index, Mat, m_pTxList);
}



int cImgListRender::RenderAlpha(int index)
{
	Util::SetAlphaChannel(TRUE);
	Render(index);
	Util::SetAlphaChannel(FALSE);


	return 0;
}


int cImgListRender::RenderBillboardAlpha(int index)
{
	Util::SetAlphaChannel(TRUE);
	RenderBillboard(index);
	Util::SetAlphaChannel(FALSE);

	return 0;
}



int cImgListRender::MultiRender(int idx1, int idx2, _D3DTEXTUREOP Op, int Stage)
{
	// 텍스쳐 합성
	SetMultiTx(idx1, idx2, Op, Stage);


	if(m_onMt)
	{
		// 행렬곱
		D3DXMATRIX Mat = m_Mat[S] * m_Mat[R] * m_Mat[T];


		// 행렬 적용
		cCore::pd3dDevice->SetTransform(D3DTS_WORLD, &Mat);
	}


	// 그리기
	m_pPlane->Draw();


	// 단위행렬 적용
	D3DXMATRIX IdMat;
	D3DXMatrixIdentity(&IdMat);
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, &IdMat);

	// 텍스쳐 삭제
	cCore::pd3dDevice->SetTexture(Stage, NULL);
	cCore::pd3dDevice->SetTexture(Stage+1, NULL);

	// 회전행렬 초기화
	D3DXMatrixIdentity(&m_Mat[R]);

	
	m_onMt = false;
	return 0;
}


int cImgListRender::SetMultiTx(int idx1, int idx2, _D3DTEXTUREOP Op, int Stage)
{
	// 텍스쳐 합성
	m_pTxList->GetTexture(idx1)->SetMultiTxToDevice(Stage
		, m_pTxList->GetTexture(idx2), Op);


	return Stage+1;
}

/*-------------------------------------------------------------------------------------*/

int cImgListRender::Draw(int index, D3DXMATRIX& Mat, cTextureList* pTxList)
{
	if(m_onMt)
	{
		// 행렬 적용
		cCore::pd3dDevice->SetTransform(D3DTS_WORLD, &Mat);
	}


	// 텍스쳐 적용
	pTxList->GetTexture(index)->SetTextureToDevice(0);


	// 그리기
	m_pPlane->Draw();


	// 단위행렬 적용
	D3DXMATRIX IdMat;
	D3DXMatrixIdentity(&IdMat);
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, &IdMat);

	// 텍스쳐 삭제
	cCore::pd3dDevice->SetTexture(0, NULL);

	// 회전행렬 초기화
	D3DXMatrixIdentity(&m_Mat[R]);

	
	m_onMt = false;
	return 0;
}

