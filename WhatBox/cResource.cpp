#include "cResource.h"

#include "cCore.h"
























cResource::cResource()
{
	m_pTxList.push_back(new cTextureList);				// �������ҽ� ����Ʈ ����
	m_p2DSndList.push_back(new c2DSoundList);			// �������ҽ� ����Ʈ ����
	m_pMeshList.push_back(new cMeshList);				// �������ҽ� ����Ʈ ����
	m_pSknMeshList.push_back(new cSknMeshList);				// �������ҽ� ����Ʈ ����
}


cResource::~cResource()
{
	for(UINT i=0; i<m_pFont.size(); i++)
		delete m_pFont[i];

	for(UINT i=0; i<m_pTxList.size(); i++)
		delete m_pTxList[i];

	for(UINT i=0; i<m_p2DSndList.size(); i++)
		delete m_p2DSndList[i];

	for(UINT i=0; i<m_pTextbox.size(); i++)
		delete m_pTextbox[i];

	for(UINT i=0; i<m_pMeshList.size(); i++)
		delete m_pMeshList[i];

	for(UINT i=0; i<m_pSknMeshList.size(); i++)
		delete m_pSknMeshList[i];
}

/*--------------------------------------------------------------------------------------*/

int cResource::Load()
{
	/* ��Ʈ */
	Font0.SetFont("����", 8, 16);
	Font1.SetFont("����", 10, 20);


	/* �� */
	Line.Init();


	/* �ؽ��� */
	// add...


	/* ���� */
	// add...


	/* �޽� */
	// add...


	/* �ִϸ��̼� �޽� */
	// add...


	return 0;
}


int cResource::Release()
{// ȭ�麹����(= ������ ����� �� �ִ� �Լ��̹Ƿ� �ڵ��� ����)
	/* ��Ʈ */
	Font0.Release();
	Font1.Release();

	for(UINT i=0; i<m_pFont.size(); i++)
		m_pFont[i]->Release();


	/* �ؽ��� */
	// add...


	/* ���� */
	// add...


	/* �޽� */
	for(UINT i=0; i<m_pMeshList.size(); i++)
		m_pMeshList[i]->Release();
	// add...


	/* �ִϸ��̼� �޽� */
	for(UINT i=0; i<m_pSknMeshList.size(); i++)
		m_pSknMeshList[i]->Release();
	// add...


	return 0;
}


int cResource::Restore()
{// ȭ�麹����(= ������ ����� �� �ִ� �Լ��̹Ƿ� �ڵ��� ����)
	/* ��Ʈ */
	Font0.Restore();
	Font1.Restore();

	for(UINT i=0; i<m_pFont.size(); i++)
		m_pFont[i]->Restore();


	/* �ؽ��� */
	// add...


	/* ���� */
	// add...


	/* �޽� */
	for(UINT i=0; i<m_pMeshList.size(); i++)
		m_pMeshList[i]->Restore();
	// add...


	/* �ִϸ��̼� �޽� */
	for(UINT i=0; i<m_pSknMeshList.size(); i++)
		m_pSknMeshList[i]->Restore();
	// add...


	return 0;
}


int cResource::CleanUp()
{/* ���α׷� ����� ȣ�� */
	/* ��Ʈ */
	Font0.Release();
	Font1.Release();

	for(UINT i=0; i<m_pFont.size(); i++)
		m_pFont[i]->Release();


	/* �� */
	Line.CleanUp();


	/* �ؽ��� */
	for(UINT i=0; i<m_pTxList.size(); i++)
		m_pTxList[i]->Release();


	/* ���� */
	for(UINT i=0; i<m_p2DSndList.size(); i++)
		m_p2DSndList[i]->Release();


	/* �޽� */
	for(UINT i=0; i<m_pMeshList.size(); i++)
		m_pMeshList[i]->CleanUp();


	/* �ִϸ��̼� �޽� */
	for(UINT i=0; i<m_pSknMeshList.size(); i++)
		m_pSknMeshList[i]->CleanUp();


	return 0;
}

/*--------------------------------------------------------------------------------------*/

cFont* cResource::CreateFontRc(std::string FontName, int Width, int Height)
{
	UINT Index = m_pFont.size();
	m_pFont.push_back(new cFont);

	m_pFont[Index]->SetFont(FontName, Width, Height);


	return m_pFont[Index];
}


cTexture* cResource::CreateTexture(std::string TxFile, cTextureList* pTxList)
{
	if(pTxList == NULL) // ���ڰ� ������ �������ҽ�
		pTxList = m_pTxList[TxList_None];


	int Index = pTxList->AddTexture(TxFile);
	return pTxList->GetTexture(Index);
}


c2DSound* cResource::Create2DSound(std::string SndFile, c2DSoundList* pSndList)
{
	if(pSndList == NULL) // ���ڰ� ������ �������ҽ�
		pSndList = m_p2DSndList[TxList_None];


	int Index = pSndList->AddSound(SndFile);
	return pSndList->GetSound(Index);
}


cTextbox* cResource::CreateTextbox(bool UseMultiLine)
{
	UINT index = m_pTextbox.size();
	m_pTextbox.push_back(new cTextbox(UseMultiLine));


	return m_pTextbox[index];
}


cMesh* cResource::CreateMesh(std::string XFile, cMeshList* pMshList)
{
	if(pMshList == NULL) // ���ڰ� ������ �������ҽ�
		pMshList = m_pMeshList[MshList_None];


	int Index = pMshList->AddMesh(XFile);
	return pMshList->GetMesh(Index);
}


cSkinnedMesh* cResource::CreateSknMesh(std::string XFile, cSknMeshList* pSknMshList)
{
	if(pSknMshList == NULL) // ���ڰ� ������ �������ҽ�
		pSknMshList = m_pSknMeshList[SknMshList_None];


	int Index = pSknMshList->AddSknMesh(XFile);
	return pSknMshList->GetSknMesh(Index);
}



cTextureList* cResource::AddTxList()
{
	UINT Index = m_pTxList.size();
	m_pTxList.push_back(new cTextureList);


	return m_pTxList[Index];
}


c2DSoundList* cResource::Add2DSndList()
{
	UINT Index = m_p2DSndList.size();
	m_p2DSndList.push_back(new c2DSoundList);


	return m_p2DSndList[Index];
}


cMeshList* cResource::AddMshList()
{
	UINT Index = m_pMeshList.size();
	m_pMeshList.push_back(new cMeshList);


	return m_pMeshList[Index];
}


cSknMeshList* cResource::AddSknMshList()
{
	UINT Index = m_pSknMeshList.size();
	m_pSknMeshList.push_back(new cSknMeshList);


	return m_pSknMeshList[Index];
}

/*--------------------------------------------------------------------------------------*/

cTextureList* cResource::GetTxList(int idx)
{
	return m_pTxList[idx];
}


cMeshList* cResource::GetMshList(int idx)
{
	return m_pMeshList[idx];
}


cSknMeshList* cResource::GetSknMshList(int idx)
{
	return m_pSknMeshList[idx];
}

/*--------------------------------------------------------------------------------------*/

int cResource::MsgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_IME_CHAR  ||  msg == WM_CHAR)
	{
		if(msg == WM_CHAR  ||  cCore::Input.KeyState(VK_HANGEUL) == cInput::NONE)
		{
			for(UINT i=0; i<m_pTextbox.size(); i++)
			{
				m_pTextbox[i]->AddChar((wchar_t)wParam);
			}
		}
	}


	return 0;
}


int cResource::FrameMove()
{
	// ��Ų�� �޽� �ִϸ��̼� ����
	for(UINT i=0; i<m_pSknMeshList.size(); i++)
	{
		m_pSknMeshList[i]->FrameMove();
	}


	return 0;
}

