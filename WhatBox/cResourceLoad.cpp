#include "cResourceLoad.h"

#include "cTextureList.h"
#include "cCore.h"





















cResourceLoad::cResourceLoad()
	: m_CurrFileNum(-1)
	, m_pLoadingImg(NULL)
	, m_LoadTime(timeGetTime())
	, m_CurrResource(0)
{
	m_Buf[0] = '\0';
	m_pLoadingImg = new cTextureList;
}


cResourceLoad::~cResourceLoad()
{
	SAFE_DELETE(m_pLoadingImg);
}

/*--------------------------------------------------------------------------------------*/

int cResourceLoad::Init()
{
	// 기본 사진 로딩
	m_pLoadingImg->AddTexture("Data/WhatBox/LoadingImg/CenterCircle.png");
	m_pLoadingImg->AddTexture("Data/WhatBox/Img/Black.png");
	m_pLoadingImg->AddTexture("Data/WhatBox/LoadingImg/Picture.png");
	m_pLoadingImg->AddTexture("Data/WhatBox/LoadingImg/Sound.png");
	m_pLoadingImg->AddTexture("Data/WhatBox/LoadingImg/Mesh.png");
	m_pLoadingImg->AddTexture("Data/WhatBox/LoadingImg/SknMesh.png");


	// 경로파일 열기
	m_LoadList.open("Data/LoadData/Img/1.txt");

	if(!m_LoadList.is_open())
		m_CurrFileNum = -1;
	else
	{
		m_CurrFileNum = 1;

		cCore::Resource.AddTxList();
	}


	m_LoadTime = timeGetTime() + 100UL;


	return 0;
}



int cResourceLoad::Loading()
{
	// 아이콘 물리이동
	for(UINT i=0; i<m_IconPos.size(); i++)
	{
		m_IconSpeed[i].y += VFR(0.8f);
		m_IconPos[i] += VFR(m_IconSpeed[i]);

		if(m_IconPos[i].y > cCore::WinSize.y+64)
		{
			m_IconPos.erase(m_IconPos.begin()+i);
			m_IconSpeed.erase(m_IconSpeed.begin()+i);
			m_IconImg.erase(m_IconImg.begin()+i);

			i--;
		}
	}


	if(timeGetTime() < m_LoadTime)
		return 0;
	else
		m_LoadTime = timeGetTime() + 10UL;


	if(m_CurrResource == 0)
		LoadImg();
	else if(m_CurrResource == 1)
		LoadSound();
	else if(m_CurrResource == 2)
		LoadMesh();
	else if(m_CurrResource == 3)
		LoadSknMesh();


	return 0;
}


int cResourceLoad::Render()
{
	cCore::Sprite.BeginDraw();
	cCore::Sprite.DrawTextureCenter(m_pLoadingImg->GetTexture(1/*Black*/)
		, Util::CenterPos());

	for(UINT i=0; i<m_IconPos.size(); i++)
	{
		cCore::Sprite.DrawTextureCenter(m_pLoadingImg->GetTexture(m_IconImg[i]/*Icon*/)
			, m_IconPos[i]);
	}
	
	cCore::Sprite.DrawTextureCenter(m_pLoadingImg->GetTexture(0/*Circle*/)
		, Util::CenterPos());
	cCore::Sprite.EndDraw();


	cCore::Resource.Font1.ShowText(m_Buf, cCore::WinSize.x>>1, (cCore::WinSize.y>>1)-8
		, 0xff000000, DT_CENTER);


	return 0;
}



bool cResourceLoad::isEnd() const
{
	return (m_CurrFileNum < 0  &&  m_IconPos.size() == 0UL);
}

/*--------------------------------------------------------------------------------------*/

int cResourceLoad::LoadImg()
{
	if(m_LoadList.eof())
	{// 다 불러옴
		m_LoadList.close(); m_LoadList.clear();


		m_CurrFileNum++;
		sprintf_s(m_Buf, 511, "Data/LoadData/Img/%d.txt", m_CurrFileNum);

		m_LoadList.open(m_Buf);

		if(!m_LoadList.is_open())
		{
			//m_CurrFileNum = -1; // 다불러옴
			m_CurrFileNum = 1;
			m_CurrResource = 1;
			strcpy_s(m_Buf, 511, "Waiting");


			m_LoadList.open("Data/LoadData/Sound/1.txt");

			if(!m_LoadList.is_open())
				m_CurrFileNum = -1;
			else
			{
				m_CurrFileNum = 1;

				cCore::Resource.Add2DSndList();
			}
		}
		else
		{
			cCore::Resource.AddTxList();
		}
	}
	else
	{// 덜 불러옴
		m_LoadList.getline(m_Buf, 511);
		if(strlen(m_Buf) >= 3)
		{// 안전장치
			AddIcon();

			cCore::Resource.CreateTexture(m_Buf, cCore::Resource.m_pTxList[m_CurrFileNum]);
		}
	}


	return 0;
}


int cResourceLoad::LoadSound()
{
	if(m_CurrFileNum < 0)
	{
		m_CurrFileNum = 0;
		m_CurrResource = 2;
		strcpy_s(m_Buf, 511, "Waiting");


		m_LoadList.open("Data/LoadData/Mesh/1.txt");

		if(!m_LoadList.is_open())
			m_CurrFileNum = -1;
		else
		{
			m_CurrFileNum = 1;

			cCore::Resource.AddMshList();
		}


		return 0;
	}


	if(m_LoadList.eof())
	{// 다 불러옴
		m_LoadList.close(); m_LoadList.clear();


		m_CurrFileNum++;
		sprintf_s(m_Buf, 511, "Data/LoadData/Sound/%d.txt", m_CurrFileNum);

		m_LoadList.open(m_Buf);

		if(!m_LoadList.is_open())
		{
			//m_CurrFileNum = -1; // 다불러옴
			m_CurrFileNum = 1;
			m_CurrResource = 2;
			strcpy_s(m_Buf, 511, "Waiting");


			m_LoadList.open("Data/LoadData/Mesh/1.txt");

			if(!m_LoadList.is_open())
				m_CurrFileNum = -1;
			else
			{
				m_CurrFileNum = 1;

				cCore::Resource.AddMshList();
			}
		}
		else
		{
			cCore::Resource.Add2DSndList();
		}
	}
	else
	{// 덜 불러옴
		m_LoadList.getline(m_Buf, 511);
		if(strlen(m_Buf) >= 3)
		{// 안전장치
			AddIcon();

			cCore::Resource.Create2DSound(m_Buf, cCore::Resource.m_p2DSndList[m_CurrFileNum]);
		}
	}


	return 0;
}


int cResourceLoad::LoadMesh()
{
	if(m_CurrFileNum < 0)
	{
		m_CurrFileNum = 1;
		m_CurrResource = 3;
		strcpy_s(m_Buf, 511, "Waiting");


		m_LoadList.open("Data/LoadData/SknMesh/1.txt");

		if(!m_LoadList.is_open())
			m_CurrFileNum = -1;
		else
		{
			m_CurrFileNum = 1;

			cCore::Resource.AddSknMshList();
		}


		return 0;
	}


	if(m_LoadList.eof())
	{// 다 불러옴
		m_LoadList.close(); m_LoadList.clear();


		m_CurrFileNum++;
		sprintf_s(m_Buf, 511, "Data/LoadData/Mesh/%d.txt", m_CurrFileNum);

		m_LoadList.open(m_Buf);

		if(!m_LoadList.is_open())
		{
			//m_CurrFileNum = -1; // 다불러옴
			m_CurrFileNum = 1;
			m_CurrResource = 3;
			strcpy_s(m_Buf, 511, "Waiting");


			m_LoadList.open("Data/LoadData/SknMesh/1.txt");

			if(!m_LoadList.is_open())
				m_CurrFileNum = -1;
			else
			{
				m_CurrFileNum = 1;

				cCore::Resource.AddSknMshList();
			}
		}
		else
		{
			cCore::Resource.AddMshList();
		}
	}
	else
	{// 덜 불러옴
		m_LoadList.getline(m_Buf, 511);
		if(strlen(m_Buf) >= 3)
		{// 안전장치
			AddIcon();

			cCore::Resource.CreateMesh(m_Buf, cCore::Resource.m_pMeshList[m_CurrFileNum]);
		}
	}
	

	return 0;
}


int cResourceLoad::LoadSknMesh()
{
	if(m_CurrFileNum < 0)
	{
		m_CurrFileNum = -1; // 다불러옴
		m_CurrResource = 4;
		strcpy_s(m_Buf, 511, "Waiting");


		return 0;
	}


	if(m_LoadList.eof())
	{// 다 불러옴
		m_LoadList.close(); m_LoadList.clear();


		m_CurrFileNum++;
		sprintf_s(m_Buf, 511, "Data/LoadData/SknMesh/%d.txt", m_CurrFileNum);

		m_LoadList.open(m_Buf);

		if(!m_LoadList.is_open())
		{
			m_CurrFileNum = -1; // 다불러옴
			m_CurrResource = 4;
			strcpy_s(m_Buf, 511, "Waiting");
		}
		else
		{
			cCore::Resource.AddSknMshList();
		}
	}
	else
	{// 덜 불러옴
		m_LoadList.getline(m_Buf, 511);
		if(strlen(m_Buf) >= 3)
		{// 안전장치
			AddIcon();

			cCore::Resource.CreateSknMesh(m_Buf, cCore::Resource.m_pSknMeshList[m_CurrFileNum]);
		}
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

int cResourceLoad::AddIcon()
{
	m_IconPos.push_back(Util::CenterPos());
	m_IconSpeed.push_back(D3DXVECTOR2(float(-rand()%16+rand()%32), float(-rand()%16)-4.f));
	m_IconImg.push_back(m_CurrResource+2);


	return 0;
}

