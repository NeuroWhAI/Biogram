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
	ULONG SendTime;					// ���۽ð�
	UINT32 MsgType;					// �޼��� ����
	UINT32 BodyLen;					// Body ũ��(BYTE)
	BYTE Fragmented;				// ���ҿ���
	BYTE LastMsg;					// ����������
	UINT16 Seq;						// ���ҹ�ȣ


public:
	virtual void GetBytes(BYTE* Result) const;
	virtual UINT GetSize() const;
};

