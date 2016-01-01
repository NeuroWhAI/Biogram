#include "Util.h"

#include "cTexture.h"

#include "cCore.h"
#include "D3D/dxutil.h"
#include "Option.h"

#include "cD3DVtxBuffer.h"
#include "cD3DIdxBuffer.h"
#include "cFont.h"

















void Util::ShowNumber(int Num, int x, int y, DWORD Color)
{
	char Buf[32];

	sprintf_s(Buf, 32, "%d", Num);
	cCore::Resource.Font1.ShowText(Buf, x, y, Color);
}


void Util::ShowNumber(long Num, int x, int y, DWORD Color)
{
	char Buf[32];

	sprintf_s(Buf, 32, "%ld", Num);
	cCore::Resource.Font1.ShowText(Buf, x, y, Color);
}


void Util::ShowNumber(float Num, int x, int y, DWORD Color)
{
	char Buf[32];

	sprintf_s(Buf, 32, "%f", Num);
	cCore::Resource.Font1.ShowText(Buf, x, y, Color);
}


void Util::ShowNumber(double Num, int x, int y, DWORD Color)
{
	char Buf[32];

	sprintf_s(Buf, 32, "%lf", Num);
	cCore::Resource.Font1.ShowText(Buf, x, y, Color);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::Log(const char* sFormatLog, ...)
{
	va_list vlist;
	va_start(vlist, sFormatLog); //인자의 시작 주소 설정

	cCore::Log.AddLog2(sFormatLog, vlist);

	va_end(vlist);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::ShowText(const char Format[], float x, float y, DWORD Color, ...)
{
	va_list vlist;
	va_start(vlist, Color); //인자의 시작 주소 설정


	char buffer[1024];
	vsprintf_s(buffer, 1023, Format, vlist);


	cCore::Resource.Font1.ShowText(buffer, CAST(x, int), CAST(y, int), Color);


	va_end(vlist);
}
 

void Util::ShowText(const char Format[], float x, float y, DWORD Color, cFont* pFont, ...)
{
	va_list vlist;
	va_start(vlist, pFont); //인자의 시작 주소 설정


	char buffer[1024];
	vsprintf_s(buffer, 1023, Format, vlist);


	pFont->ShowText(buffer, CAST(x, int), CAST(y, int), Color);


	va_end(vlist);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::PushMessage(std::wstring msg, DWORD color)
{
	cCore::MessageMgr.PushMessage(msg, color);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int Util::ErrorMessage(std::string Msg)
{
	cCore::ExitProgram();


	WCHAR* wMsg = new WCHAR[Msg.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wMsg, Msg.c_str(), 1+static_cast<int>(Msg.size()));

	MessageBox(cCore::hWnd, wMsg, L"Error!", MB_OK);


	delete[] wMsg;
	return -1;
}

/*------------------------------------------------------------------------------------*/

bool Util::FloatEqual(float A, float B)
{
	return (fabsf(A-B) < EPSILON);
}


double Util::logB(double x, double base)
{
	return log(x)/log(base);
}


float Util::flogB(float x, float base)
{
	return logf(x)/logf(base);
}


DWORD Util::GetReverseColor(DWORD rawColor)
{
	return ((rawColor | 0x00ffffff) & (~(rawColor & 0x00ffffff)));
}

/*------------------------------------------------------------------------------------*/

void Util::D3DXMatrixViewport(D3DXMATRIX* pOut)
{
	D3DVIEWPORT9 vp;
	cCore::pd3dDevice->GetViewport(&vp); 

	float fW = 0; float fH = 0; float fD = 0; float fY = 0; 
	float fX = 0; float fM = FLOAT(vp.MinZ); 

	fW = FLOAT(vp.Width)*.5f; fH = FLOAT(vp.Height)*.5f; 
	fD = FLOAT(vp.MaxZ) - FLOAT(vp.MinZ);  fX = FLOAT(vp.X) + fW; fY = FLOAT(vp.Y) + fH; 

	*pOut = D3DXMATRIX(
		fW, 0.f, 0, 0, 
		0.f, -fH, 0, 0, 
		0.f, 0.f, fD, 0, 
		fX, fY, fM, 1);
}


void Util::MouseRay(D3DXVECTOR3* pDir, D3DXVECTOR3* pOrig)
{
	// 마우스좌표
	POINT ptMouse = cCore::Input.CursorPos();

#ifdef VIEW_3D
	// Ray 광선을 계산한다.  
	// 2D 를 3D 좌표로 변경시킨다.  
	D3DXVECTOR3 vRay;  

	int nX  = ptMouse.x;  
	int nY  = ptMouse.y;  

	vRay.x  = (((2.0f * nX)/cCore::WinSize.x) - 1.0f)/cCore::Camera.GetPrj()._11;  
	vRay.y  = (((-2.0f * nY)/cCore::WinSize.y) + 1.0f)/cCore::Camera.GetPrj()._22;  
	vRay.z  = 1.0f;  

	// Ray의 원점과 방향을 결정한다.  
	*pOrig = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  
	*pDir  = D3DXVECTOR3(vRay.x,vRay.y,vRay.z);  

	// Ray를 뷰 행렬의 역행렬을 통해 월드 스페이스로 변환함  
	D3DXMATRIXA16   matView;  
	matView = cCore::Camera.GetView();

	D3DXMATRIXA16   matInverse; //  뷰 행렬의 역행렬  
	D3DXMatrixInverse(&matInverse,NULL,&matView);  

	// Ray에 뷰 행렬의 역행렬을 곱해서 월드 좌표로 변환한다.  
	D3DXVec3TransformCoord(pOrig, pOrig, &matInverse);  
	D3DXVec3TransformNormal(pDir, pDir, &matInverse);  

	// 정규화 한다.  
	D3DXVec3Normalize(pDir, pDir);  
#else
	D3DVIEWPORT9 VP;
	D3DXMATRIX PM, VM;

	D3DXMATRIX WorldMatrix;
	cCore::pd3dDevice->GetTransform(D3DTS_WORLD, &WorldMatrix);

	cCore::pd3dDevice->GetViewport(&VP);
	cCore::pd3dDevice->GetTransform(D3DTS_PROJECTION, &PM);
	cCore::pd3dDevice->GetTransform(D3DTS_VIEW, &VM);

	D3DXVec3Unproject(pOrig,&D3DXVECTOR3(static_cast<float>(ptMouse.x), static_cast<float>(ptMouse.y), 0.f)
		,&VP,&PM,&VM,&WorldMatrix); 
	D3DXVec3Unproject(pDir,&D3DXVECTOR3(static_cast<float>(ptMouse.x), static_cast<float>(ptMouse.y), 1.f)
		,&VP,&PM,&VM,&WorldMatrix); 
#endif
}


bool Util::IntersectTriangle(const D3DXVECTOR3& vDir, const D3DXVECTOR3& vOrig
							 , const D3DXVECTOR3& v0, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2
							 , FLOAT* t, FLOAT* u, FLOAT* v)
{
	// 변의 길이 계산  
	D3DXVECTOR3 e1  = v1 - v0;  
	D3DXVECTOR3 e2  = v2 - v0;  

	// u, v를 하기위해 계산을 한다.  
	// 만약 u라면,  
	// vDir과 e2를 외적한 것에 e1을 내적한다. 그 것을 역분하고, 거기에  
	// vDir과 e2를 외적한 것에 tVec을 내적한 것을 곱한다.  

	D3DXVECTOR3 pVec;  
	// 분모가 같은 놈이기 때문에 이렇게 판단한다.  
	D3DXVec3Cross(&pVec,&vDir,&e2);                 
	FLOAT   fDet    = D3DXVec3Dot(&e1,&pVec);  

	// fDet가지고 tVec을 구한다.  
	// tVec은 카메라 원점까지의 거리이다.  
	D3DXVECTOR3 tVec;  

	// 만약 내적 값이 0 보다 크면 앞에서 쏜 Ray이고, 0이면 같은 평면이고,   
	// 0 보다 작으면 뒤에서 쏜 Ray이다.  
	if(fDet > 0)  
	{  
		tVec    = vOrig - v0;  
	}  
	else if(fDet < 0)  
	{  
		tVec    = v0 - vOrig;  
		fDet    = -fDet;  
	}  

	// 0 으로 나눠주는 일이 없게 하려고  
	if(fDet < 0.0001f)  
	{  
		return FALSE;  
	}  

	// u 구하기  
	*u  = D3DXVec3Dot(&tVec,&pVec);  

	if(*u < 0.0f || *u > fDet)  
	{  
		return FALSE;  
	}  

	// v 구하기  
	D3DXVECTOR3 qVec;  
	D3DXVec3Cross(&qVec,&tVec,&e1);  

	*v  = D3DXVec3Dot(&vDir,&qVec);  

	if(*v < 0.0f || *u + *v > fDet)  
	{  
		return FALSE;  
	}  

	*t  = D3DXVec3Dot(&e2,&qVec);  
	FLOAT   fInvDet = 1.0f/fDet;  
	*t  *= fInvDet;  
	*u  *= fInvDet;  
	*v  *= fInvDet;  

	return TRUE;  
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::SetAlphaChannel(BOOL OnOff)
{
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, OnOff);
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, OnOff);
	/*
	알파테스트는 불투명/투명의 오직 두가지 상태만 가능하다는 치명적인 문제가 있다.
	*/
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::SetMatrixToDevice(D3DXVECTOR3* Position, D3DXVECTOR3* Rotation, D3DXVECTOR3* Scale)
{
	cCoord Coord;


	if(Position != NULL)
		Coord.SetPos(Position);
	if(Rotation != NULL)
		Coord.SetAngle(Rotation);
	if(Scale != NULL)
		Coord.SetScale(Scale);


	Coord.SetMatrixToDevice();
}


void Util::SetIdentityMatrix()
{
	D3DXMATRIX Mat;
	D3DXMatrixIdentity(&Mat);
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, &Mat);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::CalculateNormal(D3DXVECTOR3* pOut
						   , const D3DXVECTOR3* v0, const D3DXVECTOR3* v1, const D3DXVECTOR3* v2)
{
	D3DXVECTOR3 n;
	D3DXVECTOR3 A = *v2 - *v0;
	D3DXVECTOR3 B = *v1 - *v0;
	D3DXVec3Cross(&n, &A, &B);

	D3DXVec3Normalize(&n, &n);
	*pOut = n;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Util::DrawVtxByIdx(const cD3DVtxBuffer* pVtx, const cD3DIdxBuffer* pIdx)
{
	pVtx->SetVtxToDevice();
	pIdx->Draw();
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

Util::TempRenderState::TempRenderState(D3DRENDERSTATETYPE State, DWORD Value)
	: m_State(State)
	, m_oldValue(0UL)
{
	cCore::pd3dDevice->GetRenderState(State, &m_oldValue);	// 이전값 저장
	cCore::pd3dDevice->SetRenderState(State, Value);		// 값 변경
}


Util::TempRenderState::~TempRenderState()
{
	cCore::pd3dDevice->SetRenderState(m_State, m_oldValue); // 값 복구
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

Util::TempSamplerState::TempSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
	: m_Sampler(Sampler)
	, m_Type(Type)
	, m_oldValue(0UL)
{
	cCore::pd3dDevice->GetSamplerState(Sampler, Type, &m_oldValue);	// 이전값 저장
	cCore::pd3dDevice->SetSamplerState(Sampler, Type, Value);		// 값 변경
}


Util::TempSamplerState::~TempSamplerState()
{
	cCore::pd3dDevice->SetSamplerState(m_Sampler, m_Type, m_oldValue); // 값 복구
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

Util::TempOffCamera::TempOffCamera()
	: m_wasOn(cCore::Sprite.CameraOnCheck())
{
	cCore::Sprite.OffCamera();
}


Util::TempOffCamera::~TempOffCamera()
{
	if(m_wasOn) cCore::Sprite.OnCamera();
}

/*------------------------------------------------------------------------------------*/

const D3DXVECTOR2& Util::CenterPos()
{
	return cCore::CenterPos;
}


const POINT& Util::CenterPt()
{
	return cCore::CenterPt;
}

/*------------------------------------------------------------------------------------*/

ULONG Util::Rand()
{
	static ULONG State[16] = {
		rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand(),
		rand(), rand(), rand(), rand()
	};
	static UINT Index = 0;

	ULONG a, b, c, d;

	a = State[Index];
	c = State[(Index+13)&15];
	b = a^c^(a<<16)^(c<<15);
	c = State[(Index+9)&15];
	c ^= (c>>11);
	a = State[Index] = b^c;
	d = a^((a<<5)&0xDA442D20UL);
	Index = (Index + 15) & 15;
	a = State[Index];
	State[Index] = a^b^d^(a<<2)^(b<<18)^(c<<28);
	return State[Index];
}


bool Util::Probable(UINT Percent)
{
	return (Rand() % 100UL  <  Percent);
}


bool Util::Probable(double Percent)
{
	return (Rand() % 100000UL  <  Percent*1000.0);
}

/*------------------------------------------------------------------------------------*/

int Util::GetControlVector(D3DXVECTOR2* pOut, char UpKey, char DownKey, char LeftKey, char RightKey, float Speed)
{
	if(cCore::Input.KeyDown(UpKey)  ||  cCore::Input.KeyPress(UpKey))
	{
		pOut->y = -Speed;
	}
	else if(cCore::Input.KeyDown(DownKey)  ||  cCore::Input.KeyPress(DownKey))
	{
		pOut->y = +Speed;
	}
	else
	{
		pOut->y = 0.f;
	}

	if(cCore::Input.KeyDown(LeftKey)  ||  cCore::Input.KeyPress(LeftKey))
	{
		pOut->x = -Speed;
	}
	else if(cCore::Input.KeyDown(RightKey)  ||  cCore::Input.KeyPress(RightKey))
	{
		pOut->x = +Speed;
	}
	else
	{
		pOut->x = 0.f;
	}


	return 0;
}

/*------------------------------------------------------------------------------------*/

void Util::StrToWStr(const ::std::string& str, ::std::wstring* pOut)
{
	pOut->assign(str.begin(), str.end());
}


void Util::WStrToStr(const ::std::wstring& wStr, ::std::string* pOut)
{
	pOut->assign(wStr.begin(), wStr.end());
}


void Util::StrToWStr(const char str[], ::std::wstring* pOut)
{
	::std::string tempStr(str);

	pOut->assign(tempStr.begin(), tempStr.end());
}


void Util::WStrToStr(const wchar_t wStr[], ::std::string* pOut)
{
	::std::wstring tempWStr(wStr);

	pOut->assign(tempWStr.begin(), tempWStr.end());
}

