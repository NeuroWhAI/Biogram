#pragma once
#include <Windows.h>
#include <WinSock2.h>

#include "cNetPacket.h"

#include "cNetHeader.h"
#include "cNetBody.h"





















class cNetMessage : public cNetPacket
{
public:
	cNetMessage();
	cNetMessage(const cNetMessage* pMsg);
	cNetMessage(const cNetMessage& Msg);

	~cNetMessage();


public:
	cNetHeader* Header;
	cNetBody* Body;


public:
	virtual void GetBytes(BYTE* Result) const;
	virtual UINT GetSize() const;
};

