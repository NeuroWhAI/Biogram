// Implementation of the LcXSkinIns class.
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning(disable: 4996)

#include <vector>

#include <windows.h>
#include <D3D9.h>
#include <d3dx9.h>

#include "ILcMdl.h"
#include "LcXSkinAlloc.h"
#include "LcXSkin.h"
#include "LcXSkinSrc.h"
#include "LcXSkinIns.h"


#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }


CLcXSkinIns::CLcXSkinIns()
{
	m_pOrg	= NULL;
	m_pAC	= NULL;

	m_pFrameRoot = NULL;
	m_dTimeCur	= 0;

	D3DXMatrixIdentity(&m_mtWorld);


	m_nAniMax	= 0;
	m_nAniCur	= 0;
}


CLcXSkinIns::~CLcXSkinIns()
{
	Destroy();
}


void CLcXSkinIns::Destroy()
{
	if(!m_vAS.empty())
	{
		for(UINT i=0; i<m_vAS.size(); ++i)
			m_vAS[i]->Release();

		m_vAS.clear();
	}
}


INT CLcXSkinIns::Create(void* p1, void* p2, void* p3, void* p4)
{
	HRESULT hr=0;
	INT		i=0;

//	m_pDev	= (LPDIRECT3DDEVICE9)p1;
	m_pOrg = (CLcXSkinSrc*)p3;
	m_pFrameRoot = (SFrame*)m_pOrg->GetRootFrame();

	LPD3DXANIMATIONCONTROLLER	pAC = (LPD3DXANIMATIONCONTROLLER)m_pOrg->GetAnimationController();

	if(pAC)
	{
		pAC->GetMaxNumAnimationOutputs();
		pAC->GetMaxNumAnimationSets();
		pAC->GetMaxNumTracks();
		pAC->GetMaxNumEvents();

		UINT MaxNumAnimationOutputs	= pAC->GetMaxNumAnimationOutputs();
		UINT MaxNumAnimationSets	= pAC->GetMaxNumAnimationSets();
		UINT MaxNumTracks			= pAC->GetMaxNumTracks();
		UINT MaxNumEvents			= pAC->GetMaxNumEvents();

		pAC->CloneAnimationController(	MaxNumAnimationOutputs
										, MaxNumAnimationSets
										, MaxNumTracks
										, MaxNumEvents
										, &m_pAC);
	}





	// for Test...
	//FLOAT	fRand = float(rand()%1000);

	//m_dTimeCur = fRand/100.f;

	
	
	
	D3DXTRACK_DESC desc;
	m_pAC->GetTrackDesc(0, &desc);
		

	m_nAniMax = m_pAC->GetNumAnimationSets();

	for(i=0; i<m_nAniMax; ++i)
	{
		LPD3DXANIMATIONSET pAS = NULL;
		hr = m_pAC->GetAnimationSet(i, &pAS );

		if(FAILED( hr ) )
			continue;

		DOUBLE fPeriod = pAS->GetPeriod();			// 한 애니메이션에 대한 시간
		m_AniTimes.push_back(fPeriod);				// 시간정보 저장

//		INT nNum = pAS->GetNumAnimations();			// Animation Set에 있는 Animation 수
//		DOUBLE t = pAS->GetPeriodicPosition(2.4);	// 시간으로 값을 주면 상대적인 시간으로 다시 환원  == 1.4 - fPeriod * N :N=1
//		DOUBLE k = (2.4- 2 * fPeriod);
//
//		char* sName= (char*)pAS->GetName();
//
//		pAS->Release();

		m_vAS.push_back(pAS);
	}


	if(m_nAniMax)
		m_pAC->SetTrackAnimationSet(0, m_vAS[m_nAniMax-1]);
	
	m_pAC->SetTrackEnable(0, TRUE);

	return 0;
}

INT CLcXSkinIns::FrameMove()
{
	return 0;
}


void CLcXSkinIns::Render()
{
//	m_dTimeCur = timeGetTime()*0.001f;
	
	m_pAC->SetTrackPosition(0, 0);
	m_pAC->AdvanceTime(m_dTimeCur, NULL);

	m_pOrg->UpdateFrameMatrices(m_pFrameRoot, &m_mtWorld);
	m_pOrg->DrawFrame(m_pFrameRoot);
}


INT CLcXSkinIns::SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)
{
	if(attrib == SknMeshNameSpace::ATTRIB_Ani)
 	{
 		INT nAni =*((INT*)pVal);

		if(nAni>=m_nAniMax || nAni<0)
			return -1;


		m_CurrAniNum = m_nAniCur = nAni;
		m_pAC->SetTrackAnimationSet(0, m_vAS[m_nAniCur]);

 		return 0;
 	}

	return CLcXSkin::SetAttrib(attrib, pVal);
}

INT CLcXSkinIns::GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)
{
	return CLcXSkin::GetAttrib(attrib, pVal);
}

