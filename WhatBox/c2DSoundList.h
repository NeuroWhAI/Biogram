#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class c2DSound;














///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 2D���� ����Ʈ
// Desc : 2D���带 ��Ƽ� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class c2DSoundList
{
public:
	c2DSoundList();
	~c2DSoundList();


private:
	std::vector<c2DSound*> m_pSound;


public:
	int AddSound(std::string SndFile); // ������ ������ �ε����� ��ȯ
	int Release();


public:
	c2DSound* GetSound(UINT index);
	const c2DSound* GetSound(UINT index) const;
};

