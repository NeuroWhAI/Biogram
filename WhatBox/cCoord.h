#pragma once
#include <d3dx9.h>


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3차원 물리정보
// Desc : 위치, 속도, 크기, 각도
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cCoord
{
public:
	cCoord();
	~cCoord();


protected:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Speed;
	
	D3DXVECTOR3 m_Scale;
	
	D3DXVECTOR3 m_Angle;


public:
	enum {
		mtS, mtR, mtT
	};
	enum {
		mtX, mtY, mtZ
	};
private:
	D3DXMATRIX m_Mat[3];
	D3DMATRIX m_WorldMat;

	D3DXMATRIX m_MtAngle[3];
	D3DXQUATERNION m_Rot[3];


public:
	virtual const D3DXVECTOR3* Pos() const;
	virtual const D3DXVECTOR3* Speed() const;
	virtual const D3DXVECTOR3* Scale() const;
	virtual const D3DXVECTOR3* Angle() const;

	virtual void SetPos(const D3DXVECTOR3* pPos);
	virtual void SetSpeed(const D3DXVECTOR3* pSpeed);
	virtual void SetPos(float x, float y, float z);
	virtual void SetSpeed(float x, float y, float z);
	virtual void SetScale(const D3DXVECTOR3* pScale);
	virtual void SetScale(float x, float y, float z);

	virtual void AddPos(const D3DXVECTOR3* pPos);
	virtual void AddSpeed(const D3DXVECTOR3* pSpeed);
	virtual void AddPos(float x, float y, float z);
	virtual void AddSpeed(float x, float y, float z);
	virtual void AddScale(const D3DXVECTOR3* pScale);
	virtual void AddScale(float x, float y, float z);

	virtual void SetXPos(float x);
	virtual void SetYPos(float y);
	virtual void SetZPos(float z);
	
	virtual void AddXPos(float x);
	virtual void AddYPos(float y);
	virtual void AddZPos(float z);

	virtual void SetAngle(const D3DXVECTOR3* pDegree);
	virtual void SetAngle(float xDegree, float yDegree, float zDegree);

	virtual void AddAngle(const D3DXVECTOR3* pDegree);
	virtual void AddAngle(float xDegree, float yDegree, float zDegree);

	virtual void SetAngleX(float Degree);
	virtual void SetAngleY(float Degree);
	virtual void SetAngleZ(float Degree);

	virtual void AddAngleX(float Degree);
	virtual void AddAngleY(float Degree);
	virtual void AddAngleZ(float Degree);

	virtual void SetMatrix(int SRT, const D3DXMATRIX* pMt);


public:
	virtual const D3DMATRIX* Matrix();
	virtual void SetMatrixToDevice();


private:
	void CalAngle();
};

