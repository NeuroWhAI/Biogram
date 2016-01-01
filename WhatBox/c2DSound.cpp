#include "c2DSound.h"

#include "cCore.h"
#include "D3D/dxutil.h"

#define DSVOLUME_TO_DB(Volume) ((DWORD)(-30*(100-Volume)))	//���� ���� ��ũ��
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


	/*----------------------���� �ҷ����� ����-----------------------*/
	HMMIO          hmmio;              //wave������ �ڵ�

	MMCKINFO    ckInRIFF, ckIn;  //�θ� ûũ , �ڽ� ûũ
	PCMWAVEFORMAT  pcmWaveFormat;
	WAVEFORMATEX*     pWaveFormat = NULL;


	//���̺� ������ ����, MMIO �ڵ��� ��´�.
	hmmio = mmioOpen(wFileName, NULL, MMIO_ALLOCBUF|MMIO_READ);
	if(hmmio==NULL) return Util::ErrorMessage("mmioOpen()");

	//������ ���� ûũ�̸��� ����ϰ�, ���� ��ġ�� RIFFûũ���� WAVEûũ�� ã�� ��������.
	ckInRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if( (mmioDescend(hmmio, &ckInRIFF, NULL, MMIO_FINDRIFF)) != 0 )
	{
		mmioClose(hmmio, 0);  //�����ϸ� �����ִ� ���̺������� �ݰ� ����

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	//������ ���� ûũ�̸��� ����ϰ�, ���� ��ġ�� WAVEûũ���� fmt ûũ�� ã�� ��������.
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if( mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0)
	{
		mmioClose(hmmio, 0);//�����ϸ� �����ִ� ���̺������� �ݰ� ����

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	//fmt ûũ���� wav���� ����(Format)�� �о� ���δ�.
	if( mmioRead(hmmio, (HPSTR) &pcmWaveFormat, sizeof(pcmWaveFormat))
		!= sizeof(pcmWaveFormat) )
	{
		mmioClose(hmmio, 0);//�����ϸ� �����ִ� ���̺������� �ݰ� ����

		delete[] wFileName;
		return Util::ErrorMessage("mmioRead()");;
	}


	//WAVEFORMATEX�� �޸𸮿� �Ҵ�
	pWaveFormat = new WAVEFORMATEX;

	//PCMWAVEFORMAT�κ��� �����Ѵ�.
	memcpy( pWaveFormat, &pcmWaveFormat, sizeof(pcmWaveFormat) );
	pWaveFormat->cbSize = 0;



	//fmt Chunk ���� �θ�ûũ�� WAVE Chunk�� �ö󰣴�.
	if( mmioAscend(hmmio, &ckIn, 0) )
	{delete pWaveFormat;
		mmioClose(hmmio, 0);//�����ϸ� �����ִ� ���̺������� �ݰ� ����

		delete[] wFileName;
		return Util::ErrorMessage("mmioAscend()");
	}


	//������ ���� ûũ�̸��� ����ϰ�, ���� ��ġ�� WAVEûũ���� data ûũ�� ã�� ��������.
	ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if( mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0 )
	{delete pWaveFormat;
		mmioClose(hmmio, 0);//�����ϸ� �����ִ� ���̺������� �ݰ� ����

		delete[] wFileName;
		return Util::ErrorMessage("mmioDescend()");
	}


	// ������ ����
	m_Size = ckIn.cksize;


	BYTE*   pData = NULL;
	//data chunk ������ ��ŭ �޸� �Ҵ�
	pData = new BYTE[ckIn.cksize] ;


	//data chunk�� �ִ� ������ wave data�� �о� ���δ�.
	mmioRead(hmmio, (LPSTR)pData, ckIn.cksize);

	//������� ������ wav�����б⿡ ������ ���̹Ƿ�, �����ִ� wav������ �ݴ´�.
	mmioClose(hmmio, 0);



	// DSBUFFERDESC ����ü ������ ä���.
	DSBUFFERDESC dsbd;
	ZeroMemory( &dsbd, sizeof(DSBUFFERDESC) );

	dsbd.dwSize        = sizeof(DSBUFFERDESC);
	dsbd.dwFlags       = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE
		| DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;
	// NOTE: �������� ������ �Ҳ��� DSBCAPS_STICKYFOCUS | DSBCAPS_GLOBALFOCUS �� �߰�
	dsbd.dwBufferBytes = ckIn.cksize;
	dsbd.lpwfxFormat   = pWaveFormat;


	//���� ������ ����
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


	VOID* pBuff1 = NULL;  //���� ������ ù��° �����ּ�
	VOID* pBuff2 = NULL;  //���� ������ �ι�° �����ּ�
	DWORD dwLength;      //ù��° ����ũ��
	DWORD dwLength2;     //�ι�° ����ũ��


	//���� ���ۿ� ������ wav�����͸� �����ϱ� ���� ���� �Ǵ�.
	if( FAILED(m_pBuffer->Lock( 0, dsbd.dwBufferBytes, &pBuff1, &dwLength,
		&pBuff2, &dwLength2, 0L )) )
	{ON_LOADWAVE_ERROR
		SAFE_RELEASE(m_pBuffer);
		delete[] wFileName;
		return Util::ErrorMessage("Lock()");
	}



	memcpy( pBuff1, pData, dwLength ); //������ ù��° ������ ����
	memcpy( pBuff2, (pData+dwLength), dwLength2); //������ �ι�° ������ ����

	
	//��� ���¸� Ǯ���ش�.
	m_pBuffer->Unlock(pBuff1, dwLength, pBuff2, dwLength2 );
	pBuff1 = pBuff2 = NULL;


	//�Ҵ�� �޸𸮸� ����
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
	m_pBuffer->Stop();  //����
	

	return 0;
}


int c2DSound::Stop()
{
	m_pBuffer->Stop();  //����
	m_pBuffer->SetCurrentPosition(0L); //ó����ġ��


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

