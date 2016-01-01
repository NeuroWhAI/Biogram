// Implementation of the ILcMdl class.
//
////////////////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <D3D9.h>
#include <d3dx9.h>

#include "ILcMdl.h"
#include "LcXSkinAlloc.h"
#include "LcXSkin.h"
#include "LcXSkinSrc.h"
#include "LcXSkinIns.h"



INT LcMdl_Create(char* sCmd
				 , ILcMdl** pData	// Data
				 , void* p1			// Device
				 , void* p2			// File Name
				 , void* p3			// Source Model
				 , void* p4			// No Use
				 )
{
	ILcMdl* pObj = NULL;

	*pData = NULL;

	if( NULL != p2)
	{
		pObj = new CLcXSkinSrc;
	}
	else if(NULL != p3)
	{
		pObj = new CLcXSkinIns;
	}
	else
	{
		return -1;
	}

	if(FAILED(pObj->Create(p1, p2, p3, p4)))
	{
		delete pObj;
		return -1;
	}

	*pData = pObj;
	return 0;
}
