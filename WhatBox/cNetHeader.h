#pragma once
#include <Windows.h>
#include <WinSock2.h>

#include "cNetPacket.h"





















class cNetHeader : public cNetPacket
{
public:
	cNetHeader();
	cNetHeader(const cNetHeader* pHeader);
	cNetHeader(const cNetHeader& Header);
	cNetHeader(const BYTE* Bytes);

	~cNetHeader();
	

public:
	ULONG SendTime;					// 전송시간
	UINT32 MsgType;					// 메세지 종류
	UINT32 BodyLen;					// Body 크기(BYTE)
	BYTE Fragmented;				// 분할여부
	BYTE LastMsg;					// 마지막여부
	UINT16 Seq;						// 분할번호


public:
	virtual void GetBytes(BYTE* Result) const;
	virtual UINT GetSize() const;
};

