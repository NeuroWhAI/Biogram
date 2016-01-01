#include "cPlane.h"

#include "cD3DIdxBuffer.h"
#include "cD3DVtxBuffer.h"
#include "Util.h"



















cPlane::cPlane()
	: m_pIdxBuffer(NULL)
	, m_pVtxBuffer(NULL)
{

}


cPlane::~cPlane()
{
	Release();
}

/*-----------------------------------------------------------------------------------*/

int cPlane::Create(float X, float Z, float Width, float Height, int nWidth, int nHeight
				   , bool isUp, bool isCenter)
{
	// 타일 하나당 크기
	D3DXVECTOR2 TileSize(Width/(float)nWidth, Height/(float)nHeight);


	// 정점값 생성 및 계산
	UINT nVtx = (nWidth+1)*(nHeight+1); // 정점갯수
	sVertex *pVtxData = new sVertex[nVtx];

	// 정점정보 채우기
	Z += Height;

	UINT nIndex = 0U;
	for(int z=0; z<=nHeight; z++)
	{
		for(int x=0; x<=nWidth; x++)
		{
			pVtxData[nIndex].p.x = X + (TileSize.x * x);
			if(isCenter)
				pVtxData[nIndex].p.x -= Width/2.f;


			if(isUp)
			{
				pVtxData[nIndex].p.y = Z - (TileSize.y * z);
				pVtxData[nIndex].p.z = 0.f;

				if(isCenter)
					pVtxData[nIndex].p.y -= Height/2.f;
			}
			else
			{
				pVtxData[nIndex].p.y = 0.f;
				pVtxData[nIndex].p.z = Z - (TileSize.y * z);

				if(isCenter)
					pVtxData[nIndex].p.z -= Height/2.f;
			}

			pVtxData[nIndex].d = 0xffffffff;

			pVtxData[nIndex].u = float(x)/nWidth * nWidth; //텍스쳐 반복적용에 대한 셀 범위 조정용.
			pVtxData[nIndex].v = float(z)/nHeight * nHeight; //텍스쳐 반복적용에 대한 셀 범위 조정용.

			nIndex++;
		}
	}


	// 정점버퍼 생성
	m_pVtxBuffer = new cD3DVtxBuffer;
	m_pVtxBuffer->Create(sizeof(sVertex), nVtx, sVertex::FVF);

	m_pVtxBuffer->VtxCpy(pVtxData);


	// 인덱스값 생성 및 계산
	UINT nIdx = nWidth*nHeight*6;
	WORD *pIndex = new WORD[nIdx];

	nIndex = 0U;
	for(int z=0; z<nHeight; z++)
	{
		for(int x=0; x<nWidth; x++)
		{
			pIndex[nIndex++] = WORD( z*(nWidth+1) + x );
			pIndex[nIndex++] = WORD( (z+1) * (nWidth+1) + x + 1 );
			pIndex[nIndex++] = WORD( (z+1) * (nWidth+1) + x );

			pIndex[nIndex++] = WORD( z * (nWidth+1) + x );
			pIndex[nIndex++] = WORD( z * (nWidth+1) + x + 1 );
			pIndex[nIndex++] = WORD( (z+1) * (nWidth+1) + x + 1 );
		}
	}


	// 인덱스버퍼 생성
	m_pIdxBuffer = new cD3DIdxBuffer;
	m_pIdxBuffer->Create(nWidth*nHeight * 2);

	m_pIdxBuffer->IdxCpy(pIndex);

	
	// 메모리 반환
	SAFE_DELETE_ARR(pVtxData);
	SAFE_DELETE_ARR(pIndex);
	return 0;
}


int cPlane::Release()
{
	OnRelease();


	SAFE_DELETE(m_pIdxBuffer);
	SAFE_DELETE(m_pVtxBuffer);
	

	return 0;
}


int cPlane::Draw()
{
	Util::TempRenderState SetRenderState1(D3DRS_LIGHTING, FALSE);
	Util::TempRenderState SetRenderState2(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pVtxBuffer->SetVtxToDevice();
	m_pIdxBuffer->Draw();


	return 0;
}


int cPlane::DrawWireFrame()
{
	Util::TempRenderState SetRenderState1(D3DRS_LIGHTING, FALSE);
	Util::TempRenderState SetRenderState2(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pVtxBuffer->SetVtxToDevice();
	m_pIdxBuffer->Draw();


	return 0;
}

/*-----------------------------------------------------------------------------------*/

int cPlane::OnRelease()
{
	


	return 0;
}

