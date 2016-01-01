#pragma once
#include "c2DCoord.h"

class cShp_Rectangle;




















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D전용 카메라
// Desc : Sprite, 2DLine 등에 적용됨
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DCamera : public c2DCoord
{
public:
	c2DCamera();
	~c2DCamera();


private:
	cShp_Rectangle* m_pScreenRect;
	const D3DXVECTOR2 m_zeroPos;


public:
	int FrameMove();					// Speed 처리
	int Reset();						// 값 초기화
	int Control();


public:
	virtual const D3DXMATRIX* Matrix();
	const cShp_Rectangle* GetScreenRect() const;


public:
	virtual const D3DXVECTOR2* Pos() const override;
	const D3DXVECTOR2* RealPos() const;
};

