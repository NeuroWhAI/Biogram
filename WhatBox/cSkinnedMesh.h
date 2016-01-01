#pragma once
#include <d3d9.h>
#include <string>

struct ILcMdl;
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : (직역)피부를 가진 메쉬
// Desc : X파일을 불러와서 메쉬와 애니메이션정보를 불러온다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSkinnedMesh
{
public:
	cSkinnedMesh();
	~cSkinnedMesh();


private:
	ILcMdl* m_pMesh;


public:
	int LoadXFile(std::string XFile);

	int FrameMove();
	int Render();

	int Release();
	int Restore();

	int CleanUp();


public:
	int CreateInstance(ILcMdl** pMeshIns);
};

