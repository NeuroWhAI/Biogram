#pragma once
#include <vector>
//winmm.lib
#include <windows.h>
#include <mmsystem.h>
//dsound.lib
#include <dsound.h>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 사운드 버퍼
// Desc : D3D사운드 버퍼를 생성하고 읽을 수 있는 인터페이스 제공
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cWavBuffer
{
public:
	cWavBuffer();
	virtual ~cWavBuffer();


protected:
	std::vector<short> m_buffer;


public:
	int LoadWave(LPSTR lpFileName);    //wav파일을 불러오고 버퍼를 생성해 덮어씌움.


public:
	DWORD GetSize();
	short GetByte(DWORD idx);


public:
	short operator[](DWORD idx);
};

