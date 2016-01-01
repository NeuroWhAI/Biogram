#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cTexture;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �ؽ��ĸ���Ʈ
// Desc : �ؽ��ĸ� ��Ƽ� �����Ѵ�.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTextureList
{
public:
	cTextureList();
	~cTextureList();


private:
	std::vector<cTexture*> m_pTx;


public:
	UINT AddTexture(std::string TxFile); // ������ �ؽ����� �ε����� ��ȯ
	UINT AddTexture(cTexture* pTx); // ������ �ؽ����� �ε����� ��ȯ
	UINT AddTexture(LPDIRECT3DTEXTURE9 pTx); // ������ �ؽ����� �ε����� ��ȯ
	int Release();


public:
	cTexture* GetTexture(UINT index);
	const cTexture* GetTexture(UINT index) const;
	UINT GetSize() const;


public:
	cTexture* operator[] (int idx);
	cTexture* operator[] (unsigned int idx);
	const cTexture* operator[] (int idx) const;
	const cTexture* operator[] (unsigned int idx) const;
};

