#pragma once
#include <d3dx9.h>
#include "cCoord.h"

struct ILcMdl;
class cSkinnedMesh;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 애니메이션이 포함된 X파일 메쉬
// Desc : cSkinnedMesh에서 정보를 불러와 멀티애니메이션을 출력한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cSknMesh : public cCoord
{
public:
	cSknMesh();
	cSknMesh(cSkinnedMesh* pMeshOrg);

	~cSknMesh();


private:
	ILcMdl* m_pMeshIns;


public:
	int Create(cSkinnedMesh* pMeshOrg);

	int Render(INT AniNum);

	//int Release();
	//int Restore();

	int CleanUp();
};

