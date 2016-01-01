#include "cEngine.h"

#include <ctime>
#include <dwmapi.h>

#include "cCore.h"
#include "D3D/dxutil.h"
#include "cD3DDevice.h"
#include "cSqMgr.h"
#include "cSequence.h"
#include "cWorld.h"

#ifdef USE_COORDINATE
#include "cCoordinate.h"
#endif

#include "cRSLight.h"

#include "resource.h"


#pragma comment(lib, "dwmapi.lib")




































cEngine::cEngine()
	: m_pCore(NULL)
	, m_pD3DDevice(NULL)
	, m_pSqMgr(NULL)
	, m_bTransparent(false)
	, m_clearColor(D3DCOLOR_XRGB(19, 77, 91))

#ifdef USE_COORDINATE
	, m_pCoordinate(NULL)
#endif
#ifdef USE_RSLIGHT
	, m_pRSLight(NULL)
#endif

	, m_pWorld(new cWorld())
{
	srand(timeGetTime()); // 난수시드 초기화

	//

	m_pCore = new cCore; // 코어생성
	m_pD3DDevice = new cD3DDevice; // D3D생성
	m_pSqMgr = new cSqMgr; // 시퀀스매니저 생성

#ifdef USE_COORDINATE
	m_pCoordinate = new cCoordinate; // 좌표계 생성
#endif


	m_pCore->World = m_pWorld;
}


cEngine::~cEngine()
{
#ifdef USE_RSLIGHT
	SAFE_DELETE(m_pRSLight); // 광원제거
#endif

	SAFE_DELETE(m_pWorld);
}

/*-------------------------------------------------------------------------------------*/

int cEngine::Create(HINSTANCE hInst
					, std::string Name, int Width, int Height
					, LRESULT (CALLBACK *MsgProc) (HWND, UINT, WPARAM, LPARAM)
					, bool bWindowed
					, bool bTransparent)
{
	WCHAR* wName = new WCHAR[Name.size()+1];
	DXUtil_ConvertAnsiStringToWideCch(wName, Name.c_str(), Name.size()+1);


	/* 정보 복사 */
	m_Name = Name;
	m_bTransparent = bTransparent;


	// 클리어 색상
	if (bTransparent)
	{
		m_clearColor = 0x00000000;
	}


	// 화면 해상도
	m_pCore->WinSize.x = Width;
	m_pCore->WinSize.y = Height;

	m_pCore->fWinSize.x = static_cast<float>(Width);
	m_pCore->fWinSize.y = static_cast<float>(Height);


	/* 윈도우 생성 */
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, LoadCursor(NULL,IDC_ARROW), NULL, NULL,
		wName, NULL
	};
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // 아이콘 설정

	if (bTransparent)
	{
		wc.style = CS_HREDRAW | CS_VREDRAW;
	}
	
	m_Wc = wc;

	RegisterClassEx( &m_Wc );


	if(bWindowed)
	{
		DWORD WS = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

		if (bTransparent)
		{
			WS = WS_EX_TOPMOST | WS_POPUP;
		}


		RECT rc = {0, 0, Width, Height}; // 원하는 클라이언트 영역의 크기를 지정해준다.
		AdjustWindowRect(&rc, WS
			, FALSE); //클라이언트 영역의 크기를 저장


		m_hWnd = CreateWindow( wName, wName,
			WS
			, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
			NULL, NULL, m_Wc.hInstance, NULL );
	}
	else
	{
		m_hWnd = CreateWindow( wName, wName,
			WS_EX_TOPMOST | WS_POPUP, 0, 0, Width, Height,
			NULL, NULL, m_Wc.hInstance, NULL );
	}


	if (bTransparent)
	{
		SetWindowLong(m_hWnd, GWL_EXSTYLE, (int)GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 255, ULW_COLORKEY | LWA_ALPHA);
	}


	/* 보이기 */
	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hWnd );


	/* 코어 초기화 */
	InitCore(hInst);


	/* D3D 초기화 */
	m_pD3DDevice->Create(bWindowed, bTransparent);


	// 코어 초기화2
	m_pCore->Init(bWindowed);


	/* 시퀀스초기화 */
	m_pSqMgr->Init();


#ifdef USE_COORDINATE
	/* 좌표계 생성 */
	m_pCoordinate->Create(8.f);
#endif


	/* 월드 초기화 */
	m_pWorld->Init();


	/* 렌더링 설정 */
	RenderState();


	/* 타이머 작동 */
	DXUtil_Timer( TIMER_START );


	delete[] wName;
	return 0;
}


int cEngine::MsgLoop()
{
#ifndef USE_VFR
	DWORD previousFrameTime = timeGetTime();	//프레임레이트 고정용
#else
	const float DELAY_TIME = 0.0166666f;
	float ElapsedTime = 0.f;
#endif


	PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE);

	
	while(m_Msg.message != WM_QUIT)
	{
		if(PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_Msg);
			DispatchMessage(&m_Msg);
		}
		else
		{
#ifdef USE_VFR
			cCore::ElapsedTime = DXUtil_Timer( TIMER_GETELAPSEDTIME );
			cCore::FrameRate = cCore::ElapsedTime * 60.f; // 60고정프레임레이트처럼 값을 정할 수 있도록 해줌
#else
			previousFrameTime = timeGetTime();
#endif


			cCore::FrameMove();	// 코어정보 갱신
			
			m_pSqMgr->Update(); // 업데이트
			m_pWorld->Update(); // 월드 업데이트


			if(cCore::Exit) break; // 종료확인후 종료


#ifdef USE_VFR
			ElapsedTime += cCore::ElapsedTime;

			if(ElapsedTime >= DELAY_TIME)
			{
				ElapsedTime -= DELAY_TIME;;


				cCore::FrameMove_Limit();


				RenderLoop();		// 출력
			}
#else
			RenderLoop();		// 출력
#endif


#ifndef USE_VFR
			while(timeGetTime() - previousFrameTime < 16UL) Sleep(1UL);
#endif
		}
	}


	return 0;
}


int cEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	cCore::Input.MsgProc(msg, wParam, lParam);
	cCore::Resource.MsgProc(msg, wParam, lParam);

	if(msg==WM_KEYUP && wParam==VK_SNAPSHOT)
	{// 스크린샷
		Screenshot();	//Print screen
	}
	else if (m_bTransparent && msg == WM_PAINT)
	{
		const MARGINS margin = { 0, 0, cCore::WinSize.x, cCore::WinSize.y };
		DwmExtendFrameIntoClientArea(hWnd, &margin);
	}


	return 0;
}


WPARAM cEngine::CleanUp()
{
	WCHAR* wName = new WCHAR[m_Name.size()+1];
	DXUtil_ConvertAnsiStringToWideCch(wName, m_Name.c_str(), m_Name.size()+1);


#ifdef USE_COORDINATE
	/* 좌표계 제거 */
	SAFE_DELETE(m_pCoordinate);
#endif


	/* 월드 제거 */
	m_pWorld->Destroy();


	/* 코어+멤버제거 */
	m_pCore->CleanUp();


	if(m_pCore != NULL)
	{
		m_pCore->Release();
		delete m_pCore; // 코어제거
	}


	/* D3D 제거 */
	m_pD3DDevice->CleanUp();


	/* new한 메모리 delete */
	if(m_pSqMgr != NULL)
		delete m_pSqMgr; // 시퀀스매니저 제거
	if(m_pD3DDevice != NULL)
		delete m_pD3DDevice; // D3D제거


	/* 윈도우 종료 */
	UnregisterClass( wName, m_Wc.hInstance );

	delete[] wName;
	return m_Msg.wParam;
}

/*-------------------------------------------------------------------------------------*/

int cEngine::InitCore(HINSTANCE hInst)
{
	// 기본 핸들
	m_pCore->hWnd = m_hWnd;
	m_pCore->hInst = hInst;


	return 0;
}


int cEngine::Release()
{
	m_pSqMgr->Release();
	m_pCore->Release();


	return 0;
}


int cEngine::Restore()
{
	m_pSqMgr->Restore();
	m_pCore->Restore();

	RenderState(); // 디바이스가 리셋되었으므로 이전 디바이스에 설정한 렌더상태도 다시 설정해야한다


	return 0;
}


int cEngine::ResetDevice()
{
	Release(); // POOL_DEFAULT로 생성한 리소스 해제


	HRESULT Result = cCore::pd3dDevice->TestCooperativeLevel(); 

	while(Result == D3DERR_DEVICELOST) 
	{ 
		while(Result != D3DERR_DEVICENOTRESET) 
		{ 
			MSG msg; 
			Sleep(10); //잠시대기
			//1초간 정지했을 때를 위해 메시지 펌프 루틴을 넣는다. 
			PeekMessage(&msg, 0, 0, 0, PM_REMOVE); 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
			Result = cCore::pd3dDevice->TestCooperativeLevel(); // 상태를 다시 조사한다. 
		} 
		if(FAILED(cCore::pd3dDevice->Reset(m_pD3DDevice->pD3DPP()))) Result = D3DERR_DEVICELOST; 
		//Reset하고 에러 발생시 에러 코드를 설정한다. 
	} 


	Restore(); // 해제한 리소스 재로딩


	return 0;
}

/*-------------------------------------------------------------------------------------*/

int cEngine::RenderLoop()
{
	//백버퍼를 비움
	cCore::pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		, m_clearColor, 1.0f, 0 );


	if( SUCCEEDED( cCore::pd3dDevice->BeginScene() ) )
	{
		cCore::Camera.FrameMove(); // 카메라 행렬 설정


		m_pSqMgr->Render(); // 렌더


#ifdef USE_COORDINATE
		m_pCoordinate->Draw();
#endif


		m_pWorld->Render();


		cCore::MessageMgr.Render(); // 메세지


		cCore::Log.ShowLog(); // 로그


		cCore::pd3dDevice->EndScene();
	}


	//Present하고 디바이스소실이 일어났는지 검사.
	if( cCore::pd3dDevice->Present( NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST )
		ResetDevice();


	return 0;
}


int cEngine::RenderState()
{// 렌더링 옵션 설정
#ifdef USE_RSLIGHT
	/* 광원 설정 */
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;									// 광원의 종류
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	//light.Specular  = D3DXCOLOR(1,1,1,1) * 0.3f;  // 정반사광 색상
	//light.Ambient   = D3DXCOLOR(1,1,1,1) * 0.6f;  // 환경광 색상
#ifdef VIEW_3D
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f );
#else
	vecDir = D3DXVECTOR3(1.0f, -2.0f, 3.0f );
#endif
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range       = 1024.0f;												// 광원의 효과가 미치는 거리
	
	m_pRSLight = new cRSLight(light);

	cCore::pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE );					// 광원 설정을 켠다.
	cCore::pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x000F0F0F);				// 엠비언트 광의 색상을 설정한다.
#endif


	/* 안티엘리어싱 */
	cCore::pd3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	cCore::pd3dDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE); 


	/* 알파채널 준비 */
	cCore::pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 
	cCore::pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	/* 안개 */
	DWORD dFog    = D3DXCOLOR(0.2f, 1.f, 0.7f, 1.0f);
	float fStart  = 300.0f;
	float fEnd    = 700.0f;
	float fDens   = 0.0015f;

	cCore::pd3dDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); // 안개 활성화

	cCore::pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE); // 픽셀포그 막음
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // 선형포그 적용

	cCore::pd3dDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGCOLOR, dFog);
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&fStart)));
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGEND, FtoDW(fEnd));
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGDENSITY, FtoDW(fDens));


	return 0;
}

/*-------------------------------------------------------------------------------------*/

HRESULT cEngine::Screenshot()
{
	LPDIRECT3DSURFACE9 pBackBuffer;


	HRESULT hr = cCore::pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);


	if( SUCCEEDED(hr) )
	{
		char str[256];
		time_t ctime;
		time(&ctime);

		sprintf_s(str, 256, "Screenshot/Screenshot_%lld.png", ctime);

		WCHAR* wFontName = new WCHAR[strlen(str)+1];
		DXUtil_ConvertAnsiStringToWideCch(wFontName, str, strlen(str)+1);

		D3DXSaveSurfaceToFile(wFontName, D3DXIFF_PNG, pBackBuffer, NULL, NULL);

		pBackBuffer->Release();
		delete[] wFontName;
	}


	return hr;
}

