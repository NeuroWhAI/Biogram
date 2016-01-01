#pragma once
#include <vector>
//winmm.lib
#include <windows.h>
#include <mmsystem.h>
//dsound.lib
#include <dsound.h>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���� ����
// Desc : D3D���� ���۸� �����ϰ� ���� �� �ִ� �������̽� ����
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cWavBuffer
{
public:
	cWavBuffer();
	virtual ~cWavBuffer();


protected:
	std::vector<short> m_buffer;


public:
	int LoadWave(LPSTR lpFileName);    //wav������ �ҷ����� ���۸� ������ �����.


public:
	DWORD GetSize();
	short GetByte(DWORD idx);


public:
	short operator[](DWORD idx);
};

