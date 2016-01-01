#pragma once
#include <d3dx9.h>
#include <string>

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �޽�
// Desc : X������ �ҷ��ͼ� �޽��� �����.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cMesh
{
public:
	cMesh();
	~cMesh();


private:
	std::string m_FileName;

	ID3DXMesh* m_pMsh;				// �Ž� ������
	D3DMATERIAL9* m_pMtl;			// ���׸��� �����͵�
	LPDIRECT3DTEXTURE9* m_pTex;		// �ؽ��� �����͵�
	DWORD m_nMtl;					// ����


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

