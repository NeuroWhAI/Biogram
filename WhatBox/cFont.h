#pragma once
#include <d3dx9.h>
#include <string>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D��Ʈ
// Desc : DirectX���� �����ϴ� FontŬ������ ����� 2D���ڸ� ����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFont
{
public:
	cFont();
	~cFont();


private:
	LPD3DXFONT m_pFont;

	std::string m_FontName;
	POINT m_Size;


public:
	void SetFont(std::string FontName, int Width, int Height);
	void Release();
	void Restore();


public:
	int ShowText(std::string Str, int x, int y, D3DXCOLOR Color, DWORD dt=0x00000000);
	int ShowText(std::wstring Str, int x, int y, D3DXCOLOR Color, DWORD dt=0x00000000);

	int ShowText(std::string Str, float x, float y, D3DXCOLOR Color, DWORD dt=0x00000000);
	int ShowText(std::wstring Str, float x, float y, D3DXCOLOR Color, DWORD dt=0x00000000);


public:
	SIZE GetStringSize(std::wstring Str);
	SIZE GetStringSize(const std::wstring* Str);
};

