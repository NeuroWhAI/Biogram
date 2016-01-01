#include "cQuatCoord.h"

#include "cCore.h"






































cQuatCoord::cQuatCoord()
	: m_zPos(0.f)
	, m_zSpeed(0.f)

	, m_tempVec(0.f, 0.f)
{

}


cQuatCoord::~cQuatCoord()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cQuatCoord::GetQuaterPos(D3DXVECTOR2* pOut, float x, float y, float z)
{
	pOut->x = 0.866025f*(x - y);
	pOut->y = 0.5f*(x + y) - z;
}


void cQuatCoord::GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* xy, float z)
{
	pOut->x = 0.866025f*(xy->x - xy->y);
	pOut->y = 0.5f*(xy->x + xy->y) - z;
}


void cQuatCoord::GetQuaterPos(D3DXVECTOR2* pOut, const D3DXVECTOR3* xyz)
{
	pOut->x = 0.866025f*(xyz->x - xyz->y);
	pOut->y = 0.5f*(xyz->x + xyz->y) - xyz->z;
}


void cQuatCoord::GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, float x, float y)
{
	pOut->z = 0.f;

	pOut->x = (x + 1.73205f*y) / 1.73205f;
	pOut->y = (1.73205f*y - x) / 1.73205f;
}


void cQuatCoord::GetQuarterPosFromScreenPos(D3DXVECTOR3* pOut, const D3DXVECTOR2* pos)
{
	return GetQuarterPosFromScreenPos(pOut, pos->x, pos->y);
}


void cQuatCoord::GetQuarterPosFromScreenPos(D3DXVECTOR2* pOut, const D3DXVECTOR2* pos)
{
	D3DXVECTOR3 temp;
	GetQuarterPosFromScreenPos(&temp, pos->x, pos->y);

	pOut->x = temp.x;
	pOut->y = temp.y;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float cQuatCoord::GetZPos() const
{
	return m_zPos;
}


void cQuatCoord::SetZPos(float z)
{
	m_zPos = z;
}


void cQuatCoord::AddZPos(float z)
{
	m_zPos += z;
}

/*-----------------------------------------------------------------------------------------------------------*/

float cQuatCoord::GetZSpeed() const
{
	return m_zSpeed;
}


void cQuatCoord::SetZSpeed(float z)
{
	m_zSpeed = z;
}


void cQuatCoord::AddZSpeed(float z)
{
	m_zSpeed += z;
}

/*-----------------------------------------------------------------------------------------------------------*/

void cQuatCoord::SetQuatPos(const D3DXVECTOR3* pos)
{
	m_Pos.x = pos->x;
	m_Pos.y = pos->y;

	m_zPos = pos->z;
}


void cQuatCoord::AddQuatPos(const D3DXVECTOR3* pos)
{
	m_Pos.x += pos->x;
	m_Pos.y += pos->y;

	m_zPos += pos->z;
}

/*-----------------------------------------------------------------------------------------------------------*/

void cQuatCoord::SetQuatSpeed(const D3DXVECTOR3* speed)
{
	m_Speed.x = speed->x;
	m_Speed.y = speed->y;

	m_zSpeed = speed->z;
}


void cQuatCoord::AddQuatSpeed(const D3DXVECTOR3* speed)
{
	m_Speed.x += speed->x;
	m_Speed.y += speed->y;

	m_zSpeed += speed->z;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const D3DXMATRIX* cQuatCoord::Matrix()
{
	D3DXVECTOR2 screenPos;
	GetQuaterPos(&screenPos);


	D3DXMatrixTranslation(&m_Mat[mtT], screenPos.x, screenPos.y, 0.f);
	D3DXMatrixScaling(&m_Mat[mtS], m_Scale.x, m_Scale.y, 1.f);
	D3DXMatrixRotationZ(&m_Mat[mtR], D3DXToRadian(m_Angle));


	m_WorldMat = m_Mat[mtS] * m_Mat[mtR] * m_Mat[mtT];
	return &m_WorldMat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cQuatCoord::GetQuaterPos(D3DXVECTOR2* pOut) const
{
	pOut->x = 0.866025f*(m_Pos.x - m_Pos.y);
	pOut->y = 0.5f*(m_Pos.x + m_Pos.y) - m_zPos;
}


const D3DXVECTOR2* cQuatCoord::GetQuaterPos()
{
	GetQuaterPos(&m_tempVec);


	return &m_tempVec;
}

