// Interface for the CLcXSkinSrc class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _LcXSkinSrc_H_
#define _LcXSkinSrc_H_

#include "ATTRIB_Enum.h"



class CLcXSkinSrc : public CLcXSkin
{
public:
	// enum for various skinning modes possible
	enum METHOD 
	{
		NONE = 0,
		D3DNONINDEXED	= 1,
	};


protected:
	char						m_sFile[MAX_PATH]	;		// Model FileName
	
	LPDIRECT3DDEVICE9			m_pDevice			;
	SFrame*						m_pFrameRoot		;		// Root
	LPD3DXANIMATIONCONTROLLER	m_pAC				;		// Animation Controller
	
	D3DXVECTOR3					m_ObjectCenter		;	    // Center of bounding sphere of object
	FLOAT						m_ObjectRadius		;		// Radius of bounding sphere of object
	
	INT							m_SkinningMethod	;		// Current skinning method

	UINT						m_NumBoneMatricesMax;		// 행렬 인덱스의 수
	D3DXMATRIX*					m_pBoneMatrices		;		// 행렬의 배열

	
public:
	CLcXSkinSrc();
	virtual ~CLcXSkinSrc();
	
	virtual INT		Create(void* =0, void* =0, void* =0, void* =0);
	virtual void	Destroy();
	virtual INT		FrameMove();
	virtual void	Render();

	virtual const char*	const GetName()const	{	return m_sFile;	}
	virtual ILcMdl* GetOriginal()				{	return this;	}

	virtual INT		SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);
	virtual INT		GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);

public:
	FLOAT	GetRadius();
	D3DXVECTOR3* GetCenter();

	INT		GetMethod();
	void	SetupMethod(INT);

	void*	GetRootFrame();
	void*	GetAnimationController();

	void	UpdateFrameMatrices( SFrame* pFrameBase, D3DXMATRIX* pParentMatrix );
	void	DrawFrame(SFrame* pFrame );
	HRESULT	GenerateSkinnedMesh( SMeshContainer *pMeshContainer );

protected:
	void	DrawMeshContainer(SMeshContainer* pMeshContainerBase, SFrame* pFrameBase );
	void	UpdateSkinningMethod( SFrame* pFrameBase );

	SFrame *FindFrame(char *szName);
	HRESULT FindBones(SFrame *pframeCur);

	void	RenderNonIndexed(SMeshContainer *pMeshContainer);
	void	RenderNonAnimation(SMeshContainer *pMeshContainer, SFrame *pFrame);
};

#endif


