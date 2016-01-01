#pragma once
#include <Windows.h>
#include <d3dx9.h>

#include "Option.h"
#include "Util.h"

#include "cCamera.h"
#include "cInput.h"
#include "cResource.h"
#include "cSprite.h"
#include "cD3DSound.h"
#include "cLog.h"
#include "cD3DAudio.h"
#include "cShapeMath.h"
#include "c2DCamera.h"
#include "cWorld.h"
#include "cLayer_Fade.h"
#include "cLayer_UI.h"
#include "cLayer_Effect.h"
#include "cLayer_Unit.h"
#include "cLayer_Back.h"
#include "cMessageMgr.h"
#include "cValueProcMgr.h"
#include "cFXMgr.h"














///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���α׷� �߾��ھ�
// Desc : static����� ����ؼ� ��𼭳� ���α׷� �ֿ������� ������ �� �ְ��Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cCore
{
public:
	cCore();
	~cCore();
private:
	cCore(cCore&) {}


public: /* �⺻ ������/���� */
	static HWND hWnd;
	static HINSTANCE hInst;
	
	static POINT WinSize;					// ������ ũ��
	static D3DXVECTOR2 fWinSize;			// ������ ũ��

	static bool Exit;						// ������ ����
#ifdef USE_VFR
	static float FrameRate;					// �����ӷ���Ʈ(�Ʒ����� ��� �� ū��)
	static float ElapsedTime;				// �����ӷ���Ʈ(���������Ӱ� ������������ �ð���)
#endif


public: /* D3D */
	static LPDIRECT3DDEVICE9 pd3dDevice;	// D3D ����̽�
	static cCamera Camera;					// ī�޶�
	static cSprite Sprite;					// D3D ��������Ʈ
	static cD3DSound Sound;					// D3D ����


public: /* �������̽� */
	 static cInput Input;
	 static c2DCamera Camera2D;				// 2D ī�޶�
	 static cMessageMgr MessageMgr;			// �޼��� �Ŵ���


public: /* ���ҽ� */
	static cResource Resource;				// ���ҽ�(�ؽ���, ���� ��)
	static cD3DAudio D3DAudio;				// 3D���� �ͼ�
	static cFXMgr FxMgr;					// Ư��ȿ�� ������


public: /* ���־��� ���� */
	static D3DXVECTOR2 CenterPos;			// �߾���ǥ
	static POINT CenterPt;					// �߾���ǥ
	
	static D3DXMATRIX BillboardMt;			// ������ ���


public: /* ����� */
	static cLog Log;						// �α�


public: /* ���� */
	static cShapeMath ShapeMath;			// ���� ����
	static cValueProcMgr ValueAnimator;		// �� ������


public: /* ���� */
	static cWorld* World;


public:
	static int Init(bool bWindowed);
	static int FrameMove();
	static int FrameMove_Limit();

	static int Release();
	static int Restore();

	static int CleanUp();


public:
	static void ExitProgram();
};

