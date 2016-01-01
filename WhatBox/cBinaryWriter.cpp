#include "cBinaryWriter.h"

#include "Array.h"




























cBinaryWriter::cBinaryWriter()
	: m_Bytes(NULL)
	, m_ByteSize(0)

	, m_CurrPosition(0)
{

}


cBinaryWriter::cBinaryWriter(int ByteSize)
	: m_Bytes(new char[ByteSize])
	, m_ByteSize(static_cast<UINT>(ByteSize))

	, m_CurrPosition(0)
{
	
}


cBinaryWriter::cBinaryWriter(UINT ByteSize)
	: m_Bytes(new char[ByteSize])
	, m_ByteSize(ByteSize)

	, m_CurrPosition(0)
{
	
}


cBinaryWriter::~cBinaryWriter()
{
	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryWriter::WriteBytes(const char* Bytes, int ByteSize)
{
	ResizeBuffer(ByteSize);
	memcpy(m_Bytes + m_CurrPosition, Bytes, ByteSize);
	m_CurrPosition += ByteSize;


	return 0;
}


int cBinaryWriter::WriteBytes(const BYTE* Bytes, UINT ByteSize)
{
	ResizeBuffer(ByteSize);
	memcpy(m_Bytes + m_CurrPosition, Bytes, ByteSize);
	m_CurrPosition += ByteSize;


	return 0;
}


int cBinaryWriter::FormatWrite(const char Format[], ...)
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
				Write<int>(va_arg(vlist, int));
			}
			else if(Format[i+1] == 'l')
			{
				if(i + 2 >= StrLen) break;


				if(Format[i+2] == 'd')
				{// %ld
					Write<long>(va_arg(vlist, long));
				}
				else if(Format[i+2] == 'l')
				{// %lld
					Write<long long>(va_arg(vlist, long long));
				}
				else if(Format[i+2] == 'f')
				{// %lf
					Write<double>(va_arg(vlist, double));
				}
			}
			else if(Format[i+1] == 'f')
			{// %f
				Write<float>(va_arg(vlist, float));
			}
			else if(Format[i+1] == 'c')
			{// %c
				Write<char>(va_arg(vlist, char));
			}
			else if(Format[i+1] == 's')
			{// %s
				Write<char*>(va_arg(vlist, char*));
			}
		}
	}


	va_end(vlist);


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryWriter::ResetBuffer(int ByteSize)
{
	m_ByteSize = static_cast<UINT>(ByteSize);
	m_CurrPosition = 0;


	if(m_Bytes != NULL)
	{
		delete[] m_Bytes;
		m_Bytes = NULL;
	}


	m_Bytes = new char[ByteSize];


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryWriter::GetBytes(char pOut[]) const
{
	for(UINT i=0; i<m_ByteSize; i++)
	{
		pOut[i] = m_Bytes[i];
	}


	return 0;
}


int cBinaryWriter::GetBytes(BYTE pOut[]) const
{
	for(UINT i=0; i<m_ByteSize; i++)
	{
		pOut[i] = static_cast<BYTE>(m_Bytes[i]);
	}


	return 0;
}


UINT cBinaryWriter::ByteSize() const
{
	return m_ByteSize;
}



int cBinaryWriter::GetPos() const
{
	return m_CurrPosition;
}


int cBinaryWriter::SetPos(int Pos)
{
	m_CurrPosition = Pos;


	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cBinaryWriter::ResizeBuffer(int NeedByteSize)
{
	UINT NewSize = NeedByteSize + m_CurrPosition;

	if(NewSize > m_ByteSize)
	{// 확장 필요
		Array::Resize((BYTE**)&m_Bytes, m_ByteSize, NewSize);

		m_ByteSize = NewSize;
	}


	return 0;
}

