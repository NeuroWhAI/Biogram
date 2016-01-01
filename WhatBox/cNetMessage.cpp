#include "cNetMessage.h"

#include "Array.h"

























cNetMessage::cNetMessage()
	: Header(NULL)
	, Body(NULL)
{

}


cNetMessage::cNetMessage(const cNetMessage* pMsg)
	: Header(new cNetHeader(pMsg->Header))
	, Body(new cNetBody(pMsg->Body))
{

}


cNetMessage::cNetMessage(const cNetMessage& pMsg)
	: Header(new cNetHeader(pMsg.Header))
	, Body(new cNetBody(pMsg.Body))
{

}


cNetMessage::~cNetMessage()
{
	if(Header != NULL)
	{
		delete Header;
		Header = NULL;
	}


	if(Body != NULL)
	{
		delete Body;
		Body = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////

void cNetMessage::GetBytes(BYTE* Result) const
{
	BYTE* Temp = new BYTE[Header->GetSize()];
	Header->GetBytes(Temp);
	Array::Copy(Temp, 0, Result, 0, Header->GetSize());

	delete[] Temp;
	
	Temp = new BYTE[Body->GetSize()];
	Body->GetBytes(Temp);
	Array::Copy(Temp, 0, Result, Header->GetSize(), Body->GetSize());

	delete[] Temp;
}


UINT cNetMessage::GetSize() const
{
	return Header->GetSize() + Body->GetSize();
}

