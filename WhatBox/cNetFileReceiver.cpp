#include "cNetFileReceiver.h"

#include "cMessageSender.h"

#include "cNetMessage.h"
#include "NetMsgType.h"
#include "cBinaryReader.h"
#include "cBinaryWriter.h"
#include "NetMsgUtil.h"
#include "NetDefine.h"

#include "cCore.h"







































cNetFileReceiver::cNetFileReceiver(bool bReceiveMode)
	: m_downloadPath(new TCHAR[1])
	, m_pNetSender(nullptr)
	, m_bOnRecv(bReceiveMode)

	, m_leftByteSize(0)

	, m_downloadFileName(nullptr)
{
	lstrcpyW(m_downloadPath, TEXT(""));
}


cNetFileReceiver::~cNetFileReceiver()
{
	SAFE_DELETE_ARR(m_downloadPath);

	m_fileStream.close();
	m_fileStream.clear();

	SAFE_DELETE_ARR(m_downloadFileName);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileReceiver::Init(cMessageSender* pNetSender)
{
	m_pNetSender = pNetSender;


	return 0;
}


int cNetFileReceiver::Update(cNetMessage* pRecvMsg)
{
	if (pRecvMsg == nullptr) return -1;


	cBinaryReader br(pRecvMsg);

	UINT msgType = pRecvMsg->Header->MsgType;


	if (msgType == NetMsgType::RQ_FileSend)
	{
		Stop();


		TCHAR filePath[2048];
		br.ReadString(filePath);

		m_leftByteSize = br.Read<int>();


		bool readyForRecv = m_bOnRecv;


		if (readyForRecv)
		{
			// 파일 이름 추출
			int filePathLen = lstrlenW(filePath);

			TCHAR fileName[2048] = { '\0', };
			int startCopyIdx = 0;

			for (startCopyIdx = filePathLen - 1; startCopyIdx >= 0; --startCopyIdx)
			{
				if (filePath[startCopyIdx] == TEXT('\\') || filePath[startCopyIdx] == TEXT('/'))
				{
					++startCopyIdx;
					break;
				}
			}

			if (startCopyIdx < 0) startCopyIdx = 0;

			for (int i = startCopyIdx; i <= filePathLen; ++i)
			{
				fileName[i - startCopyIdx] = filePath[i];
			}


			// 파일 생성
			SAFE_DELETE_ARR(m_downloadFileName);
			m_downloadFileName = new TCHAR[min(lstrlenW(m_downloadPath) + lstrlenW(fileName) + 2, 4096)];

			swprintf_s(m_downloadFileName, 4096, L"%s%s", m_downloadPath, fileName);

			m_fileStream.open(m_downloadFileName);

			if (m_fileStream.is_open() == false)
			{
				Util::Log("수신할 파일 생성 실패");


				readyForRecv = false; // 파일 생성 실패
			}
		}
		else
		{
			Util::Log("파일 수신 거부함");
		}


		// 다운로드 여부 응답
		cBinaryWriter bw;
		bw.Write(readyForRecv ? NetDefine::YES : NetDefine::NO);

		cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RP_FileSend, &bw);

		m_pNetSender->PushSendMsg(pMsg);
	}
	else if (msgType == NetMsgType::NF_FileSendData)
	{
		bool bSuccess = true;


		// 파일 다운로드 진행
		int seqNum = br.Read<int>();
		int byteSize = br.Read<int>();
		char* fileData = new char[byteSize];

		br.ReadBytes(fileData, byteSize);

		if (m_fileStream.is_open())
		{
			Util::Log("파일 수신 %d 성공", seqNum);


			bSuccess = true;

			m_fileStream.write(fileData, byteSize);


			m_leftByteSize -= byteSize; // 남은 바이트 수 갱신

			if (m_leftByteSize <= 0) // 다운로드 완료
			{
				// 다운로드 성공여부 응답
				cBinaryWriter bw;
				bw.Write(NetDefine::SUCCESS);

				cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RP_FileSendEnd, &bw);

				m_pNetSender->PushSendMsg(pMsg);


				m_fileStream.close();
				m_fileStream.clear();
			}
		}
		else
		{
			Util::Log("파일 수신 %d 실패", seqNum);


			bSuccess = false;
		}

		SAFE_DELETE_ARR(fileData);


		// 파일 다운로드 상황 응답
		cBinaryWriter bw;
		bw.Write(seqNum);
		bw.Write(byteSize);
		bw.Write(bSuccess ? NetDefine::SUCCESS : NetDefine::FAIL);

		cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RP_FileSendData, &bw);

		m_pNetSender->PushSendMsg(pMsg);
	}
	else if (msgType == NetMsgType::NF_FileSendEnd)
	{
		Stop();


		bool bSuccess = true;


		BYTE goodBad = br.Read<BYTE>();

		if (goodBad == NetDefine::SUCCESS)
		{
			Util::Log("파일 수신 완료");


			bSuccess = true;
		}
		else
		{
			Util::Log("파일 수신 실패");


			bSuccess = false;
		}


		if (m_leftByteSize > 0) bSuccess = false;


		// 다운로드 성공여부 응답
		cBinaryWriter bw;
		bw.Write(bSuccess ? NetDefine::SUCCESS : NetDefine::FAIL);

		cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RP_FileSendEnd, &bw);

		m_pNetSender->PushSendMsg(pMsg);
	}


	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileReceiver::GetLeftByteSize() const
{
	return m_leftByteSize;
}


int cNetFileReceiver::GetFileName(TCHAR* pOut) const
{
	if (m_downloadFileName != nullptr)
	{
		lstrcpyW(pOut, m_downloadFileName);
	}
	else
	{
		lstrcpyW(pOut, TEXT(""));
	}


	return 0;
}


const TCHAR* cNetFileReceiver::GetFileName() const
{
	return m_downloadFileName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileReceiver::SetDownloadPath(const TCHAR path[])
{
	SAFE_DELETE_ARR(m_downloadPath);

	m_downloadPath = new TCHAR[lstrlenW(path) + 1];

	lstrcpyW(m_downloadPath, path);


	return 0;
}


int cNetFileReceiver::SetRecvMode(bool bReceive)
{
	m_bOnRecv = bReceive;


	return 0;
}


int cNetFileReceiver::Stop()
{
	//SAFE_DELETE_ARR(m_downloadFileName);

	m_leftByteSize = 0;

	m_fileStream.close();
	m_fileStream.clear();


	return 0;
}

