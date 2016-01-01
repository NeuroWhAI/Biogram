// Implementation of the CLcXSkinAlloc class.
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning(disable: 4996)

#include <windows.h>
#include <mmsystem.h>
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












SFrame* SFrame::FindFrame(char *szFrame)
{
    SFrame *pframe;

    if ((szName != NULL) && (strcmp(szName, szFrame) == 0))
        return this;

    if (pFrameFirstChild != NULL)
    {
        pframe = pFrameFirstChild->FindFrame(szFrame);
        if (pframe != NULL)
            return pframe;
    }

    if (pFrameSibling != NULL)
    {
        pframe = pFrameSibling->FindFrame(szFrame);
        if (pframe != NULL)
            return pframe;
    }

    return NULL;
}


// Name: CLcXSkinAlloc::CreateFrame()
// Desc: 

HRESULT CLcXSkinAlloc::CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	HRESULT hr = S_OK;
	SFrame *pFrame;
	
	*ppNewFrame = NULL;
	
	pFrame = new SFrame;
	if (pFrame == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	
	hr = AllocateName(Name, &pFrame->szName);
	if (FAILED(hr))
		goto e_Exit;
	
	// initialize other data members of the frame
	D3DXMatrixIdentity(&pFrame->tmMatrix);
	D3DXMatrixIdentity(&pFrame->tmWorld);
	
	pFrame->pmcMesh = NULL;
	pFrame->pFrameSibling = NULL;
	pFrame->pFrameFirstChild = NULL;
	
	*ppNewFrame = (LPD3DXFRAME)pFrame;
	pFrame = NULL;
e_Exit:
	delete pFrame;
	return hr;
}





// Name: CLcXSkinAlloc::CreateMeshContainer()
// Desc: 

HRESULT CLcXSkinAlloc::CreateMeshContainer(
												LPCSTR Name, 
												CONST D3DXMESHDATA *pMeshData,
												CONST D3DXMATERIAL *pMaterials, 
												CONST D3DXEFFECTINSTANCE *pEffectInstances,
												DWORD NumMaterials, 
												CONST DWORD *pAdjacency, 
												LPD3DXSKININFO pSkinInfo, 
												LPD3DXMESHCONTAINER *ppNewMeshContainer) 
{
	HRESULT hr;
	SMeshContainer*	pMeshContainer = NULL;
	UINT NumFaces;
	UINT iMaterial;
	UINT iBone, cBones;
	LPDIRECT3DDEVICE9 pd3dDevice = NULL;
	
	LPD3DXMESH pMesh = NULL;
	
	*ppNewMeshContainer = NULL;
	
	// this sample does not handle patch meshes, so fail when one is found
	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		hr = E_FAIL;
		goto e_Exit;
	}
	
	// get the pMesh interface pointer out of the mesh data structure
	pMesh = pMeshData->pMesh;
	
	// this sample does not FVF compatible meshes, so fail when one is found
	if (pMesh->GetFVF() == 0)
	{
		hr = E_FAIL;
		goto e_Exit;
	}
	
	// allocate the overloaded structure to return as a D3DXMESHCONTAINER
	pMeshContainer = new SMeshContainer;
	if (pMeshContainer == NULL)
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	memset(pMeshContainer, 0, sizeof(SMeshContainer));
	
	// make sure and copy the name.  All memory as input belongs to caller, interfaces can be addref'd though
	hr = AllocateName(Name, &pMeshContainer->Name);
	if (FAILED(hr))
		goto e_Exit;        
	
	pMesh->GetDevice(&pd3dDevice);
	NumFaces = pMesh->GetNumFaces();
	
	// if no normals are in the mesh, add them
	if (!(pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		
		// clone the mesh to make room for the normals
		hr = pMesh->CloneMeshFVF( pMesh->GetOptions(), 
			pMesh->GetFVF() | D3DFVF_NORMAL, 
			pd3dDevice, &pMeshContainer->MeshData.pMesh );
		if (FAILED(hr))
			goto e_Exit;
		
		// get the new pMesh pointer back out of the mesh container to use
		// NOTE: we do not release pMesh because we do not have a reference to it yet
		pMesh = pMeshContainer->MeshData.pMesh;
		
		// now generate the normals for the pmesh
		D3DXComputeNormals( pMesh, NULL );
	}
	else  // if no normals, just add a reference to the mesh for the mesh container
	{
		pMeshContainer->MeshData.pMesh = pMesh;
		pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		
		pMesh->AddRef();
	}
	
	// allocate memory to contain the material information.  This sample uses
	//   the D3D9 materials and texture names instead of the EffectInstance style materials
	pMeshContainer->NumMaterials = max(1, NumMaterials);
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	pMeshContainer->ppTextures = new LPDIRECT3DTEXTURE9[pMeshContainer->NumMaterials];
	pMeshContainer->pAdjacency = new DWORD[NumFaces*3];
	if ((pMeshContainer->pAdjacency == NULL) || (pMeshContainer->pMaterials == NULL))
	{
		hr = E_OUTOFMEMORY;
		goto e_Exit;
	}
	
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * NumFaces*3);
	memset(pMeshContainer->ppTextures, 0, sizeof(LPDIRECT3DTEXTURE9) * pMeshContainer->NumMaterials);
	
	// if materials provided, copy them
	if (NumMaterials > 0)            
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);
		
		
		char drive[_MAX_DRIVE]={0};
		char sPath[_MAX_DIR]={0};
		
		const char*	sModelFile = m_pSrc->GetName();
		
		_splitpath(sModelFile, drive, sPath ,NULL, NULL);
		
		
		for (iMaterial = 0; iMaterial < NumMaterials; iMaterial++)
		{
			if (pMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL)
			{
				/* 텍스쳐경로 패치부분 */
				char sFileFullPath[_MAX_DIR]={0,};
				
				if( strlen(pMeshContainer->pMaterials[iMaterial].pTextureFilename)>2)
				{
					sprintf_s(sFileFullPath, _MAX_DIR, "%s%s%s", drive, sPath
						, pMeshContainer->pMaterials[iMaterial].pTextureFilename);
				}
				
				WCHAR* wFileFullPath = new WCHAR[strlen(sFileFullPath)+1];
				DXUtil_ConvertAnsiStringToWideCch(wFileFullPath, sFileFullPath, strlen(sFileFullPath)+1);
				

				if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, wFileFullPath, &pMeshContainer->ppTextures[iMaterial] ) ) )
					pMeshContainer->ppTextures[iMaterial] = NULL;
				delete[] wFileFullPath;

				
				// don't remember a pointer into the dynamic memory, just forget the name after loading
				pMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else // if no materials provided, use a default one
	{
		pMeshContainer->pMaterials[0].pTextureFilename = NULL;
		memset(&pMeshContainer->pMaterials[0].MatD3D, 0, sizeof(D3DMATERIAL9));
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
		pMeshContainer->pMaterials[0].MatD3D.Specular = pMeshContainer->pMaterials[0].MatD3D.Diffuse;
	}
	
	// if there is skinning information, save off the required data and then setup for HW skinning
	if (pSkinInfo != NULL)
	{
		// first save off the SkinInfo and original mesh data
		pMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();
		
		pMeshContainer->pOrigMesh = pMesh;
		pMesh->AddRef();
		
		// Will need an array of offset matrices to move the vertices from the figure space to the bone's space
		cBones = pSkinInfo->GetNumBones();
		
		pMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[cBones];
		pMeshContainer->m_pBoneMatrix = new D3DXMATRIX*[cBones];
		
		if (pMeshContainer->pBoneOffsetMatrices == NULL)
		{
			hr = E_OUTOFMEMORY;
			goto e_Exit;
		}
		
		// get each of the bone offset matrices so that we don't need to get them later
		for (iBone = 0; iBone < cBones; iBone++)
		{
			pMeshContainer->pBoneOffsetMatrices[iBone] = *(pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}
		
		// GenerateSkinnedMesh will take the general skinning information and transform it to a HW friendly version
		hr = ((CLcXSkinSrc*)m_pSrc)->GenerateSkinnedMesh(pMeshContainer);
		if (FAILED(hr))
			goto e_Exit;
	}
	
	*ppNewMeshContainer = (LPD3DXMESHCONTAINER)pMeshContainer;
	pMeshContainer = NULL;


e_Exit: // 종료루틴
	SAFE_RELEASE(pd3dDevice);
	
	// call Destroy function to properly clean up the memory allocated 
	if (pMeshContainer != NULL)
	{
		DestroyMeshContainer((LPD3DXMESHCONTAINER)pMeshContainer);
	}
	
	return hr;
}





// Name: CLcXSkinAlloc::DestroyFrame()
// Desc: 

HRESULT CLcXSkinAlloc::DestroyFrame(LPD3DXFRAME pFrameToFree) 
{
	SAFE_DELETE_ARRAY( pFrameToFree->Name );
	SAFE_DELETE( pFrameToFree );
	return S_OK; 
}





// Name: CLcXSkinAlloc::DestroyMeshContainer()
// Desc: 

HRESULT CLcXSkinAlloc::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	UINT iMaterial;
	SMeshContainer *pMeshContainer = (SMeshContainer*)pMeshContainerBase;
	
	SAFE_DELETE_ARRAY( pMeshContainer->Name );
	SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );
	SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );
	SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );
	
	// release all the allocated textures
	if (pMeshContainer->ppTextures != NULL)
	{
		for (iMaterial = 0; iMaterial < pMeshContainer->NumMaterials; iMaterial++)
		{
			SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
		}
	}
	
	SAFE_DELETE_ARRAY(	pMeshContainer->pAttributeTable);
	SAFE_DELETE_ARRAY( pMeshContainer->ppTextures );
	SAFE_DELETE_ARRAY( pMeshContainer->m_pBoneMatrix );
	SAFE_RELEASE( pMeshContainer->pBoneCombinationBuf );
	SAFE_RELEASE( pMeshContainer->MeshData.pMesh );
	SAFE_RELEASE( pMeshContainer->pSkinInfo );
	SAFE_RELEASE( pMeshContainer->pOrigMesh );
	SAFE_DELETE( pMeshContainer );
	return S_OK;
}


HRESULT CLcXSkinAlloc::AllocateName( LPCSTR Name, LPSTR *pNewName )
{
	UINT cbLength;
	
	if (Name != NULL)
	{
		cbLength = (UINT)strlen(Name) + 1;
		*pNewName = new CHAR[cbLength];
		if (*pNewName == NULL)
			return E_OUTOFMEMORY;
		memcpy(*pNewName, Name, cbLength*sizeof(CHAR));
	}
	else
	{
		*pNewName = NULL;
	}
	
	return S_OK;
}


