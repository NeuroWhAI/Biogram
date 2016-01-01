#pragma once
#include <Windows.h>
#include <WinSock2.h>

#include "NetMsgType.h"


class cNetMessage;
class cNetHeader;
class cBinaryWriter;

























class NetMsgUtil
{
private:
	static BYTE s_Buffer[4096];


public:
	static bool Send(SOCKET Sock, BYTE Msg[], UINT MsgLength);
	static bool Send(SOCKET Sock, const cNetMessage* pMsg);
	static bool Receive(SOCKET Sock, cNetMessage* pGetMsg);

	static bool UdpSend(SOCKET Sock, const cNetMessage* pMsg, const SOCKADDR_IN* pAdr);
	static bool UdpReceive(SOCKET Sock, cNetMessage* pMsg, SOCKADDR_IN* pAdr);


public:
	static cNetHeader* MakeHeader(UINT32 MsgType, UINT32 BodyLen, BOOL isFragmented, BOOL isLastMsg, UINT16 Seq);
	static cNetMessage* MakeMessage(UINT32 MsgType, BYTE BodyBytes[], UINT32 BodySize);
	static cNetMessage* MakeMessage(UINT32 MsgType, const cBinaryWriter* pBw);
};

