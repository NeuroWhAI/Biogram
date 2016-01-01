// Interface for the CLcXSkin class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _LcXSkin_H_
#define _LcXSkin_H_

#include "ATTRIB_Enum.h"
#include <vector>


class CLcXSkin : public ILcMdl
{
protected:
	D3DXMATRIX		m_mtWorld		;	// 객체의 월드 행렬
	DOUBLE			m_dTimeCur		;	// 객체의 시간

	INT m_CurrAniNum;					// 현재 애니메이션 번호
	std::vector<DOUBLE> m_AniTimes;		// 각 애니메이션의 시간길이


public:
	CLcXSkin();
	virtual ~CLcXSkin();

	virtual INT		Create(void* =0, void* =0, void* =0, void* =0);
	virtual void	Destroy();
	virtual INT		FrameMove();
	virtual void	Render();

	virtual const char*	const GetName()const	{	return NULL;	}
	virtual ILcMdl* GetOriginal()				{	return NULL;	}

	virtual INT		SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);
	virtual INT		GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal);

	virtual INT		SetPosition(FLOAT* float3);
	virtual INT		GetPosition(FLOAT* float3);
};

#endif


