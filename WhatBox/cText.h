#pragma once
#include "cCoord.h"
#include <string>

class cImgListRender;
class cTextureList;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D문자
// Desc : 3D로 글자를 출력한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cText : public cCoord
{
public:
	cText();
	~cText();


private:
	LPD3DXMESH m_pMesh;
	HFONT m_hFont;


public:
	int Create(std::string Font);
	int Release();

	int ShowText(std::string Text, DWORD Color);
	int ShowTextBillboard(std::string Text, DWORD Color);


private:
	int Draw(std::string* pText, DWORD* pColor);
};

