#pragma once
#include <d3dx9.h>


/*

��Ų�� �ִϸ��̼��� ���ؼ� �� �� �ʿ��� ������ �����ϱ� ���ؼ� �޽������̳ʸ� ��ӹ޾� Ȯ���Ų
����ü

*/

















class cD3DMeshContainer : public D3DXMESHCONTAINER
{
public:
	cD3DMeshContainer();
	~cD3DMeshContainer();


public:
	LPDIRECT3DTEXTURE9* ppTextures; // array of textures, entries are NULL if no texture specified
	
	// SkinMesh info
	LPD3DXMESH pOrigMesh; // ���� �޽��� �ӽ� ������ ����.. LPD3DXATTRIBUTERANGE pAttributeTable; // �޽��� �Ӽ� ���̺� ����ü. 
	DWORD NumAttributeGroups; // �Ӽ� ����. 
	DWORD NumInfl; // �� ����̽��� �ִ��� ���� �� �� �ִ� ��Ʈ���� ����
	LPD3DXBUFFER pBoneCombinationBuf;// �� �޺���̼� ����
	D3DXMATRIX** ppBoneMatrixPtrs; // �����ӿ� ����Ǿ��ִ� ��ȯ��Ʈ�������� �迭�� ������. 
	D3DXMATRIX* pBoneOffsetMatrices;// ���� ��ġ�� ��Ƶ� ��Ʈ���� �迭�� ������. 
	DWORD NumPaletteEntries; // ��� �ȷ�Ʈ ��Ʈ��.. NonIndexed���� ������ ����. 
	bool UseSoftwareVP; // ����Ʈ���� ���ؽ� ���μ��� ���? 
	DWORD iAttributeSW; // used to denote the split between SW and HW if necessary for non-indexed skinning
	// ��, Mixed ���� SW�� HW ���ؽ� ���μ����� ����� �� ������ ���� ������ �����ϱ� ���� ����. 
};

