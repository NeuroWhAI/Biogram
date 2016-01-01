// TODO: 사운드버퍼를 가지고 소리가 날 3D위치를 줘서 재생하면 D3DAudio객체에 자신을 등록/갱신한다.
#pragma once
#include <d3dx9.h>

class c2DSound;


















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 3D사운드
// Desc : 2D사운드를 포함하고 D3DAudio에서 3D사운드를 계산하기위한 인터페이스 제공
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c3DSound
{
public:
	c3DSound();
	~c3DSound();


private:
	c2DSound* m_pSound;


public:
	int SetSound(c2DSound* pSound, D3DXVECTOR3 Pos);
	int SetSound(c2DSound* pSound, const D3DXVECTOR3* pPos);
	
	int Play(D3DXVECTOR3 Pos, bool bLoop);				// 초기위치 지정후 재생
	int Play(const D3DXVECTOR3* pPos, bool bLoop);		// 초기위치 지정후 재생

	int Pause();
	int Stop();

	int UpdatePos(D3DXVECTOR3 Pos);						// 스피커 위치 갱신
	int UpdatePos(const D3DXVECTOR3* pPos);				// 스피커 위치 갱신


public:
	int Release();
};

