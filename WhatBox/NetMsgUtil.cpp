#include "NetMsgUtil.h"

#include "cNetMessage.h"

#include "Array.h"

#include "cNetHeader.h"
#include "NetMsgType.h"
#include "NetDefine.h"
#include "cBinaryWriter.h"






















BYTE NetMsgUtil::s_Buffer[4096];

///////////////////////////////////////////////////////////////////////////////////////

bool NetMsgUtil::Send(SOCKET Sock, BYTE Msg[], UINT MsgLength)
{
	return (send(Sock, (const char*)Msg, MsgLength, 0) >= 0);
}


bool NetMsgUtil::Send(SOCKET Sock, const cNetMessage* pMsg)
{
	pMsg->Header->SendTime = timeGetTime();
	pMsg->Header->BodyLen = pMsg->Body->GetSize();

	
	BYTE* Bytes = new BYTE[pMsg->GetSize()];
	pMsg->GetBytes(Bytes);

	int Result = send(Sock, (const char*)Bytes, pMsg->GetSize(), 0);


	delete[] Bytes;


	return (Result >= 0);
}


bool NetMsgUtil::Receive(SOCKET Sock, cNetMessage* pGetMsg)
{
	/* Header ������ �ޱ� */
	int totalRecv = 0;
	int sizeToRead = 16;
	BYTE* hBuffer = new BYTE[sizeToRead];

	while (sizeToRead > 0)
	{
		BYTE* buffer = new BYTE[sizeToRead];

		int RecvLen = recv(Sock, (char*)buffer, sizeToRead, 0);

		if (RecvLen == 0)
		{// �Ϲ����� ����
			delete[] hBuffer;
			delete[] buffer;
			return false;
		}
		else if(RecvLen < 0)
		{// ���������� ����
			int LastError = WSAGetLastError();
			
			delete[] hBuffer;
			delete[] buffer;
			return false;
		}


		Array::Copy(buffer, 0, hBuffer, totalRecv, sizeToRead);
		totalRecv += RecvLen;
		sizeToRead -= RecvLen;


		delete[] buffer;


		if(sizeToRead > 0) Sleep(10);
	}
	

	/* Header ���� */
	cNetHeader* header = new cNetHeader(hBuffer);


	/* Body ������ �ޱ� */
	totalRecv = 0;
	BYTE* bBuffer = new BYTE[header->BodyLen];
	sizeToRead = (int)header->BodyLen;
	
	while (sizeToRead > 0)
	{
		BYTE* buffer = new BYTE[sizeToRead];
		int RecvLen = recv(Sock, (char*)buffer, sizeToRead, 0);

		if (RecvLen == 0)
		{
			delete[] bBuffer;
			delete[] hBuffer;
			delete[] buffer;
			return false;
		}
		else if(RecvLen < 0)
		{// ���������� ����
			int LastError = WSAGetLastError();
			
			delete[] bBuffer;
			delete[] hBuffer;
			delete[] buffer;
			return false;
		}

		Array::Copy(buffer, 0, bBuffer, totalRecv, sizeToRead);
		totalRecv += RecvLen;
		sizeToRead -= RecvLen;


		delete[] buffer;


		if(sizeToRead > 0) Sleep(10);
	}


	/* Body ���� */
	cNetBody* body = new cNetBody(bBuffer, header->BodyLen);


	/* �޼��� ���� */
	pGetMsg->Header = header;
	pGetMsg->Body = body;


	/* �޸� ���� */
	delete[] hBuffer;
	delete[] bBuffer;

	return true;
}

/*---------------------------------------------------------------------------------*/

bool NetMsgUtil::UdpSend(SOCKET Sock, const cNetMessage* pMsg, const SOCKADDR_IN* pAdr)
{
	pMsg->Header->SendTime = timeGetTime();
	pMsg->Header->BodyLen = pMsg->Body->GetSize();

	
	BYTE* Bytes = new BYTE[pMsg->GetSize()];
	pMsg->GetBytes(Bytes);

	int Result = sendto(Sock, (const char*)Bytes, pMsg->GetSize(), 0,
		(SOCKADDR*)pAdr, sizeof(SOCKADDR_IN));


	delete[] Bytes;


	return (Result >= 0);
}


bool NetMsgUtil::UdpReceive(SOCKET Sock, cNetMessage* pMsg, SOCKADDR_IN* pAdr)
{
	int AdrSz = sizeof(SOCKADDR_IN);

	int ReadByteNum = recvfrom(Sock, (char*)s_Buffer, 4096, 0,
		(SOCKADDR*)pAdr, &AdrSz);

	if(ReadByteNum < 0) // UDP�����϶��� recvfrom�� ��ȯ���� 0�̶���ؼ� ū �ǹ̰� �ִ°��� �ƴϴ�.
	{
		return false;
	}


	cNetHeader* pHeader = new cNetHeader(s_Buffer);


	BYTE* Buffer = s_Buffer + pHeader->GetSize();

	cNetBody* pBody = new cNetBody(Buffer, pHeader->BodyLen);


	/* �޼��� ���� */
	pMsg->Header = pHeader;
	pMsg->Body = pBody;


	return true;
}

///////////////////////////////////////////////////////////////////////////////////////

cNetHeader* NetMsgUtil::MakeHeader(UINT32 MsgType, UINT32 BodyLen, BOOL isFragmented, BOOL isLastMsg, UINT16 Seq)
{
	cNetHeader* pHeader = new cNetHeader;


	pHeader->SendTime = timeGetTime();
	pHeader->MsgType = MsgType;
	pHeader->BodyLen = BodyLen;
	pHeader->Fragmented = (isFragmented != FALSE) ? NetDefine::YES : NetDefine::NO;
	pHeader->LastMsg = (isLastMsg != FALSE) ? NetDefine::YES : NetDefine::NO;
	pHeader->Seq = Seq;


	return pHeader;
}


cNetMessage* NetMsgUtil::MakeMessage(UINT32 MsgType, BYTE BodyBytes[], UINT32 BodySize)
{
	cNetMessage* pMsg = new cNetMessage();


	pMsg->Header = MakeHeader(MsgType, BodySize, false, false, 0);
	pMsg->Body = new cNetBody(BodyBytes, BodySize);


	return pMsg;
}


cNetMessage* NetMsgUtil::MakeMessage(UINT32 MsgType, const cBinaryWriter* pBw)
{
	UINT ByteSize = pBw->ByteSize();


	cNetMessage* pMsg = new cNetMessage();


	pMsg->Header = MakeHeader(MsgType, ByteSize, false, false, 0);


	BYTE* Bytes = new BYTE[ByteSize];
	pBw->GetBytes((char*)Bytes);

	pMsg->Body = new cNetBody(Bytes, ByteSize);

	delete[] Bytes;


	return pMsg;
}

