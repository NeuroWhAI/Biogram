#pragma once
#include "c2DCoord.h"




































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 쿼터뷰 물리정보
// Desc : 위치, 속도, 크기, 각도, 각속도 지원
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cQuatCoord : public c2DCoord
{
public:
	cQuatCoord();
	virtual ~cQuatCoord();


public:
	// 3차원 좌표를 쿼터뷰 좌표로 변형시켜 줌
	static void GetQuaterPos(D3DXVECTOR2* pOut, float x, float y, float z);
	// 3차원 좌표를 쿼터뷰 좌표로 변형시켜 줌
	static void GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* xy, float z);
	// 3차원 좌표를 쿼터뷰 좌표로 변형시켜 줌
	static void GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR3* xyz);
	// 화면 좌표를 쿼터뷰상의 3차원 좌표로 변형시켜 줌
	static void GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, float x, float y);
	// 화면 좌표를 쿼터뷰상의 3차원 좌표로 변형시켜 줌
	static void GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, const D3DXVECTOR2* pos);
	// 화면 좌표를 쿼터뷰상의 3차원 좌표로 변형시켜 줌
	static void GetQuarterPosFromScreenPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* pos);


protected:
	float m_zPos;
	float m_zSpeed;


private:
	D3DXVECTOR2 m_tempVec;


public:
	virtual float GetZPos() const;
	virtual void SetZPos(float z);
	virtual void AddZPos(float z);

	virtual float GetZSpeed() const;
	virtual void SetZSpeed(float z);
	virtual void AddZSpeed(float z);

	virtual void SetQuatPos(const D3DXVECTOR3* pos);
	virtual void AddQuatPos(const D3DXVECTOR3* pos);

	virtual void SetQuatSpeed(const D3DXVECTOR3* speed);
	virtual void AddQuatSpeed(const D3DXVECTOR3* speed);


public:
	virtual const D3DXMATRIX* Matrix() override;


public:
	virtual void GetQuaterPos(D3DXVECTOR2* pOut) const;
	virtual const D3DXVECTOR2* GetQuaterPos();
};

