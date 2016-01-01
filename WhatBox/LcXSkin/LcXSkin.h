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
	D3DXMATRIX		m_mtWorld		;	// ��ü�� ���� ���
	DOUBLE			m_dTimeCur		;	// ��ü�� �ð�

	INT m_CurrAniNum;					// ���� �ִϸ��̼� ��ȣ
	std::vector<DOUBLE> m_AniTimes;		// �� �ִϸ��̼��� �ð�����


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


