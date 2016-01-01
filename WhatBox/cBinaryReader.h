#pragma once
#include <Windows.h>
#include <string>

class cNetMessage;
























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 이진 읽기
// Desc : 바이너리 모드로 바이트배열을 읽습니다
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cBinaryReader
{
public:
	cBinaryReader();
	cBinaryReader(const char Bytes[], int ByteSize);
	cBinaryReader(const BYTE Bytes[], UINT ByteSize);
	cBinaryReader(const cNetMessage* pMsg); // Body의 Bytes만 가져감

	~cBinaryReader();


private:
	char* m_Bytes;
	UINT m_ByteSize;

	int m_CurrPos;


public:
	int SetBytes(const char Bytes[], int ByteSize);
	int SetBytes(const BYTE Bytes[], UINT ByteSize);


public:
	template<typename T>
	T Read();

	int ReadString(char pOut[]);
	int ReadString(wchar_t pOut[]);

	int ReadString(std::string* pOut);
	int ReadString(std::wstring* pOut);


	int ReadBytes(char* pOut, int ReadSize);
	int ReadBytes(BYTE* pOut, UINT ReadSize);


	int FormatReceive(const char Format[], ...);


public:
	int GetPos() const;
	int SetPos(int Pos);
};


template<typename T>
T cBinaryReader::Read()
{
	T temp;
	memcpy(&temp, m_Bytes + m_CurrPos, sizeof(T));

	m_CurrPos += sizeof(T);


	return temp;
}

