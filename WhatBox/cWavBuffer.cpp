#include "cWavBuffer.h"

#include "cCore.h"
#include "D3D/dxutil.h"

#define DSVOLUME_TO_DB(Volume) ((DWORD)(-30*(100-Volume)))	//볼륨 조절 매크로
#define ON_LOADWAVE_ERROR {delete[] pData; delete pWaveFormat;}



















cWavBuffer::cWavBuffer()
{
	
}


cWavBuffer::~cWavBuffer()
{
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cWavBuffer::LoadWave(LPSTR lpFileName)
{
	WCHAR* wFileName = new WCHAR[strlen(lpFileName)+1];

	DXUtil_ConvertAnsiStringToWideCch(wFileName, lpFileName, strlen(lpFileName)+1);


	/*----------------------파일 불러오기 시작-----------------------*/
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	HMMIO          hmmio;              //wave파일의 핸들

	MMCKINFO    ckInRIFF, ckIn;  //부모 청크 , 자식 청크
	PCMWAVEFORMAT  pcmWaveFormat;
	WAVEFORMATEX*     pWaveFormat = NULL;


	//웨이브 파일을 열어, MMIO 핸들을 얻는다.
	hmmio = mmioOpen(wFileName, NULL, MMIO_ALLOCBUF|MMIO_READ);
	if(hmmio==NULL) return Util::ErrorMessage("mmioOpen()");

	//내려갈 하위 청크이름을 등록하고, 현재 위치인 RIFF청크에서 WAVE청크를 찾아 내려간다.
	ckInRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if( (mmioDescend(hmmio, &ckInRIFF, NULL, MMIO_FINDRIFF)) != 0 )
	{
		mmioClose(hmmio, 0);  //실패하면 열려있는 웨이브파일을 닫고 리턴

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	//내려갈 하위 청크이름을 등록하고, 현재 위치인 WAVE청크에서 fmt 청크를 찾아 내려간다.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if( mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0)
	{
		mmioClose(hmmio, 0);//실패하면 열려있는 웨이브파일을 닫고 리턴

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	//fmt 청크에서 wav파일 포맷(Format)을 읽어 들인다.
	if( mmioRead(hmmio, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat))
		!= sizeof(pcmWaveFormat) )
	{
		mmioClose(hmmio, 0);//실패하면 열려있는 웨이브파일을 닫고 리턴

		delete[] wFileName;
		return Util::ErrorMessage("mmioRead()");;
	}


	//WAVEFORMATEX를 메모리에 할당
	pWaveFormat = new WAVEFORMATEX;

	//PCMWAVEFORMAT로부터 복사한다.
	memcpy( pWaveFormat, &pcmWaveFormat, sizeof(pcmWaveFormat) );
	pWaveFormat->cbSize = 0;



	//fmt Chunk 에서 부모청크인 WAVE Chunk로 올라간다.
	if( mmioAscend(hmmio, &ckIn, 0) )
	{delete pWaveFormat;
		mmioClose(hmmio, 0);//실패하면 열려있는 웨이브파일을 닫고 리턴

		delete[] wFileName;
		return Util::ErrorMessage("mmioAscend()");
	}


	//내려갈 하위 청크이름을 등록하고, 현재 위치인 WAVE청크에서 data 청크를 찾아 내려간다.
	ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if( mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0 )
	{delete pWaveFormat;
		mmioClose(hmmio, 0);//실패하면 열려있는 웨이브파일을 닫고 리턴

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	BYTE*   pData = NULL;
	//data chunk 사이즈 만큼 메모리 할당
	pData = new BYTE[ckIn.cksize] ;


	//data chunk에 있는 순수한 wave data를 읽어 들인다.
	mmioRead(hmmio, (LPSTR)pData, ckIn.cksize);

	//여기까지 왔으면 wav파일읽기에 성공한 것이므로, 열려있는 wav파일을 닫는다.
	mmioClose(hmmio, 0);



	// DSBUFFERDESC 구조체 정보를 채운다.
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );

	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE
		| DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;
	dsbd.dwBufferBytes = ckIn.cksize;
	dsbd.lpwfxFormat   = pWaveFormat;


	//사운드 버퍼의 생성
	LPDIRECTSOUNDBUFFER dsBuff=NULL;

	if( FAILED(cCore::Sound.GetD3DSound()->CreateSoundBuffer( &dsbd, &dsBuff, NULL )) )
	{ON_LOADWAVE_ERROR
		delete[] wFileName;
		return Util::ErrorMessage("CreateSoundBuffer()");
	}

	if( FAILED(dsBuff->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSBuffer)) )
	{ON_LOADWAVE_ERROR
		dsBuff->Release();
		delete[] wFileName;
		return Util::ErrorMessage("QueryInterface()");
	}
	SAFE_RELEASE(dsBuff);


	VOID* pBuff1 = NULL;  //사운드 버퍼의 첫번째 영역주소
	VOID* pBuff2 = NULL;  //사운드 버퍼의 두번째 영역주소
	DWORD dwLength;      //첫번째 영역크기
	DWORD dwLength2;     //두번째 영역크기


	//사운드 버퍼에 순수한 wav데이터를 복사하기 위해 락을 건다.
	if( FAILED(pDSBuffer->Lock( 0, dsbd.dwBufferBytes, &pBuff1, &dwLength,
		&pBuff2, &dwLength2, 0L )) )
	{ON_LOADWAVE_ERROR
		SAFE_RELEASE(pDSBuffer);
		delete[] wFileName;
		return Util::ErrorMessage("Lock()");
	}



	memcpy( pBuff1, pData, dwLength ); //버퍼의 첫번째 영역을 복사
	memcpy( pBuff2, (pData+dwLength), dwLength2); //버퍼의 두번째 영역을 복사


	// 값 복사
	short* pWavBuffer = (short*)pBuff1;

	if(pWavBuffer != nullptr)
	{
		DWORD totalSize = dwLength / sizeof(short);
		//DWORD countPerFrame = pWaveFormat->nAvgBytesPerSec / 120UL;
		//DWORD countPerFrame = pWaveFormat->nAvgBytesPerSec / 2UL / 128UL / 60UL;
		DWORD countPerFrame = 1UL;

		for(DWORD i=0; i<totalSize; i+=countPerFrame)
		{
			m_buffer.emplace_back(pWavBuffer[i]);
		}
	}

	
	//잠금 상태를 풀어준다.
	pDSBuffer->Unlock(pBuff1, dwLength, pBuff2, dwLength2 );
	pBuff1 = pBuff2 = NULL;


	//할당된 메모리를 해제
	delete[] pData;
	delete pWaveFormat;

	delete[] wFileName;

	SAFE_RELEASE(pDSBuffer);

	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD cWavBuffer::GetSize()
{
	return m_buffer.size();
}


short cWavBuffer::GetByte(DWORD idx)
{
	return m_buffer[idx];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

short cWavBuffer::operator[](DWORD idx)
{
	return m_buffer[idx];
}

