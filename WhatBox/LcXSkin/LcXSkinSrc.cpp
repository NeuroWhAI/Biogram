// Implementation of the LcXSkinSrc class.
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning(disable: 4996)

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <D3D9.h>
#include <d3dx9.h>

#include "ILcMdl.h"
#include "LcXSkinAlloc.h"
#include "LcXSkin.h"
#include "LcXSkinSrc.h"

#include "dxutil.h"



#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }











CLcXSkinSrc::CLcXSkinSrc()
{
	m_pDevice			= NULL;
	m_pFrameRoot		= NULL;
	m_pAC				= NULL;
	
	m_SkinningMethod	= D3DNONINDEXED;   // Current skinning method
	m_pBoneMatrices		= NULL;
	m_NumBoneMatricesMax= 0;


	D3DXMatrixIdentity(&m_mtWorld);
	m_dTimeCur	= 0;
}


CLcXSkinSrc::~CLcXSkinSrc()
{
	Destroy();
}



D3DXVECTOR3* CLcXSkinSrc::GetCenter()
{
	return &m_ObjectCenter;
}


INT CLcXSkinSrc::GetMethod()
{
	return m_SkinningMethod;
}



void CLcXSkinSrc::SetupMethod(INT v)
{
	m_SkinningMethod = v;
	
	// update the meshes to the new skinning method
	UpdateSkinningMethod(m_pFrameRoot);
}


FLOAT CLcXSkinSrc::GetRadius()
{
	return m_ObjectRadius;
}



void* CLcXSkinSrc::GetRootFrame()
{
	return m_pFrameRoot;
}


void* CLcXSkinSrc::GetAnimationController()
{
	return m_pAC;
}

// Name: GenerateSkinnedMesh()
// Desc: Called either by CreateMeshContainer when loading a skin mesh, or when 
//       changing methods.  This function uses the pSkinInfo of the mesh 
//       container to generate the desired drawable mesh and bone combination 
//       table.

HRESULT CLcXSkinSrc::GenerateSkinnedMesh(SMeshContainer *pMeshContainer)
{
	HRESULT hr = S_OK;
	
	D3DCAPS9	devCaps;
	m_pDevice->GetDeviceCaps(&devCaps);
	
	if (pMeshContainer->pSkinInfo == NULL)
		return hr;
	
	SAFE_RELEASE( pMeshContainer->MeshData.pMesh );
	SAFE_RELEASE( pMeshContainer->pBoneCombinationBuf );
	
	// if non-indexed skinning mode selected, use ConvertToBlendedMesh to generate drawable mesh
	if (m_SkinningMethod == D3DNONINDEXED)
	{
		
		hr = pMeshContainer->pSkinInfo->ConvertToBlendedMesh
			(
			pMeshContainer->pOrigMesh,
			D3DXMESH_MANAGED|D3DXMESHOPT_VERTEXCACHE, 
			pMeshContainer->pAdjacency, 
			NULL, NULL, NULL, 
			&pMeshContainer->NumInfl,
			&pMeshContainer->NumAttributeGroups, 
			&pMeshContainer->pBoneCombinationBuf, 
			&pMeshContainer->MeshData.pMesh
			);
		if (FAILED(hr))
			goto e_Exit;
		
		
			/* If the device can only do 2 matrix blends, ConvertToBlendedMesh cannot approximate all meshes to it
			Thus we split the mesh in two parts: The part that uses at most 2 matrices and the rest. The first is
		drawn using the device's HW vertex processing and the rest is drawn using SW vertex processing. */
		LPD3DXBONECOMBINATION rgBoneCombinations  = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
		
		// look for any set of bone combinations that do not fit the caps
		for (pMeshContainer->iAttributeSW = 0; pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups; pMeshContainer->iAttributeSW++)
		{
			DWORD cInfl   = 0;
			
			for (DWORD iInfl = 0; iInfl < pMeshContainer->NumInfl; iInfl++)
			{
				if (rgBoneCombinations[pMeshContainer->iAttributeSW].BoneId[iInfl] != UINT_MAX)
				{
					++cInfl;
				}
			}
			
			if (cInfl > devCaps.MaxVertexBlendMatrices)
			{
				break;
			}
		}
		
		// if there is both HW and SW, add the Software Processing flag
		if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
		{
			LPD3DXMESH pMeshTmp;
			
			hr = pMeshContainer->MeshData.pMesh->CloneMeshFVF(D3DXMESH_SOFTWAREPROCESSING|pMeshContainer->MeshData.pMesh->GetOptions(), 
				pMeshContainer->MeshData.pMesh->GetFVF(),
				m_pDevice, &pMeshTmp);
			if (FAILED(hr))
			{
				goto e_Exit;
			}
			
			pMeshContainer->MeshData.pMesh->Release();
			pMeshContainer->MeshData.pMesh = pMeshTmp;
			pMeshTmp = NULL;
		}
	}


	else  // invalid m_SkinningMethod value
	{        
		// return failure due to invalid skinning method value
		hr = E_INVALIDARG;
		goto e_Exit;
	}
	
e_Exit:
	return hr;
}



// Name: DrawMeshContainer()
// Desc: Called to render a mesh in the hierarchy

void CLcXSkinSrc::DrawMeshContainer(SMeshContainer* pMeshContainerBase, SFrame* pFrameBase)
{
	SMeshContainer *pMeshContainer = (SMeshContainer*)pMeshContainerBase;
	SFrame *pFrame = (SFrame*)pFrameBase;
	
	if (pMeshContainer->pSkinInfo)
	{
		if (m_SkinningMethod == D3DNONINDEXED)
			RenderNonIndexed(pMeshContainer);
		
		return;
	}
	
	RenderNonAnimation(pMeshContainer, pFrame);
}



// Name: DrawFrame()
// Desc: Called to render a frame in the hierarchy

void CLcXSkinSrc::DrawFrame(SFrame* pFrame)
{
	SMeshContainer* pMeshContainer;
	
	pMeshContainer = pFrame->pmcMesh;
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(pMeshContainer, pFrame);
		
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}
	
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}





// Name: UpdateFrameMatrices()
// Desc: update the frame matrices

void CLcXSkinSrc::UpdateFrameMatrices(SFrame* pFrameBase, D3DXMATRIX* pParentMatrix)
{
	SFrame *pFrame = (SFrame*)pFrameBase;
	
	if (pParentMatrix != NULL)
		D3DXMatrixMultiply(&pFrame->tmWorld, &pFrame->tmMatrix, pParentMatrix);
	else
		pFrame->tmWorld = pFrame->tmMatrix;
	
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrame->pFrameFirstChild, &pFrame->tmWorld);
	}
}


// Name: UpdateSkinningMethod()
// Desc: update the skinning method

void CLcXSkinSrc::UpdateSkinningMethod(SFrame* pFrameBase)
{
	SFrame *pFrame = (SFrame*)pFrameBase;
	SMeshContainer *pMeshContainer;
	
	pMeshContainer = (SMeshContainer *)pFrame->pmcMesh;
	
	while (pMeshContainer != NULL)
	{
		GenerateSkinnedMesh(pMeshContainer);
		
		pMeshContainer = (SMeshContainer *)pMeshContainer->pNextMeshContainer;
	}
	
	if (pFrame->pFrameSibling != NULL)
	{
		UpdateSkinningMethod(pFrame->pFrameSibling);
	}
	
	if (pFrame->pFrameFirstChild != NULL)
	{
		UpdateSkinningMethod(pFrame->pFrameFirstChild);
	}
}



INT CLcXSkinSrc::Create(void* p1, void* p2, void*, void* )
{
	HRESULT				hr;
	CLcXSkinAlloc		Alloc(this);

	char* sFile			= NULL;
	
	m_pDevice	= (LPDIRECT3DDEVICE9)p1;
	sFile		= (char*)p2;

	::strcpy(m_sFile, sFile);
	

	WCHAR* wFile = new WCHAR[strlen(m_sFile)+1];
	DXUtil_ConvertAnsiStringToWideCch(wFile, m_sFile, strlen(m_sFile)+1);

	hr = D3DXLoadMeshHierarchyFromX(wFile
								, D3DXMESH_MANAGED
								, m_pDevice
								, &Alloc
								, NULL
								, (LPD3DXFRAME*)&m_pFrameRoot
								, &m_pAC);
	delete[] wFile;

	if (FAILED(hr))
		return hr;
	
	
	hr = FindBones(m_pFrameRoot);
	if (FAILED(hr))
		return hr;
	
	hr = D3DXFrameCalculateBoundingSphere((const D3DXFRAME*)m_pFrameRoot, &m_ObjectCenter, &m_ObjectRadius);
	if (FAILED(hr))
		return hr;
	
	
	return S_OK;
}



void CLcXSkinSrc::Destroy()
{
	if(!m_pFrameRoot)
		return;

	CLcXSkinAlloc Alloc(this);
	
	D3DXFrameDestroy((LPD3DXFRAME)m_pFrameRoot, &Alloc);
	
	SAFE_RELEASE(	m_pAC		);
	

	SAFE_DELETE_ARRAY(	m_pBoneMatrices	);


	m_pFrameRoot = NULL;
}



INT CLcXSkinSrc::FrameMove()
{
	return 0;
}



void CLcXSkinSrc::Render()
{
	if(m_pAC)
	{
		m_pAC->SetTrackPosition(0, 0);
		m_pAC->AdvanceTime(m_dTimeCur, NULL);
	}

	UpdateFrameMatrices(m_pFrameRoot, &m_mtWorld);
	DrawFrame(m_pFrameRoot);
}


INT CLcXSkinSrc::SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)
{
	if(attrib == SknMeshNameSpace::ATTRIB_Method)
 	{
		INT nMethod =*((INT*)pVal);
 		SetupMethod(nMethod);
 		return 0;
 	}

	return CLcXSkin::SetAttrib(attrib, pVal);
}

INT CLcXSkinSrc::GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)
{
	if(attrib == SknMeshNameSpace::ATTRIB_Radius)
 	{
 		*((FLOAT*)pVal) = m_ObjectRadius;
 		return 0;
 	}
	else if(attrib == SknMeshNameSpace::ATTRIB_Center)
 	{
 		*((D3DXVECTOR3*)pVal) = m_ObjectCenter;
 		return 0;
 	}

	else if(attrib == SknMeshNameSpace::ATTRIB_Method)
 	{
 		*((INT*)pVal) = GetMethod();
 		return 0;
 	}

	return CLcXSkin::GetAttrib(attrib, pVal);
}





void CLcXSkinSrc::RenderNonIndexed(SMeshContainer* pMeshContainer)
{
	UINT NumBlend;
	DWORD AttribIdPrev;
	
	LPD3DXBONECOMBINATION pBoneComb;
	UINT iAttrib;
	UINT iMatrixIndex;
	D3DXMATRIX matTemp;

	D3DCAPS9	devCaps;
	m_pDevice->GetDeviceCaps(&devCaps);
	
	//케릭터 뜯어짐 방지
	m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
	m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
	m_pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);

	AttribIdPrev = UNUSED32; 
	pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
	
	// Draw using default vtx processing of the device (typically HW)
	for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
	{
		NumBlend = 0;
		for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
		{
			if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
			{
				NumBlend = i;
			}
		}
		
		if (devCaps.MaxVertexBlendMatrices >= NumBlend + 1)
		{
			// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
			for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
			{
				iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
				if (iMatrixIndex != UINT_MAX)
				{
					D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->m_pBoneMatrix[iMatrixIndex] );
					m_pDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
				}
			}
			
			m_pDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);
			
			// lookup the material used for this subset of faces
			if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
			{
				m_pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
				m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 확대 필터
				m_pDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
				AttribIdPrev = pBoneComb[iAttrib].AttribId;
			}
			
			// draw the subset now that the correct material and matrices are loaded
			pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
		}
	}
	
	// If necessary, draw parts that HW could not handle using SW
	if (pMeshContainer->iAttributeSW < pMeshContainer->NumAttributeGroups)
	{
		AttribIdPrev = UNUSED32; 
		m_pDevice->SetSoftwareVertexProcessing(TRUE);
		for (iAttrib = pMeshContainer->iAttributeSW; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
		{
			NumBlend = 0;
			for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
			{
				if (pBoneComb[iAttrib].BoneId[i] != UINT_MAX)
				{
					NumBlend = i;
				}
			}
			
			if (devCaps.MaxVertexBlendMatrices < NumBlend + 1)
			{
				// first calculate the world matrices for the current set of blend weights and get the accurate count of the number of blends
				for (DWORD i = 0; i < pMeshContainer->NumInfl; ++i)
				{
					iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply( &matTemp, &pMeshContainer->pBoneOffsetMatrices[iMatrixIndex], pMeshContainer->m_pBoneMatrix[iMatrixIndex] );
						m_pDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTemp );
					}
				}
				
				m_pDevice->SetRenderState(D3DRS_VERTEXBLEND, NumBlend);
				
				// lookup the material used for this subset of faces
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					m_pDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
					m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 확대 필터
					m_pDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}
				
				// draw the subset now that the correct material and matrices are loaded
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}
		m_pDevice->SetSoftwareVertexProcessing(FALSE);
	}
	
	m_pDevice->SetRenderState(D3DRS_VERTEXBLEND, 0);
}






void CLcXSkinSrc::RenderNonAnimation(SMeshContainer *pMeshContainer, SFrame *pFrame)
{
	UINT iMaterial;
	
	m_pDevice->SetTransform(D3DTS_WORLD, &pFrame->tmWorld);
	
	for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
	{
		m_pDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );
		m_pDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );
		pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
	}



	m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
	m_pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);

	m_pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
}



SFrame* CLcXSkinSrc::FindFrame(char *szName)
{
    if (m_pFrameRoot == NULL)
        return NULL;

	return m_pFrameRoot->FindFrame(szName);
}



HRESULT CLcXSkinSrc::FindBones(SFrame *pframeCur)
{
	HRESULT hr = S_OK;
	SMeshContainer *pmcMesh;
	SFrame *pframeChild;

	pmcMesh = pframeCur->pmcMesh;
	while (pmcMesh != NULL)
	{
		if (pmcMesh->pSkinInfo)
		{
			for (DWORD i = 0; i < pmcMesh->pSkinInfo->GetNumBones(); ++i)
			{
				SFrame* pFrame = FindFrame((char*)pmcMesh->pSkinInfo->GetBoneName(i));
				
				
				if(pFrame)
					pmcMesh->m_pBoneMatrix[i] = &(pFrame->tmWorld);
			}
		}
		pmcMesh = (SMeshContainer*)pmcMesh->pNextMeshContainer;
	}

	pframeChild = pframeCur->pFrameFirstChild;
	while (pframeChild != NULL)
	{
		hr = FindBones(pframeChild);
		if (FAILED(hr))
			return hr;

		pframeChild = pframeChild->pFrameSibling;
	}

	return S_OK;
}


