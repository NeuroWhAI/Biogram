#include "cBinaryReader.h"

#include "cNetMessage.h"



























cBinaryReader::cBinaryReader()
	: m_Bytes(NULL)
	, m_ByteSize(0)

	, m_CurrPos(0)
{

}


cBinaryReader::cBinaryReader(const char Bytes[], int ByteSize)
	: m_Bytes(NULL)
	, m_ByteSize(0)

	, m_CurrPos(0)
{
	SetBytes(Bytes, ByteSize);
}


cBinaryReader::cBinaryReader(const BYTE Bytes[], UINT ByteSize)
	: m_Bytes(NULL)
	, m_ByteSize(0)

	, m_CurrPos(0)
{
	SetBytes(Bytes, ByteSize);
}


cBinaryReader::cBinaryReader(const cNetMessage* pMsg)
	: m_Bytes(new char[pMsg->Body->GetSize()])
	, m_ByteSize(pMsg->Body->GetSize())

	, m_CurrPos(0)
{
	pMsg->Body->GetBytes((BYTE*)m_Bytes);
}


cBinaryReader::~cBinaryReader()
{
	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryReader::SetBytes(const char Bytes[], int ByteSize)
{
	m_CurrPos = 0;
	m_ByteSize = static_cast<UINT>(ByteSize);


	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}


	m_Bytes = new char[ByteSize];

	for(int i=0; i<ByteSize; i++)
	{
		m_Bytes[i] = Bytes[i];
	}


	return 0;
}


int cBinaryReader::SetBytes(const BYTE Bytes[], UINT ByteSize)
{
	m_CurrPos = 0;
	m_ByteSize = ByteSize;


	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}


	m_Bytes = new char[ByteSize];

	for(UINT i=0; i<ByteSize; i++)
	{
		m_Bytes[i] = static_cast<char>(Bytes[i]);
	}


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryReader::ReadString(char pOut[])
{
	int StrLen = 0;

	memcpy(&StrLen, m_Bytes + m_CurrPos, sizeof(int));
	m_CurrPos += sizeof(int);

	memcpy(pOut, m_Bytes + m_CurrPos, StrLen);
	m_CurrPos += StrLen;


	return StrLen;
}


int cBinaryReader::ReadString(wchar_t pOut[])
{
	int StrLen = 0;

	memcpy(&StrLen, m_Bytes + m_CurrPos, sizeof(int));
	m_CurrPos += sizeof(int);

	memcpy(pOut, m_Bytes + m_CurrPos, StrLen);
	m_CurrPos += StrLen;


	return StrLen;
}


int cBinaryReader::ReadString(std::string* pOut)
{
	int StrLen = 0;

	memcpy(&StrLen, m_Bytes + m_CurrPos, sizeof(int));
	m_CurrPos += sizeof(int);

	for(int i=0; i<StrLen; i++)
	{
		char tempChar = '\0';

		memcpy(&tempChar, m_Bytes + m_CurrPos, sizeof(char));
		m_CurrPos += sizeof(char);

		pOut->push_back(tempChar);
	}


	return StrLen;
}


int cBinaryReader::ReadString(std::wstring* pOut)
{
	int StrLen = 0;

	memcpy(&StrLen, m_Bytes + m_CurrPos, sizeof(int));
	m_CurrPos += sizeof(int);

	StrLen /= 2;

	for(int i=0; i<StrLen; i++)
	{
		wchar_t tempChar = '\0';

		memcpy(&tempChar, m_Bytes + m_CurrPos, sizeof(wchar_t));
		m_CurrPos += sizeof(wchar_t);

		pOut->push_back(tempChar);
	}


	return StrLen;
}


int cBinaryReader::ReadBytes(char* pOut, int ReadSize)
{
	memcpy(pOut, m_Bytes + m_CurrPos, ReadSize);
	m_CurrPos += ReadSize;


	return 0;
}


int cBinaryReader::ReadBytes(BYTE* pOut, UINT ReadSize)
{
	memcpy(pOut, m_Bytes + m_CurrPos, ReadSize);
	m_CurrPos += ReadSize;


	return 0;
}


int cBinaryReader::FormatReceive(const char Format[], ...)
{// %d %ld %f %lf %s %c %lld
	va_list vlist;
	va_start(vlist, Format);


	int StrLen = strlen(Format);


	for(int i=0; i<StrLen; i++)
	{
		if(Format[i] == '%')
		{
			if(i + 1 >= StrLen) break;


			if(Format[i+1] == 'd')
			{// %d
				*va_arg(vlist, int*) = Read<int>();
			}
			else if(Format[i+1] == 'l')
			{
				if(i + 2 >= StrLen) break;


				if(Format[i+2] == 'd')
				{// %ld
					*va_arg(vlist, long*) = Read<long>();
				}
				else if(Format[i+2] == 'l')
				{// %lld
					*va_arg(vlist, long long*) = Read<long long>();
				}
				else if(Format[i+2] == 'f')
				{// %lf
					*va_arg(vlist, double*) = Read<double>();
				}
			}
			else if(Format[i+1] == 'f')
			{// %f
				*va_arg(vlist, float*) = Read<float>();
			}
			else if(Format[i+1] == 'c')
			{// %c
				*va_arg(vlist, char*) = Read<char>();
			}
			else if(Format[i+1] == 's')
			{// %s
				ReadString(va_arg(vlist, char*));
			}
		}
	}


	va_end(vlist);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryReader::GetPos() const
{
	return m_CurrPos;
}


int cBinaryReader::SetPos(int Pos)
{
	m_CurrPos = Pos;


	return 0;
}

