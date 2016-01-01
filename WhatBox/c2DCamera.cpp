#include "c2DCamera.h"

#include "cCore.h"

#include "cShp_Rectangle.h"






















c2DCamera::c2DCamera()
	: m_pScreenRect(new cShp_Rectangle())
	, m_zeroPos(0.f, 0.f)
{

}


c2DCamera::~c2DCamera()
{
	SAFE_DELETE(m_pScreenRect);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int c2DCamera::FrameMove()
{
	m_Pos += VFR(m_Speed);


	m_pScreenRect->left = m_Pos.x - 8.f;
	m_pScreenRect->top = m_Pos.y - 8.f;
	m_pScreenRect->right = m_Pos.x + cCore::WinSize.x + 8.f;
	m_pScreenRect->bottom = m_Pos.y + cCore::WinSize.y + 8.f;


	return 0;
}


int c2DCamera::Reset()
{
	m_Pos = D3DXVECTOR2(0.f, 0.f);
	m_Speed = D3DXVECTOR2(0.f, 0.f);
	m_Scale = D3DXVECTOR2(1.f, 1.f);
	m_Angle = 0.f;

	
	Matrix();


	return 0;
}


int c2DCamera::Control()
{
	const float moveSpeed = VFR(8.f);
	const float zoomSpeed = VFR(0.1f);

	if(cCore::Input.KeyPress(VK_UP))
	{
		m_Pos.y -= moveSpeed;
	}
	else if(cCore::Input.KeyPress(VK_DOWN))
	{
		m_Pos.y += moveSpeed;
	}

	if(cCore::Input.KeyPress(VK_LEFT))
	{
		m_Pos.x -= moveSpeed;
	}
	else if(cCore::Input.KeyPress(VK_RIGHT))
	{
		m_Pos.x += moveSpeed;
	}

	if(cCore::Input.GetMouseEps().z < 0.f)
	{
		m_Scale.x -= zoomSpeed;
		m_Scale.y -= zoomSpeed;
	}
	else if(cCore::Input.GetMouseEps().z > 0.f)
	{
		m_Scale.x += zoomSpeed;
		m_Scale.y += zoomSpeed;
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

const D3DXMATRIX* c2DCamera::Matrix()
{
	D3DXMatrixTranslation(&m_Mat[mtT], -m_Pos.x, -m_Pos.y, 0.f);
	D3DXMatrixScaling(&m_Mat[mtS], m_Scale.x, m_Scale.y, 1.f);
	D3DXMatrixRotationZ(&m_Mat[mtR], D3DXToRadian(m_Angle));


	m_WorldMat = m_Mat[mtS] * m_Mat[mtR] * m_Mat[mtT];
	return &m_WorldMat;
}


const cShp_Rectangle* c2DCamera::GetScreenRect() const
{
	return m_pScreenRect;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

const D3DXVECTOR2* c2DCamera::Pos() const
{
	if(cCore::Sprite.CameraOnCheck())
		return &m_Pos;

	return &m_zeroPos;
}


const D3DXVECTOR2* c2DCamera::RealPos() const
{
	return &m_Pos;
}

