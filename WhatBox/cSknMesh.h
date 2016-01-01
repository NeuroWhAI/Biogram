#pragma once
#include <d3dx9.h>
#include "cCoord.h"

struct ILcMdl;
class cSkinnedMesh;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �ִϸ��̼��� ���Ե� X���� �޽�
// Desc : cSkinnedMesh���� ������ �ҷ��� ��Ƽ�ִϸ��̼��� ����Ѵ�.
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

