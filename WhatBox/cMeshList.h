#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cMesh;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : X���� �޽� ����Ʈ
// Desc : �޽�Ŭ������ ��Ƽ� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cMeshList
{
public:
	cMeshList();
	~cMeshList();


private:
	std::vector<cMesh*> m_pMsh;


public:
	UINT AddMesh(std::string XFile); // ������ �ؽ����� �ε����� ��ȯ
	UINT AddMesh(cMesh* pMsh); // ������ �ؽ����� �ε����� ��ȯ

	int Release(); // ȭ�麹����
	int Restore();

	int CleanUp();


public:
	cMesh* GetMesh(UINT index);
	const cMesh* GetMesh(UINT index) const;
};

