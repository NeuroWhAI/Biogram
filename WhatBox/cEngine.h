#pragma once
#include <Windows.h>
#include <string>

#include "Option.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

class cCore;
class cD3DDevice;
class cSqMgr;
class cWorld;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
#ifdef USE_COORDINATE
class cCoordinate;
#endif

class cRSLight;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/













///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 프로그램엔진
// Desc : 프로그램의 시작부터 종료까지의 모든것을 진행한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cEngine
{
public:
	cEngine();
	~cEngine();


private: /* 기본 윈도우 관련 */
	HWND m_hWnd;
	std::string m_Name;

	WNDCLASSEX m_Wc;
	MSG m_Msg;

	bool m_bTransparent;
	DWORD m_clearColor;


private: /* 중앙코어 */
	cCore* m_pCore;

private: /* D3D */
	cD3DDevice* m_pD3DDevice;
#ifdef USE_COORDINATE
	cCoordinate* m_pCoordinate;			// 좌표계
#endif
#ifdef USE_RSLIGHT
	cRSLight* m_pRSLight;				// D3DRS_LIGHTING
#endif


private: /* 시퀀스 */
	cSqMgr* m_pSqMgr;

public: /* 주 함수 */
	int Create(HINSTANCE hInst
		, std::string Name, int Width, int Height
		, LRESULT (CALLBACK *MsgProc) (HWND, UINT, WPARAM, LPARAM)
		, bool bWindowed
		, bool bTransparent = false);
	int MsgLoop();
	int MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	WPARAM CleanUp();


private: /* 게임 */
	cWorld* m_pWorld;


private:
	int InitCore(HINSTANCE hInst); // 코어초기화

	int Release();
	int Restore();
	int ResetDevice(); // 디바이스복구


private:
	int RenderLoop(); // Render루프
	int RenderState();// D3D SetRenderState


private: /* 유틸 */
	HRESULT Screenshot();
};

