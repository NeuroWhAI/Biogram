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
	// ��Ʈ����
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
	// ��� ����
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
	Util::TempRenderState OnLight(D3DRS_LIGHTING, TRUE); // ����
	SAFE_RELEASE(m_pMesh); // ���� �޽� ����
	HDC hdc = CreateCompatibleDC( NULL );
	HFONT hFontOld = (HFONT)SelectObject(hdc, m_hFont);


	// �����ڵ� ��ȯ
	//wchar_t�� ���� ����
    wchar_t* pStr;
    //��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
    int strSize = MultiByteToWideChar(CP_ACP, 0, pText->c_str(), -1, NULL, NULL);
    //wchar_t �޸� �Ҵ�
    pStr = new WCHAR[strSize];
    //�� ��ȯ
    MultiByteToWideChar(CP_ACP, 0,pText->c_str(), strlen(pText->c_str())+1, pStr, strSize);


	// 3D ���ڿ��� ����
	D3DXCreateTextW(cCore::pd3dDevice, hdc, pStr, 200.f, 0.01f, &m_pMesh, 0, 0);

	m_pMesh->DrawSubset(0); // �׸���
	
	SelectObject(hdc, hFontOld);

	// DC ����
	DeleteDC( hdc );
	

	// ������� ����
	Util::SetIdentityMatrix();


	delete[] pStr; // �޸� ��ȯ
	return 0;
}

