#pragma once
#include <d3dx9.h>


/*

스킨드 애니메이션을 위해서 좀 더 필요한 정보를 저장하기 위해서 메시컨테이너를 상속받아 확장시킨
구조체

*/

















class cD3DMeshContainer : public D3DXMESHCONTAINER
{
public:
	cD3DMeshContainer();
	~cD3DMeshContainer();


public:
	LPDIRECT3DTEXTURE9* ppTextures; // array of textures, entries are NULL if no texture specified
	
	// SkinMesh info
	LPD3DXMESH pOrigMesh; // 원래 메시의 임시 저장을 위한.. LPD3DXATTRIBUTERANGE pAttributeTable; // 메시의 속성 테이블 구조체. 
	DWORD NumAttributeGroups; // 속성 갯수. 
	DWORD NumInfl; // 이 디바이스가 최대한 블랜딩 할 수 있는 매트릭스 갯수
	LPD3DXBUFFER pBoneCombinationBuf;// 본 콤비네이션 버퍼
	D3DXMATRIX** ppBoneMatrixPtrs; // 프레임에 저장되어있는 변환매트릭스들의 배열의 포인터. 
	D3DXMATRIX* pBoneOffsetMatrices;// 본의 위치를 담아둘 매트릭스 배열의 포인터. 
	DWORD NumPaletteEntries; // 행렬 팔렛트 엔트리.. NonIndexed에선 사용되지 않음. 
	bool UseSoftwareVP; // 소프트웨어 버텍스 프로세싱 사용? 
	DWORD iAttributeSW; // used to denote the split between SW and HW if necessary for non-indexed skinning
	// 즉, Mixed 에서 SW와 HW 버텍스 프로세싱을 사용할 때 나누기 위한 정보를 저장하기 위한 변수. 
};

