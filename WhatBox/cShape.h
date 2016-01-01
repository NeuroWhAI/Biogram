#pragma once
#include "cShp_Polygon.h"























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 회전가능한 다각형
// Desc : 삼각함수를 이용해서 회전후의 각 점의 위치를 계산함
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cShape : public cShp_Polygon
{
public:
	cShape();
	cShape(const D3DXVECTOR2& Center);
	cShape(const char FileName[], const D3DXVECTOR2* Center = nullptr);

	virtual ~cShape();


protected:
	D3DXVECTOR2 m_Center;
	float m_Angle; // Degree


protected:
	std::vector<float> m_AngleList;
	std::vector<float> m_DisList;


public:
	int UpdatePos();
	virtual int AddVtx(float x, float y);
	virtual UINT VtxCount() const;
	virtual const std::vector<D3DXVECTOR2>* GetVtxList() const;
	
	
public:
	int SetCenter(float x, float y);
	const D3DXVECTOR2* Center() const;
	virtual int AddPos(float x, float y);
	int SetPos(float x, float y);
	int SetAngle(float Degree);
	int AddAngle(float Degree);
};

