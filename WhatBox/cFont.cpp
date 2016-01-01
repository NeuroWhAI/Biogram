#include "cFont.h"

#include "cCore.h"
#include "D3D/dxutil.h"



















cFont::cFont()
	: m_pFont(NULL)
{

}


cFont::~cFont()
{
	Release();
}

/*--------------------------------------------------------------------------------------*/

void cFont::SetFont(std::string FontName, int Width, int Height)
{
	WCHAR* wFontName = new WCHAR[FontName.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wFontName, FontName.c_str(), FontName.size()+1);


	m_FontName = FontName;

	m_Size.x = Width;
	m_Size.y = Height;

	D3DXCreateFont( cCore::pd3dDevice, Height, Width, 1000, 1, false
		, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY
		, 0, wFontName, &m_pFont );

	delete[] wFontName;
}


void cFont::Release()
{
	if(m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}


void cFont::Restore()
{
	WCHAR* wFontName = new WCHAR[m_FontName.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wFontName, m_FontName.c_str(), m_FontName.size()+1);


	D3DXCreateFont( cCore::pd3dDevice, m_Size.y, m_Size.x, 1000, 1, false
		, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY
		, 0, wFontName, &m_pFont );


	delete[] wFontName;
}

/*--------------------------------------------------------------------------------------*/

int cFont::ShowText(std::string Str, int x, int y, D3DXCOLOR Color, DWORD dt)
{
	WCHAR* wFontName = new WCHAR[Str.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wFontName, Str.c_str(), Str.size()+1);


	RECT rc = {((dt==DT_CENTER)?(x<<1):x), y, -1, -1};
	m_pFont->DrawText( NULL, wFontName, -1, &rc, dt | DT_NOCLIP, Color );


	delete[] wFontName;
	return 0;
}


int cFont::ShowText(std::wstring Str, int x, int y, D3DXCOLOR Color, DWORD dt)
{
	RECT rc = {((dt==DT_CENTER)?(x<<1):x), y, -1, -1};
	m_pFont->DrawText( NULL, Str.c_str(), -1, &rc, dt | DT_NOCLIP, Color );


	return 0;
}

/*--------------------------------------------------------------------------------------*/

int cFont::ShowText(std::string Str, float fx, float fy, D3DXCOLOR Color, DWORD dt)
{
	int x = static_cast<int>(fx);
	int y = static_cast<int>(fy);

	WCHAR* wFontName = new WCHAR[Str.size()+1];

	DXUtil_ConvertAnsiStringToWideCch(wFontName, Str.c_str(), Str.size()+1);


	RECT rc = {((dt==DT_CENTER)?(x<<1):x), y, -1, -1};
	m_pFont->DrawText( NULL, wFontName, -1, &rc, dt | DT_NOCLIP, Color );


	delete[] wFontName;
	return 0;
}


int cFont::ShowText(std::wstring Str, float fx, float fy, D3DXCOLOR Color, DWORD dt)
{
	int x = static_cast<int>(fx);
	int y = static_cast<int>(fy);

	RECT rc = {((dt==DT_CENTER)?(x<<1):x), y, -1, -1};
	m_pFont->DrawText( NULL, Str.c_str(), -1, &rc, dt | DT_NOCLIP, Color );


	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

SIZE cFont::GetStringSize(std::wstring Str)
{
	return GetStringSize(&Str);
}


SIZE cFont::GetStringSize(const std::wstring* Str)
{
	SIZE Size;


	LOGFONTW lf;     
	D3DXFONT_DESCW desc;   

	m_pFont->GetDescW(&desc);

	int destSize  = sizeof(desc.FaceName);
	int srcSize   = sizeof(lf.lfFaceName);
	int nSize     = min(destSize, srcSize);

	ZeroMemory(&lf, sizeof(lf));

	memcpy(lf.lfFaceName, desc.FaceName, nSize);

	lf.lfCharSet          = desc.CharSet; 
	lf.lfHeight           = desc.Height;
	lf.lfItalic           = desc.Italic;
	lf.lfOutPrecision     = desc.OutputPrecision;
	lf.lfPitchAndFamily   = desc.PitchAndFamily;
	lf.lfQuality          = desc.Quality;
	lf.lfWeight           = desc.Weight;
	lf.lfWidth            = desc.Width;   


	HDC hdc = GetDC(cCore::hWnd);
	HFONT hfont = ::CreateFontIndirectW(&lf);
	HFONT holdfont; 

	holdfont = (HFONT)::SelectObject(hdc, hfont);


	GetTextExtentPoint32(hdc, Str->c_str(), Str->length(), &Size);


	::SelectObject(hdc, holdfont);
	::DeleteObject(hfont);
	::ReleaseDC(cCore::hWnd, hdc);


	return Size;
}

