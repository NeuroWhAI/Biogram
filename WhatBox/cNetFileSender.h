#pragma once
#include <Windows.h>
#include <WinSock2.h>
#include <vector>
#include <fstream>

class cMessageSender;
class cNetMessage;





































class cNetFileSender
{
public:
	cNetFileSender();
	~cNetFileSender();


private:
	cMessageSender* m_pNetSender;
	bool m_bOnSend;


private:
	TCHAR* m_fileName;
	std::ifstream m_fileStream;


private:
	int m_leftByteSize;
	int m_seqNum;


public:
	int Init(cMessageSender* pNetSender);
	int Update(cNetMessage* pRecvMsg = nullptr);


public:
	int SendFile(const TCHAR fileName[]);


public:
	int GetLeftByteSize() const;


public:
	int Stop();
};

