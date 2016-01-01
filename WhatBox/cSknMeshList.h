#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cSkinnedMesh;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��Ų��޽� ����Ʈ
// Desc : ��Ų��޽��� ��Ƽ� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSknMeshList
{
public:
	cSknMeshList();
	~cSknMeshList();


private:
	std::vector<cSkinnedMesh*> m_pSknMesh;


public:
	UINT AddSknMesh(std::string XFile); // ������ �޽��� �ε����� ��ȯ
	UINT AddSknMesh(cSkinnedMesh* pSknMesh); // ������ �޽��� �ε����� ��ȯ

	int Release();
	int Restore();

	int CleanUp();

	int FrameMove();


public:
	cSkinnedMesh* GetSknMesh(UINT index);
	const cSkinnedMesh* GetSknMesh(UINT index) const;
};

