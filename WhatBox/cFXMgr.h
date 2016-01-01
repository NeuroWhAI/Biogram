#pragma once
#include <vector>

class cFX;


































///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : Ư��ȿ�� ������
// Desc : Ư��ȿ���� �����Ű�� ����� �޸𸮿��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cFXMgr
{
public:
	cFXMgr();
	~cFXMgr();


private:
	std::vector<cFX*> m_pFXList;


public:
	int Update();
	int Render();


public:
	int AddFX(cFX* pFX);
	int RemoveFX(const cFX* pFX);
	int RemoveAll();
};

