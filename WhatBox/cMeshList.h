#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cMesh;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : X파일 메쉬 리스트
// Desc : 메쉬클래스를 모아서 관리한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cMeshList
{
public:
	cMeshList();
	~cMeshList();


private:
	std::vector<cMesh*> m_pMsh;


public:
	UINT AddMesh(std::string XFile); // 생성한 텍스쳐의 인덱스값 반환
	UINT AddMesh(cMesh* pMsh); // 생성한 텍스쳐의 인덱스값 반환

	int Release(); // 화면복구용
	int Restore();

	int CleanUp();


public:
	cMesh* GetMesh(UINT index);
	const cMesh* GetMesh(UINT index) const;
};

