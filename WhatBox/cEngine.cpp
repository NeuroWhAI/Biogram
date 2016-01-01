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
	srand(timeGetTime()); // �����õ� �ʱ�ȭ

	//

	m_pCore = new cCore; // �ھ����
	m_pD3DDevice = new cD3DDevice; // D3D����
	m_pSqMgr = new cSqMgr; // �������Ŵ��� ����

#ifdef USE_COORDINATE
	m_pCoordinate = new cCoordinate; // ��ǥ�� ����
#endif


	m_pCore->World = m_pWorld;
}


cEngine::~cEngine()
{
#ifdef USE_RSLIGHT
	SAFE_DELETE(m_pRSLight); // ��������
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


	/* ���� ���� */
	m_Name = Name;
	m_bTransparent = bTransparent;


	// Ŭ���� ����
	if (bTransparent)
	{
		m_clearColor = 0x00000000;
	}


	// ȭ�� �ػ�
	m_pCore->WinSize.x = Width;
	m_pCore->WinSize.y = Height;

	m_pCore->fWinSize.x = static_cast<float>(Width);
	m_pCore->fWinSize.y = static_cast<float>(Height);


	/* ������ ���� */
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, LoadCursor(NULL,IDC_ARROW), NULL, NULL,
		wName, NULL
	};
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ������ ����

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


		RECT rc = {0, 0, Width, Height}; // ���ϴ� Ŭ���̾�Ʈ ������ ũ�⸦ �������ش�.
		AdjustWindowRect(&rc, WS
			, FALSE); //Ŭ���̾�Ʈ ������ ũ�⸦ ����


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


	/* ���̱� */
	ShowWindow( m_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( m_hWnd );


	/* �ھ� �ʱ�ȭ */
	InitCore(hInst);


	/* D3D �ʱ�ȭ */
	m_pD3DDevice->Create(bWindowed, bTransparent);


	// �ھ� �ʱ�ȭ2
	m_pCore->Init(bWindowed);


	/* �������ʱ�ȭ */
	m_pSqMgr->Init();


#ifdef USE_COORDINATE
	/* ��ǥ�� ���� */
	m_pCoordinate->Create(8.f);
#endif


	/* ���� �ʱ�ȭ */
	m_pWorld->Init();


	/* ������ ���� */
	RenderState();


	/* Ÿ�̸� �۵� */
	DXUtil_Timer( TIMER_START );


	delete[] wName;
	return 0;
}


int cEngine::MsgLoop()
{
#ifndef USE_VFR
	DWORD previousFrameTime = timeGetTime();	//�����ӷ���Ʈ ������
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
			cCore::FrameRate = cCore::ElapsedTime * 60.f; // 60���������ӷ���Ʈó�� ���� ���� �� �ֵ��� ����
#else
			previousFrameTime = timeGetTime();
#endif


			cCore::FrameMove();	// �ھ����� ����
			
			m_pSqMgr->Update(); // ������Ʈ
			m_pWorld->Update(); // ���� ������Ʈ


			if(cCore::Exit) break; // ����Ȯ���� ����


#ifdef USE_VFR
			ElapsedTime += cCore::ElapsedTime;

			if(ElapsedTime >= DELAY_TIME)
			{
				ElapsedTime -= DELAY_TIME;;


				cCore::FrameMove_Limit();


				RenderLoop();		// ���
			}
#else
			RenderLoop();		// ���
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
	{// ��ũ����
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
	/* ��ǥ�� ���� */
	SAFE_DELETE(m_pCoordinate);
#endif


	/* ���� ���� */
	m_pWorld->Destroy();


	/* �ھ�+������� */
	m_pCore->CleanUp();


	if(m_pCore != NULL)
	{
		m_pCore->Release();
		delete m_pCore; // �ھ�����
	}


	/* D3D ���� */
	m_pD3DDevice->CleanUp();


	/* new�� �޸� delete */
	if(m_pSqMgr != NULL)
		delete m_pSqMgr; // �������Ŵ��� ����
	if(m_pD3DDevice != NULL)
		delete m_pD3DDevice; // D3D����


	/* ������ ���� */
	UnregisterClass( wName, m_Wc.hInstance );

	delete[] wName;
	return m_Msg.wParam;
}

/*-------------------------------------------------------------------------------------*/

int cEngine::InitCore(HINSTANCE hInst)
{
	// �⺻ �ڵ�
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

	RenderState(); // ����̽��� ���µǾ����Ƿ� ���� ����̽��� ������ �������µ� �ٽ� �����ؾ��Ѵ�


	return 0;
}


int cEngine::ResetDevice()
{
	Release(); // POOL_DEFAULT�� ������ ���ҽ� ����


	HRESULT Result = cCore::pd3dDevice->TestCooperativeLevel(); 

	while(Result == D3DERR_DEVICELOST) 
	{ 
		while(Result != D3DERR_DEVICENOTRESET) 
		{ 
			MSG msg; 
			Sleep(10); //��ô��
			//1�ʰ� �������� ���� ���� �޽��� ���� ��ƾ�� �ִ´�. 
			PeekMessage(&msg, 0, 0, 0, PM_REMOVE); 
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
			Result = cCore::pd3dDevice->TestCooperativeLevel(); // ���¸� �ٽ� �����Ѵ�. 
		} 
		if(FAILED(cCore::pd3dDevice->Reset(m_pD3DDevice->pD3DPP()))) Result = D3DERR_DEVICELOST; 
		//Reset�ϰ� ���� �߻��� ���� �ڵ带 �����Ѵ�. 
	} 


	Restore(); // ������ ���ҽ� ��ε�


	return 0;
}

/*-------------------------------------------------------------------------------------*/

int cEngine::RenderLoop()
{
	//����۸� ���
	cCore::pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		, m_clearColor, 1.0f, 0 );


	if( SUCCEEDED( cCore::pd3dDevice->BeginScene() ) )
	{
		cCore::Camera.FrameMove(); // ī�޶� ��� ����


		m_pSqMgr->Render(); // ����


#ifdef USE_COORDINATE
		m_pCoordinate->Draw();
#endif


		m_pWorld->Render();


		cCore::MessageMgr.Render(); // �޼���


		cCore::Log.ShowLog(); // �α�


		cCore::pd3dDevice->EndScene();
	}


	//Present�ϰ� ����̽��ҽ��� �Ͼ���� �˻�.
	if( cCore::pd3dDevice->Present( NULL, NULL, NULL, NULL ) == D3DERR_DEVICELOST )
		ResetDevice();


	return 0;
}


int cEngine::RenderState()
{// ������ �ɼ� ����
#ifdef USE_RSLIGHT
	/* ���� ���� */
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;									// ������ ����
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	//light.Specular  = D3DXCOLOR(1,1,1,1) * 0.3f;  // ���ݻ籤 ����
	//light.Ambient   = D3DXCOLOR(1,1,1,1) * 0.6f;  // ȯ�汤 ����
#ifdef VIEW_3D
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f );
#else
	vecDir = D3DXVECTOR3(1.0f, -2.0f, 3.0f );
#endif
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
	light.Range       = 1024.0f;												// ������ ȿ���� ��ġ�� �Ÿ�
	
	m_pRSLight = new cRSLight(light);

	cCore::pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE );					// ���� ������ �Ҵ�.
	cCore::pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x000F0F0F);				// �����Ʈ ���� ������ �����Ѵ�.
#endif


	/* ��Ƽ������� */
	cCore::pd3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	cCore::pd3dDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE); 


	/* ����ä�� �غ� */
	cCore::pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 
	cCore::pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	cCore::pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	/* �Ȱ� */
	DWORD dFog    = D3DXCOLOR(0.2f, 1.f, 0.7f, 1.0f);
	float fStart  = 300.0f;
	float fEnd    = 700.0f;
	float fDens   = 0.0015f;

	cCore::pd3dDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); // �Ȱ� Ȱ��ȭ

	cCore::pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_NONE); // �ȼ����� ����
	cCore::pd3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR); // �������� ����

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

