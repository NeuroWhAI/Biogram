#pragma once
#include <Windows.h>
#include <string>



























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 이진 쓰기
// Desc : 바이너리 모드로 바이트배열을 씁니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cBinaryWriter
{
public:
	cBinaryWriter();
	cBinaryWriter(int ByteSize);
	cBinaryWriter(UINT ByteSize);

	~cBinaryWriter();


private:
	char* m_Bytes;
	UINT m_ByteSize;

	int m_CurrPosition;


public:
	template<typename T>
	int Write(T Val);

	template<>
	int Write<const char*> (const char* String)
	{
		int StrLen = strlen(String) + 1;

		ResizeBuffer(sizeof(int));
		memcpy(m_Bytes + m_CurrPosition, &StrLen, sizeof(int));
		m_CurrPosition += sizeof(int);

		ResizeBuffer(StrLen);
		memcpy(m_Bytes + m_CurrPosition, String, StrLen);
		m_CurrPosition += StrLen;


		return 0;
	}

	template<>
	int Write<char*> (char* String)
	{
		return Write<const char*>(String);
	}

	template<>
	int Write<std::string> (std::string String)
	{
		return Write<const char*>(String.c_str());
	}


	template<>
	int Write<const wchar_t*> (const wchar_t* String)
	{
		int StrLen = 0;

		while(String[StrLen++] != '\0'); // 카운터에 '\0'포함됨
		StrLen *= 2;

		
		ResizeBuffer(sizeof(int));
		memcpy(m_Bytes + m_CurrPosition, &StrLen, sizeof(int));
		m_CurrPosition += sizeof(int);
		
		ResizeBuffer(StrLen);
		memcpy(m_Bytes + m_CurrPosition, String, StrLen);
		m_CurrPosition += StrLen;


		return 0;
	}

	template<>
	int Write<wchar_t*> (wchar_t* String)
	{
		return Write<const wchar_t*>(String);
	}

	template<>
	int Write<std::wstring> (std::wstring String)
	{
		return Write<const wchar_t*>(String.c_str());
	}


	int WriteBytes(const char* Bytes, int ByteSize);
	int WriteBytes(const BYTE* Bytes, UINT ByteSize);


	int FormatWrite(const char Format[], ...);


public:
	int ResetBuffer(int ByteSize);


public:
	int GetBytes(char pOut[]) const;
	int GetBytes(BYTE pOut[]) const;
	UINT ByteSize() const;

	int GetPos() const;
	int SetPos(int Pos);


private:
	int ResizeBuffer(int NeedByteSize);
};


template<typename T>
int cBinaryWriter::Write(T Val)
{
	ResizeBuffer(sizeof(T));
	memcpy(m_Bytes + m_CurrPosition, &Val, sizeof(T));
	m_CurrPosition += sizeof(T);


	return 0;
}

