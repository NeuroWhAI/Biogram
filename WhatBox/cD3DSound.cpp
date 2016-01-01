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
	//���̷�Ʈ ���� ��ü ����
	if( DirectSoundCreate8(NULL, &m_pSound, NULL) != DS_OK )
		return Util::ErrorMessage("DirectSoundCreate8()");


	//���¼��� ����- DSSCL_NORMAL�� ����
	if( m_pSound->SetCooperativeLevel( cCore::hWnd, DSSCL_NORMAL ) != DS_OK )
		return Util::ErrorMessage("SetCooperativeLevel()");
	// NOTE: DSSCL_PRIORITY�� �Ҳ��� c2DSound.cpp���� DSBCAPS_STICKYFOCUS�� Ctrl+F �غ���


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

