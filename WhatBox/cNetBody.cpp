#include "cNetBody.h"

#include "Array.h"
























cNetBody::cNetBody()
	: m_Bytes(NULL)
	, m_ByteSize(0)
{

}


cNetBody::cNetBody(const cNetBody* pBody)
	: m_Bytes(new BYTE[pBody->GetSize()])
	, m_ByteSize(pBody->GetSize())
{
	pBody->GetBytes(m_Bytes);
}


cNetBody::cNetBody(const cNetBody& Body)
	: m_Bytes(new BYTE[Body.GetSize()])
	, m_ByteSize(Body.GetSize())
{
	Body.GetBytes(m_Bytes);
}


cNetBody::cNetBody(BYTE* Bytes, UINT ByteSize)
	: m_Bytes(new BYTE[ByteSize])
	, m_ByteSize(ByteSize)
{
	Array::Copy(Bytes, 0, m_Bytes, 0, static_cast<int>(ByteSize));
}


cNetBody::~cNetBody()
{
	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////////////

void cNetBody::GetBytes(BYTE* pOut) const
{
	Array::Copy(m_Bytes, 0, pOut, 0, static_cast<int>(m_ByteSize));
}


UINT cNetBody::GetSize() const
{
	return m_ByteSize;
}

