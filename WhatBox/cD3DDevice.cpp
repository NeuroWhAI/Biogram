#include "cD3DDevice.h"

#include "cCore.h"





















cD3DDevice::cD3DDevice()
	: m_pD3D(NULL)
	, m_pd3dDevice(NULL)
{

}


cD3DDevice::~cD3DDevice()
{
	CleanUp();
}

/*-----------------------------------------------------------------------------------*/

int cD3DDevice::Create(bool bWindowed, bool bTransparent)
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return Util::ErrorMessage("Direct3DCreate9()");


	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return Util::ErrorMessage("GetAdapterDisplayMode()");


	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));

	m_d3dpp.Windowed = TRUE;//(bWindowed ? TRUE : FALSE); // FIX: 이렇게하면 전체화면같은 창모드가 가능하다.
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.BackBufferFormat = (bTransparent ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8);
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dpp.PresentationInterval = D3DPRESENT_DONOTWAIT;//D3DPRESENT_INTERVAL_IMMEDIATE; // FIX: 이게 없어야 프레임이 60으로 고정됨

	if (bTransparent == false)
	{
		m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		m_d3dpp.BackBufferFormat = d3ddm.Format;
	}

	m_d3dpp.BackBufferWidth = cCore::WinSize.x;
	m_d3dpp.BackBufferHeight = cCore::WinSize.y;


	//풀 신 안티 체크
	DWORD level;

	for(int i=D3DMULTISAMPLE_8_SAMPLES; i>=D3DMULTISAMPLE_2_SAMPLES; i--)
	{
		if( SUCCEEDED(m_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, D3DFMT_D24S8, FALSE, (D3DMULTISAMPLE_TYPE)i, &level)) )
		{
			m_d3dpp.MultiSampleQuality = level-1;
			m_d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)i;

			break;
		}
	}
	

	//디바이스 생성
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, cCore::hWnd,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&m_d3dpp, &m_pd3dDevice ) ) )
	{//D3DCREATE_MIXED_VERTEXPROCESSING을 지원하지 않음
		if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, cCore::hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp, &m_pd3dDevice ) ) )
		{
			m_pD3D->Release(); m_pD3D = NULL;
			return Util::ErrorMessage("CreateDevice()");
		}
	}


	D3DCAPS9 d3dCaps;
	m_pd3dDevice->GetDeviceCaps(&d3dCaps);

	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, d3dCaps.MaxAnisotropy);


	return InitCore(); // 코어 초기화
}


int cD3DDevice::CleanUp()
{
	if( m_pd3dDevice != NULL )
	{
		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}

	if( m_pD3D != NULL )
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}


	return 0;
}

/*-----------------------------------------------------------------------------------*/

int cD3DDevice::InitCore()
{
	cCore::pd3dDevice = m_pd3dDevice;


	return 0;
}

/*-----------------------------------------------------------------------------------*/

D3DPRESENT_PARAMETERS* cD3DDevice::pD3DPP()
{
	return &m_d3dpp;
}


const D3DPRESENT_PARAMETERS* cD3DDevice::pD3DPP() const
{
	return &m_d3dpp;
}

