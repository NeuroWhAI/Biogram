#pragma once
#include <Windows.h>
#include <WinSock2.h>






















class cNetPacket
{
public:
	virtual ~cNetPacket() {}


public:
	virtual void GetBytes(BYTE* Result) const = 0;
	virtual UINT GetSize() const = 0;
};

