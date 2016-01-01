#include "cNetFileSender.h"

#include "cMessageSender.h"

#include "cNetMessage.h"
#include "NetMsgType.h"
#include "cBinaryReader.h"
#include "cBinaryWriter.h"
#include "NetMsgUtil.h"
#include "NetDefine.h"

#include "cCore.h"







































cNetFileSender::cNetFileSender()
	: m_pNetSender(nullptr)
	, m_bOnSend(false)

	, m_fileName(nullptr)

	, m_leftByteSize(0)
	, m_seqNum(0)
{

}


cNetFileSender::~cNetFileSender()
{
	SAFE_DELETE_ARR(m_fileName);

	m_fileStream.close();
	m_fileStream.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileSender::Init(cMessageSender* pNetSender)
{
	m_pNetSender = pNetSender;


	return 0;
}


int cNetFileSender::Update(cNetMessage* pRecvMsg)
{
	if (m_bOnSend)
	{
		const int sendByteSize = 512;
		int readByteSize = min(sendByteSize, m_leftByteSize);
		char fileData[sendByteSize];

		m_fileStream.read(fileData, readByteSize);


		cBinaryWriter bw;
		bw.Write(m_seqNum);
		bw.Write(readByteSize);
		bw.WriteBytes(fileData, readByteSize);

		cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::NF_FileSendData, &bw);

		m_pNetSender->PushSendMsg(pMsg);


		if (m_fileStream.eof())
		{
			cBinaryWriter bw2;
			bw2.Write(NetDefine::SUCCESS);

			cNetMessage* pMsg2 = NetMsgUtil::MakeMessage(NetMsgType::NF_FileSendEnd, &bw2);

			m_pNetSender->PushSendMsg(pMsg2);


			Stop();
		}


		m_bOnSend = false; // 현재 단계를 다운로드 완료했다는 응답이 왔을때 또 보내도록.


		return 1;
	}


	if (pRecvMsg == nullptr) return -1;


	cBinaryReader br(pRecvMsg);

	UINT msgType = pRecvMsg->Header->MsgType;


	if (msgType == NetMsgType::RP_FileSend)
	{
		BYTE yesNo = br.Read<BYTE>();

		if (yesNo == NetDefine::YES)
		{
			Util::Log("파일 전송요청 승인됨.");


			m_bOnSend = true;
		}
		else
		{
			Util::Log("파일 전송요청 거부됨.");


			SAFE_DELETE_ARR(m_fileName);

			m_leftByteSize = 0;
			m_seqNum = 0;

			m_bOnSend = false;
		}
	}
	else if (msgType == NetMsgType::RP_FileSendData)
	{
		int seqNum = br.Read<int>();
		int recvByteSize = br.Read<int>();
		BYTE goodBad = br.Read<BYTE>();

		m_leftByteSize -= recvByteSize; // 남은 바이트 수 갱신

		if (goodBad == NetDefine::SUCCESS  &&  seqNum == m_seqNum)
		{
			Util::Log("파일 전송 %d 성공", m_seqNum);


			m_bOnSend = true;

			++m_seqNum;
		}
		else
		{
			Util::Log("파일 전송 %d 실패", m_seqNum);


			cBinaryWriter bw2;
			bw2.Write(NetDefine::FAIL);

			cNetMessage* pMsg2 = NetMsgUtil::MakeMessage(NetMsgType::NF_FileSendEnd, &bw2);

			m_pNetSender->PushSendMsg(pMsg2);


			Stop();
		}
	}
	else if (msgType == NetMsgType::RP_FileSendEnd)
	{
		BYTE goodBad = br.Read<BYTE>();

		if (goodBad == NetDefine::SUCCESS)
		{
			Util::Log("파일 전송 완료");
		}
		else
		{
			Util::Log("파일 전송 실패");
		}


		Stop();
	}


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileSender::SendFile(const TCHAR fileName[])
{
	Stop();


	m_fileStream.open(fileName);
	if (m_fileStream.is_open() == false) return -1;


	m_fileStream.seekg(0, std::ios::end);
	m_leftByteSize = static_cast<int>(m_fileStream.tellg());

	m_fileStream.seekg(0, std::ios::beg);


	m_fileName = new TCHAR[lstrlenW(fileName) + 1];
	lstrcpyW(m_fileName, fileName);


	cBinaryWriter bw;
	bw.Write(fileName);
	bw.Write(m_leftByteSize);

	cNetMessage* pMsg = NetMsgUtil::MakeMessage(NetMsgType::RQ_FileSend, &bw);

	m_pNetSender->PushSendMsg(pMsg);


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileSender::GetLeftByteSize() const
{
	return m_leftByteSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cNetFileSender::Stop()
{
	SAFE_DELETE_ARR(m_fileName);


	m_leftByteSize = 0;
	m_seqNum = 0;

	m_fileStream.close();
	m_fileStream.clear();


	m_bOnSend = false;


	return 0;
}

