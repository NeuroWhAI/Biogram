// Interface for the ILcMdl class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _ILcMdl_H_
#define _ILcMdl_H_

#include "ATTRIB_Enum.h"



#ifndef interface
#define interface struct
#endif


interface ILcMdl
{
	virtual ~ILcMdl(){}

	virtual INT		Create(void* =0, void* =0, void* =0, void* =0)=0;
	virtual void	Destroy()=0;
	virtual INT		FrameMove()=0;
	virtual void	Render()=0;

	virtual const char*	const GetName()const=0;
	virtual ILcMdl* GetOriginal()=0;

	virtual INT		SetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)=0;
	virtual INT		GetAttrib(SknMeshNameSpace::ATTRIB_ attrib, void* pVal)=0;

	virtual INT		SetPosition(FLOAT* float3)=0;
	virtual INT		GetPosition(FLOAT* float3)=0;
};



INT LcMdl_Create(char* sCmd
				 , ILcMdl** pData	// Data
				 , void* p1			// Device
				 , void* p2			// File Name
				 , void* p3	= NULL	// Source Model
				 , void* p4	= NULL	// No Use
				 );


#endif


