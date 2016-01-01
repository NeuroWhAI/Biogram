#include "c2DCoord.h"

#include "cCore.h"

#include "cBinaryReader.h"
#include "cBinaryWriter.h"

























c2DCoord::c2DCoord()
	: m_Pos(0.f, 0.f)
	, m_Speed(0.f, 0.f)

	, m_Scale(1.f, 1.f)

	, m_Angle(0.f)
	, m_AngleSpeed(0.f)
{
	this->Matrix();
}


c2DCoord::c2DCoord(const c2DCoord& other)
	: m_Pos(*other.Pos())
	, m_Speed(*other.Speed())

	, m_Scale(*other.Scale())

	, m_Angle(other.Angle())
	, m_AngleSpeed(other.AngleSpeed())
{
	m_Mat[0] = other.m_Mat[0];
	m_Mat[1] = other.m_Mat[1];
	m_Mat[2] = other.m_Mat[2];

	m_WorldMat = other.m_WorldMat;
}


c2DCoord::~c2DCoord()
{

}

/*-------------------------------------------------------------------------------------*/

const D3DXVECTOR2* c2DCoord::Pos() const
{
	return &m_Pos;
}


const D3DXVECTOR2* c2DCoord::Speed() const
{
	return &m_Speed;
}


const D3DXVECTOR2* c2DCoord::Scale() const
{
	return &m_Scale;
}


float c2DCoord::Angle() const
{
	return m_Angle;
}


float c2DCoord::AngleSpeed() const
{
	return m_AngleSpeed;
}



void c2DCoord::SetPos(const D3DXVECTOR2* pPos)
{
	m_Pos = *pPos;
}


void c2DCoord::SetSpeed(const D3DXVECTOR2* pSpeed)
{
	m_Speed = *pSpeed;
}


void c2DCoord::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}


void c2DCoord::SetSpeed(float x, float y)
{
	m_Speed.x = x;
	m_Speed.y = y;
}


void c2DCoord::SetScale(const D3DXVECTOR2* pScale)
{
	m_Scale = *pScale;
}


void c2DCoord::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}



void c2DCoord::AddPos(const D3DXVECTOR2* pPos)
{
	m_Pos += *pPos;
}


void c2DCoord::AddSpeed(const D3DXVECTOR2* pSpeed)
{
	m_Speed += *pSpeed;
}


void c2DCoord::AddPos(float x, float y)
{
	m_Pos.x += x;
	m_Pos.y += y;
}


void c2DCoord::AddSpeed(float x, float y)
{
	m_Speed.x += x;
	m_Speed.y += y;
}


void c2DCoord::AddScale(const D3DXVECTOR2* pScale)
{
	m_Scale += *pScale;
}


void c2DCoord::AddScale(float x, float y)
{
	m_Scale.x += x;
	m_Scale.y += y;
}



void c2DCoord::SetXPos(float x)
{
	m_Pos.x = x;
}


void c2DCoord::SetYPos(float y)
{
	m_Pos.y = y;
}



void c2DCoord::AddXPos(float x)
{
	m_Pos.x += x;
}


void c2DCoord::AddYPos(float y)
{
	m_Pos.y += y;
}



void c2DCoord::SetXSpeed(float x)
{
	m_Speed.x = x;
}


void c2DCoord::SetYSpeed(float y)
{
	m_Speed.y = y;
}



void c2DCoord::AddXSpeed(float x)
{
	m_Speed.x += x;
}


void c2DCoord::AddYSpeed(float y)
{
	m_Speed.y += y;
}



void c2DCoord::SetAngle(float Degree)
{
	m_Angle = Degree;
}


void c2DCoord::SetAngleSpeed(float Degree)
{
	m_AngleSpeed = Degree;
}



void c2DCoord::AddAngle(float Degree)
{
	m_Angle += Degree;
}


void c2DCoord::AddAngleSpeed(float Degree)
{
	m_AngleSpeed += Degree;
}



void c2DCoord::SetMatrix(int SRT, const D3DXMATRIX* pMt)
{
	m_Mat[SRT] = *pMt;
}

/*-------------------------------------------------------------------------------------*/

const D3DXMATRIX* c2DCoord::Matrix()
{
	D3DXMatrixTranslation(&m_Mat[mtT], m_Pos.x, m_Pos.y, 0.f);
	D3DXMatrixScaling(&m_Mat[mtS], m_Scale.x, m_Scale.y, 1.f);
	D3DXMatrixRotationZ(&m_Mat[mtR], D3DXToRadian(m_Angle));


	m_WorldMat = m_Mat[mtS] * m_Mat[mtR] * m_Mat[mtT];
	return &m_WorldMat;
}


const D3DXMATRIX* c2DCoord::WorldMatrix()
{
	return &m_WorldMat;
}


D3DXMATRIX c2DCoord::MatrixWithCamera()
{
	Matrix();
	const D3DXMATRIX* pCameraMat = cCore::Camera2D.Matrix();

	m_WorldMat._41 += pCameraMat->_41;
	m_WorldMat._42 += pCameraMat->_42;
	m_WorldMat._43 += pCameraMat->_43;


	return m_WorldMat;
}


void c2DCoord::SetMatrixToDevice()
{
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, Matrix());
}


void c2DCoord::SetMatrixToSprite()
{
	cCore::Sprite.GetSprite()->SetTransform(Matrix());
}


void c2DCoord::SetWorldMatrixToSprite()
{
	const D3DXMATRIX* pCameraMat = cCore::Camera2D.Matrix();
	m_WorldMat._41 += pCameraMat->_41;
	m_WorldMat._42 += pCameraMat->_42;
	m_WorldMat._43 += pCameraMat->_43;

	cCore::Sprite.GetSprite()->SetTransform(&m_WorldMat);
}


void c2DCoord::SetMatrixWithCameraToSprite()
{
	cCore::Sprite.GetSprite()->SetTransform(&MatrixWithCamera());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int c2DCoord::GetBytes(BYTE* pOut)
{
	cBinaryWriter bw(CAST(GetByteSize(), int));


	bw.Write(m_Pos.x);
	bw.Write(m_Pos.y);
	
	bw.Write(m_Speed.x);
	bw.Write(m_Speed.y);
	
	bw.Write(m_Scale.x);
	bw.Write(m_Scale.y);
	
	bw.Write(m_Angle);

	bw.Write(m_AngleSpeed);


	bw.GetBytes((char*)pOut);


	return 0;
}


UINT c2DCoord::GetByteSize() const
{
	return sizeof(float) * 8;
}


int c2DCoord::SetBytes(const BYTE* Bytes)
{
	cBinaryReader br((char*)Bytes, CAST(GetByteSize(), int));


	m_Pos.x = br.Read<float>();
	m_Pos.y = br.Read<float>();
	
	m_Speed.x = br.Read<float>();
	m_Speed.y = br.Read<float>();
	
	m_Scale.x = br.Read<float>();
	m_Scale.y = br.Read<float>();
	
	m_Angle = br.Read<float>();
	
	m_AngleSpeed = br.Read<float>();


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

c2DCoord& c2DCoord::operator*= (c2DCoord& other)
{
	m_WorldMat = *this->Matrix() * *other.Matrix();

	
	m_Pos = D3DXVECTOR2(m_WorldMat._41, m_WorldMat._42);
	m_Angle = -D3DXToDegree(atanf(m_WorldMat._21 / m_WorldMat._11));
	//m_Scale = D3DXVECTOR2(m_WorldMat._11, m_WorldMat._22);
	

	return *this;
}


c2DCoord& c2DCoord::operator*= (const D3DXMATRIX& other)
{
	m_WorldMat = *this->Matrix() * other;


	m_Pos = D3DXVECTOR2(m_WorldMat._41, m_WorldMat._42);
	m_Angle = -D3DXToDegree(atanf(m_WorldMat._21 / m_WorldMat._11));
	//m_Scale = D3DXVECTOR2(m_WorldMat._11, m_WorldMat._22);
	

	return *this;
}


c2DCoord c2DCoord::operator* (c2DCoord& other)
{
	c2DCoord temp(*this);

	temp *= other;


	return temp;
}


c2DCoord c2DCoord::operator* (const D3DXMATRIX& other)
{
	c2DCoord temp(*this);

	temp *= other;


	return temp;
}

