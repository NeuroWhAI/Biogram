#pragma once
#include <d3dx9.h>
#include <string>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �ؽ���
// Desc : D3D�ؽ��ĸ� ����� ���������� �̹��������� �ҷ����� �� �̹����� ������ �˷��ش�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTexture
{
public:
	cTexture();
	~cTexture();


private:
	LPDIRECT3DTEXTURE9 m_Tx;					// �ؽ���
	D3DXIMAGE_INFO	m_pImgInf;					//�ؽ��� ����

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


public: /* �ؽ����ռ� */
	int SetMultiTxToDevice(int Stage, cTexture* pTx2, _D3DTEXTUREOP Op);
	int SetMultiTxToDevice(int Stage, LPDIRECT3DTEXTURE9 pTx2, _D3DTEXTUREOP Op);
};

