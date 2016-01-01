#include "cSprite.h"

#include "cCore.h"

#include "cTexture.h"
#include "c2DCoord.h"





















cSprite::cSprite()
	: m_pSprite(NULL)
	, m_Color(0xffffffff)
	, m_bWithCamera(false)
{

}


cSprite::~cSprite()
{
	CleanUp();
}

/*------------------------------------------------------------------------------------*/

int cSprite::Create()
{
	if (FAILED(D3DXCreateSprite(cCore::pd3dDevice, &m_pSprite)))
	{
		return Util::ErrorMessage("D3DXCreateSprite()");
	}


	return 0;
}


int cSprite::CleanUp()
{
	SAFE_RELEASE(m_pSprite);


	return 0;
}

/*------------------------------------------------------------------------------------*/

int cSprite::BeginDraw()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	return 0;
}


int cSprite::EndDraw()
{
	m_pSprite->End();


	return 0;
}



int cSprite::SetColor(DWORD Color)
{
	m_Color = Color;


	return 0;
}



const LPD3DXSPRITE cSprite::GetSprite() const
{
	return m_pSprite;
}



void cSprite::OnCamera()
{
	m_bWithCamera = true;
}


void cSprite::OffCamera()
{
	m_bWithCamera = false;
}


bool cSprite::CameraOnCheck() const
{
	return m_bWithCamera;
}

/*------------------------------------------------------------------------------------*/

int cSprite::DrawTexture(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree, const D3DXVECTOR2& Scale,
	const D3DXVECTOR2& Center)
{
	D3DXVECTOR3 center(Center.x, Center.y, 0);
	Draw(pTx, &center, &Pos, &Degree, &Scale);


	return 0;
}


int cSprite::DrawTextureCenter(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree, const D3DXVECTOR2& Scale)
{
	// 이미지의 중앙이 중심
	D3DXVECTOR3 center(static_cast<float>(pTx->Width() >> 1), static_cast<float>(pTx->Height() >> 1), 0.f);
	Draw(pTx, &center, &Pos, &Degree, &Scale);


	return 0;
}


int cSprite::RenderTexture(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree, const D3DXVECTOR2& Scale,
	const D3DXVECTOR2& Center)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// 이미지의 왼쪽위가 중심
	D3DXVECTOR3 center(Center.x, Center.y, 0);
	Draw(pTx, &center, &Pos, &Degree, &Scale);

	m_pSprite->End();


	return 0;
}


int cSprite::RenderTextureCenter(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree, const D3DXVECTOR2& Scale)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// 필요변수
	D3DXVECTOR3 center(static_cast<float>(pTx->Width() >> 1), static_cast<float>(pTx->Height() >> 1), 0.f);
	Draw(pTx, &center, &Pos, &Degree, &Scale);

	m_pSprite->End();


	return 0;
}


int cSprite::Draw(cTexture* pTx, const D3DXVECTOR3* pCenter
	, const D3DXVECTOR2* pPos, float* pDegree, const D3DXVECTOR2* pScale)
{
	// 행렬
	D3DXMATRIX mtWorld;
	D3DXMATRIX mt[3];

	// 변환행렬 계산
	D3DXMatrixScaling(&mt[0], pScale->x, pScale->y, 1.f);
	D3DXMatrixRotationZ(&mt[1], D3DXToRadian(*pDegree));
	D3DXMatrixTranslation(&mt[2], pPos->x, pPos->y, 0.f);

	if (m_bWithCamera)
	{
		mtWorld = mt[0] * mt[1] * mt[2]; //Camera*S*R*T

		const D3DXMATRIX* pCameraMat = cCore::Camera2D.Matrix();

		mtWorld._41 += pCameraMat->_41;
		mtWorld._42 += pCameraMat->_42;
		mtWorld._43 += pCameraMat->_43;
	}
	else
		mtWorld = mt[0] * mt[1] * mt[2]; //S*R*T

	m_pSprite->SetTransform(&mtWorld);		// 변환행렬 적용


	// Draw정보
	RECT rt;
	D3DXVECTOR3 pos(0, 0, 0);
	POINT Size = { pTx->Width(), pTx->Height() };

	// 범위 지정
	SetRect(&rt, 0, 0, Size.x, Size.y);

	// 그린다
	m_pSprite->Draw(pTx->GetTexture(), &rt, pCenter, &pos, m_Color);


	// 월래대로 되돌림
	D3DXMatrixIdentity(&mtWorld);
	m_pSprite->SetTransform(&mtWorld);
	m_Color = 0xffffffff;
	return 0;
}

/*------------------------------------------------------------------------------------*/

int cSprite::DrawTexture(cTexture* pTx)
{
	// 이미지의 왼쪽위가 중심
	D3DXVECTOR3 center(0.f, 0.f, 0.f);
	Draw(pTx, &center);


	return 0;
}


int cSprite::DrawTextureCenter(cTexture* pTx)
{
	// 이미지의 중앙이 중심
	D3DXVECTOR3 center(static_cast<float>(pTx->Width() >> 1), static_cast<float>(pTx->Height() >> 1), 0.f);
	Draw(pTx, &center);


	return 0;
}


int cSprite::RenderTexture(cTexture* pTx)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	// 이미지의 왼쪽위가 중심
	D3DXVECTOR3 center(0.f, 0.f, 0.f);
	Draw(pTx, &center);


	m_pSprite->End();


	return 0;
}


int cSprite::RenderTextureCenter(cTexture* pTx)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	// 이미지의 중앙이 중심
	D3DXVECTOR3 center(static_cast<float>(pTx->Width() >> 1), static_cast<float>(pTx->Height() >> 1), 0.f);
	Draw(pTx, &center);


	m_pSprite->End();


	return 0;
}


int cSprite::Draw(cTexture* pTx, const D3DXVECTOR3* pCenter)
{
	// 행렬
	D3DXMATRIX mtWorld;


	// Draw정보
	RECT rt;
	D3DXVECTOR3 pos(0, 0, 0);
	POINT Size = { pTx->Width(), pTx->Height() };


	// 범위 지정
	SetRect(&rt, 0, 0, Size.x, Size.y);


	// 그린다
	m_pSprite->Draw(pTx->GetTexture(), &rt, pCenter, &pos, m_Color);


	// 월래대로 되돌림
	D3DXMatrixIdentity(&mtWorld);
	m_pSprite->SetTransform(&mtWorld);
	m_Color = 0xffffffff;
	return 0;
}

/*------------------------------------------------------------------------------------*/

int cSprite::DrawTexture(cTexture* pTx, c2DCoord* p2DCoord)
{
	p2DCoord->SetMatrixToSprite();


	DrawTexture(pTx);


	return 0;
}

int cSprite::DrawTextureCenter(cTexture* pTx, c2DCoord* p2DCoord)
{
	p2DCoord->SetMatrixToSprite();


	DrawTextureCenter(pTx);


	return 0;
}


int cSprite::RenderTexture(cTexture* pTx, c2DCoord* p2DCoord)
{
	if (m_bWithCamera)
		p2DCoord->SetMatrixWithCameraToSprite();
	else
		p2DCoord->SetMatrixToSprite();


	RenderTexture(pTx);


	return 0;
}


int cSprite::RenderTextureCenter(cTexture* pTx, c2DCoord* p2DCoord)
{
	if (m_bWithCamera)
		p2DCoord->SetMatrixWithCameraToSprite();
	else
		p2DCoord->SetMatrixToSprite();


	RenderTextureCenter(pTx);


	return 0;
}

