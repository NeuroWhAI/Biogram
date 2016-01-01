#pragma once
#include <Windows.h>
#include <string>

class cNetMessage;
























///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ���� �б�
// Desc : ���̳ʸ� ���� ����Ʈ�迭�� �н��ϴ�
///////////////////////////////////////////////////////////////////////////////////////////////////////

class cBinaryReader
{
public:
	cBinaryReader();
	cBinaryReader(const char Bytes[], int ByteSize);
	cBinaryReader(const BYTE Bytes[], UINT ByteSize);
	cBinaryReader(const cNetMessage* pMsg); // Body�� Bytes�� ������

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

