#pragma once
#include <d3dx9.h>

class cTextureList;
class cPlane;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 이미지리스트 출력기
// Desc : 텍스쳐리스트에 여러옵션을줘서 출력해준다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cImgListRender
{
public:
	cImgListRender(cTextureList* pTxList, bool isCenter/*원점이 사진의 중앙에 있냐 왼쪽아래에 있냐*/);
	~cImgListRender();


private:
	enum {
		S, R, T
	};
	D3DXMATRIX m_Mat[3];

	bool m_onMt;				// 행렬 적용여부


private:
	cPlane* m_pPlane;
	cTextureList* m_pTxList;


public:
	int SetPos(const D3DXVECTOR3& Pos);
	int SetAngle(const D3DXVECTOR3& Axis, float Radian);
	int SetScale(const D3DXVECTOR3& Scale);


public:
	int Render(int index);
	int RenderBillboard(int index);

	int RenderAlpha(int index);
	int RenderBillboardAlpha(int index);

	int MultiRender(int idx1, int idx2, _D3DTEXTUREOP Op, int Stage = 0);
	int SetMultiTx(int idx1, int idx2, _D3DTEXTUREOP Op, int Stage);


private:
	int Draw(int index, D3DXMATRIX& Mat, cTextureList* pTxList);
};

