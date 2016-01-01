#pragma once
#include <d3dx9.h>

class cTexture;
class c2DCoord;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D스프라이트
// Desc : 텍스쳐를 2D로 출력해준다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSprite
{
public:
	cSprite();
	~cSprite();


private:
	LPD3DXSPRITE m_pSprite;
	DWORD m_Color;
	bool m_bWithCamera;						// 2D카메라 행렬 적용 여부


public:
	int Create();
	int CleanUp();


public:
	int BeginDraw();
	int EndDraw();

	int SetColor(DWORD Color);

	const LPD3DXSPRITE GetSprite() const;

	void OnCamera();							// 카메라행렬 적용
	void OffCamera();							// 카메라행렬 적용 해제
	bool CameraOnCheck() const;


public:
	int DrawTexture(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree = 0.f
		, const D3DXVECTOR2& Scale = D3DXVECTOR2(1.f, 1.f)
		, const D3DXVECTOR2& Center = D3DXVECTOR2(0.f, 0.f));
	int DrawTextureCenter(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree = 0.f
		, const D3DXVECTOR2& Scale = D3DXVECTOR2(1.f, 1.f));

	int RenderTexture(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree = 0.f
		, const D3DXVECTOR2& Scale = D3DXVECTOR2(1.f, 1.f)
		, const D3DXVECTOR2& Center = D3DXVECTOR2(0.f, 0.f));
	int RenderTextureCenter(cTexture* pTx, const D3DXVECTOR2& Pos, float Degree = 0.f
		, const D3DXVECTOR2& Scale = D3DXVECTOR2(1.f, 1.f));

private:
	int Draw(cTexture* pTx, const D3DXVECTOR3* pCenter
		, const D3DXVECTOR2* pPos, float* pDegree, const D3DXVECTOR2* pScale);


public:
	int DrawTexture(cTexture* pTx);
	int DrawTextureCenter(cTexture* pTx);

	int RenderTexture(cTexture* pTx);
	int RenderTextureCenter(cTexture* pTx);

private:
	int Draw(cTexture* pTx, const D3DXVECTOR3* pCenter);


public:
	int DrawTexture(cTexture* pTx, c2DCoord* p2DCoord);
	int DrawTextureCenter(cTexture* pTx, c2DCoord* p2DCoord);

	int RenderTexture(cTexture* pTx, c2DCoord* p2DCoord);
	int RenderTextureCenter(cTexture* pTx, c2DCoord* p2DCoord);
};

