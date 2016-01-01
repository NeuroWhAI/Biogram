#include "cTopography.h"

#include "cCore.h"
#include "D3D/dxutil.h"

#include "cTexture.h"
#include "cD3DVtxBuffer.h"
#include "cD3DIdxBuffer.h"

#include <fstream>
using namespace std;













cTopography::cTopography()
	: m_pVertex(NULL)
	, m_TxFile(NULL)

	, m_pVtxBuffer(NULL)
	, m_pIdxBuffer(NULL)
	, m_pTexture(NULL)
{

}


cTopography::~cTopography()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pVtxBuffer);
	SAFE_DELETE(m_pIdxBuffer);


	delete[] m_HeightList;

	delete[] m_pVertex;

	delete[] m_RawFile;
	delete[] m_TxFile;
}

/*-------------------------------------------------------------------------------------------*/

int cTopography::Create(int nRow, int nCol, float Size
						, char* TxFile, char* RawFile)
{
	m_nRow = nRow;
	m_nCol = nCol;

	m_Size = Size;

	if(TxFile != NULL)
	{
		m_TxFile = new char[strlen(TxFile)+1];
		strcpy_s(m_TxFile, strlen(TxFile)+1, TxFile);
	}
	if(RawFile != NULL)
	{
		m_RawFile = new char[strlen(RawFile)+1];
		strcpy_s(m_RawFile, strlen(RawFile)+1, RawFile);
	}
	
	/*---------------------------------*/

	m_nVertices = (m_nCol + 1) * (m_nRow + 1);		//정점갯수 계산

	m_HeightList = new float[m_nVertices];			//높이리스트 생성
	for(DWORD n=0; n<m_nVertices; n++)
		m_HeightList[n] = 0.0f;

	m_nIndices = m_nCol * m_nRow * 6;

	/*---------------------------------*/

	//Raw파일이 있으면 읽어서 높이값으로 씀.
	if(RawFile != NULL)
	{
		FILE* fp = fopen(m_RawFile, "rb"); 
		fseek(fp, 0, SEEK_END); 
		long lSize = ftell(fp); 

		fseek(fp, 0, SEEK_SET); 
		BYTE* pH = new BYTE[lSize]; 

		fread(pH, lSize, 1, fp); 
		fclose(fp); 

		for(DWORD i=0; i<m_nVertices; i++)
		{
			m_HeightList[i] = pH[i];
		}

		delete [] pH;
	}


	if(m_pTexture == NULL)
	{
		m_pTexture = new cTexture;
		m_pTexture->LoadTexture(m_TxFile);
	}


	if(m_pVertex == NULL)
		m_pVertex = new GroundVertex[m_nVertices];


	int nIndex = 0;
	D3DXVECTOR3 StartPos( 0.0f, 0.0f
		, 0.0f);		//정점생성의 시작 위치 계산

	//정점정보 채우기
	for(int z=0; z<=m_nRow; z++)
	{
		for(int x=0; x<=m_nCol; x++)
		{
			m_pVertex[nIndex].Pos.x = StartPos.x + (m_Size * x);
			m_pVertex[nIndex].Pos.y = m_HeightList[nIndex]/4.f;
			m_pVertex[nIndex].Pos.z = StartPos.z - (m_Size * z);

			FLOAT h = m_HeightList[nIndex];
			DWORD d = D3DCOLOR_XRGB(255, 255, 255); 
			if(h < 1.0f) d = D3DCOLOR_XRGB(255, 249, 157); 
			else if(h < 45.0f) d = D3DCOLOR_XRGB(124, 197, 118); 
			else if(h < 85.5f) d = D3DCOLOR_XRGB(0, 166, 81); 
			else if(h < 120.0f) d = D3DCOLOR_XRGB(25, 123, 48); 
			else if(h < 170.5f) d = D3DCOLOR_XRGB(115, 100, 87);
			m_pVertex[nIndex].Diffuse = d; /* 모래, 풀밭, 숲, 암석, 눈 */

			m_pVertex[nIndex].u = float(x)/m_nCol * 16.0f; //16.0f는 텍스쳐 반복적용에 대한 셀 범위 조정용.
			m_pVertex[nIndex].v = float(z)/m_nRow * 16.0f; //16.0f는 텍스쳐 반복적용에 대한 셀 범위 조정용.

			nIndex++;
		}
	}


	//버텍스 버퍼 생성
	m_pVtxBuffer = new cD3DVtxBuffer;
	m_pVtxBuffer->Create(sizeof(GroundVertex), m_nVertices, GroundVertex::FVF);


	//버퍼 씌우기
	m_pVtxBuffer->VtxCpy(m_pVertex);

	/*---------------------------------*/

	//정점들 위치 계산
	WORD* pIndex = new WORD[m_nIndices];
	nIndex = 0;

	for(int z=0; z<m_nRow; z++)
	{
		for(int x=0; x<m_nCol; x++)
		{
			pIndex[nIndex++] = WORD( z*(m_nCol+1) + x );
			pIndex[nIndex++] = WORD( (z+1) * (m_nCol+1) + x + 1 );
			pIndex[nIndex++] = WORD( (z+1) * (m_nCol+1) + x );

			pIndex[nIndex++] = WORD( z * (m_nCol+1) + x );
			pIndex[nIndex++] = WORD( z * (m_nCol+1) + x + 1 );
			pIndex[nIndex++] = WORD( (z+1) * (m_nCol+1) + x + 1 );
		}
	}

	
	//인덱스 버퍼 생성
	m_pIdxBuffer = new cD3DIdxBuffer;
	m_pIdxBuffer->Create(nRow*nCol*2);

	m_pIdxBuffer->IdxCpy(pIndex);

	/*---------------------------------*/

	delete[] pIndex;


	return 0;
}



int cTopography::Render()
{
	if(m_pTexture != NULL)
	{
		m_pTexture->SetTextureToDevice(0);
	}


	Util::TempRenderState SetRenderState1(D3DRS_LIGHTING, FALSE);
	Util::TempRenderState SetRenderState2(D3DRS_CULLMODE, D3DCULL_NONE);

	
	m_pVtxBuffer->SetVtxToDevice();
	m_pIdxBuffer->Draw();


	return 0;
}


int cTopography::RenderWireframe()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( &matWorld );

	Util::TempRenderState SetRenderState1(D3DRS_LIGHTING, FALSE);
	Util::TempRenderState SetRenderState2(D3DRS_CULLMODE, D3DCULL_NONE);


	m_pVtxBuffer->SetVtxToDevice();
	m_pIdxBuffer->Draw();


	return 0;
}



int cTopography::Restore()
{
	Create(m_nRow, m_nCol, m_Size, m_TxFile, m_RawFile);


	return 0;
}


int cTopography::Release()
{
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pVtxBuffer);
	SAFE_DELETE(m_pIdxBuffer);


	return 0;
}


float cTopography::GetHeight(float x, float z)
{
	int X = static_cast<int>(x/m_Size);
	int Z = -static_cast<int>(z/m_Size);


	DWORD Num = Z*(m_nCol+1) + X;

	if(Num >= m_nVertices)
		return 0.f;


	INT _0 =  Z   *(m_nCol+1) + X  ; 
	INT _1 = (Z+1)*(m_nCol+1) + X  ; 
	INT _2 =  Z   *(m_nCol+1) + X+1; 
	INT _3 = (Z+1)*(m_nCol+1) + X+1; 

	D3DXVECTOR3 v0 = m_pVertex[_0].Pos;
	D3DXVECTOR3 v1 = m_pVertex[_1].Pos;
	D3DXVECTOR3 v2 = m_pVertex[_2].Pos;
	D3DXVECTOR3 v3 = m_pVertex[_3].Pos;	FLOAT deltaX = (x - v0.x)/m_Size; 
	FLOAT deltaZ = (z - v0.z)/m_Size; 

	D3DXVECTOR3 vcOut; 

	// 아래쪽 삼각형 
	if( (deltaX+deltaZ) <=1) 
		vcOut = v0 + (v2- v0) * deltaX + (v1- v0) * deltaZ; 

	// 위쪽 삼각형 
	else 
	{ 
		deltaX = 1 - deltaX; 
		deltaZ = 1 - deltaZ; 
		vcOut = v3 + (v2- v3) * deltaX + (v1- v3) * deltaZ; 
	} 


	return vcOut.y;
}



int cTopography::NumVertices() const
{
	return m_nVertices;
}

