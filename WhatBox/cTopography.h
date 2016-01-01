#pragma once
#include <d3dx9.h>

class cTexture;
class cD3DVtxBuffer;
class cD3DIdxBuffer;











class cTopography
{
public:
	cTopography();
	~cTopography();


private:
	struct GroundVertex
	{
		D3DXVECTOR3 Pos;
		DWORD Diffuse;
		FLOAT u, v;

		enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1};
	};
	GroundVertex* m_pVertex;


private:
	int m_nRow, m_nCol; //z-x평면임.
	float m_Size;

	DWORD m_nVertices;
	DWORD m_nIndices;

	cD3DVtxBuffer* m_pVtxBuffer;
	cD3DIdxBuffer* m_pIdxBuffer;


private:
	float* m_HeightList;
	char* m_RawFile;


private:
	cTexture* m_pTexture;
	char* m_TxFile;


public:
	int Create(int nRow, int nCol, float Size
		, char* TxFile=NULL, char* RawFile=NULL);

	int Render();
	int RenderWireframe();

	int Restore();	//화면 복구 전용
	int Release();	//화면 복구 전용


public:
	float GetHeight(float x, float z);


public:
	int NumVertices() const;
};

