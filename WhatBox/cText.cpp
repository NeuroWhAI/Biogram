#include "cText.h"

#include "cCore.h"
#include "cTextureList.h"
#include "cImgListRender.h"

#include "D3D/dxutil.h"






















cText::cText()
	: m_pMesh(NULL)
	, m_hFont(NULL)
{
	
}


cText::~cText()
{
	Release();
}

/*--------------------------------------------------------------------------------------*/

int cText::Create(std::string Font)
{
	// 폰트생성
	LOGFONT logf={0};
	logf.lfHeight      = 8L;
	logf.lfWeight      = FW_NORMAL;
	logf.lfCharSet     = HANGUL_CHARSET;
	logf.lfOutPrecision= OUT_DEFAULT_PRECIS;
	logf.lfQuality		= ANTIALIASED_QUALITY;
	logf.lfPitchAndFamily= FF_DONTCARE;
	

	char* cFaceName = new char[Font.size()+1];

	DXUtil_ConvertWideStringToAnsiCch(cFaceName, logf.lfFaceName, 1+static_cast<int>(Font.size()));


	strcpy_s(cFaceName, 32, Font.c_str());

	m_hFont = CreateFontIndirect(&logf);


	delete[] cFaceName;
	return 0;
}


int cText::Release()
{
	if(m_hFont)
	{
		DeleteObject( m_hFont );
		m_hFont = NULL;
	}

	SAFE_RELEASE(m_pMesh);


	return 0;
}


int cText::ShowText(std::string Text, DWORD Color)
{
	// 행렬 적용
	SetMatrixToDevice();

	
	return Draw(&Text, &Color);
}


int cText::ShowTextBillboard(std::string Text, DWORD Color)
{
	SetMatrix(mtR, &cCore::BillboardMt);
	cCore::pd3dDevice->SetTransform(D3DTS_WORLD, Matrix());


	return Draw(&Text, &Color);
}

/*--------------------------------------------------------------------------------------*/

int cText::Draw(std::string* pText, DWORD* pColor)
{
	Util::TempRenderState Color(D3DRS_AMBIENT, *pColor);
	Util::TempRenderState OnLight(D3DRS_LIGHTING, TRUE); // 빛켬
	SAFE_RELEASE(m_pMesh); // 기존 메쉬 삭제
	HDC hdc = CreateCompatibleDC( NULL );
	HFONT hFontOld = (HFONT)SelectObject(hdc, m_hFont);


	// 유니코드 변환
	//wchar_t형 변수 선언
    wchar_t* pStr;
    //멀티 바이트 크기 계산 길이 반환
    int strSize = MultiByteToWideChar(CP_ACP, 0, pText->c_str(), -1, NULL, NULL);
    //wchar_t 메모리 할당
    pStr = new WCHAR[strSize];
    //형 변환
    MultiByteToWideChar(CP_ACP, 0,pText->c_str(), strlen(pText->c_str())+1, pStr, strSize);


	// 3D 문자열을 생성
	D3DXCreateTextW(cCore::pd3dDevice, hdc, pStr, 200.f, 0.01f, &m_pMesh, 0, 0);

	m_pMesh->DrawSubset(0); // 그리기
	
	SelectObject(hdc, hFontOld);

	// DC 해제
	DeleteDC( hdc );
	

	// 단위행렬 적용
	Util::SetIdentityMatrix();


	delete[] pStr; // 메모리 반환
	return 0;
}

