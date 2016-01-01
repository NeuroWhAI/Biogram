// Interface for the CLcXSkinIns class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _LcXSkinIns_H_
#define _LcXSkinIns_H_

#include "ATTRIB_Enum.h"



#include <vector>

class CLcXSkinIns : public CLcXSkin
{
protected:
	CLcXSkinSrc*				m_pOrg;				// Original Pointer
	LPD3DXANIMATIONCONTROLLER	m_pAC;				// Animation Controller
	SFrame*						m_pFrameRoot;		// Root Frame

	INT								m_nAniMax;		// Animation Max
	INT								m_nAniCur;		// Animation Current
	std::vector<LPD3DXANIMATIONSET > m_vAS;			// Animation Set List

	
public:
	CLcXSkinIns();
	virtual ~CLcXSkinIns();
	
	virtual INT		Create(void* =0, void* =0, void* =0, void* =0);
	virtual void	Destroy();
	virtual INT		FrameMove();
	virtual void	Render();

	virtual const char*	const GetName()const	{	return m_pOrg->GetName();	}
	virtual ILcMdl* GetOriginal()				{	return m_pOrg;				}

	virtual INT		SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);
	virtual INT		GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);
};

#endif


