#include "cWavBuffer.h"

#include "cCore.h"
#include "D3D/dxutil.h"

#define DSVOLUME_TO_DB(Volume) ((DWORD)(-30*(100-Volume)))	//���� ���� ��ũ��
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


	/*----------------------���� �ҷ����� ����-----------------------*/
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
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
	dsbd.dwBufferBytes = ckIn.cksize;
	dsbd.lpwfxFormat   = pWaveFormat;


	//���� ������ ����
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


	VOID* pBuff1 = NULL;  //���� ������ ù��° �����ּ�
	VOID* pBuff2 = NULL;  //���� ������ �ι�° �����ּ�
	DWORD dwLength;      //ù��° ����ũ��
	DWORD dwLength2;     //�ι�° ����ũ��


	//���� ���ۿ� ������ wav�����͸� �����ϱ� ���� ���� �Ǵ�.
	if( FAILED(pDSBuffer->Lock( 0, dsbd.dwBufferBytes, &pBuff1, &dwLength,
		&pBuff2, &dwLength2, 0L )) )
	{ON_LOADWAVE_ERROR
		SAFE_RELEASE(pDSBuffer);
		delete[] wFileName;
		return Util::ErrorMessage("Lock()");
	}



	memcpy( pBuff1, pData, dwLength ); //������ ù��° ������ ����
	memcpy( pBuff2, (pData+dwLength), dwLength2); //������ �ι�° ������ ����


	// �� ����
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

	
	//��� ���¸� Ǯ���ش�.
	pDSBuffer->Unlock(pBuff1, dwLength, pBuff2, dwLength2 );
	pBuff1 = pBuff2 = NULL;


	//�Ҵ�� �޸𸮸� ����
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

