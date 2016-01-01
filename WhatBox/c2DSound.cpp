#include "c2DSound.h"

#include "cCore.h"
#include "D3D/dxutil.h"

#define DSVOLUME_TO_DB(Volume) ((DWORD)(-30*(100-Volume)))	//볼륨 조절 매크로
#define ON_LOADWAVE_ERROR {delete[] pData; delete pWaveFormat;}



















c2DSound::c2DSound()
	: m_pBuffer(NULL)
	, m_FileName(NULL)
{
	
}


c2DSound::~c2DSound()
{
	SAFE_DELETE_ARR(m_FileName);
	Release();
}


c2DSound::c2DSound(const c2DSound& org)
{
	LoadWave(org.m_FileName);
}

/*------------------------------------------------------------------------------------*/

int c2DSound::LoadWave(LPSTR lpFileName)
{
	if(m_FileName != NULL)
		delete[] m_FileName;

	m_FileName = new char[strlen(lpFileName)+1];
	strcpy_s(m_FileName, strlen(lpFileName)+1, lpFileName);


	WCHAR* wFileName = new WCHAR[strlen(lpFileName)+1];

	DXUtil_ConvertAnsiStringToWideCch(wFileName, lpFileName, strlen(lpFileName)+1);


	/*----------------------파일 불러오기 시작-----------------------*/
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


	// 사이즈 저장
	m_Size = ckIn.cksize;


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
	// NOTE: 전역으로 나오게 할꺼면 DSBCAPS_STICKYFOCUS | DSBCAPS_GLOBALFOCUS 를 추가
	dsbd.dwBufferBytes = ckIn.cksize;
	dsbd.lpwfxFormat   = pWaveFormat;


	//사운드 버퍼의 생성
	LPDIRECTSOUNDBUFFER dsBuff=NULL;

	if( FAILED(cCore::Sound.GetD3DSound()->CreateSoundBuffer( &dsbd, &dsBuff, NULL )) )
	{ON_LOADWAVE_ERROR
		delete[] wFileName;
		return Util::ErrorMessage("CreateSoundBuffer()");
	}

	if( FAILED(dsBuff->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&m_pBuffer)) )
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
	if( FAILED(m_pBuffer->Lock( 0, dsbd.dwBufferBytes, &pBuff1, &dwLength,
		&pBuff2, &dwLength2, 0L )) )
	{ON_LOADWAVE_ERROR
		SAFE_RELEASE(m_pBuffer);
		delete[] wFileName;
		return Util::ErrorMessage("Lock()");
	}



	memcpy( pBuff1, pData, dwLength ); //버퍼의 첫번째 영역을 복사
	memcpy( pBuff2, (pData+dwLength), dwLength2); //버퍼의 두번째 영역을 복사

	
	//잠금 상태를 풀어준다.
	m_pBuffer->Unlock(pBuff1, dwLength, pBuff2, dwLength2 );
	pBuff1 = pBuff2 = NULL;


	//할당된 메모리를 해제
	delete[] pData;
	delete pWaveFormat;

	delete[] wFileName;

	
	return 0;
}


int c2DSound::Release()
{
	SAFE_RELEASE(m_pBuffer);


	return 0;
}



const LPDIRECTSOUNDBUFFER8 c2DSound::GetBuffer() const
{
	return m_pBuffer;
}


LPDIRECTSOUNDBUFFER8 c2DSound::GetBuffer()
{
	return m_pBuffer;
}



int c2DSound::Play(bool bLoop)
{
	if( !m_pBuffer->Play( 0, 0, (bLoop)?DSBPLAY_LOOPING:0 ) ) return -1;

	
	return 0;
}


int c2DSound::Pause()
{
	m_pBuffer->Stop();  //멈춤
	

	return 0;
}


int c2DSound::Stop()
{
	m_pBuffer->Stop();  //멈춤
	m_pBuffer->SetCurrentPosition(0L); //처음위치로


	return 0;
}



HRESULT c2DSound::Mute()
{
	if(m_pBuffer == NULL) return E_FAIL;


	return m_pBuffer->SetVolume(-10000L);
}



HRESULT c2DSound::SetVolume(long Vol)
{
	if(m_pBuffer == NULL) return E_FAIL;

	if(Vol > 100L) Vol = 100L;
	else if(Vol <= 0L)
	{
		return m_pBuffer->SetVolume(-10000L);
	}


	return m_pBuffer->SetVolume(DSVOLUME_TO_DB(Vol));
}


HRESULT c2DSound::SetVolumeEx(long Vol)
{
	if(m_pBuffer == NULL) return E_FAIL;


	return m_pBuffer->SetVolume(Vol);
}


HRESULT c2DSound::SetPan(long Pan)
{
	if(m_pBuffer == NULL) return E_FAIL;

	if(Pan > 10000L) Pan = 10000L;
	else if(Pan < -10000L) Pan = -10000L;

	
	return m_pBuffer->SetPan(Pan);
}


HRESULT c2DSound::SetFrequency(DWORD Freq)
{
	if(m_pBuffer == NULL) return E_FAIL;


	return m_pBuffer->SetFrequency(Freq);
}



long c2DSound::GetVolume() const
{
	if(m_pBuffer == NULL) return 0L;

	LONG Vol = 0UL;
	m_pBuffer->GetVolume(&Vol);

	return Vol;
}


long c2DSound::GetPan() const
{
	if(m_pBuffer == NULL) return 0L;

	LONG Pan = 0UL;
	m_pBuffer->GetPan(&Pan);

	return Pan;
}


DWORD c2DSound::GetFrequency() const
{
	if(m_pBuffer == NULL) return 0UL;

	DWORD Freq = 0UL;
	m_pBuffer->GetFrequency(&Freq);

	return Freq;
}



bool c2DSound::isEnd() const
{
	DWORD Pos1 = 0, Pos2 = 0;
	m_pBuffer->GetCurrentPosition(&Pos1, &Pos2);


	return (Pos1 >= m_Size - 7052);
}


DWORD c2DSound::GetCurrBytePos() const
{
	DWORD Pos1 = 0, Pos2 = 0;
	m_pBuffer->GetCurrentPosition(&Pos1, &Pos2);


	return Pos1;
}

