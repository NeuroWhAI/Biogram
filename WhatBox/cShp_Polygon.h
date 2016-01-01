#pragma once
#include <d3dx9.h>
#include <vector>

























class cShp_Polygon
{
public:
	cShp_Polygon();
	cShp_Polygon(const char FileName[]);

	virtual ~cShp_Polygon();


protected:
	std::vector<D3DXVECTOR2> m_VtxList;


public:
	virtual int Render(DWORD Color = 0xffff0000);


public:
	virtual int AddVtx(float x, float y);
	virtual int SetVtx(UINT Idx, float x, float y);
	virtual UINT VtxCount() const;
	virtual std::vector<D3DXVECTOR2>* GetVtxList();
	virtual const std::vector<D3DXVECTOR2>* GetVtxList() const;
	
	
public:
	virtual int AddPos(float x, float y);


public:
	virtual bool isCollided(const cShp_Polygon* pOther, D3DXVECTOR2* IntersectPos);
};

