#include "cCore.h"













/*---------------------------------------------------------------------------------*/

HWND cCore::hWnd = NULL;
HINSTANCE cCore::hInst = NULL;

POINT cCore::WinSize = {0, 0};
D3DXVECTOR2 cCore::fWinSize(0.f, 0.f);

bool cCore::Exit = false;

#ifdef USE_VFR
float cCore::FrameRate = 1.f;
float cCore::ElapsedTime = 1.f;
#endif
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
LPDIRECT3DDEVICE9 cCore::pd3dDevice = NULL;
cCamera cCore::Camera;
cSprite cCore::Sprite;
cD3DSound cCore::Sound;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
cInput cCore::Input;
c2DCamera cCore::Camera2D;
cMessageMgr cCore::MessageMgr;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
cResource cCore::Resource;
cD3DAudio cCore::D3DAudio;
cFXMgr cCore::FxMgr;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
D3DXVECTOR2 cCore::CenterPos;
POINT cCore::CenterPt;

D3DXMATRIX cCore::BillboardMt;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
cLog cCore::Log;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
cShapeMath cCore::ShapeMath;
cValueProcMgr cCore::ValueAnimator;
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
cWorld* cCore::World = NULL;

/*---------------------------------------------------------------------------------*/

cCore::cCore()
{

}


cCore::~cCore()
{

}

/*---------------------------------------------------------------------------------*/

int cCore::Init(bool bWindowed)
{
	Resource.Load();
	Sprite.Create();
	Sound.Create();

	// 좌표 구하기
	if(!bWindowed)
	{
		WinSize.x = GetSystemMetrics(SM_CXSCREEN);
		WinSize.y = GetSystemMetrics(SM_CYSCREEN);

		fWinSize.x = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
		fWinSize.y = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));
	}

	CenterPt.x = WinSize.x>>1;
	CenterPt.y = WinSize.y>>1;

	CenterPos.x = static_cast<float>(CenterPt.x);
	CenterPos.y = static_cast<float>(CenterPt.y);


	return 0;
}


int cCore::FrameMove()
{
	// 입력상태 갱신
	Input.FrameMove();


	// 2D카메라 움직임
	Camera2D.FrameMove();


	// 프레임마다 갱신이 필요한 리소스들을 위함
	Resource.FrameMove();


	// 빌보드 행렬 구함
	D3DXMatrixIdentity(&BillboardMt);

	D3DXMATRIX View = cCore::Camera.GetView();

	BillboardMt._11 = View._11;
	BillboardMt._13 = View._13;
	BillboardMt._31 = View._31;
	BillboardMt._33 = View._33;

	D3DXMatrixInverse(&BillboardMt, NULL, &BillboardMt);
	
	
	// 로그 토글
	if(Input.KeyDown(VK_OEM_3/* '`' */))
		Log.Toggle();


	// 푸시메세지
	MessageMgr.Update();


	// 값 진행자
	ValueAnimator.FrameMove();


	return 0;
}


int cCore::FrameMove_Limit()
{
	Input.FrameMove_Limit();


	return 0;
}


int cCore::Release()
{// 화면복구용
	Resource.Release();
	Sprite.CleanUp();


	return 0;
}


int cCore::Restore()
{// 화면복구용
	Resource.Restore();
	Sprite.Create();


	return 0;
}


int cCore::CleanUp()
{/* 프로그램종료시 호출 */
	Resource.CleanUp(); // 리소스는 스프라이트, 사운드객체등에 의해 생성되므로 먼저 해제한다
	Sprite.CleanUp();
	Sound.Release();

	
	return 0;
}

/*---------------------------------------------------------------------------------*/

void cCore::ExitProgram()
{
	Exit = true;
}

