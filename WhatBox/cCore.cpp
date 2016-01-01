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

	// ��ǥ ���ϱ�
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
	// �Է»��� ����
	Input.FrameMove();


	// 2Dī�޶� ������
	Camera2D.FrameMove();


	// �����Ӹ��� ������ �ʿ��� ���ҽ����� ����
	Resource.FrameMove();


	// ������ ��� ����
	D3DXMatrixIdentity(&BillboardMt);

	D3DXMATRIX View = cCore::Camera.GetView();

	BillboardMt._11 = View._11;
	BillboardMt._13 = View._13;
	BillboardMt._31 = View._31;
	BillboardMt._33 = View._33;

	D3DXMatrixInverse(&BillboardMt, NULL, &BillboardMt);
	
	
	// �α� ���
	if(Input.KeyDown(VK_OEM_3/* '`' */))
		Log.Toggle();


	// Ǫ�ø޼���
	MessageMgr.Update();


	// �� ������
	ValueAnimator.FrameMove();


	return 0;
}


int cCore::FrameMove_Limit()
{
	Input.FrameMove_Limit();


	return 0;
}


int cCore::Release()
{// ȭ�麹����
	Resource.Release();
	Sprite.CleanUp();


	return 0;
}


int cCore::Restore()
{// ȭ�麹����
	Resource.Restore();
	Sprite.Create();


	return 0;
}


int cCore::CleanUp()
{/* ���α׷������ ȣ�� */
	Resource.CleanUp(); // ���ҽ��� ��������Ʈ, ���尴ü� ���� �����ǹǷ� ���� �����Ѵ�
	Sprite.CleanUp();
	Sound.Release();

	
	return 0;
}

/*---------------------------------------------------------------------------------*/

void cCore::ExitProgram()
{
	Exit = true;
}

