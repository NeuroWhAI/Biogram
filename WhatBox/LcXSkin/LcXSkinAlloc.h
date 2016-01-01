// Interface for the CLcXSkinAlloc class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _LcXSkinAlloc_H_
#define _LcXSkinAlloc_H_


// Name: struct SMeshContainer
// Desc: Structure derived from D3DXMESHCONTAINER so we can add some app-specific
//       info that will be stored with each mesh

struct SMeshContainer //: D3DXMESHCONTAINER
{
	LPSTR                   Name;
	
	D3DXMESHDATA            MeshData;
	
	LPD3DXMATERIAL          pMaterials;
	LPD3DXEFFECTINSTANCE    pEffects;
	DWORD                   NumMaterials;
	DWORD                  *pAdjacency;
	
	LPD3DXSKININFO          pSkinInfo;
	
	SMeshContainer*			pNextMeshContainer;
	
	
	LPDIRECT3DTEXTURE9*		ppTextures;       // array of textures, entries are NULL if no texture specified    
	
	// SkinMesh info             
	LPD3DXMESH           pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD                NumAttributeGroups; 
	DWORD                NumInfl;
	LPD3DXBUFFER         pBoneCombinationBuf;
	D3DXMATRIX**         m_pBoneMatrix;
	D3DXMATRIX*          pBoneOffsetMatrices;
	DWORD                NumPaletteEntries;
	bool                 UseSoftwareVP;
	DWORD                iAttributeSW;     // used to denote the split between SW and HW if necessary for non-indexed skinning

	SMeshContainer()
	{
		Name		= NULL;
		pAdjacency	= NULL;
		pMaterials	= NULL;
		pBoneOffsetMatrices	= NULL;
		ppTextures		 	= NULL;
		pAttributeTable		= NULL;;
		ppTextures			= NULL;
		m_pBoneMatrix		= NULL;
		pBoneCombinationBuf	= NULL;
		MeshData.pMesh		= NULL;
		pSkinInfo			= NULL;
		pOrigMesh			= NULL;
	}
};



// Name: struct SFrame
// Desc: Structure derived from D3DXFRAME so we can add some app-specific
//       info that will be stored with each frame

struct SFrame	//: public D3DXFRAME
{
	//LPSTR                   Name;
	char*			szName;
	D3DXMATRIX		tmMatrix;
	
	SMeshContainer*	pmcMesh;
	
	SFrame*			pFrameSibling;
	SFrame*			pFrameFirstChild;
	
	D3DXMATRIX		tmWorld;
	SFrame *FindFrame(char *szFrame);
};



class CLcXSkinAlloc: public ID3DXAllocateHierarchy
{
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	
	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);
	
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase);
	
	
public:
	CLcXSkinAlloc(ILcMdl *pSrc) :m_pSrc(pSrc) {}
	HRESULT AllocateName( LPCSTR Name, LPSTR *pNewName );

protected:
	ILcMdl* m_pSrc;
};


#endif


