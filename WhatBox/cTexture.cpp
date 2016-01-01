#include "cTexture.h"

#include "cCore.h"
#include "D3D/dxutil.h"





















cTexture::cTexture()
	: m_Tx(NULL)
{

}


cTexture::~cTexture()
{
	Release();
}

/*------------------------------------------------------------------------------------*/

int cTexture::LoadTexture(std::string File)
{
	D3DXIMAGE_INFO info;


	WCHAR* wMsg = new WCHAR[File.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wMsg, File.c_str(), 1+static_cast<int>(File.size()));

	D3DXGetImageInfoFromFile(wMsg, &info);


	//텍스쳐 생성
	if(FAILED(D3DXCreateTextureFromFileEx(cCore::pd3dDevice, wMsg, info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, 0x00000000, &m_pImgInf, NULL, &m_Tx)))
	{
		delete[] wMsg;
		std::string s = "Load -> " + File;
		return Util::ErrorMessage(s);
	}


	delete[] wMsg;
	return 0;
}


int cTexture::SetTexture(LPDIRECT3DTEXTURE9 pTx)
{
	m_Tx = pTx;

	D3DSURFACE_DESC desc;
	m_Tx->GetLevelDesc(0, &desc);

	m_pImgInf.Width = desc.Width;
	m_pImgInf.Height = desc.Height;
	m_pImgInf.Format = desc.Format;
	m_pImgInf.ResourceType = desc.Type;


	return 0;
}


int cTexture::Release()
{
	if(m_Tx != NULL)
	{
		m_Tx->Release();
		m_Tx = NULL;
	}
	

	return 0;
}

/*------------------------------------------------------------------------------------*/

DWORD* cTexture::Lock()
{
	m_Tx->LockRect(0, &m_LockRt, NULL, D3DLOCK_DISCARD);
	return (m_LockRect = static_cast<DWORD*>(m_LockRt.pBits));
}


void cTexture::Unlock()
{
	m_Tx->UnlockRect(0);
}


DWORD* cTexture::AccessToPixel(int x, int y)
{
	return &m_LockRect[y * m_LockRt.Pitch/4 + x];
}

/*------------------------------------------------------------------------------------*/

HRESULT cTexture::SetTextureToDevice(DWORD Stage)
{
	cCore::pd3dDevice->SetSamplerState(Stage, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// 확대필터를 적용하지 않으면 리소스 재로드후에 계단현상이 발생한다
	return cCore::pd3dDevice->SetTexture(Stage, m_Tx);
}


LPDIRECT3DTEXTURE9 cTexture::GetTexture()
{
	return m_Tx;
}


const LPDIRECT3DTEXTURE9 cTexture::GetTexture() const
{
	return m_Tx;
}


int cTexture::Width() const
{
	return m_pImgInf.Width;
}


int cTexture::Height() const
{
	return m_pImgInf.Height;
}


D3DXVECTOR2 cTexture::Size() const
{
	return D3DXVECTOR2(CAST(m_pImgInf.Width, float), CAST(m_pImgInf.Height, float));
}


D3DXVECTOR2 cTexture::CenterPos() const
{
	return D3DXVECTOR2(CAST(m_pImgInf.Width, float) / 2.f, CAST(m_pImgInf.Height, float) / 2.f);
}

/*------------------------------------------------------------------------------------*/

int cTexture::SetMultiTxToDevice(int Stage, cTexture* pTx2, _D3DTEXTUREOP Op)
{
	SetTextureToDevice(Stage);
	pTx2->SetTextureToDevice(Stage+1);

	cCore::pd3dDevice->SetTextureStageState( Stage, D3DTSS_TEXCOORDINDEX, 0 );
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_TEXCOORDINDEX, 0 );

	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLORARG1, D3DTA_CURRENT ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLORARG2, D3DTA_TEXTURE ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLOROP, Op ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+2, D3DTSS_COLOROP, D3DTOP_DISABLE );


	return 0;
}


int cTexture::SetMultiTxToDevice(int Stage, LPDIRECT3DTEXTURE9 pTx2, _D3DTEXTUREOP Op)
{
	SetTextureToDevice(Stage);
	cCore::pd3dDevice->SetSamplerState(Stage+1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	cCore::pd3dDevice->SetTexture(Stage+1, pTx2);

	cCore::pd3dDevice->SetTextureStageState( Stage, D3DTSS_TEXCOORDINDEX, 0 );
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_TEXCOORDINDEX, 0 );

	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLORARG1, D3DTA_CURRENT ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLORARG2, D3DTA_TEXTURE ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+1, D3DTSS_COLOROP, Op ); 
	cCore::pd3dDevice->SetTextureStageState( Stage+2, D3DTSS_COLOROP, D3DTOP_DISABLE );


	return 0;
}

