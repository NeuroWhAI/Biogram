#include "cMesh.h"

#include "cCore.h"
#include "D3D/dxutil.h"





















cMesh::cMesh()
	: m_pMsh(NULL)
	, m_pMtl(NULL)
	, m_pTex(NULL)
	, m_nMtl(0)
{

}


cMesh::~cMesh()
{
	Release();
}

/*------------------------------------------------------------------------------------*/

int cMesh::LoadXFile(std::string File)
{
	WCHAR* wFile = new WCHAR[File.size()+1];
	DXUtil_ConvertAnsiStringToWideCch(wFile, File.c_str(), 1+static_cast<int>(File.size()));


	m_FileName = File; // 파일경로 저장
	std::string FilePath(File); // 텍스쳐파일 경로


	// 텍스쳐파일 경로 계산
	for(UINT i=FilePath.size()-1; i>=0; i--)
	{
		if(FilePath[i] == '/'  ||  FilePath[i] == '\\')
		{
			//FilePath.push_back('\0'); // +=을 쓰기위함임.
			break;
		}
		else
		{
			FilePath.erase(FilePath.begin() + i);

			if(FilePath.size() <= 1)
			{
				FilePath.clear();
				break;
			}
		}
	}


	//메테리얼 버퍼를 가져오기 위한 임시 버퍼
	LPD3DXBUFFER pD3DXMtrlBuffer;

	//1. 메쉬를 먼저 로딩한다.
	if( FAILED( D3DXLoadMeshFromX(wFile
		,	D3DXMESH_SYSTEMMEM
		,	cCore::pd3dDevice, NULL
		,	&pD3DXMtrlBuffer, NULL
		,	&m_nMtl, &m_pMsh ) ) )
	{
		Util::ErrorMessage("D3DXLoadMeshFromX()");

		delete[] wFile;
		return E_FAIL;
	}


	// 2. 머티리얼과 텍스처를 생성한다.

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMtl = new D3DMATERIAL9[m_nMtl];
	m_pTex  = new LPDIRECT3DTEXTURE9[m_nMtl];


	for( DWORD i=0; i<m_nMtl; i++ )
	{
		// 머티리얼 복사
		m_pMtl[i] = d3dxMaterials[i].MatD3D;

		// 머티리얼의 Ambient 설정
		m_pMtl[i].Ambient = m_pMtl[i].Diffuse;

		m_pTex[i] = NULL;


		if( d3dxMaterials[i].pTextureFilename != NULL )
		{
			WCHAR* pTextureFilename = new WCHAR[strlen(d3dxMaterials[i].pTextureFilename)+1];
			DXUtil_ConvertAnsiStringToWideCch(pTextureFilename, d3dxMaterials[i].pTextureFilename
				, strlen(d3dxMaterials[i].pTextureFilename)+1);


			if(lstrlen(pTextureFilename) > 0)
			{
				// 텍스처를 생성한다.
				std::string TxFile(FilePath);
				TxFile += d3dxMaterials[i].pTextureFilename;

				WCHAR* wTxFile = new WCHAR[TxFile.size()+1];
				DXUtil_ConvertAnsiStringToWideCch(wTxFile, TxFile.c_str(), 1+static_cast<int>(TxFile.size()));

				if( FAILED( D3DXCreateTextureFromFile( cCore::pd3dDevice, wTxFile, &m_pTex[i] ) ) )
				{
					delete[] pTextureFilename;
					delete[] wTxFile;
					delete[] wFile;
					return Util::ErrorMessage("D3DXCreateTextureFromFile()");
				}

				delete[] wTxFile;
			}


			delete[] pTextureFilename;
		}
	}

	// 임시 버퍼를 해제한다.
	pD3DXMtrlBuffer->Release();

	

	delete[] wFile;
	return 0;
}



int cMesh::Release()
{
	SAFE_DELETE_ARR(m_pMtl);

	if( m_pTex != NULL )
	{
		for( DWORD i=0; i < m_nMtl; i++ )
		{
			SAFE_RELEASE(m_pTex[i]);
		}

		SAFE_DELETE_ARR(m_pTex);
	}

	SAFE_RELEASE(m_pMsh);

	m_nMtl = 0;


	return 0;
}


int cMesh::Restore()
{
	return LoadXFile(m_FileName);
}



int cMesh::Render()
{
	cCore::pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	for( DWORD i=0; i<m_nMtl; i++ )
	{
		// 메테리얼, 텍스쳐 설정
		cCore::pd3dDevice->SetMaterial( &m_pMtl[i] );

		cCore::pd3dDevice->SetTexture( 0, m_pTex[i] );

		// 서브셋 그리기
		m_pMsh->DrawSubset( i );
	}
	
	cCore::pd3dDevice->SetTexture( 0, NULL );


	return 0;
}

/*------------------------------------------------------------------------------------*/

DWORD cMesh::MtlNum() const
{
	return m_nMtl;
}



LPD3DXMESH cMesh::GetMesh()
{
	return m_pMsh;
}


const LPD3DXMESH cMesh::GetMesh() const
{
	return m_pMsh;
}



D3DMATERIAL9* cMesh::GetMtl(DWORD index)
{
	return &m_pMtl[index];
}


const D3DMATERIAL9* cMesh::GetMtl(DWORD index) const
{
	return &m_pMtl[index];
}



LPDIRECT3DTEXTURE9* cMesh::GetTex(DWORD index)
{
	return &m_pTex[index];
}


const LPDIRECT3DTEXTURE9* cMesh::GetTex(DWORD index) const
{
	return &m_pTex[index];
}

