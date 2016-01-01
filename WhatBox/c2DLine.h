#pragma once
#include <d3dx9.h>
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D 선 객체
// Desc : 색, 굵기를 지정해 선을 그릴 수 있음
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DLine
{
public:
	c2DLine();
	~c2DLine();


private:
	ID3DXLine* m_pLine;


public:
	int Init();
	int CleanUp();

	int Render(float left, float top, float right, float bottom, DWORD Color, float Width);
	int Render(const D3DXVECTOR2* pP1, const D3DXVECTOR2* pP2, DWORD Color, float Width);
	int Render(const D3DXVECTOR2 VtxArr[], int VtxNum, DWORD Color, float Width);

	int Begin();
	int End();

	int Draw(float left, float top, float right, float bottom, DWORD Color);
	int Draw(const D3DXVECTOR2* pP1, const D3DXVECTOR2* pP2, DWORD Color);
	int Draw(const D3DXVECTOR2 VtxArr[], int VtxNum, DWORD Color);

	int SetWidth(float width);
};

