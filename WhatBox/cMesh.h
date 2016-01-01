#pragma once
#include <d3dx9.h>
#include <string>

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 메쉬
// Desc : X파일을 불러와서 메쉬를 만든다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cMesh
{
public:
	cMesh();
	~cMesh();


private:
	std::string m_FileName;

	ID3DXMesh* m_pMsh;				// 매쉬 데이터
	D3DMATERIAL9* m_pMtl;			// 메테리얼 데이터들
	LPDIRECT3DTEXTURE9* m_pTex;		// 텍스쳐 데이터들
	DWORD m_nMtl;					// 갯수


public:
	int LoadXFile(std::string File);

	int Release();
	int Restore();

	int Render();


public:
	DWORD MtlNum() const;

	LPD3DXMESH GetMesh();
	const LPD3DXMESH GetMesh() const;

	D3DMATERIAL9* GetMtl(DWORD index);
	const D3DMATERIAL9* GetMtl(DWORD index) const;

	LPDIRECT3DTEXTURE9* GetTex(DWORD index);
	const LPDIRECT3DTEXTURE9* GetTex(DWORD index) const;
};

