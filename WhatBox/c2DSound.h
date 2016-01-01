#pragma once
//winmm.lib
#include <windows.h>
#include <mmsystem.h>
//dsound.lib
#include <dsound.h>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D����
// Desc : D3D���� ���۸� �����ϰ� Wav������ �ҷ��� ����Ѵ�.
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
	int LoadWave(LPSTR lpFileName);    //wav������ �ҷ����� ���۸� ������ �����.
	int Release();

	const LPDIRECTSOUNDBUFFER8 GetBuffer() const;
	LPDIRECTSOUNDBUFFER8 GetBuffer();

	int Play(bool bLoop);
	int Pause();
	int Stop();

	HRESULT Mute();

	HRESULT SetVolume(long Vol/*0~100*/);		// dB ����
	HRESULT SetVolumeEx(long Vol);
	HRESULT SetPan(long Pan);
	HRESULT SetFrequency(DWORD Freq);

	long GetVolume() const;
	long GetPan() const;
	DWORD GetFrequency() const;

	bool isEnd() const;
	DWORD GetCurrBytePos() const;
};

