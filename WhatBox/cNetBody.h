#pragma once
#include <Windows.h>
#include <WinSock2.h>

#include "cNetPacket.h"





















class cNetBody : public cNetPacket
{
public:
	cNetBody();
	cNetBody(const cNetBody* pBody);
	cNetBody(const cNetBody& Body);
	cNetBody(BYTE* Bytes, UINT ByteSize);

	~cNetBody();


private:
	BYTE* m_Bytes;
	UINT m_ByteSize;


public:
	virtual void GetBytes(BYTE* pOut) const;
	virtual UINT GetSize() const;
};

