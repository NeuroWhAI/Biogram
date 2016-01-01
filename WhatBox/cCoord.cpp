#include "cCoord.h"

#include "cCore.h"























cCoord::cCoord()
	: m_Pos(0.f, 0.f, 0.f)
	, m_Speed(0.f, 0.f, 0.f)

	, m_Scale(1.f, 1.f, 1.f)

	, m_Angle(0.f, 0.f, 0.f)
{
	D3DXVECTOR3 Axis(0.f, 1.f, 0.f);
	D3DXMatrixRotationAxis(&m_Mat[mtR], &Axis, 0.f);

	m_Rot[0].x = m_Rot[0].y = m_Rot[0].z = 0.f;
	m_Rot[0].w = 1.f;
	m_Rot[1].x = m_Rot[1].y = m_Rot[1].z = 0.f;
	m_Rot[1].w = 1.f;
	m_Rot[2].x = m_Rot[2].y = m_Rot[2].z = 0.f;
	m_Rot[2].w = 1.f;
}


cCoord::~cCoord()
{

}

/*-------------------------------------------------------------------------------------*/

const D3DXVECTOR3* cCoord::Pos() const
{
	return &m_Pos;
}


const D3DXVECTOR3* cCoord::Speed() const
{
	return &m_Speed;
}


const D3DXVECTOR3* cCoord::Scale() const
{
	return &m_Scale;
}


const D3DXVECTOR3* cCoord::Angle() const
{
	return &m_Angle;
}



void cCoord::SetPos(const D3DXVECTOR3* pPos)
{
	m_Pos = *pPos;
}


void cCoord::SetSpeed(const D3DXVECTOR3* pSpeed)
{
	m_Speed = *pSpeed;
}


void cCoord::SetPos(float x, float y, float z)
{
	m_Pos.x = x;
	m_Pos.y = y;
	m_Pos.z = z;
}


void cCoord::SetSpeed(float x, float y, float z)
{
	m_Speed.x = x;
	m_Speed.y = y;
	m_Speed.z = z;
}


void cCoord::SetScale(const D3DXVECTOR3* pScale)
{
	m_Scale = *pScale;
}


void cCoord::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}



void cCoord::AddPos(const D3DXVECTOR3* pPos)
{
	m_Pos += *pPos;
}


void cCoord::AddSpeed(const D3DXVECTOR3* pSpeed)
{
	m_Speed += *pSpeed;
}


void cCoord::AddPos(float x, float y, float z)
{
	m_Pos.x += x;
	m_Pos.y += y;
	m_Pos.z += z;
}


void cCoord::AddSpeed(float x, float y, float z)
{
	m_Speed.x += x;
	m_Speed.y += y;
	m_Speed.z += z;
}


void cCoord::AddScale(const D3DXVECTOR3* pScale)
{
	m_Scale += *pScale;
}


void cCoord::AddScale(float x, float y, float z)
{
	m_Scale.x += x;
	m_Scale.y += y;
	m_Scale.z += z;
}



void cCoord::SetXPos(float x)
{
	m_Pos.x = x;
}


void cCoord::SetYPos(float y)
{
	m_Pos.y = y;
}


void cCoord::SetZPos(float z)
{
	m_Pos.z = z;
}



void cCoord::AddXPos(float x)
{
	m_Pos.x += x;
}


void cCoord::AddYPos(float y)
{
	m_Pos.y += y;
}


void cCoord::AddZPos(float z)
{
	m_Pos.z += z;
}



void cCoord::SetAngle(const D3DXVECTOR3* pDegree)
{
	m_Angle = *pDegree;
}


void cCoord::SetAngle(float xDegree, float yDegree, float zDegree)
{
	m_Angle.x = xDegree;
	m_Angle.y = yDegree;
	m_Angle.z = zDegree;
}



void cCoord::AddAngle(const D3DXVECTOR3* pDegree)
{
	m_Angle += *pDegree;
}


void cCoord::AddAngle(float xDegree, float yDegree, float zDegree)
{
	m_Angle.x += xDegree;
	m_Angle.y += yDegree;
	m_Angle.z += zDegree;
}




void cCoord::SetAngleX(float Degree)
{
	m_Angle.x = Degree;
}


void cCoord::SetAngleY(float Degree)
{
	m_Angle.y = Degree;
}


void cCoord::SetAngleZ(float Degree)
{
	m_Angle.z = Degree;
}



void cCoord::AddAngleX(float Degree)
{
	m_Angle.x += Degree;
}


void cCoord::AddAngleY(float Degree)
{
	m_Angle.y += Degree;
}


void cCoord::AddAngleZ(float Degree)
{
	m_Angle.z += Degree;
}



void cCoord::SetMatrix(int SRT, const D3DXMATRIX* pMt)
{
	m_Mat[SRT] = *pMt;
}

/*-------------------------------------------------------------------------------------*/

const D3DMATRIX* cCoord::Matrix()
{
	D3DXMatrixTranslation(&m_Mat[mtT], m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixScaling(&m_Mat[mtS], m_Scale.x, m_Scale.y, m_Scale.z);
	CalAngle();


	m_WorldMat = m_Mat[mtS] * m_Mat[mtR] * m_Mat[mtT];
	return &m_WorldMat;
}


void cCoord::SetMatrixToDevice()
{
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, Matrix());
}

/*-----------------------------------------------------------------------------------------------*/

void cCoord::CalAngle()
{
	// X쿼터니언
	D3DXVECTOR3	axisX = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXMatrixRotationQuaternion(&m_MtAngle[mtX], &m_Rot[mtX]); 
	D3DXVec3TransformCoord	(&axisX, &axisX, &m_MtAngle[mtX]); 
	D3DXQuaternionRotationAxis	(&m_Rot[mtX], &axisX, D3DXToRadian(m_Angle.x));


	// Y쿼터니언
	D3DXVECTOR3	axisY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixRotationQuaternion(&m_MtAngle[mtY], &m_Rot[mtY]); 
	D3DXVec3TransformCoord	(&axisY, &axisY, &m_MtAngle[mtY]); 
	D3DXQuaternionRotationAxis	(&m_Rot[mtY], &axisY, D3DXToRadian(m_Angle.y));


	// Z쿼터니언
	D3DXVECTOR3	axisZ = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXMatrixRotationQuaternion(&m_MtAngle[mtZ], &m_Rot[mtZ]); 
	D3DXVec3TransformCoord	(&axisZ, &axisZ, &m_MtAngle[mtZ]); 
	D3DXQuaternionRotationAxis	(&m_Rot[mtZ], &axisZ, D3DXToRadian(m_Angle.z));


	// XYZ쿼터니언
	D3DXQUATERNION quatAll(0.f, 0.f, 0.f, 1.f);

	D3DXQuaternionMultiply	(&quatAll, &m_Rot[mtX], &m_Rot[mtY]); 
	D3DXQuaternionNormalize	(&quatAll, &quatAll);

	D3DXQuaternionMultiply	(&quatAll, &quatAll, &m_Rot[mtZ]); 
	D3DXQuaternionNormalize	(&quatAll, &quatAll);

	
	// 회전행렬 계산
	D3DXMatrixRotationQuaternion(&m_Mat[mtR], &quatAll); 
}

