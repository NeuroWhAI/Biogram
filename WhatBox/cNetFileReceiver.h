#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>
#include <fstream>

class cMessageSender;
class cNetMessage;





































class cNetFileReceiver
{
public:
	// * bReceiveMode : 파일 수신을 허용할지 여부를 설정
	cNetFileReceiver(bool bReceiveMode = true);
	~cNetFileReceiver();


private:
	TCHAR* m_downloadPath;
	cMessageSender* m_pNetSender;
	bool m_bOnRecv;


private:
	int m_leftByteSize;
	std::ofstream m_fileStream;


private:
	TCHAR* m_downloadFileName;


public:
	int Init(cMessageSender* pNetSender);
	int Update(cNetMessage* pRecvMsg);


public:
	int GetLeftByteSize() const;
	int GetFileName(TCHAR* pOut) const;
	const TCHAR* GetFileName() const;


public:
	int SetDownloadPath(const TCHAR path[]);
	int SetRecvMode(bool bReceive);
	int Stop();
};

