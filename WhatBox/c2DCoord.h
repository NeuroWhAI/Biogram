#pragma once
#include <d3dx9.h>

#include "cSygnVal.h"




















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2차원 물리정보
// Desc : 위치, 속도, 크기, 각도, 각속도, 바이트화 지원
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DCoord : public cSygnVal
{
public:
	c2DCoord();
	c2DCoord(const c2DCoord& other);
	virtual ~c2DCoord();


protected:
	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Speed;
	
	D3DXVECTOR2 m_Scale;
	
	float m_Angle;
	float m_AngleSpeed;


public:
	enum {
		mtS, mtR, mtT
	};
protected:
	D3DXMATRIX m_Mat[3];
	D3DXMATRIX m_WorldMat;


public:
	virtual const D3DXVECTOR2* Pos() const;
	virtual const D3DXVECTOR2* Speed() const;
	virtual const D3DXVECTOR2* Scale() const;
	virtual float Angle() const;
	virtual float AngleSpeed() const;

	virtual void SetPos(const D3DXVECTOR2* pPos);
	virtual void SetSpeed(const D3DXVECTOR2* pSpeed);
	virtual void SetPos(float x, float y);
	virtual void SetSpeed(float x, float y);
	virtual void SetScale(const D3DXVECTOR2* pScale);
	virtual void SetScale(float x, float y);

	virtual void AddPos(const D3DXVECTOR2* pPos);
	virtual void AddSpeed(const D3DXVECTOR2* pSpeed);
	virtual void AddPos(float x, float y);
	virtual void AddSpeed(float x, float y);
	virtual void AddScale(const D3DXVECTOR2* pScale);
	virtual void AddScale(float x, float y);

	virtual void SetXPos(float x);
	virtual void SetYPos(float y);
	
	virtual void AddXPos(float x);
	virtual void AddYPos(float y);

	virtual void SetXSpeed(float x);
	virtual void SetYSpeed(float y);
	
	virtual void AddXSpeed(float x);
	virtual void AddYSpeed(float y);

	virtual void SetAngle(float Degree);
	virtual void SetAngleSpeed(float Degree);

	virtual void AddAngle(float Degree);
	virtual void AddAngleSpeed(float Degree);

	virtual void SetMatrix(int SRT, const D3DXMATRIX* pMt);


public:
	virtual const D3DXMATRIX* Matrix();
	virtual const D3DXMATRIX* WorldMatrix();
	virtual D3DXMATRIX MatrixWithCamera();
	virtual void SetMatrixToDevice();
	virtual void SetMatrixToSprite();
	virtual void SetWorldMatrixToSprite();
	virtual void SetMatrixWithCameraToSprite();


public:
	// 자신의 정보를 바이트화
	virtual int GetBytes(BYTE* pOut);

	// 바이트배열의 크기
	virtual UINT GetByteSize() const;

	// 바이트배열로 자신의 정보를 갱신
	virtual int SetBytes(const BYTE* Bytes);


public:
	c2DCoord& operator*= (c2DCoord& other);
	c2DCoord& operator*= (const D3DXMATRIX& other);
	c2DCoord operator* (c2DCoord& other);
	c2DCoord operator* (const D3DXMATRIX& other);
};

