#pragma once
#include <dsound.h>














///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : D3D���尴ü
// Desc : D3D������ �ʱ�ȭ����, ���¼����� �����ϰ� D3D��������� ����� �����ϰ� ���ش�.
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

