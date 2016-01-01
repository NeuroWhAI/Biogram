#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class c2DSound;














///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D사운드 리스트
// Desc : 2D사운드를 모아서 관리한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DSoundList
{
public:
	c2DSoundList();
	~c2DSoundList();


private:
	std::vector<c2DSound*> m_pSound;


public:
	int AddSound(std::string SndFile); // 생성한 사운드의 인덱스값 반환
	int Release();


public:
	c2DSound* GetSound(UINT index);
	const c2DSound* GetSound(UINT index) const;
};

