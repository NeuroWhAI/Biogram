#pragma once
#include "ImgListName.h"
#include "MshListName.h"
#include "SknMeshListName.h"
#include "SndListName.h"

#include "cFont.h"
#include "c2DLine.h"
#include "cTexture.h"
#include "cTextureList.h"
#include "c2DSound.h"
#include "c2DSoundList.h"
#include "cTextbox.h"
#include "cMesh.h"
#include "cMeshList.h"
#include "cSkinnedMesh.h"
#include "cSknMeshList.h"

#include <vector>















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���ҽ�
// Desc : ���ҽ��� ����, ���� �׸��� �ı��� ����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cResource
{
public:
	cResource();
	~cResource();
private:
	cResource(cResource&) {}; // �������


	/* Ư�����ҽ� */
public: /* ��Ʈ */
	cFont Font0;
	cFont Font1; // ��ƿ/������ ��Ʈ


public: /* �� */
	c2DLine Line; // 2D �� �׸���


public: /* �ؽ��� */
	// add...


public: /* ���� */
	// add...


public: /* �޽� */
	// add...


public: /* �ִϸ��̼� �޽� */
	// add...


public: /* �Ϲݸ��ҽ� */
	std::vector<cFont*> m_pFont;
	std::vector<cTextureList*> m_pTxList;		// 0���� �������ҽ�
	std::vector<c2DSoundList*> m_p2DSndList;	// 0���� �������ҽ�
	std::vector<cTextbox*> m_pTextbox;
	std::vector<cMeshList*> m_pMeshList;		// 0���� �������ҽ�
	std::vector<cSknMeshList*> m_pSknMeshList;	// 0���� �������ҽ�


public:
	int Load();

	int Release();
	int Restore();

	int CleanUp(); // ���α׷� ����� ȣ��


public: /* ���ҽ� ���� �Լ� */ // �� �Լ��� �̿��� ������ ���ҽ��� ���α׷�����ÿ� �ڵ������ȴ�
	cFont* CreateFontRc(std::string FontName, int Width, int Height);
	cTexture* CreateTexture(std::string TxFile, cTextureList* pTxList = NULL);
	c2DSound* Create2DSound(std::string SndFile, c2DSoundList* pSndList = NULL);
	cTextbox* CreateTextbox(bool UseMultiLine);
	cMesh* CreateMesh(std::string XFile, cMeshList* pMshList = NULL);
	cSkinnedMesh* CreateSknMesh(std::string XFile, cSknMeshList* pSknMshList = NULL);

	cTextureList* AddTxList();
	c2DSoundList* Add2DSndList();
	cMeshList* AddMshList();
	cSknMeshList* AddSknMshList();


public: /* ���ҽ� ���� �Լ� */
	cTextureList* GetTxList(int idx);
	cMeshList* GetMshList(int idx);
	cSknMeshList* GetSknMshList(int idx);


public: /* �ΰ������ �ʿ��� ���ҽ��� ���� */
	int MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	int FrameMove();
};

