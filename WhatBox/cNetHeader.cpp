#include "cNetHeader.h"

#include "cBinaryReader.h"
#include "cBinaryWriter.h"
#include "Array.h"

#include "NetDefine.h"
#include "NetMsgType.h"


























cNetHeader::cNetHeader()
	: SendTime(timeGetTime())
	, MsgType(0)
	, BodyLen(1)
	, Fragmented(NetDefine::YES)
	, LastMsg(NetDefine::YES)
	, Seq(0)
{

}


cNetHeader::cNetHeader(const cNetHeader* pHeader)
	: SendTime(pHeader->SendTime)
	, MsgType(pHeader->MsgType)
	, BodyLen(pHeader->BodyLen)
	, Fragmented(pHeader->Fragmented)
	, LastMsg(pHeader->LastMsg)
	, Seq(pHeader->Seq)
{

}


cNetHeader::cNetHeader(const cNetHeader& Header)
	: SendTime(Header.SendTime)
	, MsgType(Header.MsgType)
	, BodyLen(Header.BodyLen)
	, Fragmented(Header.Fragmented)
	, LastMsg(Header.LastMsg)
	, Seq(Header.Seq)
{

}


cNetHeader::cNetHeader(const BYTE* Bytes)
{
	cBinaryReader br((const char*)Bytes, 16);

	SendTime = br.Read<ULONG>();
	MsgType = br.Read<UINT32>();
	BodyLen = br.Read<UINT32>();
	Fragmented = br.Read<BYTE>();
	LastMsg = br.Read<BYTE>();
	Seq = br.Read<UINT16>();
}


cNetHeader::~cNetHeader()
{

}

//////////////////////////////////////////////////////////////////////////////////////

void cNetHeader::GetBytes(BYTE* Result) const
{
	cBinaryWriter bw(16);

	bw.Write(SendTime);
	bw.Write(MsgType);
	bw.Write(BodyLen);
	bw.Write(Fragmented);
	bw.Write(LastMsg);
	bw.Write(Seq);


	bw.GetBytes((char*)Result);
}


UINT cNetHeader::GetSize() const
{
	return 16U;
}

