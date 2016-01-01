#include "cD3DSound.h"

#include "cCore.h"



















cD3DSound::cD3DSound()
	: m_pSound(NULL)
{

}


cD3DSound::~cD3DSound()
{
	Release();
}

/*----------------------------------------------------------------------------------*/

int cD3DSound::Create()
{
	//다이렉트 사운드 개체 생성
	if( DirectSoundCreate8(NULL, &m_pSound, NULL) != DS_OK )
		return Util::ErrorMessage("DirectSoundCreate8()");


	//협력수준 설정- DSSCL_NORMAL로 설정
	if( m_pSound->SetCooperativeLevel( cCore::hWnd, DSSCL_NORMAL ) != DS_OK )
		return Util::ErrorMessage("SetCooperativeLevel()");
	// NOTE: DSSCL_PRIORITY로 할꺼면 c2DSound.cpp에서 DSBCAPS_STICKYFOCUS를 Ctrl+F 해봐라


	return 0;
}


int cD3DSound::Release()
{
	SAFE_RELEASE(m_pSound);


	return 0;
}

/*----------------------------------------------------------------------------------*/

LPDIRECTSOUND cD3DSound::GetD3DSound()
{
	return m_pSound;
}


const LPDIRECTSOUND cD3DSound::GetD3DSound() const
{
	return m_pSound;
}

