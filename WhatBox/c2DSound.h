#pragma once
//winmm.lib
#include <windows.h>
#include <mmsystem.h>
//dsound.lib
#include <dsound.h>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D사운드
// Desc : D3D사운드 버퍼를 생성하고 Wav파일을 불러와 재생한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DSound
{
public:
	c2DSound();
	virtual ~c2DSound();

	c2DSound(const c2DSound&);


protected:
	char* m_FileName;
	LPDIRECTSOUNDBUFFER8 m_pBuffer;
	DWORD m_Size;


public:
	int LoadWave(LPSTR lpFileName);    //wav파일을 불러오고 버퍼를 생성해 덮어씌움.
	int Release();

	const LPDIRECTSOUNDBUFFER8 GetBuffer() const;
	LPDIRECTSOUNDBUFFER8 GetBuffer();

	int Play(bool bLoop);
	int Pause();
	int Stop();

	HRESULT Mute();

	HRESULT SetVolume(long Vol/*0~100*/);		// dB 단위
	HRESULT SetVolumeEx(long Vol);
	HRESULT SetPan(long Pan);
	HRESULT SetFrequency(DWORD Freq);

	long GetVolume() const;
	long GetPan() const;
	DWORD GetFrequency() const;

	bool isEnd() const;
	DWORD GetCurrBytePos() const;
};

