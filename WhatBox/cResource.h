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
// Name : 리소스
// Desc : 리소스의 생성, 갱신 그리고 파괴를 담당한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cResource
{
public:
	cResource();
	~cResource();
private:
	cResource(cResource&) {}; // 복사금지


	/* 특수리소스 */
public: /* 폰트 */
	cFont Font0;
	cFont Font1; // 유틸/디버깅용 폰트


public: /* 선 */
	c2DLine Line; // 2D 선 그리기


public: /* 텍스쳐 */
	// add...


public: /* 사운드 */
	// add...


public: /* 메쉬 */
	// add...


public: /* 애니메이션 메쉬 */
	// add...


public: /* 일반리소스 */
	std::vector<cFont*> m_pFont;
	std::vector<cTextureList*> m_pTxList;		// 0번은 자유리소스
	std::vector<c2DSoundList*> m_p2DSndList;	// 0번은 자유리소스
	std::vector<cTextbox*> m_pTextbox;
	std::vector<cMeshList*> m_pMeshList;		// 0번은 자유리소스
	std::vector<cSknMeshList*> m_pSknMeshList;	// 0번은 자유리소스


public:
	int Load();

	int Release();
	int Restore();

	int CleanUp(); // 프로그램 종료시 호출


public: /* 리소스 관리 함수 */ // 이 함수를 이용해 생성한 리소스는 프로그램종료시에 자동해제된다
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


public: /* 리소스 접근 함수 */
	cTextureList* GetTxList(int idx);
	cMeshList* GetMshList(int idx);
	cSknMeshList* GetSknMshList(int idx);


public: /* 부가기능이 필요한 리소스를 위함 */
	int MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	int FrameMove();
};

