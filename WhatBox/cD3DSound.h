#pragma once
#include <dsound.h>














///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D사운드객체
// Desc : D3D사운드의 초기화진행, 협력수준을 설정하고 D3D사운드버퍼의 재생을 가능하게 해준다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cD3DSound
{
public:
	cD3DSound();
	~cD3DSound();


private:
	LPDIRECTSOUND8 m_pSound;
	

public:
	int Create();
	int Release();


public:
	LPDIRECTSOUND GetD3DSound();
	const LPDIRECTSOUND GetD3DSound() const;
};

