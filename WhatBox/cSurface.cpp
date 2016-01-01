#include "cSurface.h"

#include "cD3DIdxBuffer.h"
#include "cD3DVtxBuffer.h"

#include "Util.h"























cSurface::cSurface()
	: m_pIdxBuffer(NULL)
	, m_pVtxBuffer(NULL)
{

}


cSurface::~cSurface()
{
	SAFE_DELETE(m_pIdxBuffer);
	SAFE_DELETE(m_pVtxBuffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cSurface::Create(float Width, float Height)
{
	// Ÿ�� �迭 ������
	const int nWidth = 1, nHeight = 1;


	// Ÿ�� �ϳ��� ũ��
	D3DXVECTOR2 TileSize(Width/(float)nWidth, Height/(float)nHeight);


	// ������ ���� �� ���
	UINT nVtx = (nWidth+1)*(nHeight+1); // ��������
	sVertex *pVtxData = new sVertex[nVtx];

	// �������� ä���
	D3DXVECTOR3 StartPos(-Width/2.f, Height/2.f, 0.f);
	UINT nIndex = 0U;

	for(int y=0; y<=nHeight; y++)
	{
		for(int x=0; x<=nWidth; x++)
		{
			pVtxData[nIndex].p.x = StartPos.x + (TileSize.x * x);
			pVtxData[nIndex].p.y = StartPos.y - (TileSize.y * y);
			pVtxData[nIndex].p.z = StartPos.z;

			pVtxData[nIndex].d = 0xffffffff; // White

			pVtxData[nIndex].u = float(x)/float(nWidth) * float(nWidth);	//�ؽ��� �ݺ����뿡 ���� �� ���� ������.
			pVtxData[nIndex].v = float(y)/float(nHeight) * float(nHeight);	//�ؽ��� �ݺ����뿡 ���� �� ���� ������.

			nIndex++;
		}
	}
	
	
	// �������� ����
	m_pVtxBuffer = new cD3DVtxBuffer;
	m_pVtxBuffer->Create(sizeof(sVertex), nVtx, sVertex::FVF);

	m_pVtxBuffer->VtxCpy(pVtxData);


	// �ε����� ���� �� ���
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


	// �ε������� ����
	m_pIdxBuffer = new cD3DIdxBuffer;
	m_pIdxBuffer->Create(nWidth*nHeight * 2);

	m_pIdxBuffer->IdxCpy(pIndex);

	
	// �޸� ��ȯ
	SAFE_DELETE_ARR(pVtxData);
	SAFE_DELETE_ARR(pIndex);
	return 0;
}


int cSurface::Draw()
{
	m_pVtxBuffer->SetVtxToDevice();
	m_pIdxBuffer->Draw();


	return 0;
}

