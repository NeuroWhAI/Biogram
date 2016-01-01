#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cSkinnedMesh;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 스킨드메쉬 리스트
// Desc : 스킨드메쉬를 모아서 관리한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSknMeshList
{
public:
	cSknMeshList();
	~cSknMeshList();


private:
	std::vector<cSkinnedMesh*> m_pSknMesh;


public:
	UINT AddSknMesh(std::string XFile); // 생성한 메쉬의 인덱스값 반환
	UINT AddSknMesh(cSkinnedMesh* pSknMesh); // 생성한 메쉬의 인덱스값 반환

	int Release();
	int Restore();

	int CleanUp();

	int FrameMove();


public:
	cSkinnedMesh* GetSknMesh(UINT index);
	const cSkinnedMesh* GetSknMesh(UINT index) const;
};

