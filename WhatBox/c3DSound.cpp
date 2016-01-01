#include "c3DSound.h"

#include "c2DSound.h"

#include "cCore.h" // D3DAudio에 접근을 위함























c3DSound::c3DSound()
	: m_pSound(NULL)
{

}


c3DSound::~c3DSound()
{
	Release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int c3DSound::SetSound(c2DSound* pSound, D3DXVECTOR3 Pos)
{
	return SetSound(pSound, &Pos);
}


int c3DSound::SetSound(c2DSound* pSound, const D3DXVECTOR3* pPos)
{
	// D3DAudio에 재등록(기존꺼 삭제 및 새 사운드 등록)
	if(m_pSound != NULL)
	{
		cCore::D3DAudio.Delete3DSound(m_pSound);	// 이전 사운드 목록에서 삭제
		delete m_pSound; m_pSound = NULL;			// 사운드 해제
	}


	// pSound 복사
	m_pSound = new c2DSound(*pSound);


	// 복사한 사운드 목록에 추가
	cCore::D3DAudio.Add3DSound(m_pSound, pPos);


	return 0;
}



int c3DSound::Play(D3DXVECTOR3 Pos, bool bLoop)
{
	return Play(&Pos, bLoop);
}


int c3DSound::Play(const D3DXVECTOR3* pPos, bool bLoop)
{
	if(m_pSound == NULL) return -1;


	return m_pSound->Play(bLoop);
}



int c3DSound::Pause()
{
	if(m_pSound == NULL) return -1;


	return m_pSound->Pause();
}


int c3DSound::Stop()
{
	if(m_pSound == NULL) return -1;


	return m_pSound->Stop();
}



int c3DSound::UpdatePos(D3DXVECTOR3 Pos)
{
	return UpdatePos(&Pos);
}


int c3DSound::UpdatePos(const D3DXVECTOR3* pPos)
{
	if(m_pSound == NULL) return -1;


	return cCore::D3DAudio.SetSoundPos(m_pSound, pPos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int c3DSound::Release()
{
	// D3DAudio등록 해제
	cCore::D3DAudio.Delete3DSound(m_pSound);


	SAFE_DELETE(m_pSound);


	return 0;
}

