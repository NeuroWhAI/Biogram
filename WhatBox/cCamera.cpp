#include "cCamera.h"

#include "cCore.h"
#include "Option.h"














int cCamera::Number = 0;
int cCamera::CurrCamera = 0;


int cCamera::CurrCameraNum()
{
	return CurrCamera;
}


void cCamera::SetCurrCamera(int num)
{
	CurrCamera = num;
}

/*-------------------------------------------------------------------------------*/

cCamera::cCamera()
	: m_vEyePt(0, 3, -30)
	, m_vLookAt(0, 0, 0)
	, m_vUpVec(0, 1, 0)
{
	if(m_Number == 0)
	{
		CurrCamera = 0;
	}
	
	m_Number = Number;
	Number++;


#ifdef DIMENSION_3D // 3D
#ifndef VIEW_3D // 쿼터뷰
	SetEyePt(-8.f, 8.f, -8.f);
	SetLookAt(0.f, 0.f, 0.f);
#endif
#else // 2D
	SetEyePt(0.f, 0.f, -8.f);
	SetLookAt(0.f, 0.f, 0.f);
#endif
}


cCamera::~cCamera()
{

}

/*-------------------------------------------------------------------------------*/

int cCamera::Setup(D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookAt)
{
	m_vEyePt = vEyePt;
	m_vLookAt = vLookAt;


	return 0;
}



int cCamera::FrameMove()
{
	if(m_Number != CurrCamera) return -1;
	
	
	D3DXMatrixIdentity( &m_mtWorld );
	cCore::pd3dDevice->SetTransform( D3DTS_WORLD, &m_mtWorld );


	D3DXMatrixLookAtLH(&m_mtView, &m_vEyePt, &m_vLookAt, &m_vUpVec);
	cCore::pd3dDevice->SetTransform(D3DTS_VIEW, &m_mtView);


#ifdef VIEW_3D
	D3DXMatrixPerspectiveFovLH(&m_mtPrj, D3DX_PI/4.f, 1.f, 1.f, 4000.f);
#else
	D3DXMatrixOrthoLH(&m_mtPrj, 4.0f, 3.0f, 1.0f, 4000.0f); // 직교투영
#endif
	cCore::pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_mtPrj);


	return 0;
}



int cCamera::Control()
{
	if(m_Number != CurrCamera) return -1;


#ifndef DIMENSION_3D // 2D
	/* 상하좌우 이동 */
	float Speed = VFR(0.05f);

	if(cCore::Input.KeyPress('W'))
	{
		AddEyePt(0.f, Speed, 0.f);
		AddLookAt(0.f, Speed, 0.f);
	}
	else if(cCore::Input.KeyPress('S'))
	{
		AddEyePt(0.f, -Speed, 0.f);
		AddLookAt(0.f, -Speed, 0.f);
	}

	if(cCore::Input.KeyPress('A'))
	{
		AddEyePt(-Speed, 0.f, 0.f);
		AddLookAt(-Speed, 0.f, 0.f);
	}
	else if(cCore::Input.KeyPress('D'))
	{
		AddEyePt(Speed, 0.f, 0.f);
		AddLookAt(Speed, 0.f, 0.f);
	}
#else
#ifdef VIEW_3D
	/* 마우스 좌클릭 드래그로 카메라 회전 */
	if(cCore::Input.MousePress(VK_LBUTTON))
	{
#ifdef NOTUSE_VFR
		Rotation(VFR(+0.2f));
#else
		Rotation(VFR(+0.2f));
#endif
	}


	/* 쉬프트키와 스페이스키로 위아래 이동 */
	if(cCore::Input.KeyPress(VK_LSHIFT))
	{
		AddEyePt(0, VFR(-0.2f), 0);
		AddLookAt(0, VFR(-0.2f), 0);
	}
	else if(cCore::Input.KeyPress(VK_SPACE))
	{
		AddEyePt(0, VFR(0.2f), 0);
		AddLookAt(0, VFR(0.2f), 0);
	}


	/* 카메라가 보는 방향을 기준으로 앞, 뒤, 옆으로 이동 */
	if(cCore::Input.KeyPress('W'))
	{
		MoveForward(VFR(+0.2f));
	}
	else if(cCore::Input.KeyPress('S'))
	{
		MoveBackward(VFR(0.2f));
	}

	if(cCore::Input.KeyPress('A'))
	{
		MoveSideward(VFR(-0.1f));
	}
	else if(cCore::Input.KeyPress('D'))
	{
		MoveSideward(VFR(+0.1f));
	}


	/* 카메라가 보는곳을 중심으로 회전 */
	if(cCore::Input.KeyPress('Q'))
	{
		MoveSideward(VFR(-0.2f), false);
	}
	else if(cCore::Input.KeyPress('E'))
	{
		MoveSideward(VFR(+0.2f), false);
	}
#else
	/* 상하좌우 이동 */
	float Speed = VFR(0.05f);

	if(cCore::Input.KeyPress('W'))
	{
		AddEyePt(Speed, 0.f, Speed);
		AddLookAt(Speed, 0.f, Speed);
	}
	else if(cCore::Input.KeyPress('S'))
	{
		AddEyePt(-Speed, 0.f, -Speed);
		AddLookAt(-Speed, 0.f, -Speed);
	}

	if(cCore::Input.KeyPress('A'))
	{
		AddEyePt(-Speed, 0.f, Speed);
		AddLookAt(-Speed, 0.f, Speed);
	}
	else if(cCore::Input.KeyPress('D'))
	{
		AddEyePt(Speed, 0.f, -Speed);
		AddLookAt(Speed, 0.f, -Speed);
	}
#endif
#endif


	return 0;
}



void cCamera::MoveForward(float speed)
{
	D3DXVECTOR3 move(m_mtView._13, m_mtView._23*1.f, m_mtView._33);
	D3DXVec3Normalize(&move, &move);

	move *= speed;

	m_vEyePt += move;
	m_vLookAt += move;
}


void cCamera::MoveBackward(float speed)
{
	D3DXVECTOR3 move(m_mtView._13, m_mtView._23*1.f, m_mtView._33);
	D3DXVec3Normalize(&move, &move);

	move *= speed;

	m_vEyePt -= move;
	m_vLookAt -= move;
}



void cCamera::MoveSideward(float speed/* 음수이냐 양수냐로 방향 설정 */, bool MoveLookAt)
{
	D3DXVECTOR3 move(m_mtView._11, 0, m_mtView._31);
	D3DXVec3Normalize(&move,&move);

	move *= speed;

	m_vEyePt += move;
	if(MoveLookAt) m_vLookAt += move;
}



void cCamera::Rotation(float speed/* 음수이냐 양수냐로 방향 설정 */)
{
	D3DXVECTOR3 vcEps = cCore::Input.GetMouseEps()/2.f;

	FLOAT   fYaw    ;
	FLOAT   fPitch  ;

	D3DXVECTOR3 vcZ;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcX;

	D3DXMATRIX rtY;
	D3DXMATRIX rtX;

	// 월드 좌표 y 축에 대한 회전
	fYaw    = D3DXToRadian(vcEps.x * speed);
	D3DXMatrixRotationY(&rtY, fYaw);

	vcZ = m_vLookAt-m_vEyePt;
	vcY = D3DXVECTOR3(m_mtView._12, m_mtView._22, m_mtView._32);

	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vLookAt= vcZ + m_vEyePt;
	m_vUpVec  = vcY;
	D3DXMatrixLookAtLH(&m_mtView, &m_vEyePt, &m_vLookAt, &m_vUpVec);

	// 카메라의 x 축에 대한 회전
	fPitch  = D3DXToRadian(vcEps.y * speed);
	vcX = D3DXVECTOR3(m_mtView._11, m_mtView._21, m_mtView._31);
	vcY = D3DXVECTOR3(m_mtView._12, m_mtView._22, m_mtView._32);
	vcZ = m_vLookAt-m_vEyePt;

	D3DXMatrixRotationAxis(&rtX, &vcX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vLookAt= vcZ + m_vEyePt;
	m_vUpVec  = vcY;
	D3DXMatrixLookAtLH(&m_mtView, &m_vEyePt, &m_vLookAt, &m_vUpVec);
}

/*-------------------------------------------------------------------------------*/

void cCamera::SetEyePt(float x, float y, float z)
{
	m_vEyePt.x = x;
	m_vEyePt.y = y;
	m_vEyePt.z = z;
}


void cCamera::SetLookAt(float x, float y, float z)
{
	m_vLookAt.x = x;
	m_vLookAt.y = y;
	m_vLookAt.z = z;
}


void cCamera::SetUpVec(float x, float y, float z)
{
	m_vUpVec.x = x;
	m_vUpVec.y = y;
	m_vUpVec.z = z;
}



void cCamera::AddEyePt(float x, float y, float z)
{
	m_vEyePt.x += x;
	m_vEyePt.y += y;
	m_vEyePt.z += z;
}


void cCamera::AddLookAt(float x, float y, float z)
{
	m_vLookAt.x += x;
	m_vLookAt.y += y;
	m_vLookAt.z += z;
}

/*-------------------------------------------------------------------------------*/

D3DXVECTOR3 cCamera::GetEyePt() const
{
	return m_vEyePt;
}


D3DXVECTOR3 cCamera::GetLookAt() const
{
	return m_vLookAt;
}


D3DXVECTOR3 cCamera::GetUpVec() const
{
	return m_vUpVec;
}



D3DXMATRIX cCamera::GetPrj() const
{
	return m_mtPrj;
}


D3DXMATRIX cCamera::GetView() const
{
	return m_mtView;
}

