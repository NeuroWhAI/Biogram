#pragma once
#include "c2DCoord.h"

class cShp_Rectangle;




















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D���� ī�޶�
// Desc : Sprite, 2DLine � �����
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
	int FrameMove();					// Speed ó��
	int Reset();						// �� �ʱ�ȭ
	int Control();


public:
	virtual const D3DXMATRIX* Matrix();
	const cShp_Rectangle* GetScreenRect() const;


public:
	virtual const D3DXVECTOR2* Pos() const override;
	const D3DXVECTOR2* RealPos() const;
};

