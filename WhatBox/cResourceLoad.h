#pragma once
#include <d3dx9.h>
#include <fstream>
#include <string>
#include <vector>

class cTextureList;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 텍스쳐로드 클래스
// Desc : 텍스쳐의 경로를 불러와 리소스에 텍스쳐로딩
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cResourceLoad
{
public:
	cResourceLoad();
	~cResourceLoad();


private:
	DWORD m_LoadTime;
	std::ifstream m_LoadList;						// 로드할 이미지경로가 적힌 텍스트 파일
	int m_CurrFileNum;								// 현재 경로파일 번호
	char m_Buf[512];								// 경로 버퍼


private:
	cTextureList* m_pLoadingImg;					// 시각적 사진

	std::vector<D3DXVECTOR2> m_IconPos;				// 아이콘 위치
	std::vector<D3DXVECTOR2> m_IconSpeed;			// 아이콘 속도
	std::vector<int> m_IconImg;						// 아이콘 이미지 번호

	int m_CurrResource;


public:
	int Init();

	int Loading();
	int Render();

	bool isEnd() const;


private:
	int LoadImg();
	int LoadSound();
	int LoadMesh();
	int LoadSknMesh();


private:
	int AddIcon();
};

