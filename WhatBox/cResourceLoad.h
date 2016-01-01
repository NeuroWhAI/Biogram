#pragma once
#include <d3dx9.h>
#include <fstream>
#include <string>
#include <vector>

class cTextureList;

















///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : �ؽ��ķε� Ŭ����
// Desc : �ؽ����� ��θ� �ҷ��� ���ҽ��� �ؽ��ķε�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cResourceLoad
{
public:
	cResourceLoad();
	~cResourceLoad();


private:
	DWORD m_LoadTime;
	std::ifstream m_LoadList;						// �ε��� �̹�����ΰ� ���� �ؽ�Ʈ ����
	int m_CurrFileNum;								// ���� ������� ��ȣ
	char m_Buf[512];								// ��� ����


private:
	cTextureList* m_pLoadingImg;					// �ð��� ����

	std::vector<D3DXVECTOR2> m_IconPos;				// ������ ��ġ
	std::vector<D3DXVECTOR2> m_IconSpeed;			// ������ �ӵ�
	std::vector<int> m_IconImg;						// ������ �̹��� ��ȣ

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

