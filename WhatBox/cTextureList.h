#pragma once
#include <d3dx9.h>
#include <vector>
#include <string>

class cTexture;















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 텍스쳐리스트
// Desc : 텍스쳐를 모아서 관리한다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cTextureList
{
public:
	cTextureList();
	~cTextureList();


private:
	std::vector<cTexture*> m_pTx;


public:
	UINT AddTexture(std::string TxFile); // 생성한 텍스쳐의 인덱스값 반환
	UINT AddTexture(cTexture* pTx); // 생성한 텍스쳐의 인덱스값 반환
	UINT AddTexture(LPDIRECT3DTEXTURE9 pTx); // 생성한 텍스쳐의 인덱스값 반환
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

