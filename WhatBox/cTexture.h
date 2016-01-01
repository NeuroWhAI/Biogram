#pragma once
#include <d3dx9.h>
#include <string>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 텍스쳐
// Desc : D3D텍스쳐를 사용해 여러포맷의 이미지파일을 불러오고 그 이미지의 정보를 알려준다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTexture
{
public:
	cTexture();
	~cTexture();


private:
	LPDIRECT3DTEXTURE9 m_Tx;					// 텍스쳐
	D3DXIMAGE_INFO	m_pImgInf;					//텍스쳐 정보

	D3DLOCKED_RECT m_LockRt;
	DWORD* m_LockRect;


public:
	int LoadTexture(std::string File);
	int SetTexture(LPDIRECT3DTEXTURE9 pTx);
	int Release();


public:
	DWORD* Lock();
	void Unlock();

	DWORD* AccessToPixel(int x, int y);

	HRESULT SetTextureToDevice(DWORD Stage);
	LPDIRECT3DTEXTURE9 GetTexture();
	const LPDIRECT3DTEXTURE9 GetTexture() const;
	int Width() const;
	int Height() const;
	D3DXVECTOR2 Size() const;
	D3DXVECTOR2 CenterPos() const;


public: /* 텍스쳐합성 */
	int SetMultiTxToDevice(int Stage, cTexture* pTx2, _D3DTEXTUREOP Op);
	int SetMultiTxToDevice(int Stage, LPDIRECT3DTEXTURE9 pTx2, _D3DTEXTUREOP Op);
};

