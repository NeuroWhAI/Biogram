#pragma once
#include "cCoord.h"
#include <string>

class cImgListRender;
class cTextureList;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D����
// Desc : 3D�� ���ڸ� ����Ѵ�.
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

