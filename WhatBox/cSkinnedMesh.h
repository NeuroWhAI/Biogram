#pragma once
#include <d3d9.h>
#include <string>

struct ILcMdl;
















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : (����)�Ǻθ� ���� �޽�
// Desc : X������ �ҷ��ͼ� �޽��� �ִϸ��̼������� �ҷ��´�.
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

