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
// Name : 프로그램 중앙코어
// Desc : static멤버를 사용해서 어디서나 프로그램 주요정보에 접근할 수 있게한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cCore
{
public:
	cCore();
	~cCore();
private:
	cCore(cCore&) {}


public: /* 기본 윈도우/루프 */
	static HWND hWnd;
	static HINSTANCE hInst;
	
	static POINT WinSize;					// 윈도우 크기
	static D3DXVECTOR2 fWinSize;			// 윈도우 크기

	static bool Exit;						// 윈도우 종료
#ifdef USE_VFR
	static float FrameRate;					// 프레임레이트(아래보다 몇배 더 큰값)
	static float ElapsedTime;				// 프레임레이트(이전프레임과 현재프레임의 시간차)
#endif


public: /* D3D */
	static LPDIRECT3DDEVICE9 pd3dDevice;	// D3D 디바이스
	static cCamera Camera;					// 카메라
	static cSprite Sprite;					// D3D 스프라이트
	static cD3DSound Sound;					// D3D 사운드


public: /* 인터페이스 */
	 static cInput Input;
	 static c2DCamera Camera2D;				// 2D 카메라
	 static cMessageMgr MessageMgr;			// 메세지 매니저


public: /* 리소스 */
	static cResource Resource;				// 리소스(텍스쳐, 음악 등)
	static cD3DAudio D3DAudio;				// 3D사운드 믹서
	static cFXMgr FxMgr;					// 특수효과 관리자


public: /* 자주쓰는 정보 */
	static D3DXVECTOR2 CenterPos;			// 중앙좌표
	static POINT CenterPt;					// 중앙좌표
	
	static D3DXMATRIX BillboardMt;			// 빌보드 행렬


public: /* 디버깅 */
	static cLog Log;						// 로그


public: /* 수학 */
	static cShapeMath ShapeMath;			// 도형 수학
	static cValueProcMgr ValueAnimator;		// 값 진행자


public: /* 게임 */
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

